#!/usr/bin/env python3

import numpy as np
import numpy.typing as npt
import scipy.fft

NFFT = 10
POINT_SIZE = 1 << NFFT
CYCLES = 16


def printArray(data: npt.NDArray[np.csingle]):
    for i in range(0, len(data), 4):
        for j in data[i:i+4]:
            print(
                f"{np.format_float_positional(np.real(j))}, "  # type: ignore
                f"{np.format_float_positional(np.imag(j))}, ",  # type: ignore
                end="")
            pass

        print()
        pass
    pass


def main():
    length = np.pi * 2 * CYCLES
    cosData = np.cos(
        np.arange(0, length, length/POINT_SIZE), dtype=np.csingle)  # type: ignore # noqa

    print("Test vector")
    printArray(cosData)
    print()

    fftData = scipy.fft.fft(cosData, norm="backward")  # No forward norm
    print("Test vector key")
    printArray(fftData)
    pass


if __name__ == "__main__":
    main()
    pass
