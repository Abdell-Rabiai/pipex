/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:42:19 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:38:20 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

/*utils split join strnsrt next_line*/
size_t	ft_strlen(const char *str);
int		ft_printf(const char *string_format, ...);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_how_many_words(const char *s, char c);
char	**ft_free_split(char **strings);
int		ft_get_length_of_word(const char *s, char c);
char	*return_the_first_word(const char *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*get_next_line(int fd);

/*commands and envp*/
char	**get_envpath(char **envp);
char	*get_command_path(char **splited_paths, char **command);

/**processss*/
void	first_child_process(char **argv, int pipe_ends[2], char **envp);
void	last_child_process(char **argv, int ac, char **envp);
void	inter_process(char *argv_cmd, int pipe_ends[2], char **envp);
void	main_pipex(int ac, char **argv, char **envp, int pipe_ends[2]);
void	open_file_in_firstchild(char **argv, char **strs, char **splited_paths);
void	closepipe_waitall(int pipe_ends[2], pid_t pid);
void	redirect_process(int pipe_ends[2]);

/*bonu heredoc multiple pipes**/
int		check_heredoc(char *str);
void	here_doc_pipex(char *limiter);
void	main_pipex(int ac, char **argv, char **envp, int pipe_ends[2]);

/**erroars*/
void	error_handling(int x);
void	errorfile_free(int x, char **strs, char **splited_paths, char *cmd);

#endif