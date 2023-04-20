#!/usr/bin/env python3

import numpy as np
import scipy.fftpack
import datetime

NFFT = 3
POINT_SIZE = 1 << NFFT
CYCLES = 1

ITERATIONS = 1 << 16


def main():
    length = np.pi * 2 * CYCLES
    cosData = np.cos(
        np.arange(0, length, length/POINT_SIZE), dtype=np.csingle)  # type: ignore # noqa

    print(f"Performing {ITERATIONS} iterations")

    start = datetime.datetime.now()
    for _ in range(ITERATIONS):
        scipy.fftpack.fft(cosData)
        pass

    end = datetime.datetime.now()

    print(f"Took: {(end-start).total_seconds()*1000}ms")
    pass


if __name__ == "__main__":
    main()
    pass
