/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:34:25 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:23:19 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(s1 + i) - *(s2 + i));
		else
			i++;
	}
	return (0);
}

int	check_heredoc(char *str)
{
	if (ft_strncmp(str, "here_doc", 8) == 0 && str[8] == '\0')
		return (1);
	else
		return (0);
}

void	here_doc_pipex(char *limiter)
{
	char	*str;
	char	*lim;
	int		fd;

	fd = open("temp_file", O_CREAT | O_RDWR | O_TRUNC, 777);
	if (fd < 0)
		perror("ERROR : here_doc");
	lim = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_printf("pipe heredoc> ");
		str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str, lim, ft_strlen(str)) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(lim);
}

void	redirect_process(int pipe_ends[2])
{
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(pipe_ends[0]);
}
