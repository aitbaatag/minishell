# TO DO LIST #
* fix strjoin leaks when used with add_var_to_envs_or_app_modif_exis()
* cd ~ if runned with env -i
* grep eof (no file) => CTRL+C problem
* fix ls >| ls
* echo "'$USER'" ==> '$USER' problem should print 'user name'
* echo hello$USER ==> hellousername
* expand should take char** as argument
* exit builtin
* handle echo/expand
* when removed a parent directory, pwd/oldpwd shall work
* expand isnside heredoc, but not if there is a quote? in delimeter
* clear_history() when copyied ?
* cmd_not found if "unset $PATH"
* (ls) > out -la  ==> syntax error near unexpected token `-la'
* sleep 4 | ls ; sleep 4 || ls
* echo $USER$PATH
* (ls) <Makefile -ls ==> syntax error
* TEST: echo "'$USER' "$USER" "'$USER'""	==>	;'asadiqui' asadiqui $USER;		(only space error)
* TEST: echo '$USER"' ' "$USER" ''""'		==>	;$USER"  "$USER" "";			(only space error)
* TEST: echo "'$USER"""'$USER' "$USER'"		==> ;'asadiqui$USER asadiqui';		(only space error)
* TEST: echo '$'"---$?'$?'$?"?				==> ;$---130'130'130?;				(only space error)
* TEST: echo $'USER'						==> USER (special case)				(only space error)

# TEST CASES TO FIX #
```
```

# TRIVIAL CASES HANDLED ###
```
minishell:~$ (ls) -la (syntax error)

minishell:~$ notfound | (echo "hello " > file0 || ls && ls -la) | grep mini
 
minishell:~$ (echo "hello " > file4 || ls && ls -la) | grep mini

minishell:~$ ((ls && ls -la) | cat | cat) || pwd

CTRL+C ==> exit status 130

echo $ignore?no_status

echo $?status

minishell:~$ sleep 4 || ls (do not exec ls after Ctrl+C)

should execute executable file without ./ initially like lsss
```

# SYNTAX ANALYSIS #
()()			=> error	V
()				=> error	V
(())			=> no_error	V
ls  >| wc 		=> no_error	X
ls > | wc		=> error	V
'utgig'"		=> error	V

# REFERENCES #
- man bash
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/html_node/index.html)
- [Advanced Bash-Scripting Guide](https://linux.die.net/abs-guide/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html)
- [Process Completion Status (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html)
- [Exit status of a child process in Linux](https://www.geeksforgeeks.org/exit-status-child-process-linux/)
- [pipe, fork, dup, exec explained](https://youtu.be/pO1wuN3hJZ4)
- [LeetCode explore - Binary Tree](https://leetcode.com/explore/learn/card/data-structure-tree/)
- [Exit Codes With Special Meanings](https://linux.die.net/abs-guide/exitcodes.html)
- [How Does Bash Parse Quotes](https://stackoverflow.com/questions/74973830/how-does-bash-parse-double-quotes-and-single-quotes)