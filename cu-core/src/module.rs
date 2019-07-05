use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;



#[derive(Debug,Clone)]
pub struct Module(pub (super) *mut ffi::CUmod_st);

unsafe impl Send for Module {}


impl Module {
    pub fn new(fname: &str) -> Self {
        unsafe {
            let mut newmod = mem::uninitialized();
            let mut name = CString::new(fname).unwrap();
            cuda_call!(ffi::cuModuleLoad(&mut newmod as _, name.as_ptr()));
            Module(newmod)
        }
    }
    pub fn from_data(data: &[u8]) -> Self {
        unsafe {
            let mut newmod = mem::uninitialized();
            cuda_call!(ffi::cuModuleLoadData(&mut newmod as _, data.as_ptr() as _));
            Module(newmod)
        }
    }
    pub fn from_data_ex(data: &[u8], opts: &[ffi::CUjit_option_enum], opt_vals: &[*mut ::std::os::raw::c_void]) -> Self {
        unsafe {
            assert!(opts.len() == opt_vals.len());
            let mut newmod = mem::uninitialized();

            ffi::cuModuleLoadDataEx(&mut newmod as _, data.as_ptr() as _, opts.len() as u32, opts.as_ptr() as _, opt_vals.as_ptr() as _);
            Module(newmod)
        }
    }
    pub fn from_fat(fat_data: &[u8]) -> Self {
        unsafe {
            let mut nmod = mem::uninitialized();
            cuda_call!(ffi::cuModuleLoadFatBinary(&mut nmod as _,fat_data.as_ptr() as _));
            Module(nmod)
        }
    }
    pub fn unload(self) {
        cuda_call!(ffi::cuModuleUnload(self.0));
    }
    pub fn function(&self, name: &str) -> super::function::Function {
        unsafe {
            let mut f = mem::uninitialized();
            let mut n = CString::new(name).unwrap();
            cuda_call!(ffi::cuModuleGetFunction(&mut f as _, self.0,n.as_ptr() as _));
            super::function::Function(f)
        }
    }
    pub fn global(&self, name: &str) -> super::memory::DevMem {
        unsafe {
            let mut n = CString::new(name).unwrap();
            let mut x: super::memory::DevMem = mem::uninitialized();
            x.allocated = false;
            cuda_call!(ffi::cuModuleGetGlobal_v2(&mut x.ptr as _, &mut x.len as _, self.0, n.as_ptr() as _));
            x
        }
    }
    // TODO, implemet text ref and surfRef
}

pub struct Link;
// Todo, module linking implementation
