/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:28:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:29:03 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*get_command_path(char **splited_paths, char **command)
{
	int		i;
	char	*str;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", command[0]);
	if (splited_paths == NULL)
		return (free(cmd),
			errorfile_free(3, command, splited_paths, command[0]), NULL);
	if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (free(cmd), ft_free_split(splited_paths), command[0]);
	while (splited_paths[i] != NULL)
	{
		str = ft_strjoin(splited_paths[i], cmd);
		if (access(str, F_OK) == 0)
			break ;
		i++;
		free(str);
	}
	if (splited_paths[i] == NULL)
		return (free(cmd),
			errorfile_free(2, command, splited_paths, command[0]), NULL);
	else
		return (free(cmd), ft_free_split(splited_paths), str);
}

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

int	main(int ac, char **argv, char **envp)
{
	int	pipe_ends[2];

	if (ac < 5 || (check_heredoc(argv[1]) && ac < 6))
		error_handling(0);
	main_pipex(ac, argv, envp, pipe_ends);
	return (0);
}
