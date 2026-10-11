// spell-checker:ignore ARMTHUMB memlimit

pub(crate) use _lzma::module_def;

#[pymodule]
mod _lzma {
    use crate::compression::{
        DecompressArgs, DecompressError, DecompressState, DecompressStatus, Decompressor,
    };
    use alloc::fmt;
    use lzma_rust2::{Action, CheckType, FilterType, Status, StreamResult};
    use rustpython_common::lock::PyMutex;
    use rustpython_vm::builtins::{PyBaseExceptionRef, PyBytesRef, PyDict, PyType, PyTypeRef};
    use rustpython_vm::convert::ToPyException;
    use rustpython_vm::function::ArgBytesLike;
    use rustpython_vm::types::Constructor;
    use rustpython_vm::{Py, PyObjectRef, PyPayload, PyResult, VirtualMachine};
    use std::io::{Read, Write};
    use std::sync::{Arc, Mutex};

    const BUFSIZ: usize = 8192;

    #[pyattr]
    const FILTER_ARM: u64 = 0x07;
    #[pyattr]
    const FILTER_ARMTHUMB: u64 = 0x08;
    #[pyattr]
    const FILTER_DELTA: u64 = 0x03;
    #[pyattr]
    const FILTER_IA64: u64 = 0x06;
    #[pyattr]
    const FILTER_LZMA1: u64 = 0x4000_0000_0000_0001;
    #[pyattr]
    const FILTER_LZMA2: u64 = 0x21;
    #[pyattr]
    const FILTER_POWERPC: u64 = 0x05;
    #[pyattr]
    const FILTER_SPARC: u64 = 0x09;
    #[pyattr]
    const FILTER_X86: u64 = 0x04;

    #[pyattr]
    const PRESET_DEFAULT: u32 = 6;
    #[pyattr]
    const PRESET_EXTREME: u32 = 1 << 31;

    #[pyattr]
    const CHECK_NONE: i32 = 0;
    #[pyattr]
    const CHECK_CRC32: i32 = 1;
    #[pyattr]
    const CHECK_CRC64: i32 = 4;
    #[pyattr]
    const CHECK_SHA256: i32 = 10;
    #[pyattr]
    const CHECK_ID_MAX: i32 = 15;
    #[pyattr]
    const CHECK_UNKNOWN: i32 = CHECK_ID_MAX + 1;

    #[pyattr]
    const MF_HC3: i32 = 0x03;
    #[pyattr]
    const MF_HC4: i32 = 0x04;
    #[pyattr]
    const MF_BT2: i32 = 0x12;
    #[pyattr]
    const MF_BT3: i32 = 0x13;
    #[pyattr]
    const MF_BT4: i32 = 0x14;

    #[pyattr]
    const MODE_FAST: i32 = 1;
    #[pyattr]
    const MODE_NORMAL: i32 = 2;

    enum Format {
        Auto = 0,
        Xz = 1,
        Alone = 2,
        Raw = 3,
    }

    #[pyattr]
    const FORMAT_AUTO: i32 = Format::Auto as i32;
    #[pyattr]
    const FORMAT_XZ: i32 = Format::Xz as i32;
    #[pyattr]
    const FORMAT_ALONE: i32 = Format::Alone as i32;
    #[pyattr]
    const FORMAT_RAW: i32 = Format::Raw as i32;

    const DEFAULT_LC: u32 = 3;
    const DEFAULT_LP: u32 = 0;
    const DEFAULT_PB: u32 = 2;

    const PRESET_DICT_SIZES: [u32; 10] = [
        1 << 18, // 0: 256 KiB
        1 << 20, // 1: 1 MiB
        1 << 21, // 2: 2 MiB
        1 << 22, // 3: 4 MiB
        1 << 22, // 4: 4 MiB
        1 << 23, // 5: 8 MiB
        1 << 23, // 6: 8 MiB
        1 << 24, // 7: 16 MiB
        1 << 25, // 8: 32 MiB
        1 << 26, // 9: 64 MiB
    ];

    #[pyattr(once, name = "LZMAError")]
    fn error(vm: &VirtualMachine) -> PyTypeRef {
        vm.ctx.new_exception_type(
            "lzma",
            "LZMAError",
            Some(vec![vm.ctx.exceptions.exception_type.to_owned()]),
        )
    }

