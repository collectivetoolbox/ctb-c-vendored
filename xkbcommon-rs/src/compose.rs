// SPDX-License-Identifier for parts derived from libxkbcommon: X11
use std::collections::{BTreeMap, BTreeSet};
use std::env;
use std::fs;
use std::path::{Path, PathBuf};

use log::warn;
use xkeysym::Keysym;

/// Result of feeding a keysym into the compose state machine.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ComposeFeedResult {
    Ignored,
    Accepted,
}

/// Current state of the compose state machine.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ComposeStatus {
    Nothing,
    Composing,
    Composed,
    Cancelled,
}

#[derive(Clone, Debug, Default)]
pub struct ComposeTable {
    _locale: Option<String>,
    entries: BTreeMap<Vec<Keysym>, String>,
}

impl ComposeTable {
    pub fn new_from_locale(locale: Option<&str>) -> Option<Self> {
        let requested_locale = locale
            .map(ToOwned::to_owned)
            .or_else(|| compose_locale_from_env());
        let entries = load_compose_entries(requested_locale.as_deref()).unwrap_or_else(|error| {
            warn!("failed to load Compose table: {error}");
            BTreeMap::new()
        });

        Some(Self { _locale: requested_locale, entries })
    }

    pub fn new_state(&self) -> ComposeState {
        ComposeState { table: self.entries.clone(), ..ComposeState::default() }
    }
}

#[derive(Clone, Debug, Default)]
pub struct ComposeState {
    table: BTreeMap<Vec<Keysym>, String>,
    sequence: Vec<Keysym>,
    state: ComposeInner,
}

#[derive(Clone, Debug, Default)]
enum ComposeInner {
    #[default]
    Nothing,
    MultiKey,
    Dead(Vec<DeadAccent>),
    TableComposing,
    Composed(String),
    Cancelled,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
struct DeadAccent {
    keysym: Keysym,
    combining: char,
    spacing: Option<char>,
}

impl ComposeState {
    /// The transition behavior intentionally follows libxkbcommon's compose
    /// state machine shape from `src/compose/state.c`, but this Rust backend
    /// currently implements algorithmic dead-key composition instead of
    /// loading locale-specific Compose tables.
    pub fn feed(&mut self, keysym: Keysym) -> ComposeFeedResult {
        if keysym.is_modifier_key() {
            return ComposeFeedResult::Ignored;
        }

        if matches!(self.state, ComposeInner::Composed(_) | ComposeInner::Cancelled) {
            self.reset();
        }

        if !self.table.is_empty() {
            return self.feed_table(keysym);
        }

        match &mut self.state {
            ComposeInner::Nothing => {
                if keysym == Keysym::Multi_key {
                    self.state = ComposeInner::MultiKey;
                } else if let Some(accent) = dead_accent_from_keysym(keysym) {
                    self.state = ComposeInner::Dead(vec![accent]);
                }
            },
            ComposeInner::MultiKey => {
                if let Some(accent) = dead_accent_from_keysym(keysym)
                    .or_else(|| dead_accent_from_prefix(keysym))
                {
                    self.state = ComposeInner::Dead(vec![accent]);
                } else {
                    self.state = ComposeInner::Cancelled;
                }
            },
            ComposeInner::Dead(accents) => {
                if let Some(accent) = dead_accent_from_keysym(keysym)
                    .or_else(|| dead_accent_from_prefix(keysym))
                {
                    if accents.len() == 1 && accents[0] == accent {
                        self.state = ComposeInner::Composed(
                            accent.spacing.unwrap_or(accent.combining).to_string(),
                        );
                    } else {
                        accents.push(accent);
                    }
                } else if let Some(base) = keysym.key_char() {
                    if accents.len() == 1 && base == ' ' {
                        let accent = accents[0];
                        self.state = ComposeInner::Composed(
                            accent.spacing.unwrap_or(accent.combining).to_string(),
                        );
                    } else {
                        self.state = ComposeInner::Composed(compose_text(base, accents));
                    }
                } else {
                    self.state = ComposeInner::Cancelled;
                }
            },
            ComposeInner::Composed(_) | ComposeInner::Cancelled => {
                self.reset();
                return self.feed(keysym);
            },
            ComposeInner::TableComposing => {
                self.state = ComposeInner::Cancelled;
            },
        }

        ComposeFeedResult::Accepted
    }

    pub fn reset(&mut self) {
        self.sequence.clear();
        self.state = ComposeInner::Nothing;
    }

