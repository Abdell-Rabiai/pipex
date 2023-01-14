/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:45:23 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/14 21:03:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handling(int x)
{
	if (x == 0)
		ft_printf("EROOR : invalid number of arguments \n");
	else if (x == 1)
		ft_printf("EROOR creating the pipe \n");
	else if (x == 2)
		ft_printf("EROOR forking the process \n");
	exit(EXIT_FAILURE);
}

void	errorfile_free(int x, char **strs, char **splited_paths, char *cmd)
{
	if (x == 0)
		ft_printf("EROOR : opening the infile\n");
	else if (x == 1)
		ft_printf("EROOR : opening the outfile\n");
	else if (x == 2)
		ft_printf("ERROR : %s command not found \n", cmd);
	else if (x == 3)
		ft_printf("ERROR : %s command not found \n", cmd);
	ft_free_split(strs);
	ft_free_split(splited_paths);
	exit(EXIT_FAILURE);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	strjoin = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!strjoin)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		strjoin[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	strjoin[i] = '\0';
	return (strjoin);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	char	*nee;
	size_t	i;
	size_t	j;

	if ((!haystack && !len))
		return (NULL);
	hay = (char *)haystack;
	nee = (char *)needle;
	i = 0;
	j = 0;
	if (nee[j] == '\0')
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		j = 0;
		while (nee[j] == hay[i + j] && hay[i + j] != '\0' && (i + j) < len)
			j++;
		if (nee[j] == '\0')
			return (hay + i);
		i++;
	}
	return (0);
}
