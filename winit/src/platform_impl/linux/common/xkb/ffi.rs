#![allow(dead_code, non_camel_case_types)]

use bitflags::bitflags;
use std::os::raw::{c_char, c_int, c_uint};

pub const XKB_MOD_NAME_SHIFT: &[u8] = b"Shift\0";
pub const XKB_MOD_NAME_CAPS: &[u8] = b"Lock\0";
pub const XKB_MOD_NAME_CTRL: &[u8] = b"Control\0";
pub const XKB_MOD_NAME_ALT: &[u8] = b"Mod1\0";
pub const XKB_MOD_NAME_NUM: &[u8] = b"Mod2\0";
pub const XKB_MOD_NAME_LOGO: &[u8] = b"Mod4\0";

pub const XKB_MOD_INVALID: u32 = 0xffffffff;

pub type xkb_keycode_t = u32;
pub type xkb_keysym_t = u32;
pub type xkb_layout_index_t = u32;
pub type xkb_layout_mask_t = u32;
pub type xkb_mod_index_t = u32;
pub type xkb_mod_mask_t = u32;

#[repr(C)]
pub struct xkb_context {
    _private: [u8; 0],
}

#[repr(C)]
pub struct xkb_keymap {
    _private: [u8; 0],
}

#[repr(C)]
pub struct xkb_state {
    _private: [u8; 0],
}

#[repr(C)]
pub struct xkb_compose_table {
    _private: [u8; 0],
}

