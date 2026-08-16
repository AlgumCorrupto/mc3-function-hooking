## Description

This project is a proof of concept demostrating that it is possible to inject C code
into Midnight Club 3 Remix.

https://youtu.be/-N2QR7W1_kM?si=dWXQzRLOo9o4xrEb

## Prerequisites

- GNUMake
- original.elf: Place the original game's .elf file in the root of the project, and rename it to original.elf
- ps2dev: https://github.com/ps2dev/ps2dev
    - Follow the installation step-by-step guide
- armips: https://github.com/Kingcom/armips
    - Add its path to the PATH environment variable
    - Or install it using your favorite package manager

## Building

Run ``make`` on the command-line inside the project's folder
it should generate ``modded.iso`` if it ran successfully
