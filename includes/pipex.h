/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:04:25 by akitty            #+#    #+#             */
/*   Updated: 2022/03/07 15:04:26 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_general
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fds[2];
	char	**paths;
	char	**cmd1;
	char	**cmd2;
}	t_general;

char	*ft_strnstr(const char *big, const char *little, size_t n);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

void	ft_error(t_general *general, char *msg);
int		open_file(char *filename, int mode);
char	**get_paths(char **env);
char	*mk_cmd(t_general *general, char *cmd);
void	clear_data(t_general *general);

#endif
