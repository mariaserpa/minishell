/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:58 by vados-sa          #+#    #+#             */
/*   Updated: 2024/08/23 15:45:06 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_data*data)
{
	int		qt_cmd;
	int		**fds;
	pid_t	*id_p;

	qt_cmd = ft_lstsize_mod(data->command);
	fds = create_pipes(qt_cmd);
	if (!fds)
		return (EXIT_FAIL);
	id_p = (pid_t *)ft_calloc((qt_cmd), sizeof(pid_t));
	if (!id_p)
		return (EXIT_FAIL);
	processing(fds, id_p, data);
	free_double_pointer(fds);
	free(id_p);
	return (EXIT_SUCC);
}

void	child_exec(pid_t *id_p, int pos, t_data *data, int **fds)
{
	int	i;
	int	exit_code;

	if (!id_p || pos <= 0 || !data || !fds)
		return ;
	i = 0;
	while (i < pos)
	{
		if (id_p[i] > 0)
		{
			waitpid(id_p[i], &exit_code, 0);
			if (i == pos - 1)
			{
				if (WIFEXITED(exit_code))
					data->exit_status = WEXITSTATUS(exit_code);
				else if (WIFSIGNALED(exit_code))
					data->exit_status = WTERMSIG(exit_code) + 128;
				else
					data->exit_status = -1;
			}
			close_fd(&fds[i][0]);
			close_fd(&fds[i][1]);
		}
		i++;
	}
}

int	processing(int **fds, pid_t *id_p, t_data *data)
{
	t_command	*command;
	int			i;

	if (!fds || !id_p || !data)
		return (EXIT_FAIL); //check necessity
	command = data->command;
	i = 0;
	while (command)
	{
		if (check_if_builtin(command))
		{
			if (process_builtin(fds, i, command, data))
				return (EXIT_FAIL);
		}
		else
		{
			if (process_not_builtin(fds, i, &id_p[i], data))
				return (EXIT_FAIL);
		}
		i++;
		command = command->next;
	}
	child_exec(id_p, i, data, fds);
	return (EXIT_SUCC);
}
