use core::DevMem;
use std::ops::{DerefMut, Deref};
use num::Num;
use std::mem;

use std::marker::PhantomData;
use std::rc::Rc;
use std::slice;

use ::val::CudaVal;

#[derive(Debug, Clone)]
pub struct Buffer<T: ::val::CudaVal>(Rc<DevMem>, PhantomData<T>);

impl<T: CudaVal> Buffer<T> {
    pub fn new(count: usize) -> Buffer<T> {
        return Buffer(Rc::new(DevMem::alloc(mem::size_of::<T>() * count)), PhantomData {});
    }
    pub (crate) fn from_mem(mem: DevMem) -> Buffer < T >{
        return Buffer(Rc::new(mem),PhantomData{});
    }
    pub fn read(&self, buf: &mut [T]) {
        unsafe {
            let mut data = slice::from_raw_parts_mut(buf.as_mut_ptr() as *mut u8, buf.len() * mem::size_of::<T>());
            self.0.read(&mut data);
        }
    }
    pub fn write(&self, buf: &[T]) {
        unsafe {
            let mut data = slice::from_raw_parts(buf.as_ptr() as *mut u8, buf.len() * mem::size_of::<T>());
            self.0.write(&mut data);
        }
    }
    pub fn len(&self) -> usize {
        return self.0.len() / mem::size_of::<T>();
    }
}


impl<T: CudaVal> Deref for Buffer<T> {
    type Target = DevMem;

    fn deref(&self) -> &Self::Target {
        return &self.0;
    }
}