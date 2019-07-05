use std::ops::{Deref,DerefMut};

pub use core::Stream as StreamCore;

#[derive(Debug,Clone)]
pub struct Stream(StreamCore);

impl Stream{
    pub fn new() -> Self {
        Stream(StreamCore::new(::core::ffi::CUstream_flags_enum::CU_STREAM_DEFAULT))
    }
    pub fn new_nonblocking() -> Self {
        Stream(StreamCore::new(::core::ffi::CUstream_flags_enum::CU_STREAM_NON_BLOCKING))
    }
}

impl Deref for Stream {
    type Target = StreamCore;

    fn deref(&self) -> &Self::Target {
        return &self.0;
    }
}
impl DerefMut for Stream{
    fn deref_mut(&mut self) -> &mut Self::Target {
        return &mut self.0;
    }
}