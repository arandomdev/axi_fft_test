#!/usr/bin/env bash

# scp build/axi_fft_test adi_analog:/home/analog/source/axi_fft_test/axi_fft_test
rclone copy ./ adi:/home/analog/source/axi_fft_test/ --transfers=1 --checkers=1 --include-from=programList.txt