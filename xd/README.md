# xd - Hex Dump Program

`xd` is a simplified version of the Unix `xxd` utility. It reads a file or standard input and prints its contents in hexadecimal and ASCII format. Each line shows:

- **Offset:** Index of the first byte (8 hex digits).  
- **Hex values:** Next 16 bytes, grouped in pairs. Missing bytes are shown as spaces.  
- **ASCII:** Printable characters are shown; others appear as `.`.

Instead of `fopen()`/`fgetc()`, `xd` uses **Unix system calls** (`open()`, `read()`, `close()`) with a 16-byte buffer, giving direct control over I/O. The program handles invalid filenames or incorrect arguments by exiting with a non-zero code.

Optionally, `bad_xd.c` is a minimal version under 1000 characters I made for extra credit.
