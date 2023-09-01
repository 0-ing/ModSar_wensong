```
cd vsomeip-qnx-all-in
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../qnx_7.0.0_linux_x86_64.cmake -DCMAKE_INSTALL_PREFIX= < where you want to install vsomeip > ..
make
make install
```



