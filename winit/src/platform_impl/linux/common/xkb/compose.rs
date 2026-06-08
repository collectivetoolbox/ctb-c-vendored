//! XKB compose handling.

use std::env;
use std::ffi::CString;
use std::ops::Deref;
use std::os::unix::ffi::OsStringExt;
use std::ptr::NonNull;

#[cfg(wayland_platform)]
use xkbcommon_rs as rxkb;

use super::{XkbContext, XKBCH};
use smol_str::SmolStr;
use xkbcommon_dl::{
    xkb_compose_compile_flags, xkb_compose_feed_result, xkb_compose_state, xkb_compose_state_flags,
    xkb_compose_table, xkb_keysym_t,
};

#[derive(Debug)]
pub struct XkbComposeTable {
    backend: ComposeTableBackend,
}

#[derive(Debug)]
enum ComposeTableBackend {
    System(NonNull<xkb_compose_table>),
    #[cfg(wayland_platform)]
    Rust(rxkb::xkb_compose::ComposeTable),
}

impl XkbComposeTable {
    pub fn new(context: &XkbContext) -> Option<Self> {
        #[cfg(wayland_platform)]
        if context.is_rust_backend() {
            return rxkb::xkb_compose::ComposeTable::new_from_locale(None)
                .map(|table| Self { backend: ComposeTableBackend::Rust(table) });
        }

        let locale = env::var_os("LC_ALL")
            .and_then(|v| if v.is_empty() { None } else { Some(v) })
            .or_else(|| env::var_os("LC_CTYPE"))
            .and_then(|v| if v.is_empty() { None } else { Some(v) })
            .or_else(|| env::var_os("LANG"))
            .and_then(|v| if v.is_empty() { None } else { Some(v) })
            .unwrap_or_else(|| "C".into());
        let locale = CString::new(locale.into_vec()).unwrap();

        let table = unsafe {
            (XKBCH.xkb_compose_table_new_from_locale)(
                context.as_ptr(),
                locale.as_ptr(),
                xkb_compose_compile_flags::XKB_COMPOSE_COMPILE_NO_FLAGS,
            )
        };

        let table = NonNull::new(table)?;
        Some(Self { backend: ComposeTableBackend::System(table) })
    }

    /// Create new state with the given compose table.
    pub fn new_state(&self) -> Option<XkbComposeState> {
        match &self.backend {
            ComposeTableBackend::System(table) => {
                let state = unsafe {
                    (XKBCH.xkb_compose_state_new)(
                        table.as_ptr(),
                        xkb_compose_state_flags::XKB_COMPOSE_STATE_NO_FLAGS,
                    )
                };

                let state = NonNull::new(state)?;
                Some(XkbComposeState { backend: ComposeStateBackend::System(state) })
            },
            #[cfg(wayland_platform)]
            ComposeTableBackend::Rust(table) => Some(XkbComposeState {
                backend: ComposeStateBackend::Rust(table.new_state()),
            }),
        }
    }
}

impl Deref for XkbComposeTable {
    type Target = NonNull<xkb_compose_table>;

    fn deref(&self) -> &Self::Target {
        match &self.backend {
            ComposeTableBackend::System(table) => table,
            #[cfg(wayland_platform)]
            ComposeTableBackend::Rust(_) => panic!("system compose table unavailable on rust backend"),
        }
    }
}

impl Drop for XkbComposeTable {
    fn drop(&mut self) {
        if let ComposeTableBackend::System(table) = self.backend {
            unsafe {
                (XKBCH.xkb_compose_table_unref)(table.as_ptr());
            }
        }
    }
}

#[derive(Debug)]
pub struct XkbComposeState {
    backend: ComposeStateBackend,
}

