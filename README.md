# C-Shell
A user-defined interactive shell program that can create and manage new processes.

## Overview
C-Shell supports the following features :

1. A prompt that displays username, systemname and current working directory.
2. Builtin Commands: `pwd`, `cd`, `echo`, `ls`, `pinfo`, `history`, `discover`        
3. All other System Commands (with and wihout arguments). This however is not implemented manually and the given shell is emulated.
4. Process management (executing foreground and background) processes.

## Running and exiting the shell
In the source directory

- Run the make command.
- Run ./a.out to start the shell.
- Enter exit to exit the shell.

## Implementation Details

- The directory from which the shell is invoked is the home directory of the shell, represented by `~`.

- C-Shell supports `;` separated list of commands. C-Shell also handles random multiple `tabs` and `spaces` in the command.

- `Prompt` For every next command a prompt of the format `<username@systemname:curr_dir>` is printed.

#### Built-in Commands
1. Apart from basic functionality `cd` command supports multiple flags `.`, `..`, `-`, `~`. More than one command-line arguments are not allowed. `cd` with no flags or arguments cd into home directory.

2. `echo` command displays the line of text/string that is passed as a command line argument.

3. `pwd` command prints the path of the current working directory.

4. `ls` commands with multiple flags `-a`, `-l`, multiple directory/file names. Handles arguments in any order.

5. `pinfo` prints process related information. `pinfo` accepts one command line argument that is PID and prints the process info of the given `PID`. With no command-line arguments, it prints the process info of the `shell program` itself. Process info printed includes, `pid`, `process status`, `virtual memory (in kB)`, `executable path`. `+` in process status signifies that the process is running in `foreground`.  

6. `discover` This is a command used to search  in a given directory. Discover command emulates the basics of the find command. It has optional flags like  -d  searches for all directories and -f ,searches for all files. e.g. is `discover <target_dir> <type_flags> <file_name>`

7. `history` command prints the last `10` commands executed by the shell across all sessions. `history` accepts a positive integer (say `n)` as a command line argument and prints the last n commands executed by the shell across all sessions. At `max`, the shell stores `20` commands in history.


#### System Commands - Foreground and Background Processes

Other than the builtin commands, C-Shell executes all other system commands either in foreground or background. It supports the `&` operator which lets a program run in the background after printing the `pid` of the newly created process. Running a process in background implies that the shell will spawn that process and doesn't wait for the process to exit. It will keep taking other user commands. SeaShell can handle multiple background processes at a time. This implies that your shell will spawn that process and doesn't wait for the process to exit. It will keep taking other user commands. When the background process exits the shell, it display the appropriate message to the user.

### Assumptions:
 - Each command is no longer than 200 characters.
 - There are no more than 200 background processes running at a time.
