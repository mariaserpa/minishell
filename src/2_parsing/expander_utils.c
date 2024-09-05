/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:23:36 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/05 14:53:55 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_len(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (str[1] == '{')
		i++;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '}')
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_exp_env(char *str, int len, char **env_arg)
{
	if (!env_arg)
	{
		printf("Environment variable array is NULL\n");
		return ("");
	}
	while (*env_arg)
	{
		if (!ft_strncmp(str + 1, *env_arg, len) && (*env_arg)[len] == '=')
			return (*env_arg + len + 1);
		env_arg++;
	}
	return ("");
}
