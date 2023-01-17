/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:42:19 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/14 21:03:39 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen(const char *str);
int		ft_printf(const char *string_format, ...);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_how_many_words(const char *s, char c);
char	**ft_free_split(char **strings);
int		ft_get_length_of_word(const char *s, char c);
char	*return_the_first_word(const char *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

void	error_handling(int x);
void	errorfile_free(int x, char **strs, char **splited_paths, char *cmd);

#endif