#include "../include/minishell.h"

int set_type_redi(t_tree *redi)
{
    t_redi_exec *redi_exec;

    redi_exec = (t_redi_exec *)redi;
    if (redi_exec)
    {
        if (redi->type == INPUT_REDIRECTION)
            return (handle_redir_input((t_redi_exec *)redi));
        else if (redi->type == OUTPUT_REDIRECTION)
            return (handle_redir_output((t_redi_exec *)redi));
        else if (redi->type == APPEND_REDIRECTION)
            return (handle_redir_output((t_redi_exec *)redi));
        else if (redi->type == HEREDOC)
            return (handle_redir_input((t_redi_exec *)redi));
    }
    return (EXIT_SUCCESS);
}

// int	handle_redir_input(t_redi_exec *redi)
// {
//     int fd;

//     if (!redi)
//         return (EXIT_SUCCESS);
//     set_type_redi((t_tree *)redi->exec_child);
//     if (redi->type == HEREDOC)
//         fd = open(redi->file_name, O_RDONLY);
//     else
//         fd = open(redi->file_name, redi->flags, 0644);

//     if (fd == -1)
//     {
//         perror(redi->file_name);
// 		return (set_exit_status(1), get_exit_status());
//     }
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         perror("dup2");
//         close(fd);
//         return (set_exit_status(1), get_exit_status());
//     }
//     close (fd);
// 	return (set_exit_status(0), get_exit_status());
// }

// int	handle_redir_output(t_redi_exec *redi)
// {
//     int fd;

//     if (!redi)
//         return (EXIT_SUCCESS);
//     // global.stdout = dup(STDOUT_FILENO);
//     set_type_redi((t_tree *)redi->exec_child);
//     fd = open(redi->file_name, redi->flags, 0644);
//     if (fd == -1)
//     {
//         perror(redi->file_name);
//         return (set_exit_status(1), get_exit_status());
// 	}
//     if (dup2(fd, STDOUT_FILENO) == -1)
//     {
//         perror("dup2");
//         close(fd);
//         return (set_exit_status(1), get_exit_status());
//     }

//     close (fd);
// 	return (set_exit_status(0), get_exit_status());
// }
int save_and_redirect(int old_fd, int new_fd)
{
    int saved_fd;

    saved_fd = dup(old_fd);
    if (saved_fd == -1)
    {
        perror("dup");
        return -1;
    }

    if (dup2(new_fd, old_fd) == -1)
    {
        perror("dup2");
        close(saved_fd);
        return -1;
    }

    close(new_fd);
    return saved_fd;
}

void restore_fd(int old_fd, int saved_fd)
{
    dup2(saved_fd, old_fd);
    close(saved_fd);
}

int handle_redir_input(t_redi_exec *redi)
{
    int fd;

    if (!redi)
        return EXIT_SUCCESS;
    if (set_type_redi((t_tree *)redi->exec_child) != 0)
    {
        return set_exit_status(1), get_exit_status();
    }
    if (redi->type == HEREDOC)
        fd = open(redi->file_name, O_RDONLY);
    else
        fd = open(redi->file_name, redi->flags, 0644);
    if (fd == -1)
    {
        perror(redi->file_name);
        return set_exit_status(1), get_exit_status();
    }
    dup2(fd, STDIN_FILENO);
    close (fd);
    return set_exit_status(0), get_exit_status();
}

int handle_redir_output(t_redi_exec *redi)
{
    int fd;

    if (!redi)
        return EXIT_SUCCESS;
    if (set_type_redi((t_tree *)redi->exec_child) != 0)
    {

        return set_exit_status(1), get_exit_status();
    }
    fd = open(redi->file_name, redi->flags, 0644);
    if (fd == -1)
    {
        perror(redi->file_name);
        return set_exit_status(1), get_exit_status();
    }
    dup2(fd, STDOUT_FILENO);
    close (fd);
    return set_exit_status(0), get_exit_status();
}