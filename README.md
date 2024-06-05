# TO DO LIST #
* add shell history
* fix syntax analyser
* fix strjoin leaks when used with add_var_to_envs_or_app_modif_exis()
* cd ~ if runned with env -i
* grep eof (no file) => CTRL+C problem
* echo "'$USER'" ==> '$USER' problem should print 'user name'
* echo hello$USER ==> hellousername
* expand should take char** as argument
* syntax quotes
* exit builtin
* handle echo/expand
* when removed a parent directory, pwd/oldpwd shall work
* expand isnside heredoc, but not if there is a quote? in delimeter
* clear_history() when copyied ?
* cmd_not found if "unset $PATH"
* (ls) > out -la  ==> syntax error near unexpected token `-la'
* sleep 4 | ls ; sleep 4 || ls
* should execute execute wthout ./ like lsss 

# TEST CASES TO FIX #
```
minishell:~$ notfound | (echo "hello " > file0 || ls && ls -la) | grep mini
 
minishell:~$ (echo "hello " > file4 || ls && ls -la) | grep mini
```

# TRIVIAL CASES HANDLED ###
```
CTRL+C ==> exit status 130

echo ignore?status
➜  minishell git:(main) ✗ cp /bin/ls lsss

echo $?status
```

# REFERENCES #
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/html_node/index.html)
- [Advanced Bash-Scripting Guide](https://linux.die.net/abs-guide/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html)
- [Process Completion Status (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html)
- [Exit status of a child process in Linux](https://www.geeksforgeeks.org/exit-status-child-process-linux/)
- [pipe, fork, dup, exec explained](https://youtu.be/pO1wuN3hJZ4)
- [LeetCode explore - Binary Tree](https://leetcode.com/explore/learn/card/data-structure-tree/)
- [Exit Codes With Special Meanings](https://linux.die.net/abs-guide/exitcodes.html)    