/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:28:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 18:05:40 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_envpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_command_path(char **paths, char **main_cmd, pid_t pid)
{
	int		i;
	char	*str;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", main_cmd[0]);
	if (paths == NULL)
		return (free(cmd), close(pid),
			errorfile_free(3, main_cmd, paths, main_cmd[0]), NULL);
	if (access(main_cmd[0], F_OK | X_OK) == 0)
		return (free(cmd), ft_free_split(paths), main_cmd[0]);
	while (paths[i] != NULL)
	{
		str = ft_strjoin(paths[i], cmd);
		if (access(str, F_OK) == 0)
			break ;
		i++;
		free(str);
	}
	if (paths[i] == NULL)
		return (free(cmd), close(pid),
			errorfile_free(2, main_cmd, paths, main_cmd[0]), NULL);
	else
		return (free(cmd), ft_free_split(paths), str);
}

void	child_process(char **argv, int pipe_ends[2], char **envp, pid_t pid)
{
	int		fd_in;
	char	*path;
	char	**strs;
	char	**splited_paths;

	splited_paths = get_envpath(envp);
	strs = ft_split(argv[2], ' ');
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		close(pid);
		errorfile_free(0, strs, splited_paths, "no_use");
	}
	path = get_command_path(splited_paths, strs, pid);
	close(pipe_ends[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(fd_in);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

void	child1_process(char **argv, int pipe_ends[2], char **envp, pid_t pid)
{
	char	*path;
	char	**strs;
	int		fd_out;
	char	**splited_paths;

	splited_paths = get_envpath(envp);
	strs = ft_split(argv[3], ' ');
	fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close(pid);
		errorfile_free(1, strs, splited_paths, "no_use");
	}
	path = get_command_path(splited_paths, strs, pid);
	close(pipe_ends[1]);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(fd_out);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **argv, char **envp)
{
	pid_t	pid;
	pid_t	pid1;
	int		pipe_ends[2];

	if (ac != 5)
		error_handling(0);
	if (pipe(pipe_ends) == -1)
		error_handling(1);
	pid = fork();
	if (pid == -1)
		error_handling(2);
	if (pid == 0)
		child_process(argv, pipe_ends, envp, pid);
	pid1 = fork();
	if (pid1 == 0)
		child1_process(argv, pipe_ends, envp, pid);
	close(pipe_ends[1]);
	close(pipe_ends[0]);
	while (wait(NULL) != -1)
	{
	}
	return (0);
}
