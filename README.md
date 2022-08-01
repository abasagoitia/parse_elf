# Parse Elf: Basic API for Interacting with ELF files
## Version 0.1.0
## Program Structure:
* build/
    * location where executable is output
* include/ 
    * parse_elf.h
        * Header file with variable defines and function prototypes
* src/
    * linked_list.c
        * Basic linked list implimentation
    * parse_elf_api.c
        * Utility functions used to parse an ELF
    * parse_elf_prints.c
        * Functions used to print information associated with ELF headers
* tests/
    * hello_world_test.c
        * Hello world src file used for examples
    * hello_world_test
        * ELF files compiled with `-pi` used for examples
* buildall
    * builds all project files and places executable in `build/`
* README.md
    * This readme


## Important Information
- Parse Elf currently only supports parsing ELF files on 64bit Linux. All ELF's analyzed using this program must be 64bit.
- This is an incomplete project further work will be done to complete functionality.
- Currently main is in src/parse_elf_api.c but will be moved in the future

## Usage:

Basic
```
./buildall
./build/parse_elf_api <path_to_ELF>
```
Helpful
```
gcc <some_file.c> -o <some_file> -pi
objdump -D -Mintel,x86-64 -b binary -m i386 <some binary> - Useful for reading `.text` section
readelf -a <some_ELF>
```

## Functionality
### 64-bit
#### Parse
- [x] Parse ELF Header
- [x] Parse Program Headers
- [x] Parse Section Headers
- [x] Parse Section String
- [ ] Parse Symbol Table
- [ ] Parse `.bss`
- [ ] Parse `.comment`
- [ ] Parse `ctors`
- [ ] Parse `.data`
- [ ] Parse `.data1`
- [ ] Parse `.debug`
- [ ] Parse `dtors`
- [ ] Parse `.dynamic`
- [ ] Parse `.dynstr`
- [ ] Parse `.dynsym`
- [ ] Parse `.fini`
- [ ] Parse `.gnu.version`
- [ ] Parse `.gnu.version.d`
- [ ] Parse `.gnu.version.r`
- [ ] Parse `.got`
- [ ] Parse `.hash`
- [ ] Parse `.init`
- [ ] Parse `.interp`
- [ ] Parse `.line`
- [ ] Parse `.note`
- [ ] Parse `.note.ABI-tag`
- [ ] Parse `.note.gnu.build-id`
- [ ] Parse `.note.GNU-stack`
- [ ] Parse `.note.openbsd.ident`
- [ ] Parse `.plt`
- [ ] Parse `.relNAME`
- [ ] Parse `.relaNAME`
- [ ] Parse `.rodata`
- [ ] Parse `.rodata1`
- [x] Parse `.shstrtab`
- [ ] Parse `.strtab`
- [ ] Parse `.symtab`
- [x] Parse `.text`
- [ ] Parse String table
- [ ] Parse Relocation Entries
- [ ] Parse Dynamic Tags
- [ ] Parse Notes
#### Edit
- [ ] Add functionality to edit ELF's
### 32bit
#### Parse
- [ ] Parse ELF Header
- [ ] Parse Program Headers
- [ ] Parse Section Headers
- [ ] Parse Section String
- [ ] Parse Symbol Table
- [ ] Parse `.bss`
- [ ] Parse `.comment`
- [ ] Parse `ctors`
- [ ] Parse `.data`
- [ ] Parse `.data1`
- [ ] Parse `.debug`
- [ ] Parse `dtors`
- [ ] Parse `.dynamic`
- [ ] Parse `.dynstr`
- [ ] Parse `.dynsym`
- [ ] Parse `.fini`
- [ ] Parse `.gnu.version`
- [ ] Parse `.gnu.version.d`
- [ ] Parse `.gnu.version.r`
- [ ] Parse `.got`
- [ ] Parse `.hash`
- [ ] Parse `.init`
- [ ] Parse `.interp`
- [ ] Parse `.line`
- [ ] Parse `.note`
- [ ] Parse `.note.ABI-tag`
- [ ] Parse `.note.gnu.build-id`
- [ ] Parse `.note.GNU-stack`
- [ ] Parse `.note.openbsd.ident`
- [ ] Parse `.plt`
- [ ] Parse `.relNAME`
- [ ] Parse `.relaNAME`
- [ ] Parse `.rodata`
- [ ] Parse `.rodata1`
- [ ] Parse `.shstrtab`
- [ ] Parse `.strtab`
- [ ] Parse `.symtab`
- [ ] Parse `.text`
- [ ] Parse String table
- [ ] Parse Relocation Entries
- [ ] Parse Dynamic Tags
- [ ] Parse Notes
#### Edit
- [ ] Add functionality to edit ELF's

## Credits
I used these resources for help in creating this program
* https://github.com/statusfailed/elf-from-scratch/blob/master/main.py
* https://github.com/TheCodeArtist/elf-parser/blob/master/elf-parser.c
* https://linux.die.net/man/5/elf