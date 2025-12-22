# Simple Shell

A simple UNIX command interpreter written in C.

## Description
This program is a custom implementation of a UNIX shell. It executes commands read from standard input or from a file. It is capable of executing simple commands, handling arguments, and managing the `PATH` environment variable.

## Compilation
All files are compiled on Ubuntu 20.04 LTS using `gcc`:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
