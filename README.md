# hdump -- Canonical hexadecimal and ASCII dump display

## Goal

Replicate ``hexdump -C'' behaviour.

Display the input offset in hexadecimal, followed by sixteen
space-separated, two-column, hexadecimal bytes, followed by the same
sixteen bytes in `%_p` format enclosed in `|` characters.

## Compilation

    $ make all

## Usage

    $ ./hdump <file>

## Output example

    $  hdump mbfi | head
    00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
    00000010  03 00 3e 00 01 00 00 00  00 12 00 00 00 00 00 00  |..>.............|
    00000020  40 00 00 00 00 00 00 00  a8 31 00 00 00 00 00 00  |@........1......|
    00000030  00 00 00 00 40 00 38 00  0e 00 40 00 1d 00 1c 00  |....@.8...@.....|
    00000040  06 00 00 00 04 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
    00000050  40 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |@.......@.......|
    00000060  10 03 00 00 00 00 00 00  10 03 00 00 00 00 00 00  |................|
    00000070  08 00 00 00 00 00 00 00  03 00 00 00 04 00 00 00  |................|
    00000080  94 03 00 00 00 00 00 00  94 03 00 00 00 00 00 00  |................|
    00000090  94 03 00 00 00 00 00 00  1c 00 00 00 00 00 00 00  |................|


## License

  - Copyright (c) 2019-2025, J. A. Corbal
  - The MIT License (MIT)
  - Read [`LICENSE`](LICENSE) for more information
