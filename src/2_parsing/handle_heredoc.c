/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabelo- <mrabelo-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:23:31 by mrabelo-          #+#    #+#             */
/*   Updated: 2024/08/14 15:53:20 by mrabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_all_file(int fd1, char *limiter)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(line) == ft_strlen(limiter)) //CHECK IF THIS LINE IS NECESSARY
		{
			free(line);
			break ;
		}
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd1);
}

int	handle_heredoc(t_data *data)
{
	int	fd[2];

	if (pipe(fd) < 0)
		perror_return_error("heredoc pipe");
	data->input_fd = fd[0];
	get_all_file(fd[1], data->input_value);
	return (EXIT_SUCC);
}

