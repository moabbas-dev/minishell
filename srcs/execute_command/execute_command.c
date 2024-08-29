/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfatfat <jfatfat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:31:23 by moabbas           #+#    #+#             */
/*   Updated: 2024/08/06 14:45:43 by jfatfat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_simple_cmd(t_tools *tools, t_parser *parser, char **envp)
{
	pid_t	pid;

	if (parser->builtin != NULL && parser->builtin == builtin_exit)
		printf("exit\n");
	if (parser->builtin != NULL)
		return (set_redirection_and_execute(parser, tools));
	set_execution_signals();
	pid = fork();
	if (pid == 0)
		exec_simple_non_builtin_cmd(tools, parser, envp);
	else
		give_status_value(pid, &(tools->last_exit_status));
	return (tools->last_exit_status);
}

int	exec_full_cmd(t_tools *tools, t_parser *parser, int num_pipes, char **envp)
{
	int		**pipes;
	int		i;
	int		*pids;

	pids = create_forks(num_pipes + 1);
	pipes = create_pipes(num_pipes);
	i = 0;
	if (parser)
		set_execution_signals();
	while (parser)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			assign_pipes_and_redirection(parser, pipes, i, num_pipes);
			exec_full_cmd_in_process(tools, parser, envp);
		}
		else
			(close_parent_pipe(parser, pipes, i));
		parser = parser->next;
		i++;
	}
	wait_pids_and_collect(pids, num_pipes, &(tools->last_exit_status));
	(close_pipes(pipes, num_pipes), free_pipes(pipes, num_pipes), free(pids));
	return (tools->last_exit_status);
}

int	execute_command(t_tools *tools, char **envp)
{
	t_parser	*parser;
	int			num_pipes;
	int			status;

	parser = tools->parser;
	num_pipes = get_parser_len(parser);
	if (num_pipes == 0)
		return (0);
	num_pipes = num_pipes - 1;
	if (num_pipes == 0)
	{
		status = exec_simple_cmd(tools, parser, envp);
		set_signals();
		return (status);
	}
	status = exec_full_cmd(tools, parser, num_pipes, envp);
	set_signals();
	return (status);
}
