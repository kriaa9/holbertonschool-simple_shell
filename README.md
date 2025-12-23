# Simple Shell

A simple UNIX command interpreter written in C. This project is a custom implementation of a shell that emulates the basic functionality of the `sh` shell. It was built step-by-step to handle input parsing, path resolution, and command execution.

## 📋 Table of Contents
- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Progression](#project-progression)
- [How It Works](#how-it-works)
- [System Calls and Functions](#system-calls-and-functions)
- [File Structure](#file-structure)
- [Examples](#examples)
- [Troubleshooting](#troubleshooting)
- [Authors](#authors)
- [License](#license)

## 📝 Description
**Simple Shell** is a command-line interpreter that reads lines from either a file or standard input, parses them, and executes commands. It is designed to run on Linux distributions and provides a basic shell environment for executing system commands and built-in functions.

## ✨ Features
- **Interactive Mode**: Prompts for user input and executes commands in real-time.
- **Non-Interactive Mode**: Accepts commands from files or piped input.
- **PATH Resolution**: Searches for executables in the system's PATH environment variable.
- **Built-in Commands**: Supports `exit` and `env` commands.
- **Error Handling**: Provides appropriate exit statuses and error messages.
- **Signal Handling**: Handles Ctrl+D (EOF) for graceful exit.
- **Argument Parsing**: Handles commands with multiple arguments.

## 📋 Requirements
- **Operating System**: Linux (tested on Ubuntu and other distributions)
- **Compiler**: GCC (GNU Compiler Collection)
- **Libraries**: Standard C libraries (included with GCC)
- **Permissions**: Execute permissions on the compiled binary

## 📈 Project Progression
This shell was built in iterations. Below is a breakdown of the tasks and the files involved in each step:

### Task 0: Simple shell 0.1
Basic command execution. The shell prompts, reads input, and executes commands found in the current directory (absolute paths).
* **Files:** `main.c`, `shell.h`, `AUTHORS`, `README.md`, `man_1_simple_shell`

### Task 1: Simple shell 0.2
Argument parsing. Added the ability to handle command arguments (e.g., `ls -l /tmp`).
* **Files Modified:** `main.c` (added tokenization logic)

### Task 2: Simple shell 0.3
`PATH` handling. The shell now searches the environment variable `PATH` to find executables (e.g., typing `ls` instead of `/bin/ls`).
* **New File:** `path.c` (logic to split PATH and check file existence)
* **Files Modified:** `main.c`, `shell.h`

### Task 3: Simple shell 0.4
`exit` built-in. Implemented the ability to close the shell gracefully using the `exit` command.
* **Files Modified:** `main.c` (added check for "exit" string)

### Task 4: Simple shell 1.0
`env` built-in. Added support for printing the current environment variables.
* **Files Modified:** `main.c` (added check for "env" string and loop to print `environ`)

## 🛠 Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/kriaa9/holbertonschool-simple_shell.git
   cd holbertonschool-simple_shell
   ```

2. Compile the source code:
   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

3. Make the binary executable:
   ```bash
   chmod +x hsh
   ```
## 💻 Usage
### Interactive Mode
Run the shell and type commands directly:
```bash
./hsh
($) ls -l
... (file listing) ...
($) env
... (environment variables) ...
($) exit
```

### Non-Interactive Mode
Pipe commands into the shell or run scripts:
```bash
echo "ls -l" | ./hsh
```
## ⚙️ How It Works
The shell operates in an infinite loop that follows a specific lifecycle for every command entered:

1. **Initialization & Prompt**: Checks if input is from a terminal using `isatty()`. Prints prompt ($) if interactive.

2. **Reading Input**: Uses `getline()` to read the entire line from stdin. Exits on EOF (Ctrl+D).

3. **Tokenization**: Splits the input string using `strtok()` with delimiters (spaces, tabs, newlines).

4. **Built-in Check**: Checks if the command is a built-in (`exit` or `env`).

5. **Path Resolution**: Searches PATH for the executable using `stat()`.

6. **Execution**: Forks a child process, executes the command with `execve()`, and waits for completion.

7. **Memory Cleanup**: Frees allocated memory and restarts the loop.

## ## 📚 System Calls and Functions
This project utilizes the following standard library functions and system calls:
- `access` (man 2 access)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getline` (man 3 getline)
- `isatty` (man 3 isatty)
- `malloc` (man 3 malloc)
- `perror` (man 3 perror)
- `stat` (man 2 stat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)

## 📁 File Structure
```
holbertonschool-simple_shell/
├── main.c              # Main shell logic
├── path.c              # PATH resolution functions
├── shell.h             # Header file with prototypes and includes
├── AUTHORS             # List of contributors
├── man_1_simple_shell  # Manual page
├── README.md           # This file
└── hsh                 # Compiled binary (after build)
```

## 📖 Examples
### Basic Commands
```bash
./hsh
($) pwd
/home/user/holbertonschool-simple_shell
($) echo "Hello, World!"
Hello, World!
($) date
Mon Dec 23 12:00:00 UTC 2025
```

### Built-in Commands
```bash
./hsh
($) env | head -5
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
USER=user
...
($) exit
```

### Non-Interactive Mode
```bash
echo -e "ls -la\npwd\nexit" | ./hsh
```

## 🔧 Troubleshooting
- **Command not found**: Ensure the command exists in PATH or provide absolute path.
- **Permission denied**: Check file permissions with `ls -l`.
- **Segmentation fault**: Check for memory leaks or invalid pointers in code.
- **Compilation errors**: Ensure all source files are present and GCC is installed.

## ✍️ Authors
- Abdallah - [GitHub Profile](https://github.com/kriaa9)

## 📄 License
This project is part of the Holberton School curriculum. All rights reserved.
