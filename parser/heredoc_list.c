#include "../include/parser.h"
#include <stdio.h>

// void	read_from_user(char *delimiter, t_redi_exec *node_heredoc, int i, int flag)
// {
// 	char	*line;
// 	char	*path_tmp_file;
// 	int		n;

// 	(void)flag;
// 	n = -1;
// 	path_tmp_file = ft_strjoin("/tmp/.here_doc", ft_itoa(i));
// 	node_heredoc->infile = open(path_tmp_file,
// 			O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0666);
// 	if (node_heredoc->infile == -1)
// 	{
// 		perror("open");
// 		return ;
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		// if (!flag)
// 		// 	expand(&line);
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(node_heredoc->infile, line, ft_strlen(line));
// 		write(node_heredoc->infile, "\n", 1);
// 		free(line);
// 	}
// 	close(node_heredoc->infile);
// 	node_heredoc->file_name = ft_strdup(path_tmp_file);
// 	free(path_tmp_file);
// }
// t_redi_exec	*creat_list_heredoc(t_token *tokens)
// {
// 	t_token		*ptr_token;
// 	t_redi_exec	*list_heredoc;
// 	t_redi_exec	*last_node;
// 	t_redi_exec	*new_node;
// 	int			i;
// 	char		*delimiter;
// 	int flag;

// 	flag = 0;
// 	i = 0;
// 	list_heredoc = NULL;
// 	ptr_token = tokens;
// 	while (ptr_token)
// 	{
// 		if (ptr_token->type == HEREDOC)
// 		{
// 			if (ptr_token->next->value[0] == '\'')
// 				flag = 1;
// 			delimiter = remove_quotes(ptr_token->next->value);
// 			new_node = new_node_here_doc(HEREDOC);
// 			read_from_user(delimiter, new_node, i, flag);
// 			free(delimiter);
// 			if (!list_heredoc)
// 				list_heredoc = new_node;
// 			else
// 			{
// 				last_node->next = new_node;
// 				new_node->prev = last_node;
// 			}
// 			last_node = new_node;
// 		}
// 		else if (ptr_token->type & PARN || ptr_token->type & PIPE || ptr_token->type & LOGICAL)
// 		i++;
// 		ptr_token = ptr_token->next;
// 	}
// 	while (list_heredoc && list_heredoc->next)
// 		list_heredoc = list_heredoc->next;
// 	return (list_heredoc);
// }
void	open_file(char *path, t_redi_exec *node_heredoc)
{
	node_heredoc->infile = open(path, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC,
			0666);
	if (node_heredoc->infile == -1)
	{
		perror("open");
		return ;
	}
}

int	write_to_file(char *line, t_redi_exec *node_heredoc, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	write(node_heredoc->infile, line, ft_strlen(line));
	write(node_heredoc->infile, "\n", 1);
	free(line);
	return (1);
}

void	read_from_user(char *delimiter, t_redi_exec *node_heredoc, int i,
		int flag)
{
	char	*line;
	char	*path_tmp_file;
	int		break_;

	break_ = 1;
	(void)flag;
	path_tmp_file = ft_strjoin("/tmp/.here_doc", ft_itoa(i));
	open_file(path_tmp_file, node_heredoc);
	while (break_)
	{
		line = readline("> ");
		if (!line)
			break ;
		break_ = write_to_file(line, node_heredoc, delimiter);
	}
	close(node_heredoc->infile);
	node_heredoc->file_name = ft_strdup(path_tmp_file);
	free(path_tmp_file);
}

void	process_token(t_token *ptr_token, t_redi_exec **list_heredoc,
		t_redi_exec **last_node, int *i)
{
	char		*delimiter;
	t_redi_exec	*new_node;
	int			flag;

	flag = 0;
	if (ptr_token->type == HEREDOC)
	{
		delimiter = remove_quotes(ptr_token->next->value);
		new_node = new_node_here_doc(HEREDOC);
		read_from_user(delimiter, new_node, *i, flag);
		free(delimiter);
		if (!*list_heredoc)
			*list_heredoc = new_node;
		else
		{	
			(*last_node)->next = new_node;
			new_node->prev = *last_node;
		}
		*last_node = new_node;
	}
	else if (ptr_token->type & PARN || ptr_token->type & PIPE
			|| ptr_token->type & LOGICAL)
		(*i)++;
}

t_redi_exec	*creat_list_heredoc(t_token *tokens)
{
	t_token *ptr_token;
	t_redi_exec *list_heredoc = NULL;
	t_redi_exec *last_node = NULL;
	int i;

	i = 0;
	ptr_token = tokens;
	while (ptr_token)
	{
		process_token(ptr_token, &list_heredoc, &last_node, &i);
		ptr_token = ptr_token->next;
	}
	while (list_heredoc && list_heredoc->next)
		list_heredoc = list_heredoc->next;
	return (list_heredoc);
}