    pub fn status(&self) -> ComposeStatus {
        match &self.state {
            ComposeInner::Nothing => ComposeStatus::Nothing,
            ComposeInner::MultiKey | ComposeInner::Dead(_) | ComposeInner::TableComposing => {
                ComposeStatus::Composing
            }
            ComposeInner::Composed(_) => ComposeStatus::Composed,
            ComposeInner::Cancelled => ComposeStatus::Cancelled,
        }
    }

    pub fn get_utf8(&self) -> Option<Vec<u8>> {
        let ComposeInner::Composed(text) = &self.state else {
            return None;
        };
        Some(text.as_bytes().to_vec())
    }

    fn feed_table(&mut self, keysym: Keysym) -> ComposeFeedResult {
        self.sequence.push(keysym);

        if let Some(text) = self.table.get(&self.sequence) {
            self.state = ComposeInner::Composed(text.clone());
            return ComposeFeedResult::Accepted;
        }

        let has_prefix = self
            .table
            .keys()
            .any(|sequence| sequence.starts_with(&self.sequence));

        if has_prefix {
            self.state = ComposeInner::TableComposing;
            return ComposeFeedResult::Accepted;
        }

        self.sequence.pop();

        if self.sequence.is_empty() {
            self.feed_algorithmic(keysym)
        } else {
            self.state = ComposeInner::Cancelled;
            ComposeFeedResult::Accepted
        }
    }

