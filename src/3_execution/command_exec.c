/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:41:00 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/09 11:45:59 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_command *cmd, t_data *data, int pos)
{
	handle_redirect_and_exit(data, pos);
	close_unused_fd(data->fds, pos, FD_RW, ft_lstsize_mod(data->command));
	execute_command(cmd, data);
	free_everything(data);
	exit(data->exit_status);
}

int	process_not_builtin(int pos, t_data *data)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = data->command;
	while (cmd && i < pos)
	{
		cmd = cmd->next;
		i++;
	}
	data->id_p[pos] = fork();
	if (data->id_p[pos] < 0)
		return (EXIT_FAIL);
	if (data->id_p[pos] == 0)
		child_process(cmd, data, pos);
	return (EXIT_SUCC);
}

static int	validate_command(t_command *cmd, t_data *data)
{
	if (!cmd || !cmd->command || ft_strlen(cmd->command) == 0)
	{
		data->exit_status = 0;
		return (1);
	}
	return (0);
}

static void	exec_with_path(t_command *cmd, t_data *data)
{
	DIR	*dir;

	if (access(cmd->command, F_OK) == 0)
	{
		dir = opendir(cmd->command);
		if (dir)
		{
			closedir(dir);
			pe_status(data, cmd->command, ": Is a directory", 126);
			exit(data->exit_status);
		}
		if (access(cmd->command, X_OK) != 0)
		{
			pe_status(data, cmd->command, ": Permission denied", 126);
			exit(data->exit_status);
		}
		data->exit_status = execve(cmd->command, cmd->final_av, data->env);
	}
	else
		pe_status(data, cmd->command, ": No such file or directory", 127);
}

void	execute_command(t_command *cmd, t_data *data)
{
	char	*path;

	if (validate_command(cmd, data))
		return ;
	path = NULL;
	if (ft_strchr(cmd->command, '/'))
		exec_with_path(cmd, data);
	else
	{
		if (data->env)
			path = get_cmd_path(cmd, data->env);
		if (path)
			data->exit_status = execve(path, cmd->final_av, data->env);
		else
			pe_status(data, cmd->command, ": command not found", 127);
	}
	free(path);
	free_everything(data);
	exit(data->exit_status);
}
