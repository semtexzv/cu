use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Function(pub (super) ffi::CUfunction);

impl Function {
    pub fn max_active_blocks(&self, block_size: i32, block_shmem: usize) -> i32 {
        let mut res = 0;
        cuda_call!(ffi::cuOccupancyMaxActiveBlocksPerMultiprocessor(&mut res as _,self.0,block_size,block_shmem));
        res
    }
    pub fn launch(&self, stream: &super::stream::Stream, grid_size: (u32, u32, u32), block_size: (u32, u32, u32), block_mem: u32,
                  params: &[*const c_void]) {
        cuda_call!(ffi::cuLaunchKernel_wrap(self.0, grid_size.0, grid_size.1, grid_size.2, block_size.0, block_size.1, block_size.2, block_mem,
                                stream.0,
                                params.as_ptr(), ::std::ptr::null()
            ));
    }
}