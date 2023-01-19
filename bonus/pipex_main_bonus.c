/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:28:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:33:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_process(char **argv, int pipe_ends[2], char **envp)
{
	char	*path;
	char	**strs;
	char	**splited_paths;

	splited_paths = get_envpath(envp);
	if (check_heredoc(argv[1]) == 1)
		strs = ft_split(argv[3], ' ');
	else
		strs = ft_split(argv[2], ' ');
	open_file_in_firstchild(argv, strs, splited_paths);
	path = get_command_path(splited_paths, strs);
	close(pipe_ends[0]);
	dup2(pipe_ends[1], STDOUT_FILENO);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

void	last_child_process(char **argv, int ac, char **envp)
{
	int		fd_out;
	char	*path;
	char	**strs;
	char	**splited_splited_paths;

	splited_splited_paths = get_envpath(envp);
	strs = ft_split(argv[ac - 2], ' ');
	fd_out = open(argv[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
		errorfile_free(1, strs, splited_splited_paths, "no_use");
	path = get_command_path(splited_splited_paths, strs);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

void	inter_process(char *argv_cmd, int pipe_ends[2], char **envp)
{
	char	*path;
	char	**strs;
	char	**splited_splited_paths;

	splited_splited_paths = get_envpath(envp);
	strs = ft_split(argv_cmd, ' ');
	path = get_command_path(splited_splited_paths, strs);
	close(pipe_ends[0]);
	dup2(pipe_ends[1], STDOUT_FILENO);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

void	main_pipex(int ac, char **argv, char **envp, int pipe_ends[2])
{
	int		i;
	pid_t	pid;

	i = 2 + check_heredoc(argv[1]);
	while (i < ac - 1)
	{
		if (pipe(pipe_ends) == -1)
			error_handling(1);
		pid = fork();
		if (pid == -1)
			error_handling(2);
		else if (pid == 0)
		{
			if (i == 2 || (check_heredoc(argv[1]) && i == 3))
				first_child_process(argv, pipe_ends, envp);
			else if (i == ac - 2)
				last_child_process(argv, ac, envp);
			inter_process(argv[i], pipe_ends, envp);
		}
		if (check_heredoc(argv[1]))
			wait(NULL);
		redirect_process(pipe_ends);
		i++;
	}
	closepipe_waitall(pipe_ends, pid);
}

int	main(int ac, char **argv, char **envp)
{
	int	pipe_ends[2];

	if (ac < 5 || (check_heredoc(argv[1]) && ac < 6))
		error_handling(0);
	main_pipex(ac, argv, envp, pipe_ends);
	return (0);
}
