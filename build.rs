fn main() {
    println!("cargo:rustc-link-search=/usr/include/");
    println!("cargo:rustc-link-lib=swsscommon");

    println!("cargo:rerun-if-changed=wrapper.h");
    println!("cargo:rerun-if-changed=wrapper.cpp");
    
    cxx_build::bridge("src/lib.rs")
        .file("wrapper.cpp")
        .compile("swss-common-rs");
}