    fn new_lzma_error(message: impl Into<String>, vm: &VirtualMachine) -> PyBaseExceptionRef {
        let msg: String = message.into();
        vm.new_exception_msg(vm.class("lzma", "LZMAError"), msg.into())
    }

    fn int_to_check(check: i32) -> Option<CheckType> {
        if check == -1 {
            return Some(CheckType::Crc64);
        }
        match check {
            CHECK_NONE => Some(CheckType::None),
            CHECK_CRC32 => Some(CheckType::Crc32),
            CHECK_CRC64 => Some(CheckType::Crc64),
            CHECK_SHA256 => Some(CheckType::Sha256),
            _ => None,
        }
    }

    fn check_to_int(check: Option<CheckType>) -> i32 {
        match check {
            Some(CheckType::None) => CHECK_NONE,
            Some(CheckType::Crc32) => CHECK_CRC32,
            Some(CheckType::Crc64) => CHECK_CRC64,
            Some(CheckType::Sha256) => CHECK_SHA256,
            None => CHECK_UNKNOWN,
        }
    }

    #[pyfunction]
    fn is_check_supported(check_id: i32) -> bool {
        matches!(
            check_id,
            CHECK_NONE | CHECK_CRC32 | CHECK_CRC64 | CHECK_SHA256
        )
    }

    fn preset_dict_size(preset: u32) -> u32 {
        let level = (preset & 0x1F) as usize;
        if level < PRESET_DICT_SIZES.len() {
            PRESET_DICT_SIZES[level]
        } else {
            1 << 23
        }
    }

    fn lzma2_dict_size_from_prop(prop: u8) -> u32 {
        if prop == 40 {
            u32::MAX
        } else {
            let base = 2 | (prop as u32 & 1);
            base << (prop as u32 / 2 + 11)
        }
    }

    fn lzma2_prop_from_dict_size(dict_size: u32) -> u8 {
        for i in 0..=40 {
            if lzma2_dict_size_from_prop(i) >= dict_size {
                return i;
            }
        }
        40
    }

    fn encode_lzma1_properties(lc: u32, lp: u32, pb: u32, dict_size: u32) -> Vec<u8> {
        let mut props = Vec::with_capacity(5);
        props.push(((pb * 5 + lp) * 9 + lc) as u8);
        props.extend_from_slice(&dict_size.to_le_bytes());
        props
    }

    fn decode_lzma1_properties(props: &[u8]) -> Option<(u32, u32, u32, u32)> {
        if props.len() != 5 {
            return None;
        }
        let prop = props[0] as u32;
        if prop >= 9 * 5 * 5 {
            return None;
        }
        let lc = prop % 9;
        let remainder = prop / 9;
        let lp = remainder % 5;
        let pb = remainder / 5;
        let dict_size = u32::from_le_bytes([props[1], props[2], props[3], props[4]]);
        Some((lc, lp, pb, dict_size))
    }

    fn get_dict_opt_u32(
        spec: &PyObjectRef,
        key: &str,
        vm: &VirtualMachine,
    ) -> PyResult<Option<u32>> {
        let dict = spec.downcast_ref::<PyDict>().ok_or_else(|| {
            vm.new_type_error("Filter specifier must be a dict or dict-like object")
        })?;
        match dict.get_item_opt(key, vm)? {
            Some(obj) => Ok(Some(obj.try_into_value::<u32>(vm)?)),
            None => Ok(None),
        }
    }

    fn get_dict_opt_u64(
        spec: &PyObjectRef,
        key: &str,
        vm: &VirtualMachine,
    ) -> PyResult<Option<u64>> {
        let dict = spec.downcast_ref::<PyDict>().ok_or_else(|| {
            vm.new_type_error("Filter specifier must be a dict or dict-like object")
        })?;
        match dict.get_item_opt(key, vm)? {
            Some(obj) => Ok(Some(obj.try_into_value::<u64>(vm)?)),
            None => Ok(None),
        }
    }

