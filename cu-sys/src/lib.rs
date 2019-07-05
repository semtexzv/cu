#![allow(unused_mut, dead_code, unused_variables, unused_imports, unused_unsafe,
non_upper_case_globals, non_camel_case_types, non_snake_case)]
pub extern crate libc;

pub mod driver_api;

pub use driver_api::*;
pub use driver_api::cudaError_enum as cudaError;

pub fn cuLaunchKernel_wrap(f: CUfunction, gridDimX: ::std::os::raw::c_uint,
                           gridDimY: ::std::os::raw::c_uint,
                           gridDimZ: ::std::os::raw::c_uint,
                           blockDimX: ::std::os::raw::c_uint,
                           blockDimY: ::std::os::raw::c_uint,
                           blockDimZ: ::std::os::raw::c_uint,
                           sharedMemBytes: ::std::os::raw::c_uint,
                           hStream: CUstream,
                           kernelParams: *const *const ::std::os::raw::c_void,
                           extra: *const *const ::std::os::raw::c_void) -> driver_api::cudaError_enum {
    unsafe {
        return driver_api::cuLaunchKernel(f, gridDimX, gridDimY, gridDimZ,
                                          blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream,
                                          kernelParams as *mut *mut _, extra as *mut *mut  _);
    }
}
