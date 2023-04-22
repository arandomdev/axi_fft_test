#!/usr/bin/env bash

rclone copy ./ adi:/home/analog/source/axi_fft_test/ --transfers=1 --checkers=1 --include-from=programList.txt