/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:14:46 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/10/05 18:35:14 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_list
{
	char			*content;
	int				type_quote;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char			*value;
	char			*type;
	int				type_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*command;
	int					type_quote;
	t_list				*arguments;
	t_list				*flags;
	struct s_command	*next;
	char				**final_av;
}	t_command;

typedef struct s_fd_node
{
	int					fd;
	struct s_fd_node	*next;
}	t_fd_node;

typedef struct s_data
{
	char		*args;
	char		**env;
	char		*path;
	int			input_fd;
	char		*input_type;
	int			input_type_quote;
	char		*input_value;
	int			output_fd;
	char		*output_type;
	int			output_type_quote;
	char		*output_value;
	int			exit_status;
	int			saved_stdin;
	int			saved_stdout;
	int			**fds;
	pid_t		*id_p;
	t_token		*token;
	t_command	*command;
	t_fd_node	*open_fds;
}	t_data;

#endif
