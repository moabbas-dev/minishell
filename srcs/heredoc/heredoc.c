/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfatfat <jfatfat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:02:46 by moabbas           #+#    #+#             */
/*   Updated: 2024/08/29 10:06:49 by jfatfat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_heredoc_file_and_redirect(char **delimiters, t_tools *tools,
	t_quote_type quote_type, int i)
{
	t_lexer	*heredoc_lex;
	char	*filename;
	char	*file_num;
	int		fd;
	t_lexer	*tmp;

	file_num = ft_itoa(i);
	filename = ft_strjoin(ft_strdup("/tmp/heredoc_tmp.txt_"), file_num);
	heredoc_lex = render_input_to_lexer(delimiters[i]);
	update_heredoc_words(heredoc_lex, tools, quote_type);
	tmp = heredoc_lex;
	fd = open_file(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ((free(filename), free(file_num)), NULL);
	while (tmp)
	{
		ft_putstr_fd(tmp->str, fd);
		tmp = tmp->next;
	}
	(free_lexer(&heredoc_lex), close(fd));
	return (free(file_num), filename);
}

char	*handle_heredoc_case(char **delimiters, t_tools *tools,
	t_quote_type quote_type)
{
	char	*name;
	int		delimiters_count;
	int		i;

	name = NULL;
	delimiters_count = get_delimiters_count(delimiters);
	i = 0;
	set_execution_signals();
	while (i < delimiters_count)
	{
		reset_signals();
		name = create_heredoc_file_and_redirect(delimiters, tools, quote_type,
			i);
		if (i < delimiters_count - 1 && name)
		{
			free(name);
			name = NULL;
		}
		i++;
	}
	return (name);
}
