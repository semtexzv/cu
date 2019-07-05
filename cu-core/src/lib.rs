#![allow(unused_mut, dead_code, unused_variables, unused_imports, unused_unsafe)]
pub extern crate cu_sys as ffi;
extern crate error_chain;
pub extern crate libc;

#[macro_use]
pub extern crate bitflags;
use std::mem;

#[macro_export]
macro_rules! cuda_call {
    ($call:expr) => (
        unsafe {
            let err = $call;
            if err != ffi::cudaError::CUDA_SUCCESS{
                panic!("Cuda error: {:?}",err)
            }
        }
    )
}

#[macro_export]
macro_rules! cuda_handle {
    ($call:expr) => (
        unsafe {
            let err = $call;
            if err != ffi::cudaError::CUDA_SUCCESS {
                return Err(err.into())
            }
        }
    )
}

#[macro_export]
macro_rules! str {
    ($data: expr) => (
        unsafe {
            let mut res = CString::from_raw($data.as_mut_ptr()).to_string_lossy().into_owned();
            mem::forget($data);
            res
        }
    )
}

pub mod flags;
pub mod error;
pub mod device;
pub mod context;
pub mod stream;
pub mod module;
pub mod function;
pub mod memory;
pub mod event;
pub mod profiler;

pub use flags::*;
pub use error::{Result, CudaError};
pub use device::Device;
pub use context::Context;
pub use stream::Stream;
pub use module::{Module, Link};
pub use function::Function;
pub use memory::DevMem;
pub use event::Event;

pub use profiler::*;


pub fn version() -> i32 {
    let mut v = 0;
    cuda_call!(ffi::cuDriverGetVersion(&mut v as *mut _));
    v
}


pub fn init() -> error::Result<()> {
    unsafe {
        if !ffi::cuda_init() {
            return Err(CudaError {
                code: ffi::cudaError::CUDA_ERROR_UNKNOWN
            });
        }
        cuda_handle!(ffi::cuInit(0));
        Ok(())
    }
}