    fn build_filter_spec(
        filter_id: u64,
        props: &[u8],
        vm: &VirtualMachine,
    ) -> PyResult<PyObjectRef> {
        let dict = vm.ctx.new_dict();
        dict.set_item("id", vm.new_pyobj(filter_id), vm)?;

        match filter_id {
            FILTER_LZMA1 => {
                let (lc, lp, pb, dict_size) = decode_lzma1_properties(props)
                    .ok_or_else(|| new_lzma_error("Invalid or unsupported options", vm))?;
                dict.set_item("lc", vm.new_pyobj(lc), vm)?;
                dict.set_item("lp", vm.new_pyobj(lp), vm)?;
                dict.set_item("pb", vm.new_pyobj(pb), vm)?;
                dict.set_item("dict_size", vm.new_pyobj(dict_size), vm)?;
            }
            FILTER_LZMA2 => {
                if props.len() != 1 {
                    return Err(new_lzma_error("Invalid or unsupported options", vm));
                }
                let dict_size = lzma2_dict_size_from_prop(props[0]);
                dict.set_item("dict_size", vm.new_pyobj(dict_size), vm)?;
            }
            FILTER_DELTA => {
                if props.len() != 1 {
                    return Err(new_lzma_error("Invalid or unsupported options", vm));
                }
                let dist = props[0] as u32 + 1;
                dict.set_item("dist", vm.new_pyobj(dist), vm)?;
            }
            FILTER_X86 | FILTER_POWERPC | FILTER_IA64 | FILTER_ARM | FILTER_ARMTHUMB
            | FILTER_SPARC => {
                if props.is_empty() {
                    // default: no start_offset
                } else if props.len() == 4 {
                    let start_offset =
                        u32::from_le_bytes([props[0], props[1], props[2], props[3]]);
                    dict.set_item("start_offset", vm.new_pyobj(start_offset), vm)?;
                } else {
                    return Err(new_lzma_error("Invalid or unsupported options", vm));
                }
            }
            _ => {
                return Err(vm.new_value_error(format!("Invalid filter ID: {filter_id}")));
            }
        }

        Ok(dict.into())
    }

    #[pyfunction]
    fn _encode_filter_properties(
        filter_spec: PyObjectRef,
        vm: &VirtualMachine,
    ) -> PyResult<Vec<u8>> {
        let filter_id = get_dict_opt_u64(&filter_spec, "id", vm)?
            .ok_or_else(|| vm.new_value_error("Filter specifier must have an \"id\" entry"))?;

        match filter_id {
            FILTER_LZMA1 => {
                let preset =
                    get_dict_opt_u32(&filter_spec, "preset", vm)?.unwrap_or(PRESET_DEFAULT);
                let lc = get_dict_opt_u32(&filter_spec, "lc", vm)?.unwrap_or(DEFAULT_LC);
                let lp = get_dict_opt_u32(&filter_spec, "lp", vm)?.unwrap_or(DEFAULT_LP);
                let pb = get_dict_opt_u32(&filter_spec, "pb", vm)?.unwrap_or(DEFAULT_PB);
                let dict_size = get_dict_opt_u32(&filter_spec, "dict_size", vm)?
                    .unwrap_or_else(|| preset_dict_size(preset));
                Ok(encode_lzma1_properties(lc, lp, pb, dict_size))
            }
            FILTER_LZMA2 => {
                let preset =
                    get_dict_opt_u32(&filter_spec, "preset", vm)?.unwrap_or(PRESET_DEFAULT);
                let dict_size = get_dict_opt_u32(&filter_spec, "dict_size", vm)?
                    .unwrap_or_else(|| preset_dict_size(preset));
                Ok(vec![lzma2_prop_from_dict_size(dict_size)])
            }
            FILTER_DELTA => {
                let dist = get_dict_opt_u32(&filter_spec, "dist", vm)?.unwrap_or(1);
                if dist == 0 || dist > 256 {
                    return Err(vm.new_value_error("Invalid filter specifier for delta filter"));
                }
                Ok(vec![(dist - 1) as u8])
            }
            FILTER_X86 | FILTER_POWERPC | FILTER_IA64 | FILTER_ARM | FILTER_ARMTHUMB
            | FILTER_SPARC => {
                let start_offset =
                    get_dict_opt_u32(&filter_spec, "start_offset", vm)?.unwrap_or(0);
                if start_offset == 0 {
                    Ok(vec![])
                } else {
                    Ok(start_offset.to_le_bytes().to_vec())
                }
            }
            _ => Err(vm.new_value_error(format!("Invalid filter ID: {filter_id}"))),
        }
    }

    #[pyfunction]
    fn _decode_filter_properties(
        filter_id: u64,
        encoded_props: ArgBytesLike,
        vm: &VirtualMachine,
    ) -> PyResult<PyObjectRef> {
        let props = encoded_props.borrow_buf();
        build_filter_spec(filter_id, &props, vm)
    }

