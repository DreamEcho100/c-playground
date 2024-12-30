# Notes

- `malloc` = "memory allocate" - gives you raw memory
  - `malloc` just gives you memory with whatever was there before on the memory address. It doesn't initialize it to zero.
- `calloc` = "clear allocate" - gives you zeroed memory
  - `calloc` initializes everything to zero/NULL (like new Array(5) in JavaScript), but it's slower than `malloc`, because it has to set everything to zero explicitly every time even if you don't need it.
