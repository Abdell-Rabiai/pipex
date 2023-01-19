/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:45:23 by arabiai           #+#    #+#             */
/*   Updated: 2023/01/19 17:31:15 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_printf("EROOR : infile No sush file or directory\n");
	else if (x == 1)
		ft_printf("EROOR : outfile No sush file or directory\n");
	else if (x == 2)
	{
		ft_printf("ERROR : %s command not found \n", cmd);
		ft_free_split(strs);
		ft_free_split(splited_paths);
	}
	else if (x == 3)
	{
		ft_printf("ERROR : %s command not found : ", cmd);
		ft_printf("All commands not available \n");
		ft_free_split(strs);
		ft_free_split(splited_paths);
	}
	exit(EXIT_FAILURE);
}
