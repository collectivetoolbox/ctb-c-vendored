use std::time::SystemTime;

use yaxi::clipboard::Clipboard;

#[cfg(test)]
#[cfg(feature = "clipboard")]
mod tests {
    use super::*;
    use serial_test::serial;
    use yaxi::clipboard::*;

    fn run_with_clipboard<T>(f: impl FnOnce(&Clipboard) -> T) -> Option<T> {
        match Clipboard::new(None) {
            Ok(clipboard) => {
                let result = f(&clipboard);
                std::mem::forget(clipboard);
                Some(result)
            }
            Err(e) => {
                println!("Skipping clipboard test: failed to open display connection: {:?}", e);
                None
            }
        }
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_get_targets() {
        let Some(result) = run_with_clipboard(|clipboard| clipboard.get_targets_with_name()) else {
            return;
        };
        println!("{:?}", result);
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_clear() {
        let Some((result, text)) = run_with_clipboard(|clipboard| {
            let result = clipboard.clear();
            let text = clipboard.get_text();
            (result, text)
        }) else {
            return;
        };
        assert!(result.is_ok());
        assert!(text.is_ok());
        assert_eq!(None, text.unwrap());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_write_image() {
        let data = include_bytes!("../assets/logo1.png");
        let bytes = data.to_vec();

        let Some(result) = run_with_clipboard(|clipboard| {
            clipboard.set_image(bytes, ImageFormat::Png)
        }) else {
            return;
        };
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_get_image() {
        let Some(result) = run_with_clipboard(|clipboard| clipboard.get_image()) else {
            return;
        };
        assert!(result.is_ok());

        if let Ok(Some(image)) = result {
            assert!(!image.is_empty());
        }
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_write_uri_list() {
        let temp_path = std::env::temp_dir().join(format!(
            "yaxi_test_clipboard_uri_{}.txt",
            std::process::id()
        ));
        std::fs::write(&temp_path, b"test uri list").unwrap();

        let uris = vec![temp_path.as_path()];
        let result = run_with_clipboard(|clipboard| clipboard.set_uri_list(&uris));
        let _ = std::fs::remove_file(&temp_path);
        let Some(result) = result else {
            return;
        };
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_read_uri_list() {
        let Some(result) = run_with_clipboard(|clipboard| clipboard.get_uri_list()) else {
            return;
        };
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_write_html() {
        let now = SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)
            .unwrap()
            .as_millis();
        let html = format!("<html><body>test {}</body></html>", now);
        let alt = Some(format!("test {}", now));

        let Some(result) = run_with_clipboard(|clipboard| clipboard.set_html(&html, alt.as_deref())) else {
            return;
        };
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_read_html() {
        let Some(result) = run_with_clipboard(|clipboard| clipboard.get_html()) else {
            return;
        };
        println!("{:?}", result);
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_text_consistency() {
        let time = SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)
            .unwrap()
            .as_millis();

        let excepted = format!("test-{}", time);

        let Some((result, text)) = run_with_clipboard(|clipboard| {
            let result = clipboard.set_text(&excepted);
            let text = clipboard.get_text();
            (result, text)
        }) else {
            return;
        };

        assert!(result.is_ok());
        let text = text.unwrap();

        assert_eq!(Some(excepted.clone()), text);
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_write_text() {
        let now = SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)
            .unwrap()
            .as_millis();
        let excepted = format!("test {}", now);
        let Some(result) = run_with_clipboard(|clipboard| clipboard.set_text(&excepted)) else {
            return;
        };
        assert!(result.is_ok());
    }

    #[test]
    #[serial]
    #[cfg_attr(windows, ignore = "X11 clipboard server is not available on Windows")]
    fn test_clipboard_read_text() {
        let Some(result) = run_with_clipboard(|clipboard| clipboard.get_text()) else {
            return;
        };
        assert!(result.is_ok());
    }

    // #[test]
    // fn test_all() {
    //     println!("read html");
    //     test_clipboard_read_html();

    //     println!("read text");
    //     test_clipboard_read_text();

    //     // TODO: the reason why write html, write text and text consistency use a long time is
    //     // because they try to hand it over to the clipboard manager

    //     println!("write html");
    //     test_clipboard_write_html();

    //     println!("write text");
    //     test_clipboard_write_text();

    //     println!("text consistency");
    //     test_clipboard_text_consistency();

    //     println!("clear");
    //     test_clipboard_clear();
    // }
}
