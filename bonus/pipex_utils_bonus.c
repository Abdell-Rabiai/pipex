/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:03:11 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/18 18:16:45 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_file_in_firstchild(char **argv, char **strs, char **splited_paths)
{
	int	fd_in;

	if (check_heredoc(argv[1]) == 1)
	{
		here_doc_pipex(argv[2]);
		fd_in = open("file_stdout", O_RDONLY);
	}
	else
	{
		fd_in = open(argv[1], O_RDONLY);
	}
	if (fd_in < 0)
		errorfile_free(0, strs, splited_paths, "no_use");
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	main_pipex(int ac, char **argv, char **envp, int pipe_ends[2])
{
	int		i;
	pid_t	pid;

	i = 1 + check_heredoc(argv[1]);
	while (i < ac - 1)
	{
		if (pipe(pipe_ends) == -1)
			error_handling(1);
		pid = fork();
		if (pid == -1)
			error_handling(2);
		else if (pid == 0)
		{
			if (i == 1 || (check_heredoc(argv[1]) && i == 2))
				first_child_process(argv, pipe_ends, envp);
			else if (i == ac - 2)
				last_child_process(argv, ac, envp);
			inter_process(argv[i], pipe_ends, envp);
		}
		wait(NULL);
		redirect_process(pipe_ends);
		i++;
	}
	closepipe_waitall(pipe_ends, pid);
}

void	closepipe_waitall(int pipe_ends[2], pid_t pid)
{
	if (pid != 0)
	{
		close(pipe_ends[1]);
		close(pipe_ends[0]);
		while (wait(NULL) != -1)
		{
		}
	}
}
