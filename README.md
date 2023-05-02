# AXI FFT Testing
This repo contains tester programs for the AXI FFT core and the AXI Loopback Test core. It targets the ZedBoard and AD-FMCOMMS3-EBZ which runs a modified version of Raspberry Pi OS, so a [toolchain][1] is needed for cross compilation unless you are building on the device.
The toolchain should be extracted to a directory called "toolchain", for example:
```
./
└── toolchain/
    └── gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/
        ├── bin/
        ├── include/
        └── ...
```

# Report
Report detailing workflow for creating AXI FFT and AXI Loopback Test are available [here][2].

[1]: https://developer.arm.com/-/media/Files/downloads/gnu-a/8.3-2019.03/binrel/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tar.xz
[2]: https://github.com/arandomdev/axi_fft_test/blob/9c2fdc32de1b3cd7b569d800763fa02231b1859c/Report.pdf
