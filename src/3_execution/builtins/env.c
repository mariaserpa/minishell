/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:20:43 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/31 15:41:55 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_env(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->flags || cmd->arguments)
	{
		ft_putstr_fd("minishell: env don't support options or arguments\n", 1); //check if it is 1 or 2
		return (EXIT_FAIL);
	}
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (EXIT_SUCC);
}
