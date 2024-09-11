# minishell

<p align="center">
  <a href="https://github.com/">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193606493-2969e425-6bad-44ce-97af-89fec62bee22.gif" width=500>
    </picture>
  </a>
</p>

## About

Minishell is the second project of the Unix branch at 42.
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

# minishell 
Minishell is a simple shell project aimed at replicating features of a Unix shell. The project includes various functionalities such as command execution, signal handling, and built-in commands. Below is a guide on how this project was developed and how to use it.

## Table of Contents
1. [Overview](#overview)
2. [The Challenge](#the-challenge)
3. [Features](#features)
4. [Bonus Features](#bonus-features)
5. [Implementations](#implementations)
    - [Frontend](#frontend)
    - [Lexer](#lexer)
    - [Parser](#parser)
6. [Backend](#backend)
7. [Execution Process](#execution-process)
8. [How to Use](#how-to-use)


# Overview
Minishell is a project from 42 School designed to mimic the behavior of a Unix shell. It provides an interactive shell with basic features like command parsing, execution, and redirection. The project was coded in C and aimed at building a deeper understanding of how shells function.

## The Challenge

This project was the biggest one I’ve worked on so far, and it was also the first project I did as part of a team. The goal was to build a small version of bash, but even though we call it "mini," it was still a big project. We had to figure out how bash works—how it takes input, processes commands, and runs them. Here are the key features we built:

- **Prompt**: The shell shows a prompt while waiting for the user to type a command.
- **Command history**: You can access previous commands like in bash.
- **Executable search**: The shell finds and runs programs using either the `PATH` variable or an absolute path.
- **Quote handling**: It properly handles single quotes (`'`) and double quotes (`"`) as bash does.
- **Redirections**: We added support for:
  - `<` to redirect input.
  - `>` to redirect output.
  - `<<` for heredoc (doesn't affect history).
  - `>>` to append output to a file.
- **Pipes**: You can connect commands with `|` to pass the output of one command to another.
- **Environment variables**: The shell can use and modify environment variables.
- **Exit status**: It handles `$?`, which shows the exit status of the last command.
- **Signal handling**: `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` work like they do in bash (e.g., `Ctrl+C` stops the current process).
- **Built-in commands**: We re-implemented several bash built-ins:
  - `echo` with support for `-n`.
  - `cd` to change directories with relative or absolute paths.
  - `pwd` to show the current directory (no options needed).
  - `export` to set environment variables (no options).
  - `unset` to remove environment variables (no options).
  - `env` to print environment variables (no options).
  - `exit` to quit the shell (no options).

### Bonus Features
- **Subshells**: We added support for parentheses `()` to run commands in a subshell.
- **Logical operators**: We implemented `&&` and `||` for conditional execution of commands.

## Implementations

### Frontend

### Lexer

The lexer (lexical analyzer) is a crucial component of the shell that processes input text and breaks it down into tokens. These tokens are essential for the parser to understand and execute commands. The lexer performs the following key tasks:

1. **Tokenization**: Reads the input command string and divides it into meaningful units, called tokens.
2. **Token Classification**: Classifies each token into one of the predefined types to assist the parser in understanding its role within the command.

### Lexer

The lexer (lexical analyzer) is a crucial component of the shell that processes input text and breaks it down into tokens. These tokens are essential for the parser to understand and execute commands. The lexer performs the following key tasks:

1. **Tokenization**: Reads the input command string and divides it into meaningful units, called tokens.
2. **Token Classification**: Classifies each token into one of the predefined types to assist the parser in understanding its role within the command.

#### Token Types

The lexer supports the following token types:

- **WORD**: Represents a sequence of characters that form a word or command.
- **PIPE**: Denotes a pipe symbol (`|`) used to connect the output of one command to the input of another.
- **INPUT_REDIRECTION**: Handles input redirection using the `<` symbol.
- **OUTPUT_REDIRECTION**: Handles output redirection using the `>` symbol.
- **APPEND_REDIRECTION**: Handles output redirection in append mode using the `>>` symbol.
- **HEREDOC**: Represents a heredoc redirection, which allows for multi-line input redirection using `<<`.
- **AND**: Represents the logical AND operator (`&&`) used for conditional command execution.
- **OR**: Represents the logical OR operator (`||`) used for conditional command execution.
- **OPENING_PARENTHESES**: Represents an opening parenthesis (`(`) used for grouping commands or creating subshells.
- **CLOSING_PARENTHESES**: Represents a closing parenthesis (`)`) used for grouping commands or closing subshells.
- **WHITE_SPACE**: Represents any whitespace character used to separate tokens.

The role of the lexer is to accurately identify and categorize these tokens to facilitate the subsequent parsing and execution phases of the shell.

#### Token Structure

The lexer uses the following structure to represent and manage tokens:

```c
typedef struct s_token
{
    t_token_type    type;    // The type of the token (e.g., WORD, PIPE, INPUT_REDIRECTION)
    char            *value;  // The actual text value of the token
    struct s_token  *next;   // Pointer to the next token in the list
    struct s_token  *prev;   // Pointer to the previous token in the list
}   t_token;
```
### Parser

The parser builds an Abstract Syntax Tree (AST) from the tokens provided by the lexer. The AST represents the syntactic structure of the command input and helps in executing commands by organizing them into a hierarchical structure. The parser uses several data structures to model different aspects of the command input.

#### Data Structures

Here are the key data structures used in the parser:

```c
// Base structure for tokens in the AST
typedef struct s_tree
{
    t_token_type type; // The type of the token (e.g., WORD, PIPE)
} t_tree;

// Structure for handling pipe commands
typedef struct s_pipecmd
{
    t_token_type type; // The type of the token (PIPE)
    t_tree       *left; // Left subtree (command before the pipe)
    t_tree       *right; // Right subtree (command after the pipe)
} t_pipe;

// Structure for execution commands with arguments and redirections
typedef struct s_exec
{
    t_token_type type; // The type of the token (e.g., WORD)
    char         *line; // The command line string
    char         **args; // Array of arguments for the command
    t_tree       *child_redi; // Child node for redirection details
    struct s_env *env; // Environment variables for the command
} t_exec;

// Structure for logical commands with operators such as && and ||
typedef struct s_logiccmd
{
    t_token_type type; // The type of the token (AND/OR)
    t_tree       *left; // Left subtree (command before the logical operator)
    t_tree       *right; // Right subtree (command after the logical operator)
} t_logic;

// Structure for redirection commands (input/output)
typedef struct s_redcmd
{
    t_token_type type; // The type of the token (INPUT_REDIRECTION/OUTPUT_REDIRECTION)
    int          infile; // File descriptor for input redirection
    int          outfile; // File descriptor for output redirection
    char         *file_name; // Name of the file used in redirection
    char         *dlmt; // Delimiter for heredoc redirection
    int          flags; // Flags for redirection modes (e.g., append mode)
    t_tree       *exec_child; // Child node with execution details
    struct s_redcmd *next; // Pointer to the next redirection command
    struct s_redcmd *prev; // Pointer to the previous redirection command
} t_redi_exec;

// Structure for grouped commands and outer redirections
typedef struct s_grouped_commands
{
    t_token_type type; // The type of the token (GROUPED_COMMAND)
    t_tree       *child; // Child node (grouped command)
    t_tree       *outer_redir; // Outer redirection details
} t_grp_exec;
```
## Backend

### Executor

1. File Descriptor Management:
  - Before executing commands, the shell saves the original file descriptors 
    for standard input (stdin) and output (stdout).
  - After command execution, these file descriptors are restored to ensure 
    the shell’s I/O remains intact.

2. Recursive Execution of the Command Tree:
  - Execution starts by traversing the Abstract Syntax Tree (AST), which is built 
    by the parser from tokens generated by the lexer.
  - The 'executer' function initiates the process, recursively traversing 
    AST nodes and executing commands at each level.
  - The 'ft_run_node' function determines the node type (e.g., pipe, command, 
    logic operator) and calls the appropriate function to handle it.
  - This recursive traversal ensures the shell can handle complex nested structures 
    (e.g., pipelines, subshells, and logical operators like AND/OR) by breaking 
    them down and executing each component in sequence.

3. Command Types:
  - Pipes (PIPE):
    * Handled by the 'run_pipe' function, which manages connecting the output 
      of one command to the input of another through pipes.

  - Subshells (SUBSHELL):
    * Executed in a new process using the 'run_subshell' function.

  - Executable Commands (EXEC):
    * Managed by the 'run_cmd' function, which handles both built-in and external 
      commands. It also takes care of input/output redirections.

  - Logical Operators (AND, OR):
    * Managed by the 'run_logic' function, which executes commands based on 
      logical conditions (AND/OR).

  - Redirections (INPUT_REDIRECTION, OUTPUT_REDIRECTION, etc.):
    * Managed by 'run_redir' and 'set_type_redi', these functions handle changing 
      file descriptors for input/output redirection.

4. Redirection Handling:
  - The shell modifies standard input/output to/from files when handling redirections. 
    This is done by opening the specified file and adjusting the relevant file descriptor.

5. Error Handling:
  - Errors such as "command not found", permission issues, or attempting to execute 
    directories are handled gracefully. The shell sets appropriate exit statuses 
    and displays error messages to the user.
      
##### Example 1:
```sh
> (export A=123) && echo $A

Output:

```
Command: (export A=123) && echo $A

1. Subshell Execution:
   - The command within parentheses `(export A=123)` is executed in a subshell.
   - The 'run_subshell' function is responsible for forking a new process, where the 
     'export' command sets the variable `A` to `123`. However, this change is isolated 
     to the subshell, meaning it won’t affect the parent shell environment.

2. Logical AND Execution:
   - After the subshell completes, the result of the subshell command determines 
     whether the second command (`echo $A`) should be executed.
   - The 'run_logic' function checks the exit status of the subshell:
     * If the exit status is `0` (success), the right-hand command (`echo $A`) will run.
     * Otherwise, the right-hand command is skipped.

3. Environment Variable Expansion:
   - The second command (`echo $A`) is executed in the parent shell.
   - Before executing, the shell performs variable expansion:
     * The shell looks for `A` in its environment.
     * Since the `export A=123` was run in a subshell, the parent shell’s environment 
       does not contain `A`, and `$A` is expanded to an empty string.

4. Command Execution:
   - The shell runs the `echo` command with an empty argument (`echo ""`), 
     and as a result, it outputs an empty line.

5. Result:
  - Since the environment variable `A` was set in a subshell, it does not persist 
    to the parent shell, and the final output of `echo $A` is an empty line.
## How to Use
### Clone the repository:
``` 
git clone https://github.com/aitbaatag/minishell.git
cd minishell
make
```
### Run Minishell
```
./minishell
```
### Test some basic commands
You can start testing the functionality of the shell by trying the following commands:
```
$ echo Hello, World!
Hello, World!

$ export NAME=Minishell
$ echo $NAME
Minishell

$ ls | grep .c
minishell.c
lexer.c
parser.c
executor.c
```
```
ls -la | grep a | tr 'a-z' 'A-Z'
```

```
cat << EOF > file
cat file
rm file
```

```
ls | rev > file
cat file
rev file | cat
rm file
```

*to exit the program:*
```
exit
```

# Liked it?

Hope you liked this project, don't forget to give it a star ⭐.
<a href="https://github.com/aitbaatag/minishell.git">
</a>
