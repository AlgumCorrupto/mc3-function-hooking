## Description

This project is a proof of concept demostrating that it is possible to inject C code
into Midnight Club 3 Remix.

https://youtu.be/-N2QR7W1_kM?si=dWXQzRLOo9o4xrEb

## Prerequisites

- ps2iso: https://github.com/anasrar/ps2iso/releases/tag/v0.0.3
    - Rename the executable to ps2iso or ps2iso.exe
    - Add its path to the PATH environment variable
- GNUMake
- default.iso: Place the MC3DER NTSC ISO inside the project folder and rename it to `default.iso`
- ps2dev: https://github.com/ps2dev/ps2dev
    - Follow the installation step-by-step guide
- armips: https://github.com/Kingcom/armips
    - Add its path to the PATH environment variable
    - Or install it using your favorite package manager

## Building

- Run ``make`` on the command-line inside the project's folder
it should generate a pnach if it ran successfully
-  ``make iso`` to generate a modded iso