#[derive(Debug)]
enum ComposeStateBackend {
    System(NonNull<xkb_compose_state>),
    #[cfg(wayland_platform)]
    Rust(rxkb::xkb_compose::ComposeState),
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum ComposeStatusValue {
    Nothing,
    Composing,
    Composed,
    Cancelled,
}

impl XkbComposeState {
    pub fn get_string(&mut self, scratch_buffer: &mut Vec<u8>) -> Option<SmolStr> {
        match &mut self.backend {
            ComposeStateBackend::System(state) => super::make_string_with(scratch_buffer, |ptr, len| unsafe {
                (XKBCH.xkb_compose_state_get_utf8)(state.as_ptr(), ptr, len)
            }),
            #[cfg(wayland_platform)]
            ComposeStateBackend::Rust(state) => state
                .get_utf8()
                .and_then(|utf8| super::byte_slice_to_smol_str(&utf8)),
        }
    }

    #[inline]
    pub fn feed(&mut self, keysym: xkb_keysym_t) -> ComposeStatus {
        match &mut self.backend {
            ComposeStateBackend::System(state) => {
                let feed_result = unsafe { (XKBCH.xkb_compose_state_feed)(state.as_ptr(), keysym) };
                match feed_result {
                    xkb_compose_feed_result::XKB_COMPOSE_FEED_IGNORED => ComposeStatus::Ignored,
                    xkb_compose_feed_result::XKB_COMPOSE_FEED_ACCEPTED => {
                        ComposeStatus::Accepted(self.status())
                    },
                }
            },
            #[cfg(wayland_platform)]
            ComposeStateBackend::Rust(state) => match state.feed(rxkb::keysym::Keysym::from(keysym)) {
                rxkb::xkb_compose::ComposeFeedResult::Ignored => ComposeStatus::Ignored,
                rxkb::xkb_compose::ComposeFeedResult::Accepted => {
                    ComposeStatus::Accepted(self.status())
                },
            },
        }
    }

    #[inline]
    pub fn reset(&mut self) {
        match &mut self.backend {
            ComposeStateBackend::System(state) => unsafe {
                (XKBCH.xkb_compose_state_reset)(state.as_ptr());
            },
            #[cfg(wayland_platform)]
            ComposeStateBackend::Rust(state) => state.reset(),
        }
    }

    #[inline]
    pub fn status(&mut self) -> ComposeStatusValue {
        match &mut self.backend {
            ComposeStateBackend::System(state) => match unsafe {
                (XKBCH.xkb_compose_state_get_status)(state.as_ptr())
            } {
                xkbcommon_dl::xkb_compose_status::XKB_COMPOSE_NOTHING => ComposeStatusValue::Nothing,
                xkbcommon_dl::xkb_compose_status::XKB_COMPOSE_COMPOSING => ComposeStatusValue::Composing,
                xkbcommon_dl::xkb_compose_status::XKB_COMPOSE_COMPOSED => ComposeStatusValue::Composed,
                xkbcommon_dl::xkb_compose_status::XKB_COMPOSE_CANCELLED => ComposeStatusValue::Cancelled,
            },
            #[cfg(wayland_platform)]
            ComposeStateBackend::Rust(state) => match state.status() {
                rxkb::xkb_compose::ComposeStatus::Nothing => ComposeStatusValue::Nothing,
                rxkb::xkb_compose::ComposeStatus::Composing => ComposeStatusValue::Composing,
                rxkb::xkb_compose::ComposeStatus::Composed => ComposeStatusValue::Composed,
                rxkb::xkb_compose::ComposeStatus::Cancelled => ComposeStatusValue::Cancelled,
            },
        }
    }
}

impl Drop for XkbComposeState {
    fn drop(&mut self) {
        if let ComposeStateBackend::System(state) = self.backend {
            unsafe {
                (XKBCH.xkb_compose_state_unref)(state.as_ptr());
            };
        }
    }
}

#[derive(Copy, Clone, Debug)]
pub enum ComposeStatus {
    Accepted(ComposeStatusValue),
    Ignored,
    None,
}
