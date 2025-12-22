# Simple Shell

A simple UNIX command interpreter written in C.

## Description

This program is a custom implementation of a UNIX shell. It executes commands read from standard input or from a file. It is capable of executing simple commands, handling arguments, and managing the `PATH` environment variable.

## Compilation

All files are compiled on Ubuntu 20.04 LTS using `gcc`:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### Non-Interactive Mode
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
```

## Features

- Execute simple commands with arguments
- Handle the `PATH` environment variable
- Support for both interactive and non-interactive modes
- Process management using fork and execve
- Simple command parsing and execution

## Requirements

- Ubuntu 20.04 LTS
- gcc compiler
- Standard C library (gnu89 standard)

## Project Structure

- `main.c` - Entry point of the shell
- `shell.c` - Core shell functionality
- `AUTHORS` - List of contributors
- `README.md` - This file

## Man Page

For more information about the shell, see the man page: `man_1_simple_shell`

## Authors

See the `AUTHORS` file for the list of contributors.

## License

This project is part of the Holberton School curriculum.
