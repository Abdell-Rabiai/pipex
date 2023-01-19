/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:34:25 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 16:34:57 by arabiai          ###   ########.fr       */
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

