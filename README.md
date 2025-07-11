# Lioz Jason Ralston Hen's Shell

LJRH Shell is a custom command-line interpreter (shell) built in C. It provides a basic interactive environment for executing common shell commands, including some custom implementations and support for piping and I/O redirection.

## Features

* **Custom Built-in Commands**: `cd`, `cp`, `rm`, `mv`, `read`, `wc`, and `echo` with redirection.
* **External Command Execution**: Ability to run standard Linux commands like `ls`, `grep`, `cat`, etc.
* **Piping (`|`)**: Support for connecting the output of one command to the input of another (e.g., `ls -l | grep .c`).
* **I/O Redirection (`>` and `>>`)**:
    * `>`: Overwrite text to a file (e.g., `echo "hello" > file.txt`).
    * `>>`: Append text to a file (e.g., `echo "world" >> file.txt`).
* **Dynamic Prompt**: Displays the current `username@hostname:current_directory$` for easy navigation.
* **Interactive Welcome/Logout**: Features a loading bar and ASCII art at startup and shutdown for a unique user experience.
* **Memory Management**: Handles dynamic memory allocation and deallocation for input and arguments.

## Getting Started

### Prerequisites

To compile and run this shell, you need:

* A C compiler (e.g., GCC)
* Standard C libraries
* `make` utility (for compilation)

### Compilation

Navigate to the directory containing your source files and the `Makefile`. Then, simply run the `make` command:

```bash
make
```

### Running the shell

After successful compilation, run the executable command:

```bash
./myShell
```
