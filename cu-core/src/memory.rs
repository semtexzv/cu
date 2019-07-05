use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;

use ::stream::Stream;
use ::std::cmp::{min, max};


#[derive(Debug, Clone)]
pub struct DevMem {
    pub ( crate )  ptr: ffi::CUdeviceptr,
    pub ( crate )  len: usize,
    pub ( crate ) allocated: bool
}

impl DevMem {
    pub fn alloc(len: usize) -> DevMem {
        unsafe {
            let mut m: DevMem = mem::zeroed();
            m.len = len;
            m.allocated = true;


            cuda_call!(ffi::cuMemAlloc_v2(&mut m.ptr as _,len));
            m
        }
    }

    pub fn read(&self, data: &mut [u8]) {
        self.read_offset(data, 0);
    }
    pub fn read_offset(&self, data: &mut [u8], offset: usize) {
        cuda_call!(ffi::cuMemcpyDtoH_v2(data.as_mut_ptr() as _, self.ptr + offset as u64, min(self.len - offset, data.len())));
    }

    pub fn read_async(&self, data: &mut [u8], stream: &Stream) {
        self.read_offset_async(data, 0, stream);
    }
    pub fn read_offset_async(&self, data: &mut [u8], offset: usize, stream: &Stream) {
        cuda_call!(ffi::cuMemcpyDtoHAsync_v2(data.as_mut_ptr() as _, self.ptr + offset as u64, min(self.len - offset, data.len()), stream.0));
    }

    pub fn write(&self, data: &[u8]) {
        self.write_offset(data, 0);
    }
    pub fn write_offset(&self, data: &[u8], offset: usize) {
        cuda_call!(ffi::cuMemcpyHtoD_v2( self.ptr + offset as u64, data.as_ptr() as _, min(self.len - offset, data.len())));
    }

    pub fn write_async(&self, data: &[u8], stream: &Stream) {
        self.write_offset_async(data, 0, stream);
    }
    pub fn write_offset_async(&self, data: &[u8], offset: usize, stream: &Stream) {
        cuda_call!(ffi::cuMemcpyHtoDAsync_v2(self.ptr + offset as u64,data.as_ptr() as _, min(self.len - offset ,data.len()),stream.0));
    }

    pub fn len(&self) -> usize {
        return self.len;
    }

    pub fn dev_ptr(&self) -> ::ffi::CUdeviceptr {
        return self.ptr;
    }
    pub fn dev_ptr_ref(&self) -> &::ffi::CUdeviceptr {
        return &self.ptr;
    }
}

impl Drop for DevMem {
    fn drop(&mut self) {
        unsafe {
            if self.allocated {
                cuda_call!(ffi::cuMemFree_v2(self.ptr));
            }
        }
    }
}