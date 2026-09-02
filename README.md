# Alphashell — A Custom Unix Shell in C

A lightweight Unix-like shell written in C, built to explore process
management, command parsing, and directory navigation using core Linux
system calls.

## Features

- **Dynamic Prompt** — displays the current working directory as the prompt, so you always know where you are.
- **Command Execution** — runs standard commands (`ls`, `pwd`, `whoami`, etc.) using `fork()` and `execvp()`.
- **Built-in `cd` Command** — changes the shell's working directory, including:
  - `cd` with no arguments → goes to the home directory
  - `cd ~/path` → expands `~` to the user's home directory
  - `cd path` → changes to a relative or absolute path
- **Exit Command** — type `exit` to quit the shell cleanly.
- **Command Parsing** — splits raw input into a command and its arguments using `strtok()`.

## How It Works

1. The shell prints the current working directory as the prompt.
2. It reads a line of input from the user.
3. The input is tokenized into a command and its arguments.
4. If the command is `cd`, it's handled directly by the shell (since changing
   directory only makes sense in the shell's own process, not a child).
5. Otherwise, the shell forks a child process:
   - The **child** replaces itself with the requested program using `execvp()`.
   - The **parent** waits for the child to finish before showing the next prompt.

## Build

```bash
gcc alpha.c -o alpha
```

Or, if you add a Makefile:

```bash
make
```

## Run

```bash
./alpha
```

You'll see a prompt showing your current directory:

```
/home/yourname$
```

## Example Usage

```
/home/yourname$ ls
/home/yourname$ cd Documents
/home/yourname/Documents$ cd ~
/home/yourname$ pwd
/home/yourname$ exit
```

## Project Structure

```
alphashell/
├── alpha.c        # Main source code
├── .gitignore     # Excludes the compiled binary from version control
└── README.md      # This file
```

## Possible Future Improvements

- I/O redirection (`<`, `>`)
- Piping (`|`) between commands
- Command history/logging
- Support for more than 9 arguments per command
- Signal handling (e.g. `Ctrl+C` shouldn't kill the shell itself)

## What I Learned

Building this project helped me understand:
- Process creation and management (`fork`, `execvp`, `wait`)
- How shells track and change working directories (`getcwd`, `chdir`)
- Safe string parsing and tokenizing in C
- Handling environment variables (`getenv("HOME")`) for path expansion

## Author

Built by [Mahtab Alam] as a B.Tech 2nd year project.
