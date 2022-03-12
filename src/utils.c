/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:03:17 by akitty            #+#    #+#             */
/*   Updated: 2022/03/07 15:03:17 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(t_general *general, char *msg)
{
	if (general)
	{
		clear_data(general);
		free(general);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_file(char *filename, int mode)
{
	int	fd;

	if (mode)
	{
		if (access(filename, F_OK) < 0
			|| access(filename, R_OK) < 0)
		{
			write(2, "File isn't found or isn't available for read.\n", 46);
			return (-1);
		}
		fd = open(filename, O_RDONLY);
		if (fd != -1)
			return (fd);
	}
	else
	{
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd > -1)
			return (fd);
	}
	write(2, "Cannot open the file.\n", 22);
	return (-1);
}

char	**get_paths(char **env)
{
	int		i;
	int		len;
	char	**paths;

	while (*env++)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			break ;
		if (!(*env))
			return (NULL);
	}
	paths = ft_split((*env + 5), ':');
	i = -1;
	while (paths[++i])
	{
		len = ft_strlen(paths[i]);
		paths[i][len] = '/';
		paths[i][len + 1] = '\0';
	}
	return (paths);
}

char	*mk_cmd(t_general *general, char *cmd)
{
	char	*temp;
	int		i;

	temp = cmd;
	i = -1;
	if (access(cmd, F_OK) > -1)
		return (cmd);
	while (general->paths[++i])
	{
		cmd = ft_strjoin(general->paths[i], temp);
		if (access(cmd, F_OK) > -1)
			return (cmd);
		free(cmd);
	}
	return (NULL);
}

void	clear_data(t_general *general)
{
	char	**temp;

	if (general->paths)
	{
		temp = general->paths;
		while (*general->paths)
			free(*general->paths++);
		free(temp);
	}
	if (general->cmd1)
	{
		temp = general->cmd1;
		while (*general->cmd1)
			free(*general->cmd1++);
		free(temp);
	}
	if (general->cmd2)
	{
		temp = general->cmd2;
		while (*general->cmd2)
			free(*general->cmd2++);
		free(temp);
	}
}
