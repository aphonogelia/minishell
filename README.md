# minishell

A lightweight Unix shell written in C, built as part of the 42 curriculum.

This project focuses on building a real interactive shell from scratch: lexical analysis, parsing, expansion, command tree construction, process execution, pipes, redirections, heredocs, builtin commands, and signal handling.

## Why This Project Matters

`minishell` is a systems programming project that demonstrates:

- Process control with `fork`, `execve`, `waitpid`
- File descriptor orchestration for pipes and redirections
- Stateful parsing pipeline (tokenize -> expand -> retoken -> combine -> grammar -> command tree)
- Environment management in user space (copy/update/unset shell env)
- Interactive terminal behavior with `readline` + POSIX signals

For recruiters, this is a practical example of low-level engineering, debugging discipline, and modular C design.

## Features Implemented

- Interactive prompt with history (`readline` / `add_history`)
- Builtins:
  - `cd`
  - `echo` (supports `-n`)
  - `env`
  - `exit`
  - `export`
  - `pwd`
  - `unset`
- External command execution via `execve`
- `PATH` resolution for executables
- Pipelines (`|`)
- Redirections:
  - input: `<`
  - output: `>`
  - append: `>>`
  - heredoc: `<<`
- Quote-aware tokenization (`'` and `"`)
- Environment variable expansion:
  - `$VAR`
  - `$?`
- Basic syntax validation (pipes/redirection placement)
- Signal behavior for interactive shell and child processes

## Architecture Overview

The codebase is split into focused modules:

- `src/main`: shell lifecycle, init/cleanup, interactive loop, signal setup
- `src/parse`: tokenization, expansion, grammar checks, command graph construction, heredoc handling
- `src/execute`: builtin dispatch, process creation, pipe orchestration, redirection setup, command path resolution
- `src/builtins`: implementations of shell builtins
- `libft`: custom utility library used by the shell
- `inc/minishell.h`: shared data structures and function contracts

Core runtime structs:

- `t_shell`: global shell state (env, parser state, command tree, last exit code)
- `t_state`: current input + token stream
- `t_xnode`: command node in pipeline linked list (`argv` + redirections)
- `t_redir`: redirection metadata

## Parser / Executor Flow

For each input line:

1. Tokenize input into words/operators/quoted values
2. Expand variables where allowed
3. Remove empty tokens, retoken expanded values when needed
4. Combine adjacent quote/word fragments into final arguments
5. Validate grammar (pipe and redirection sanity checks)
6. Build command nodes (`t_xnode` linked list)
7. Pre-process heredocs
8. Execute as:
   - single builtin in parent shell process when possible
   - otherwise pipeline of child processes

## Build And Run

### Requirements

- Linux (or Unix-like environment)
- `cc`
- GNU Make
- `readline` development library

On Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

### Compile

```bash
make
```

Useful targets:

```bash
make clean
make fclean
make re
make debug
```

### Launch

```bash
./minishell
```

## Quick Usage Examples

```bash
echo hello world
pwd
export PROJECT=mini
echo $PROJECT
cat < infile_big | grep 42 | wc -l
echo line >> out.txt
cat << EOF
value is $PROJECT
EOF
```

## Known Limitations

This implementation intentionally stays within a scoped feature set and currently does not include:

- Logical operators (`&&`, `||`)
- Wildcard/glob expansion (`*`)
- Subshells (`(...)`)
- Command substitution (`$(...)`)
- Full POSIX compatibility edge cases
- Advanced `echo` flags beyond basic `-n`
- `cd` without argument (`HOME`) behavior

## Notes On Quality

- Modular source organization by responsibility
- Dedicated cleanup paths for parser/execution structures
- Clear exit code propagation from children and builtins
- Defensive handling for allocation and syscall failures

## Project Context

This repository is an educational shell implementation created to practice low-level Unix programming and interpreter-style architecture.