    fn feed_algorithmic(&mut self, keysym: Keysym) -> ComposeFeedResult {
        match &mut self.state {
            ComposeInner::Nothing => {
                if keysym == Keysym::Multi_key {
                    self.state = ComposeInner::MultiKey;
                } else if let Some(accent) = dead_accent_from_keysym(keysym) {
                    self.state = ComposeInner::Dead(vec![accent]);
                }
            },
            ComposeInner::MultiKey => {
                if let Some(accent) = dead_accent_from_keysym(keysym)
                    .or_else(|| dead_accent_from_prefix(keysym))
                {
                    self.state = ComposeInner::Dead(vec![accent]);
                } else {
                    self.state = ComposeInner::Cancelled;
                }
            },
            ComposeInner::Dead(accents) => {
                if let Some(accent) = dead_accent_from_keysym(keysym)
                    .or_else(|| dead_accent_from_prefix(keysym))
                {
                    if accents.len() == 1 && accents[0] == accent {
                        self.state = ComposeInner::Composed(
                            accent.spacing.unwrap_or(accent.combining).to_string(),
                        );
                    } else {
                        accents.push(accent);
                    }
                } else if let Some(base) = keysym.key_char() {
                    if accents.len() == 1 && base == ' ' {
                        let accent = accents[0];
                        self.state = ComposeInner::Composed(
                            accent.spacing.unwrap_or(accent.combining).to_string(),
                        );
                    } else {
                        self.state = ComposeInner::Composed(compose_text(base, accents));
                    }
                } else {
                    self.state = ComposeInner::Cancelled;
                }
            },
            ComposeInner::Composed(_) | ComposeInner::Cancelled => {
                self.reset();
                return self.feed(keysym);
            },
            ComposeInner::TableComposing => {
                self.state = ComposeInner::Cancelled;
            },
        }

        ComposeFeedResult::Accepted
    }
}

fn compose_text(base: char, accents: &[DeadAccent]) -> String {
    let mut text = String::new();
    text.push(base);
    for accent in accents {
        text.push(accent.combining);
    }
    text
}

fn dead_accent_from_prefix(keysym: Keysym) -> Option<DeadAccent> {
    let ch = keysym.key_char()?;
    match ch {
        '\'' => dead_accent_from_keysym(Keysym::dead_acute),
        '`' => dead_accent_from_keysym(Keysym::dead_grave),
        '^' => dead_accent_from_keysym(Keysym::dead_circumflex),
        '~' => dead_accent_from_keysym(Keysym::dead_tilde),
        '"' => dead_accent_from_keysym(Keysym::dead_diaeresis),
        '-' => dead_accent_from_keysym(Keysym::dead_macron),
        ',' => dead_accent_from_keysym(Keysym::dead_cedilla),
        '.' => dead_accent_from_keysym(Keysym::dead_belowdot),
        'o' | 'O' => dead_accent_from_keysym(Keysym::dead_abovering),
        'u' | 'U' => dead_accent_from_keysym(Keysym::dead_breve),
        'v' | 'V' => dead_accent_from_keysym(Keysym::dead_caron),
        ';' => dead_accent_from_keysym(Keysym::dead_ogonek),
        '/' => dead_accent_from_keysym(Keysym::dead_stroke),
        _ => None,
    }
}

fn dead_accent_from_keysym(keysym: Keysym) -> Option<DeadAccent> {
    let accent = match keysym {
        Keysym::dead_grave => DeadAccent { keysym, combining: '\u{0300}', spacing: Some('`') },
        Keysym::dead_acute => DeadAccent { keysym, combining: '\u{0301}', spacing: Some('\u{00B4}') },
        Keysym::dead_circumflex => DeadAccent { keysym, combining: '\u{0302}', spacing: Some('^') },
        Keysym::dead_tilde => DeadAccent { keysym, combining: '\u{0303}', spacing: Some('~') },
        Keysym::dead_macron => DeadAccent { keysym, combining: '\u{0304}', spacing: Some('\u{00AF}') },
        Keysym::dead_breve => DeadAccent { keysym, combining: '\u{0306}', spacing: Some('\u{02D8}') },
        Keysym::dead_abovedot => DeadAccent { keysym, combining: '\u{0307}', spacing: Some('\u{02D9}') },
        Keysym::dead_diaeresis => DeadAccent { keysym, combining: '\u{0308}', spacing: Some('\u{00A8}') },
        Keysym::dead_abovering => DeadAccent { keysym, combining: '\u{030A}', spacing: Some('\u{02DA}') },
        Keysym::dead_doubleacute => DeadAccent { keysym, combining: '\u{030B}', spacing: Some('\u{02DD}') },
        Keysym::dead_caron => DeadAccent { keysym, combining: '\u{030C}', spacing: Some('\u{02C7}') },
        Keysym::dead_cedilla => DeadAccent { keysym, combining: '\u{0327}', spacing: Some('\u{00B8}') },
        Keysym::dead_ogonek => DeadAccent { keysym, combining: '\u{0328}', spacing: Some('\u{02DB}') },
        Keysym::dead_belowdot => DeadAccent { keysym, combining: '\u{0323}', spacing: None },
        Keysym::dead_hook => DeadAccent { keysym, combining: '\u{0309}', spacing: None },
        Keysym::dead_horn => DeadAccent { keysym, combining: '\u{031B}', spacing: None },
        Keysym::dead_stroke => DeadAccent { keysym, combining: '\u{0335}', spacing: None },
        _ => return None,
    };
    Some(accent)
}

fn compose_locale_from_env() -> Option<String> {
    ["LC_ALL", "LC_CTYPE", "LANG"]
        .into_iter()
        .find_map(|key| env::var_os(key))
        .and_then(|value| {
            let value = value.to_string_lossy().trim().to_string();
            if value.is_empty() { None } else { Some(value) }
        })
}

fn load_compose_entries(locale: Option<&str>) -> Result<BTreeMap<Vec<Keysym>, String>, String> {
    let locale_root = locale_root().ok_or_else(|| "XLOCALEDIR is not set".to_string())?;

    if let Some(path) = env::var_os("XCOMPOSEFILE") {
        let path = PathBuf::from(path);
        if path.is_file() {
            let mut visited = BTreeSet::new();
            return parse_compose_file(&path, &locale_root, &mut visited);
        }
    }

    let requested = locale.unwrap_or("C");
    let alias_map = parse_locale_aliases(&locale_root.join("locale.alias"))?;
    let compose_map = parse_locale_index(&locale_root.join("compose.dir"))?;
    let resolved = resolve_locale(requested, &alias_map, &compose_map)
        .ok_or_else(|| format!("no compose mapping for locale {requested}"))?;
    let compose_path = locale_root.join(resolved);
    let mut visited = BTreeSet::new();
    parse_compose_file(&compose_path, &locale_root, &mut visited)
}

fn locale_root() -> Option<PathBuf> {
    env::var_os("XLOCALEDIR").map(PathBuf::from).filter(|path| path.is_dir())
}

fn parse_locale_aliases(path: &Path) -> Result<BTreeMap<String, String>, String> {
    let contents = fs::read_to_string(path)
        .map_err(|error| format!("read {}: {error}", path.display()))?;
    let mut aliases = BTreeMap::new();
    for line in contents.lines() {
        let line = line.trim();
        if line.is_empty() || line.starts_with("XCOMM") {
            continue;
        }
        let Some((alias, target)) = split_mapping(line) else {
            continue;
        };
        aliases.insert(alias.to_string(), target.to_string());
    }
    Ok(aliases)
}

fn parse_locale_index(path: &Path) -> Result<BTreeMap<String, String>, String> {
    let contents = fs::read_to_string(path)
        .map_err(|error| format!("read {}: {error}", path.display()))?;
    let mut mappings = BTreeMap::new();
    for line in contents.lines() {
        let line = line.trim();
        if line.is_empty() || line.starts_with("XCOMM") {
            continue;
        }
        let Some((file_name, locale)) = split_mapping(line) else {
            continue;
        };
        mappings.insert(locale.to_string(), file_name.to_string());
    }
    Ok(mappings)
}

fn split_mapping(line: &str) -> Option<(&str, &str)> {
    let mut parts = line.splitn(2, ':');
    let left = parts.next()?.trim();
    let right = parts.next()?.trim();
    if left.is_empty() || right.is_empty() {
        return None;
    }
    Some((left, right))
}

fn resolve_locale(
    requested: &str,
    aliases: &BTreeMap<String, String>,
    mappings: &BTreeMap<String, String>,
) -> Option<String> {
    let mut candidates = Vec::new();
    candidates.push(requested.to_string());

    if let Some(alias) = aliases.get(requested) {
        candidates.push(alias.clone());
    }

    if let Some(stripped) = requested.split('@').next() {
        if stripped != requested {
            candidates.push(stripped.to_string());
        }
    }

    if let Some(stripped) = requested.split('.').next() {
        if stripped != requested {
            candidates.push(stripped.to_string());
        }
    }

    if let Some((lang, _)) = requested.split_once('_') {
        candidates.push(lang.to_string());
    }

    candidates.push("C".to_string());

    for candidate in candidates {
        if let Some(path) = mappings.get(&candidate) {
            return Some(path.clone());
        }
        if let Some(alias) = aliases.get(&candidate) {
            if let Some(path) = mappings.get(alias) {
                return Some(path.clone());
            }
        }
    }

    None
}

fn parse_compose_file(
    path: &Path,
    locale_root: &Path,
    visited: &mut BTreeSet<PathBuf>,
) -> Result<BTreeMap<Vec<Keysym>, String>, String> {
    let canonical = path.to_path_buf();
    if !visited.insert(canonical.clone()) {
        return Ok(BTreeMap::new());
    }

    let contents = fs::read_to_string(&canonical)
        .map_err(|error| format!("read {}: {error}", canonical.display()))?;
    let mut entries = BTreeMap::new();

    for raw_line in contents.lines() {
        let line = raw_line.trim();
        if line.is_empty() || line.starts_with("XCOMM") || line.starts_with('#') {
            continue;
        }

        if let Some(include_path) = parse_include(line) {
            let include_path = resolve_include_path(&canonical, locale_root, &include_path);
            let included = parse_compose_file(&include_path, locale_root, visited)?;
            for (sequence, text) in included {
                entries.insert(sequence, text);
            }
            continue;
        }

        if let Some((sequence, text)) = parse_compose_entry(line) {
            entries.insert(sequence, text);
        }
    }

    Ok(entries)
}

fn parse_include(line: &str) -> Option<String> {
    let line = line.strip_prefix("include")?.trim();
    let line = line.strip_prefix('"')?;
    let end = line.find('"')?;
    Some(line[..end].to_string())
}

fn resolve_include_path(current_file: &Path, locale_root: &Path, include_path: &str) -> PathBuf {
    if let Some(stripped) = include_path.strip_prefix("X11_LOCALEDATADIR/") {
        return locale_root.join(stripped);
    }

    let include = Path::new(include_path);
    if include.is_absolute() {
        include.to_path_buf()
    } else {
        current_file.parent().unwrap_or(locale_root).join(include)
    }
}

fn parse_compose_entry(line: &str) -> Option<(Vec<Keysym>, String)> {
    let commentless = line.split('#').next()?.trim();
    let (lhs, rhs) = commentless.split_once(':')?;
    let sequence = parse_sequence(lhs.trim())?;
    let text = parse_compose_string(rhs.trim())?;
    Some((sequence, text))
}

fn parse_sequence(input: &str) -> Option<Vec<Keysym>> {
    let mut sequence = Vec::new();
    let mut rest = input.trim();
    while let Some(start) = rest.find('<') {
        let rest_after = &rest[start + 1..];
        let end = rest_after.find('>')?;
        let token = &rest_after[..end];
        let keysym = crate::keysym::keysym_from_name(token, 0)?;
        sequence.push(keysym);
        rest = &rest_after[end + 1..];
    }
    if sequence.is_empty() { None } else { Some(sequence) }
}

fn parse_compose_string(input: &str) -> Option<String> {
    let input = input.strip_prefix('"')?;
    let mut out = String::new();
    let mut chars = input.chars().peekable();
    while let Some(ch) = chars.next() {
        match ch {
            '"' => return Some(out),
            '\\' => {
                let escaped = chars.next()?;
                match escaped {
                    '\\' => out.push('\\'),
                    '"' => out.push('"'),
                    'n' => out.push('\n'),
                    'r' => out.push('\r'),
                    't' => out.push('\t'),
                    '0'..='7' => {
                        let mut octal = String::new();
                        octal.push(escaped);
                        for _ in 0..2 {
                            let Some(next) = chars.peek().copied() else {
                                break;
                            };
                            if !matches!(next, '0'..='7') {
                                break;
                            }
                            octal.push(chars.next().unwrap());
                        }
                        let byte = u8::from_str_radix(&octal, 8).ok()?;
                        out.push(char::from(byte));
                    }
                    other => out.push(other),
                }
            }
            other => out.push(other),
        }
    }
    None
}

/*

Based on libxkbcommon, which has the following license notices.
-----------------



The following is a list of all copyright notices and license statements which
appear in the xkbcommon source tree.

If making new contributions, the first form (i.e. Daniel Stone, Ran Benita,
etc) is vastly preferred.

All licenses are derivative of the MIT/X11 license, mostly identical other
than no-endorsement clauses (e.g. paragraph 4 of The Open Group's license).

These statements are split into two sections: one for the code compiled and
distributed as part of the libxkbcommon shared library and the code
component of all tests (i.e. everything under src/ and xkbcommon/, plus the
.c and .h files under test/), and another for the test data under test/data,
which is distributed with the xkbcommon source tarball, but not installed to
the system.


BEGINNING OF SOFTWARE COPYRIGHT/LICENSE STATEMENTS:


-------------------------------------------------------------------------------

Copyright © 2009-2012, 2016 Daniel Stone
Copyright © 2012 Ran Benita <ran234@gmail.com>
Copyright © 2010, 2012 Intel Corporation
Copyright © 2008, 2009 Dan Nicholson
Copyright © 2010 Francisco Jerez <currojerez@riseup.net>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.


-------------------------------------------------------------------------------


Copyright 1985, 1987, 1988, 1990, 1998  The Open Group

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the names of the authors or their
institutions shall not be used in advertising or otherwise to promote the
sale, use or other dealings in this Software without prior written
authorization from the authors.


-------------------------------------------------------------------------------


Copyright (c) 1993, 1994, 1995, 1996 by Silicon Graphics Computer Systems, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of Silicon Graphics not be
used in advertising or publicity pertaining to distribution
of the software without specific prior written permission.
Silicon Graphics makes no representation about the suitability
of this software for any purpose. It is provided "as is"
without any express or implied warranty.

SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.


-------------------------------------------------------------------------------


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.


-------------------------------------------------------------------------------


Copyright (C) 2011 Joseph Adams <joeyadams3.14159@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


-------------------------------------------------------------------------------



END OF SOFTWARE COPYRIGHT/LICENSE STATEMENTS


BEGINNING OF LICENSE STATEMENTS FOR UNDISTRIBUTED DATA FILES IN test/data,
derived from xkeyboard-config:



-------------------------------------------------------------------------------

Copyright 1996 by Joseph Moss
Copyright (C) 2002-2007 Free Software Foundation, Inc.
Copyright (C) Dmitry Golubev <lastguru@mail.ru>, 2003-2004
Copyright (C) 2004, Gregory Mokhin <mokhin@bog.msu.ru>
Copyright (C) 2006 Erdal Ronahî

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of the copyright holder(s) not be used in
advertising or publicity pertaining to distribution of the software without
specific, written prior permission.  The copyright holder(s) makes no
representations about the suitability of this software for any purpose.  It
is provided "as is" without express or implied warranty.

THE COPYRIGHT HOLDER(S) DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.


-------------------------------------------------------------------------------

              Copyright 1992 by Oki Technosystems Laboratory, Inc.
              Copyright 1992 by Fuji Xerox Co., Ltd.

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation, and that the name of Oki Technosystems
Laboratory and Fuji Xerox not be used in advertising or publicity
pertaining to distribution of the software without specific, written
prior permission.
Oki Technosystems Laboratory and Fuji Xerox make no representations
about the suitability of this software for any purpose.  It is provided
"as is" without express or implied warranty.

OKI TECHNOSYSTEMS LABORATORY AND FUJI XEROX DISCLAIM ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL OKI TECHNOSYSTEMS
LABORATORY AND FUJI XEROX BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
OR PERFORMANCE OF THIS SOFTWARE.

*/