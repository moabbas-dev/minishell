# Minishell

## Overview

`minishell` is a simple Unix-like shell implementation written in C. It aims to replicate the basic functionality
of a standard shell, allowing users to execute commands, manage environment variables, and handle input/output redirections and pipes.

## Features

- **Prompt Display:** A customizable prompt that displays before accepting user input.
- **Command Execution:** Ability to execute built-in and external commands.
- **Built-in Commands:** Support for built-in commands like `cd`, `pwd`, `echo`, `env`, `export`, `unset`, and `exit`.
- **Path Resolution:** Resolves commands using the `PATH` environment variable.
- **Environment Variable Handling:** Management of environment variables, including setting and unsetting.
- **Input Parsing:** Parsing user input to handle commands, arguments, pipes, and redirections.
- **Pipes and Redirections:** Support for command piping (`|`) and input/output redirections (`<`, `>`, `>>`).
- **Signal Handling:** Graceful handling of signals like `SIGINT` and `SIGQUIT`.
- **Error Handling:** Informative error messages for invalid commands and syntax errors.

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/moabbas-dev/minishell/
   ```
2. run the program
   ```sh
   make
   ```
