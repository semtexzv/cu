extern crate gcc;
fn main() {

    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=native/wrap.cpp");
    println!("cargo:rerun-if-changed=native/wrap.hpp");


    println!(r"cargo:rustc-link-search=/opt/cuda/lib64/");
    println!(r"cargo:rustc-link-search=/usr/local/cuda/lib64");

    let mut config = gcc::Build::new();

    config
        .include("native/")
        .include(r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\include")
        .include(r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.0\include")
        .include(r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.1\include")
        .include(r"/opt/cuda/include/")
        .cpp(true)
        .file("native/wrap.cpp")
        .static_flag(true)
        .flag("-fpermissive")
        .compile("libcudawrap.a");
}