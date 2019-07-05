
#[repr(C)]
#[derive(Debug,Clone,Copy,PartialEq,Eq,PartialOrd,Ord,Hash)]
pub struct Dims(u32,u32,u32);

impl Dims{
    pub fn to_tuple(&self) -> (u32,u32,u32) {
        return (self.0,self.1,self.2);
    }
}
macro_rules! impl_from {
    ($name:ident from $($t:ty)*) => ($(

        impl From<$t> for $name {
            fn from(val: $t) -> Self {
                return $name(val as u32,1,1);
            }
        }
        impl From<($t,$t)> for $name {
            fn from((x,y): ($t,$t)) -> Self {
                return $name(x as u32,y as u32,1);
            }
        }
        impl From<($t,$t,$t)> for $name {
            fn from((x,y,z): ($t,$t,$t)) -> Self {
                return Dims(x as u32,y as u32 ,z as u32);
            }
        }
    )*)
}

impl_from!(Dims from i8 u8 i16 u16 i32 u32 i64 u64 usize);