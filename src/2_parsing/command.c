/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:59:32 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/09/30 12:39:29 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*create_command_node(t_data *data)
{
	t_command	*new_command;

	if (!data->command)
	{
		data->command = ft_calloc(1, sizeof(t_command));
		if (!data->command)
		{
			perror("malloc new command node");
			return (NULL);
		}
		return (data->command);
	}
	else
	{
		new_command = ft_calloc(1, sizeof(t_command));
		if (!new_command)
		{
			perror("malloc new command node");
			return (NULL);
		}
		create_command_list(data, new_command);
		return (new_command);
	}
}

void	create_command_list(t_data *data, t_command *new)
{
	t_command	*last;

	last = ft_lst_last_command(data->command);
	if (!last)
	{
		data->command = new;
		return ;
	}
	last->next = new;
}

static int	fill_argument_node(t_command *cmd_node, t_token *token)
{
	if (ft_strcmp(cmd_node->command, "export") == 0)
	{
		if (handle_export_builtin_arg(cmd_node, token))
			return (EXIT_FAIL);
	}
	else
	{
		if (add_new_list_node(&cmd_node->arguments, token))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCCESS);
}

int	fill_node(t_command *cmd_node, t_token *token, char *flag)
{
	if (!cmd_node)
		return (EXIT_FAIL);
	if (ft_strcmp(flag, "COMMAND") == 0)
	{
		cmd_node->command = ft_strdup(token->value);
		if (!cmd_node->command)
			return (EXIT_FAIL);
		cmd_node->type_quote = token->type_quote;
	}
	else if (ft_strcmp(flag, "FLAG") == 0)
	{
		if (add_new_list_node(&cmd_node->flags, token))
			return (EXIT_FAIL);
	}
	else if (ft_strcmp(flag, "ARGUMENT") == 0)
	{
		if (fill_argument_node(cmd_node, token))
			return (EXIT_FAIL);
	}
	return (EXIT_SUCC);
}

int	add_new_list_node(t_list **lst, t_token *token)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (perror_return_error("malloc new list node"));
	new->content = ft_strdup(token->value);
	if (!new->content)
		return (perror_return_error("ft_strdup new list node"));
	new->type_quote = token->type_quote;
	if (!*lst)
		*lst = new;
	else
		ft_lstadd_back(lst, new);
	return (EXIT_SUCC);
}
