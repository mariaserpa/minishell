/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg_for_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:06 by vados-sa          #+#    #+#             */
/*   Updated: 2024/09/30 12:45:24 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_quotes(t_command *cmd_node)
{
	t_list	*lst_arg;
	int		quote_count;
	int		i;
	char	quote;

	quote_count = 0;
	i = 0;
	quote = '\0';
	lst_arg = ft_lst_last(cmd_node->arguments);
	while (lst_arg->content[i] != '\'' && lst_arg->content[i] != '\"')
	{
		if (lst_arg->content[i + 1] == '\'' || lst_arg->content[i + 1] == '\"')
			quote = lst_arg->content[i + 1];
		i++;
	}
	if (quote != '\0')
	{
		while (lst_arg->content[i])
		{
			if (lst_arg->content[i] == quote)
				quote_count++;
			i++;
		}
	}
	return (quote_count % 2 != 0);
}

char	*get_equal_sign_pos(t_command *cmd_node)
{
	t_list	*ptr;
	char	*equal_pos;

	ptr = cmd_node->arguments;
	while (ptr->next)
		ptr = ptr->next;
	if (!ptr || !ptr->content)
	{
		printf("Pointer or content is NULL\n");
		return (NULL);
	}
	equal_pos = ft_strchr(ptr->content, '=');
	if (!equal_pos)
		return (NULL);
	return (equal_pos);
}

int	concat_args(t_command *cmd_node, t_token *token, int *add_new_node)
{
	t_list	*current_arg;
	char	*temp;

	current_arg = cmd_node->arguments;
	while (current_arg->next)
		current_arg = current_arg->next;
	temp = ft_concat_three_str(current_arg->content, " ", token->value);
	if (!temp)
		return (EXIT_FAIL);
	free (current_arg->content);
	current_arg->content = temp;
	closed_quote(temp, add_new_node);
	return (EXIT_SUCC);
}

int	handle_export_builtin_arg(t_command *cmd_node, t_token *token)
{
	char		*equal_pos;
	static int	add_new_node;

	if (!cmd_node->arguments || add_new_node == 1)
	{
		add_new_list_node(&cmd_node->arguments, token);
		equal_pos = get_equal_sign_pos(cmd_node);
		if (equal_pos && equal_pos[1])
			closed_quote((equal_pos + 1), &add_new_node);
	}
	else
	{
		equal_pos = get_equal_sign_pos(cmd_node);
		if (equal_pos && *(equal_pos + 1) && open_quotes(cmd_node))
		{
			if (concat_args(cmd_node, token, &add_new_node))
				return (EXIT_FAIL);
		}
		else
		{
			add_new_list_node(&cmd_node->arguments, token);
			add_new_node = 0;
		}
	}
	return (EXIT_SUCC);
}
