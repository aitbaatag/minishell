#include "../include/parser.h"
#include <stdio.h>

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
	if (!line)
		return (1);
	if (ft_strcmp(line, delimiter) == 0)
		return (0);
	write(node_heredoc->infile, line, ft_strlen(line));
	write(node_heredoc->infile, "\n", 1);	
	return (1);
}

void	read_from_user(char *delimiter, t_redi_exec *node_heredoc, int i,
		int flag)
{
	char	*line;
	char	*path_tmp_file;
	int		break_;
	char **line_split;

	break_ = 1;
	path_tmp_file = ft_strjoin("/tmp/.here_doc", ft_itoa(i));
	open_file(path_tmp_file, node_heredoc);
	while (break_)
	{
		line = readline("> ");
		signal(SIGINT, heredoc_handler);
		if (!line)
		{
			// heredoc_eof();
			break ;
		}
		line_split = ft_split(line, '\0');
		if (!flag)
			expand(line_split, 1);
		break_ = write_to_file(line_split[0], node_heredoc, delimiter);
		add_garbage_node(&global.garbage_list ,new_garbage_node(line));
	}
	close(node_heredoc->infile);
	node_heredoc->file_name = ft_strdup(path_tmp_file);
}

void	process_token_here_doc(t_token *ptr_token, t_redi_exec **list_heredoc,
		t_redi_exec **last_node, int *i)
{
	char		*delimiter;
	t_redi_exec	*new_node;
	int			flag;

	flag = 0;
	if (ptr_token->type == HEREDOC)
	{
		if (!check_expand(ptr_token->next->value))
			flag = 1;
		delimiter = remove_quotes(ptr_token->next->value);
		new_node = new_node_here_doc(HEREDOC);
		read_from_user(delimiter, new_node, *i, flag);
		if (!*list_heredoc)
			*list_heredoc = new_node;
		else
		{
			(*last_node)->next = new_node;
			new_node->prev = *last_node;
		}
		*last_node = new_node;
	(*i)++;
	}
}

t_redi_exec	*creat_list_heredoc(t_token *tokens)
{
	t_token *ptr_token;
	t_redi_exec *list_heredoc;
	t_redi_exec *last_node;
	int i;

	i = 0;
	list_heredoc = NULL;
	last_node = NULL;
	ptr_token = tokens;
	while (ptr_token)
	{
		process_token_here_doc(ptr_token, &list_heredoc, &last_node, &i);
		ptr_token = ptr_token->next;
	}
	while (list_heredoc && list_heredoc->next)
		list_heredoc = list_heredoc->next;
	return (list_heredoc);
}
