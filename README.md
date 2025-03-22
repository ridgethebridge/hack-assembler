My attempt at the assembler for the hack language from the Nand2Tetris site and book, I'm using C to test myself on the language.

to compile just type in make, it should compile everything into a binary called hasm.
To use hasm run
```
./hasm file.asm
```
and it should produce a file called file.hack, with file being a placeholder for any name.
The hack file can then be run on the cpu emulator which can be downloaded from the Nand2Tetris website

**Things I might add**
* indexing for the M register so A and C instructions can be combined
* other Macro support
