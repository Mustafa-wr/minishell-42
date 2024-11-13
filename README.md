# Minishell

A custom unix implementation inspired by bash.

## Overview

Minishell is a shell that implements core shell functionalities including command execution, pipes, redirections, environment variables, and basic built-in commands.

## Features

### Command Execution
- Execute commands with relative or absolute paths
- PATH variable support for command lookup
- Command history
- Signal handling (ctrl-C, ctrl-D, ctrl-\)

### Input/Output
- Input/Output redirections (`<`, `>`, `>>`)
- Here document (`<<`)
- Pipes (`|`)
- Interactive prompt

### Quotes Handling
- Single quotes (`'`) - Preserve literal value of characters
- Double quotes (`"`) - Preserve literal value except for `$`

### Variable Expansion
- Environment variables (`$VAR`)
- Last command exit status (`$?`)

### Built-in Commands
- `echo` (with -n option)
- `cd` (with relative/absolute paths)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Prerequisites

- GCC or Clang compiler
- GNU Make
- readline library
- Linux/Unix environment

## Installation

```bash
# Clone the repository
git clone https://github.com/username/minishell.git

# Navigate to project directory
cd minishell

# Build the project
make
```

## Usage

```bash
./minishell
```

### Basic Commands
```bash
# Basic command execution
minishell$ ls -l

# Using pipes
minishell$ ls | grep filename

# Input/Output redirections
minishell$ cat < input.txt
minishell$ echo "Hello" > output.txt

# Environment variables
minishell$ echo $PATH
minishell$ echo $?

# Built-in commands
minishell$ pwd
minishell$ cd /path/to/directory
minishell$ echo -n "Hello World"
```

## Technical Details

### Memory Management
- All heap-allocated memory is properly freed
- No memory leaks (except those from readline)
- No unexpected quits (segfault, bus error, double free)

### Signal Handling
- Uses only one global variable for signal handling
- Implements bash-like behavior for:
  - Ctrl-C (SIGINT): Display new prompt
  - Ctrl-D (EOF): Exit shell
  - Ctrl-\ (SIGQUIT): No action

### Error Handling
- Proper error messages for command not found
- Syntax error handling for unclosed quotes
- Permission and file existence checks

## Compilation

The project comes with a Makefile that includes the following rules:
- `make`: Compile the program
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Recompile the program

## Development Guidelines

- All functions are error-checked
- Proper memory management
- Clear separation of concerns (lexing, parsing, execution)

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Writing Your Own Shell](https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html)
- [Advanced Programming in the Unix Environment](https://www.man7.org/tlpi/)
