use std::mem;
use std::ffi::{CStr, CString};
use std::os::raw::c_void;

use error_chain;

use ffi;
use libc;

use std::fmt::{self, Display, Debug, Formatter};

#[derive(Clone)]
pub struct CudaError {
    pub(crate) code: ffi::cudaError_enum
}

impl Default for CudaError {
    fn default() -> Self {
        CudaError {
            code: ffi::cudaError_enum::CUDA_SUCCESS
        }
    }
}

impl Display for CudaError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f, "{} - {}", error_name(self.code), err_str(self.code))
    }
}

impl Debug for CudaError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f, "{} - {}", error_name(self.code), err_str(self.code))
    }
}

impl ::std::error::Error for CudaError {
    fn description(&self) -> &str {
        "Cuda call failed"
    }

    fn cause(&self) -> Option<&::std::error::Error> {
        None
    }
    /*
    fn type_id(&self) -> ::std::any::TypeId where Self: 'static {
        ::std::any::TypeId::of::<CudaError>()
    }*/
}

pub type Result<T> = ::std::result::Result<T, CudaError>;


impl From<ffi::cudaError_enum> for CudaError {
    fn from(err: ffi::cudaError_enum) -> Self {
        CudaError {
            code: err
        }
    }
}

pub fn error_name(code: ffi::cudaError_enum) -> String {
    unsafe {
        if code == ffi::cudaError::CUDA_ERROR_UNKNOWN {
            return format!("Unknown error");
        }
        let mut n: *const i8 = ::std::ptr::null();
        let res = ffi::cuGetErrorName(code, &mut n as *mut _);
        if res == ffi::CUresult::CUDA_ERROR_INVALID_VALUE || n == ::std::ptr::null(){
            return format!("Unknown cuda error: {:?}", code as i32);
        }else {
            CStr::from_ptr(n).to_string_lossy().to_string()
        }
    }
}

pub fn err_str(code: ffi::cudaError_enum) -> String {
    unsafe {

        if code == ffi::cudaError::CUDA_ERROR_UNKNOWN {
            return format!("Unknown error");
        }
        let mut n: *const i8 = ::std::ptr::null();
        let res = ffi::cuGetErrorString(code, &mut n as *mut _);
        if res == ffi::CUresult::CUDA_ERROR_INVALID_VALUE || n == ::std::ptr::null() {
            return format!("Unknown cuda error: {:?}", code as i32);
        }else {
            CStr::from_ptr(n).to_string_lossy().to_string()
        }
    }
}