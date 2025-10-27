# Data Compression

Implements a **lossless text file compressor and decompressor** using a nibble-based encoding scheme inspired by the original MacWrite algorithm.

## How It Works
- **Common characters** (`a, c, d, e, f, h, i, l, n, o, p, r, s, t, space`) → **1 nibble**.  
- **All other characters** → **3 nibbles** (prefixed by 0).  
- Compression reduces file size by storing frequent characters in fewer bits.  
- Decompression reverses the process to restore the original file.  
- Uses a **Nibbler ADT** for nibble-level file I/O:  
  - `nib_open()`  
  - `nib_close()`  
  - `nib_get_nibble()`  
  - `nib_put_nibble()`

## Implementation
- Reads input **byte-by-byte** using `fgetc()`.  
- Writes compressed data **nibble-by-nibble** via Nibbler functions.  
- Decompression reads nibbles and reconstructs bytes accordingly.  
- Unit tests provided for all Nibbler functions.  
- C files: `compress.c`, `decompress.c`, `nibbler.c`, `unittests.c`.  
- Compiled using a **Makefile**.

## Usage
```bash
# Compile all executables
$ make

# Compress a file
$ ./compress file.txt -o file.comp

# Decompress a file
$ ./decompress file.comp -o file.dec

# Verify output matches original
$ diff file.txt file.dec

# Run unit tests for Nibbler ADT
$ ./unittests
