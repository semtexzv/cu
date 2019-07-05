
/// This trait is used as a marker for types that can be passed into Cuda
/// by value
pub unsafe trait CudaVal {
    fn mark(&self) -> &Self{
        return &self;
    }
}
macro_rules! impl_val {
    ($name:ident for $($t:ty)*) => ($(
        unsafe impl $name for $t{}
        unsafe impl $name for [$t;2] {}
        unsafe impl $name for [$t;4] {}
    )*)
}

impl_val!(CudaVal for u8 i8 u16 i16 u32 i32 u64 i64 usize isize f32 f64 );