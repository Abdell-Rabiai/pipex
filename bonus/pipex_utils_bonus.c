/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:03:11 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:34:09 by arabiai          ###   ########.fr       */
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

void	open_file_in_firstchild(char **argv, char **strs, char **splited_paths)
{
	int	fd_in;

	if (check_heredoc(argv[1]) == 1)
	{
		here_doc_pipex(argv[2]);
		fd_in = open("temp_file", O_RDONLY);
		if (fd_in == -1)
		{
			unlink("temp_file");
			perror("ERROR : here_doc :");
		}
	}
	else
		fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		errorfile_free(0, strs, splited_paths, "no_use");
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	unlink("temp_file");
}

void	redirect_process(int pipe_ends[2])
{
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(pipe_ends[0]);
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
