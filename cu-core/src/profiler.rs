use ffi;
use std::ffi::{CStr, CString};
use std::path::{Path, PathBuf};

pub fn init(config_file: &str, output_file: &str) {
    let mut conf = CString::new(config_file).unwrap();
    let mut out = CString::new(output_file).unwrap();

    cuda_call!(ffi::cuProfilerInitialize(conf.as_ptr(), out.as_ptr(), ffi::CUoutput_mode_enum::CU_OUT_CSV));
}

pub fn start(){
    cuda_call!(ffi::cuProfilerStart());
}

pub fn stop(){
    cuda_call!(ffi::cuProfilerStop());
}