    fn parse_filter_spec_lzma(
        spec: &PyObjectRef,
        vm: &VirtualMachine,
    ) -> PyResult<lzma_rust2::LzmaOptions> {
        let preset = get_dict_opt_u32(spec, "preset", vm)?.unwrap_or(PRESET_DEFAULT);
        let mut opts = lzma_rust2::LzmaOptions::with_preset(preset & 0x1F);
        if let Some(v) = get_dict_opt_u32(spec, "dict_size", vm)? {
            opts.dict_size = v;
        }
        if let Some(v) = get_dict_opt_u32(spec, "lc", vm)? {
            opts.lc = v;
        }
        if let Some(v) = get_dict_opt_u32(spec, "lp", vm)? {
            opts.lp = v;
        }
        if let Some(v) = get_dict_opt_u32(spec, "pb", vm)? {
            opts.pb = v;
        }
        if let Some(v) = get_dict_opt_u32(spec, "nice_len", vm)? {
            opts.nice_len = v;
        }
        if let Some(v) = get_dict_opt_u32(spec, "depth", vm)? {
            opts.depth_limit = v as i32;
        }
        if let Some(v) = get_dict_opt_u32(spec, "mode", vm)? {
            match v as i32 {
                MODE_FAST => opts.mode = lzma_rust2::EncodeMode::Fast,
                MODE_NORMAL => opts.mode = lzma_rust2::EncodeMode::Normal,
                _ => return Err(vm.new_value_error("Invalid filter specifier for LZMA filter")),
            }
        }
        if let Some(v) = get_dict_opt_u32(spec, "mf", vm)? {
            match v as i32 {
                MF_HC3 | MF_HC4 => opts.mf = lzma_rust2::MfType::Hc4,
                MF_BT2 | MF_BT3 | MF_BT4 => opts.mf = lzma_rust2::MfType::Bt4,
                _ => return Err(vm.new_value_error("Invalid filter specifier for LZMA filter")),
            }
        }
        Ok(opts)
    }

