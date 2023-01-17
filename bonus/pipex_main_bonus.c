/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:28:55 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/17 17:07:56 by arabiai          ###   ########.fr       */
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

void	child_process(char **argv, int pipe_ends[2], char **envp)
{
	int		fd_in;
	char	*path;
	char	**strs;
	char	**splited_splited_paths;

	splited_splited_paths = get_envpath(envp);
	strs = ft_split(argv[2], ' ');
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		errorfile_free(0, strs, splited_splited_paths, "no_use");
	path = get_command_path(splited_splited_paths, strs);
	close(pipe_ends[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(fd_in);
	execve(path, strs, envp);
	exit(EXIT_SUCCESS);
}

// void	child1_process(char **argv, int pipe_ends[2], char **envp)
// {
// 	char	**strs;
// 	int		fd_out;
// 	char	**splited_splited_paths;

// 	splited_splited_paths = get_envpath(envp);
// 	strs = ft_split(argv[3], ' ');
// 	fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd_out < 0)
// 		errorfile_free(1, strs, splited_splited_paths, "no_use");
// 	path = get_command_path(splited_splited_paths, strs);
// 	close(pipe_ends[1]);
// 	dup2(fd_out, STDOUT_FILENO);
// 	dup2(pipe_ends[0], STDIN_FILENO);
// 	close(fd_out);
// 	// execve(path, strs, envp);
// 	execute_cmd(argv, envp);
// 	exit(EXIT_SUCCESS);
// }

void execute_cmd_from_infile(char *infile, char *command, char **envp)
{
	char	**splited_splited_paths;
	char	**strs;
	char	*path;
	int		fd_in;
	
	splited_splited_paths = get_envpath(envp);
	strs = ft_split(command, ' ');
	path = get_command_path(splited_splited_paths, strs);
	fd_in = open(infile, O_CREAT | O_RDONLY);
	if (fd_in < 0)
		errorfile_free(1, strs, splited_splited_paths, "no_use");
	dup2(fd_in, STDIN_FILENO);
	execve(path, strs, envp);	
}

void execute_cmd_to_outfile(char *outfile, char *command, char **envp)
{
	char	**splited_splited_paths;
	char	**strs;
	char	*path;
	int		fd_out;

	splited_splited_paths = get_envpath(envp);
	strs = ft_split(command, ' ');//argv[3]
	fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644); //argv[4]
	if (fd_out < 0)
		errorfile_free(1, strs, splited_splited_paths, "no_use");
	path = get_command_path(splited_splited_paths, strs);
	dup2(fd_out, STDOUT_FILENO);
	execve(path, strs, envp);
}

void execute_cmd_infile_to_outfile(char *infile, char *outfile, char *command, char **envp)
{
	int		fd_out;
	
	fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644); //argv[4]
	if (fd_out < 0)
		perror("ERROR : ");
	dup2(fd_out, STDOUT_FILENO);
	execute_cmd_from_infile(infile, command, envp);
}

void execute_cmd(char *command, char **envp)
{
	execute_cmd_from_infile("/dev/stdin", command, envp);
}

int check_command(char *command, char **envp)
{
	char	**splited_paths;
	char	**strs;
	char	*cmd;
	char	*str;

	strs = ft_split(command, ' '); // strs = "ls" "-a" "-l"
	cmd = ft_strjoin("/", strs[0]); // cmd = /ls
	splited_paths = get_envpath(envp);
	
	if (splited_paths == NULL)
		return (free(cmd),ft_free_split(splited_paths), ft_free_split(strs), 0);
		
	if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
		return (free(cmd), ft_free_split(splited_paths), ft_free_split(strs), 1);
	while (*splited_paths++)
	{
		str = ft_strjoin(*splited_paths, cmd);
		if (access(str, F_OK) == 0)
			return (free(str), 1);
		free(str);
	}
	if (*splited_paths == NULL)
		return (free(cmd), ft_free_split(strs), 0);
	else
		return (free(cmd), ft_free_split(splited_paths), ft_free_split(strs), 1);
}

int	main(int ac, char **argv, char **envp)
{

	return (0);
	
}