#[repr(C)]
pub struct xkb_compose_state {
    _private: [u8; 0],
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_context_flags {
    XKB_CONTEXT_NO_FLAGS = 0,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_keymap_compile_flags {
    XKB_KEYMAP_COMPILE_NO_FLAGS = 0,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_keymap_format {
    XKB_KEYMAP_FORMAT_TEXT_V1 = 1,
}

bitflags! {
    pub struct xkb_state_component: u32 {
        const XKB_STATE_MODS_DEPRESSED = 1 << 0;
        const XKB_STATE_MODS_LATCHED = 1 << 1;
        const XKB_STATE_MODS_LOCKED = 1 << 2;
        const XKB_STATE_MODS_EFFECTIVE = 1 << 3;
        const XKB_STATE_LAYOUT_DEPRESSED = 1 << 4;
        const XKB_STATE_LAYOUT_LATCHED = 1 << 5;
        const XKB_STATE_LAYOUT_LOCKED = 1 << 6;
        const XKB_STATE_LAYOUT_EFFECTIVE = 1 << 7;
        const XKB_STATE_LEDS = 1 << 8;
    }
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_compose_compile_flags {
    XKB_COMPOSE_COMPILE_NO_FLAGS = 0,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_compose_state_flags {
    XKB_COMPOSE_STATE_NO_FLAGS = 0,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_compose_status {
    XKB_COMPOSE_NOTHING = 0,
    XKB_COMPOSE_COMPOSING = 1,
    XKB_COMPOSE_COMPOSED = 2,
    XKB_COMPOSE_CANCELLED = 3,
}

#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_compose_feed_result {
    XKB_COMPOSE_FEED_IGNORED = 0,
    XKB_COMPOSE_FEED_ACCEPTED = 1,
}

#[link(name = "xkbcommon")]
extern "C" {
    pub fn xkb_keysym_to_utf8(keysym: xkb_keysym_t, buffer: *mut c_char, size: usize) -> c_int;

    pub fn xkb_context_new(flags: xkb_context_flags) -> *mut xkb_context;
    pub fn xkb_context_unref(context: *mut xkb_context);

    pub fn xkb_keymap_new_from_string(
        context: *mut xkb_context,
        string: *const c_char,
        format: xkb_keymap_format,
        flags: xkb_keymap_compile_flags,
    ) -> *mut xkb_keymap;
    pub fn xkb_keymap_key_get_syms_by_level(
        keymap: *mut xkb_keymap,
        key: xkb_keycode_t,
        layout: xkb_layout_index_t,
        level: u32,
        syms_out: *mut *const xkb_keysym_t,
    ) -> c_int;
    pub fn xkb_keymap_key_repeats(keymap: *mut xkb_keymap, key: xkb_keycode_t) -> c_int;
    pub fn xkb_keymap_mod_get_index(keymap: *mut xkb_keymap, name: *const c_char) -> xkb_mod_index_t;
    pub fn xkb_keymap_unref(keymap: *mut xkb_keymap);

    pub fn xkb_state_new(keymap: *mut xkb_keymap) -> *mut xkb_state;
    pub fn xkb_state_key_get_one_sym(state: *mut xkb_state, key: xkb_keycode_t) -> xkb_keysym_t;
    pub fn xkb_state_key_get_layout(state: *mut xkb_state, key: xkb_keycode_t) -> xkb_layout_index_t;
    pub fn xkb_state_serialize_mods(state: *mut xkb_state, components: xkb_state_component) -> xkb_mod_mask_t;
    pub fn xkb_state_key_get_utf8(state: *mut xkb_state, key: xkb_keycode_t, buffer: *mut c_char, size: usize) -> c_int;
    pub fn xkb_state_update_mask(
        state: *mut xkb_state,
        depressed_mods: xkb_mod_mask_t,
        latched_mods: xkb_mod_mask_t,
        locked_mods: xkb_mod_mask_t,
        depressed_layout: xkb_layout_mask_t,
        latched_layout: xkb_layout_mask_t,
        locked_layout: xkb_layout_mask_t,
    ) -> xkb_state_component;
    pub fn xkb_state_mod_name_is_active(
        state: *mut xkb_state,
        name: *const c_char,
        component: xkb_state_component,
    ) -> c_int;
    pub fn xkb_state_unref(state: *mut xkb_state);

    pub fn xkb_compose_table_new_from_locale(
        context: *mut xkb_context,
        locale: *const c_char,
        flags: xkb_compose_compile_flags,
    ) -> *mut xkb_compose_table;
    pub fn xkb_compose_table_unref(table: *mut xkb_compose_table);

    pub fn xkb_compose_state_new(
        table: *mut xkb_compose_table,
        flags: xkb_compose_state_flags,
    ) -> *mut xkb_compose_state;
    pub fn xkb_compose_state_unref(state: *mut xkb_compose_state);
    pub fn xkb_compose_state_get_utf8(
        state: *mut xkb_compose_state,
        buffer: *mut c_char,
        size: usize,
    ) -> c_int;
    pub fn xkb_compose_state_feed(state: *mut xkb_compose_state, keysym: xkb_keysym_t) -> xkb_compose_feed_result;
    pub fn xkb_compose_state_reset(state: *mut xkb_compose_state);
    pub fn xkb_compose_state_get_status(state: *mut xkb_compose_state) -> xkb_compose_status;
}

#[cfg(x11_platform)]
#[repr(C)]
#[derive(Copy, Clone, Debug, PartialEq, Eq)]
pub enum xkb_x11_setup_xkb_extension_flags {
    XKB_X11_SETUP_XKB_EXTENSION_NO_FLAGS = 0,
}

#[cfg(x11_platform)]
#[link(name = "xkbcommon-x11")]
extern "C" {
    pub fn xkb_x11_setup_xkb_extension(
        conn: *mut crate::platform_impl::linux::x11::ffi::xcb_connection_t,
        major_xkb_version: c_uint,
        minor_xkb_version: c_uint,
        flags: xkb_x11_setup_xkb_extension_flags,
        major_rtrn: *mut c_uint,
        minor_rtrn: *mut c_uint,
        base_event_out: *mut c_int,
        base_error_out: *mut c_int,
    ) -> c_int;

    pub fn xkb_x11_get_core_keyboard_device_id(
        conn: *mut crate::platform_impl::linux::x11::ffi::xcb_connection_t,
    ) -> c_int;

    pub fn xkb_x11_keymap_new_from_device(
        context: *mut xkb_context,
        conn: *mut crate::platform_impl::linux::x11::ffi::xcb_connection_t,
        device_id: c_int,
        flags: xkb_keymap_compile_flags,
    ) -> *mut xkb_keymap;

    pub fn xkb_x11_state_new_from_device(
        keymap: *mut xkb_keymap,
        conn: *mut crate::platform_impl::linux::x11::ffi::xcb_connection_t,
        device_id: c_int,
    ) -> *mut xkb_state;
}