    fn apply_filter_specs_to_xz(
        options: &mut lzma_rust2::XzOptions,
        filter_specs: Vec<PyObjectRef>,
        vm: &VirtualMachine,
    ) -> PyResult<()> {
        const LZMA_FILTERS_MAX: usize = 4;
        if filter_specs.len() > LZMA_FILTERS_MAX {
            return Err(new_lzma_error(
                format!("Too many filters - maximum of {LZMA_FILTERS_MAX}"),
                vm,
            ));
        }
        for (i, spec) in filter_specs.iter().enumerate() {
            let filter_id = get_dict_opt_u64(spec, "id", vm)?
                .ok_or_else(|| vm.new_value_error("Filter specifier must have an \"id\" entry"))?;
            let is_last = i == filter_specs.len() - 1;
            if is_last {
                if filter_id != FILTER_LZMA2 {
                    return Err(new_lzma_error("Last filter must be LZMA2", vm));
                }
                options.lzma_options = parse_filter_spec_lzma(spec, vm)?;
            } else {
                match filter_id {
                    FILTER_DELTA => {
                        let dist = get_dict_opt_u32(spec, "dist", vm)?.unwrap_or(1);
                        options.prepend_pre_filter(FilterType::Delta, dist);
                    }
                    FILTER_X86 => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjX86, offset);
                    }
                    FILTER_POWERPC => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjPpc, offset);
                    }
                    FILTER_IA64 => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjIa64, offset);
                    }
                    FILTER_ARM => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjArm, offset);
                    }
                    FILTER_ARMTHUMB => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjArmThumb, offset);
                    }
                    FILTER_SPARC => {
                        let offset = get_dict_opt_u32(spec, "start_offset", vm)?.unwrap_or(0);
                        options.prepend_pre_filter(FilterType::BcjSparc, offset);
                    }
                    _ => {
                        return Err(new_lzma_error(
                            format!("Unsupported filter ID: {filter_id}"),
                            vm,
                        ));
                    }
                }
            }
        }
        Ok(())
    }

    fn apply_filter_specs_to_lzma(
        options: &mut lzma_rust2::LzmaOptions,
        filter_specs: Vec<PyObjectRef>,
        vm: &VirtualMachine,
    ) -> PyResult<()> {
        if filter_specs.len() != 1 {
            return Err(new_lzma_error(
                "Only one filter can be specified for LZMA format",
                vm,
            ));
        }
        let filter_id = get_dict_opt_u64(&filter_specs[0], "id", vm)?
            .ok_or_else(|| vm.new_value_error("Filter specifier must have an \"id\" entry"))?;
        if filter_id != FILTER_LZMA1 {
            return Err(new_lzma_error("Filter must be LZMA1 for LZMA format", vm));
        }
        *options = parse_filter_spec_lzma(&filter_specs[0], vm)?;
        Ok(())
    }

    fn apply_filter_specs_to_lzma2(
        options: &mut lzma_rust2::Lzma2Options,
        filter_specs: Vec<PyObjectRef>,
        vm: &VirtualMachine,
    ) -> PyResult<()> {
        if filter_specs.len() != 1 {
            return Err(new_lzma_error(
                "Only one filter can be specified for raw LZMA2 format",
                vm,
            ));
        }
        let filter_id = get_dict_opt_u64(&filter_specs[0], "id", vm)?
            .ok_or_else(|| vm.new_value_error("Filter specifier must have an \"id\" entry"))?;
        if filter_id != FILTER_LZMA2 {
            return Err(new_lzma_error("Filter must be LZMA2 for raw format", vm));
        }
        options.lzma_options = parse_filter_spec_lzma(&filter_specs[0], vm)?;
        Ok(())
    }

    enum DecompressEngine {
        Xz(lzma_rust2::XzStream),
        Raw(lzma_rust2::Lzma2Stream),
        Alone {
            input_buf: Vec<u8>,
            last_pos: usize,
            reader: Option<lzma_rust2::LzmaReader<std::io::Cursor<Vec<u8>>>>,
            end_reached: bool,
            memlimit: u32,
        },
        Auto {
            engine: Option<Box<DecompressEngine>>,
            header_buf: Vec<u8>,
            memlimit: u32,
        },
    }

    impl DecompressEngine {
        fn process(
            &mut self,
            input: &[u8],
            output: &mut [u8],
            check_out: &mut i32,
        ) -> Result<StreamResult, String> {
            match self {
                Self::Xz(s) => {
                    let res = s
                        .process(input, output, Action::Run)
                        .map_err(|e| e.to_string())?;
                    if *check_out == CHECK_UNKNOWN {
                        *check_out = check_to_int(s.check_type());
                    }
                    Ok(res)
                }
                Self::Raw(s) => s
                    .process(input, output, Action::Run)
                    .map_err(|e| e.to_string()),
                Self::Alone {
                    input_buf,
                    last_pos,
                    reader,
                    end_reached,
                    memlimit,
                } => {
                    if *end_reached {
                        return Ok(StreamResult {
                            bytes_consumed: 0,
                            bytes_produced: 0,
                            status: Status::StreamEnd,
                        });
                    }
                    input_buf.extend_from_slice(input);
                    if reader.is_none() {
                        if input_buf.len() < 13 {
                            return Ok(StreamResult {
                                bytes_consumed: input.len(),
                                bytes_produced: 0,
                                status: Status::Ok,
                            });
                        }
                        let cursor = std::io::Cursor::new(core::mem::take(input_buf));
                        let r = lzma_rust2::LzmaReader::new_mem_limit(cursor, *memlimit, None)
                            .map_err(|e| e.to_string())?;
                        *reader = Some(r);
                    }
                    let r = reader.as_mut().unwrap();
                    if !input_buf.is_empty() {
                        let to_append = core::mem::take(input_buf);
                        r.inner_mut().get_mut().extend_from_slice(&to_append);
                    }
                    let mut total_produced = 0;
                    while total_produced < output.len() {
                        match r.read(&mut output[total_produced..]) {
                            Ok(0) => {
                                *end_reached = true;
                                break;
                            }
                            Ok(n) => {
                                total_produced += n;
                            }
                            Err(e) if e.kind() == std::io::ErrorKind::UnexpectedEof => {
                                break;
                            }
                            Err(e) => return Err(e.to_string()),
                        }
                    }
                    let new_pos = r.inner().position() as usize;
                    let consumed = new_pos.saturating_sub(*last_pos).min(input.len());
                    *last_pos = new_pos;
                    let status = if *end_reached {
                        Status::StreamEnd
                    } else {
                        Status::Ok
                    };
                    Ok(StreamResult {
                        bytes_consumed: consumed,
                        bytes_produced: total_produced,
                        status,
                    })
                }
                Self::Auto {
                    engine,
                    header_buf,
                    memlimit,
                } => {
                    if engine.is_none() {
                        let needed = 6usize.saturating_sub(header_buf.len());
                        let take = needed.min(input.len());
                        header_buf.extend_from_slice(&input[..take]);
                        if header_buf.len() < 6 {
                            return Ok(StreamResult {
                                bytes_consumed: take,
                                bytes_produced: 0,
                                status: Status::Ok,
                            });
                        }
                        const XZ_MAGIC: [u8; 6] = [0xFD, b'7', b'z', b'X', b'Z', 0x00];
                        let new_eng = if header_buf.starts_with(&XZ_MAGIC) {
                            DecompressEngine::Xz(lzma_rust2::XzStream::new(false))
                        } else {
                            DecompressEngine::Alone {
                                input_buf: Vec::new(),
                                last_pos: 0,
                                reader: None,
                                end_reached: false,
                                memlimit: *memlimit,
                            }
                        };
                        *engine = Some(Box::new(new_eng));
                        let buffered = core::mem::take(header_buf);
                        let prev_buffered_len = buffered.len().saturating_sub(take);
                        let mut combined = buffered;
                        combined.extend_from_slice(&input[take..]);
                        let eng = engine.as_mut().unwrap();
                        let res = eng.process(&combined, output, check_out)?;
                        let consumed_from_input = res
                            .bytes_consumed
                            .saturating_sub(prev_buffered_len)
                            .min(input.len());
                        return Ok(StreamResult {
                            bytes_consumed: consumed_from_input,
                            bytes_produced: res.bytes_produced,
                            status: res.status,
                        });
                    }
                    let eng = engine.as_mut().unwrap();
                    eng.process(input, output, check_out)
                }
            }
        }
    }

    struct LzmaDecompressorStream {
        engine: DecompressEngine,
        total_in: u64,
        check: i32,
    }

    impl Decompressor for LzmaDecompressorStream {
        type Flush = ();
        type Status = Status;
        type Error = String;

        fn total_in(&self) -> u64 {
            self.total_in
        }

        fn decompress_vec(
            &mut self,
            input: &[u8],
            output: &mut Vec<u8>,
            (): Self::Flush,
        ) -> Result<Self::Status, Self::Error> {
            let old_len = output.len();
            output.resize(old_len + 8192, 0);
            let res = self
                .engine
                .process(input, &mut output[old_len..], &mut self.check)?;
            output.truncate(old_len + res.bytes_produced);
            self.total_in += res.bytes_consumed as u64;
            Ok(res.status)
        }
    }

    impl DecompressStatus for Status {
        fn is_stream_end(&self) -> bool {
            *self == Status::StreamEnd
        }
    }

    #[pyattr]
    #[pyclass(name = "LZMADecompressor")]
    #[derive(PyPayload)]
    struct LZMADecompressor {
        state: PyMutex<DecompressState<LzmaDecompressorStream>>,
    }

    impl fmt::Debug for LZMADecompressor {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            write!(f, "_lzma.LZMADecompressor")
        }
    }

    #[derive(FromArgs)]
    pub struct LZMADecompressorConstructorArgs {
        #[pyarg(any, default = FORMAT_AUTO)]
        format: i32,
        #[pyarg(any, optional)]
        memlimit: Option<u64>,
        #[pyarg(any, optional)]
        filters: Option<Vec<PyObjectRef>>,
    }

    impl Constructor for LZMADecompressor {
        type Args = LZMADecompressorConstructorArgs;

        fn py_new(_cls: &Py<PyType>, args: Self::Args, vm: &VirtualMachine) -> PyResult<Self> {
            if args.format == FORMAT_RAW && args.memlimit.is_some() {
                return Err(vm.new_value_error("Cannot specify memory limit with FORMAT_RAW"));
            }

            if args.format == FORMAT_RAW && args.filters.is_none() {
                return Err(vm.new_value_error("Must specify filters for FORMAT_RAW"));
            }
            if args.format != FORMAT_RAW && args.filters.is_some() {
                return Err(vm.new_value_error("Cannot specify filters except with FORMAT_RAW"));
            }

            let memlimit = args
                .memlimit
                .map(|m| m.min(u32::MAX as u64) as u32)
                .unwrap_or(u32::MAX);

            let (engine, check) = match args.format {
                FORMAT_AUTO => (
                    DecompressEngine::Auto {
                        engine: None,
                        header_buf: Vec::new(),
                        memlimit,
                    },
                    CHECK_UNKNOWN,
                ),
                FORMAT_XZ => (
                    DecompressEngine::Xz(lzma_rust2::XzStream::new(false)),
                    CHECK_UNKNOWN,
                ),
                FORMAT_ALONE => (
                    DecompressEngine::Alone {
                        input_buf: Vec::new(),
                        last_pos: 0,
                        reader: None,
                        end_reached: false,
                        memlimit,
                    },
                    CHECK_NONE,
                ),
                FORMAT_RAW => {
                    let filter_specs = args.filters.unwrap();
                    let mut opts = lzma_rust2::Lzma2Options::default();
                    apply_filter_specs_to_lzma2(&mut opts, filter_specs, vm)?;
                    (
                        DecompressEngine::Raw(lzma_rust2::Lzma2Stream::new(
                            opts.lzma_options.dict_size,
                        )),
                        CHECK_NONE,
                    )
                }
                _ => {
                    return Err(
                        vm.new_value_error(format!("Invalid container format: {}", args.format))
                    );
                }
            };

            let stream = LzmaDecompressorStream {
                engine,
                total_in: 0,
                check,
            };

            Ok(Self {
                state: PyMutex::new(DecompressState::new(stream, vm)),
            })
        }
    }

    #[pyclass(with(Constructor))]
    impl LZMADecompressor {
        #[pymethod]
        fn decompress(&self, args: DecompressArgs, vm: &VirtualMachine) -> PyResult<Vec<u8>> {
            let max_length = args.max_length();
            let data = &*args.data();

            let mut state = self.state.lock();
            state
                .decompress(data, max_length, BUFSIZ, vm)
                .map_err(|e| match e {
                    DecompressError::Decompress(err) => new_lzma_error(err, vm),
                    DecompressError::Eof(err) => err.to_pyexception(vm),
                })
        }

        #[pygetset]
        fn check(&self) -> i32 {
            self.state.lock().decompressor().check
        }

        #[pygetset]
        fn eof(&self) -> bool {
            self.state.lock().eof()
        }

        #[pygetset]
        fn unused_data(&self) -> PyBytesRef {
            self.state.lock().unused_data()
        }

        #[pygetset]
        fn needs_input(&self) -> bool {
            self.state.lock().needs_input()
        }
    }

    #[derive(Default, Clone)]
    struct SharedBuffer(Arc<Mutex<Vec<u8>>>);

    impl Write for SharedBuffer {
        fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
            self.0.lock().unwrap().extend_from_slice(buf);
            Ok(buf.len())
        }
        fn flush(&mut self) -> std::io::Result<()> {
            Ok(())
        }
    }

    enum CompressorEngine {
        Xz(lzma_rust2::XzWriter<SharedBuffer>),
        Alone(lzma_rust2::LzmaWriter<SharedBuffer>),
        Raw(lzma_rust2::Lzma2Writer<SharedBuffer>),
    }

    struct CompressorState {
        inner: Option<CompressorEngine>,
        out_buf: SharedBuffer,
        flushed: bool,
    }

    #[pyattr]
    #[pyclass(name = "LZMACompressor")]
    #[derive(PyPayload)]
    struct LZMACompressor {
        state: PyMutex<CompressorState>,
    }

    impl fmt::Debug for LZMACompressor {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            write!(f, "_lzma.LZMACompressor")
        }
    }

    #[derive(FromArgs)]
    pub struct LZMACompressorConstructorArgs {
        #[pyarg(any, default = FORMAT_XZ)]
        format: i32,
        #[pyarg(any, default = -1)]
        check: i32,
        #[pyarg(any, optional)]
        preset: Option<PyObjectRef>,
        #[pyarg(any, optional)]
        filters: Option<Vec<PyObjectRef>>,
    }

    impl Constructor for LZMACompressor {
        type Args = LZMACompressorConstructorArgs;

        fn py_new(_cls: &Py<PyType>, args: Self::Args, vm: &VirtualMachine) -> PyResult<Self> {
            if args.format != FORMAT_XZ && args.check != -1 && args.check != CHECK_NONE {
                return Err(new_lzma_error(
                    "Integrity checks are only supported by FORMAT_XZ",
                    vm,
                ));
            }

            if args.preset.is_some() && args.filters.is_some() {
                return Err(new_lzma_error(
                    "Cannot specify both preset and filter chain",
                    vm,
                ));
            }

            let preset: u32 = match &args.preset {
                Some(obj) => obj.clone().try_into_value(vm)?,
                None => PRESET_DEFAULT,
            };

            let shared_buf = SharedBuffer::default();

            let inner = match args.format {
                FORMAT_XZ => {
                    let mut opts = lzma_rust2::XzOptions::with_preset(preset & 0x1F);
                    if args.check != -1 {
                        let check_type = int_to_check(args.check)
                            .ok_or_else(|| vm.new_value_error("Invalid check value"))?;
                        opts.set_check_sum_type(check_type);
                    }
                    if let Some(filter_specs) = args.filters {
                        apply_filter_specs_to_xz(&mut opts, filter_specs, vm)?;
                    }
                    CompressorEngine::Xz(
                        lzma_rust2::XzWriter::new(shared_buf.clone(), opts)
                            .map_err(|e| new_lzma_error(e.to_string(), vm))?,
                    )
                }
                FORMAT_ALONE => {
                    let mut opts = lzma_rust2::LzmaOptions::with_preset(preset & 0x1F);
                    if let Some(filter_specs) = args.filters {
                        apply_filter_specs_to_lzma(&mut opts, filter_specs, vm)?;
                    }
                    CompressorEngine::Alone(
                        lzma_rust2::LzmaWriter::new(shared_buf.clone(), &opts, true, true, None)
                            .map_err(|e| new_lzma_error(e.to_string(), vm))?,
                    )
                }
                FORMAT_RAW => {
                    let filter_specs = args
                        .filters
                        .ok_or_else(|| vm.new_value_error("Must specify filters for FORMAT_RAW"))?;
                    let mut opts = lzma_rust2::Lzma2Options::with_preset(preset & 0x1F);
                    apply_filter_specs_to_lzma2(&mut opts, filter_specs, vm)?;
                    CompressorEngine::Raw(lzma_rust2::Lzma2Writer::new(shared_buf.clone(), opts))
                }
                _ => {
                    return Err(
                        vm.new_value_error(format!("Invalid container format: {}", args.format))
                    );
                }
            };

            Ok(Self {
                state: PyMutex::new(CompressorState {
                    inner: Some(inner),
                    out_buf: shared_buf,
                    flushed: false,
                }),
            })
        }
    }

    #[pyclass(with(Constructor))]
    impl LZMACompressor {
        #[pymethod]
        fn compress(&self, data: ArgBytesLike, vm: &VirtualMachine) -> PyResult<Vec<u8>> {
            let mut state = self.state.lock();
            if state.flushed {
                return Err(vm.new_value_error("Compressor has been flushed"));
            }
            let inner = state
                .inner
                .as_mut()
                .ok_or_else(|| new_lzma_error("Compressor is closed", vm))?;
            data.with_ref(|buf| -> PyResult<()> {
                match inner {
                    CompressorEngine::Xz(w) => {
                        w.write_all(buf)
                            .map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                    CompressorEngine::Alone(w) => {
                        w.write_all(buf)
                            .map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                    CompressorEngine::Raw(w) => {
                        w.write_all(buf)
                            .map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                }
                Ok(())
            })?;
            let mut guard = state.out_buf.0.lock().unwrap();
            Ok(core::mem::take(&mut *guard))
        }

        #[pymethod]
        fn flush(&self, vm: &VirtualMachine) -> PyResult<Vec<u8>> {
            let mut state = self.state.lock();
            if state.flushed {
                return Err(vm.new_value_error("Repeated call to flush()"));
            }
            state.flushed = true;
            if let Some(inner) = state.inner.take() {
                match inner {
                    CompressorEngine::Xz(w) => {
                        w.finish().map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                    CompressorEngine::Alone(w) => {
                        w.finish().map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                    CompressorEngine::Raw(w) => {
                        w.finish().map_err(|e| new_lzma_error(e.to_string(), vm))?;
                    }
                }
            }
            let mut guard = state.out_buf.0.lock().unwrap();
            Ok(core::mem::take(&mut *guard))
        }
    }
}
