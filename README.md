# Simple Shell

A simple UNIX command interpreter written in C. This program is a custom implementation of a shell that emulates the basic functionality of the `sh` shell.

## 📋 Table of Contents
* [Description](#description)
* [Installation](#installation)
* [Usage](#usage)
* [How It Works (Internal Flow)](#how-it-works-internal-flow)
  
## 📝 Description
Simple Shell is a command-line interpreter that reads lines from either a file or standard input, parses them, and executes commands. It supports:
* Interactive and Non-interactive mode.
* Command execution from the System `PATH`.
* Built-in commands (`exit`, `env`).
* Error handling with correct exit status.

## 🛠 Installation
To install and compile the shell, clone the repository and compile using `gcc`:

```bash
git clone [https://github.com/kriaa9/holbertonschool-simple_shell.git](https://github.com/kriaa9/holbertonschool-simple_shell.git)
cd holbertonschool-simple_shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
