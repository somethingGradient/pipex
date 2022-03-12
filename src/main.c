/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:02:13 by akitty            #+#    #+#             */
/*   Updated: 2022/03/07 15:02:14 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(t_general *general, char **env)
{
	close(general->pipe_fds[0]);
	if (dup2(general->pipe_fds[1], STDOUT_FILENO) < 0)
		ft_error(general, "Child dup2 error: ");
	if (dup2(general->infile_fd, STDIN_FILENO) < 0)
		ft_error(general, "Child dup2 error: ");
	if (execve(mk_cmd(general, general->cmd1[0]),
			general->cmd1, env) < 0)
		ft_error(general, "Child execve error: ");
	close(general->infile_fd);
	clear_data(general);
	exit(EXIT_SUCCESS);
}

void	parrent_process(t_general *general, char **env)
{
	close(general->pipe_fds[1]);
	if (dup2(general->pipe_fds[0], STDIN_FILENO) < 0)
		ft_error(general, "Parrent dup2 error");
	if (dup2(general->outfile_fd, STDOUT_FILENO) < 0)
		ft_error(general, "Parrent dup2 error");
	if (execve(mk_cmd(general, general->cmd2[0]),
			general->cmd2, env) < 0)
		ft_error(general, "Parrent execve error");
	close(general->outfile_fd);
}

void	pipex(t_general *general, char **argv, char **env)
{
	pid_t	child;

	general->paths = get_paths(env);
	if (!general->paths)
		ft_error(general, "PATH error");
	general->cmd1 = ft_split(argv[2], ' ');
	general->cmd2 = ft_split(argv[3], ' ');
	if (!general->cmd1 || !general->cmd2)
		ft_error(general, "Command parse error");
	if (pipe(general->pipe_fds) < 0)
		ft_error(general, "Pipe error");
	child = fork();
	if (child < (pid_t) 0)
		ft_error(general, "Fork error");
	if (child == 0)
		child_process(general, env);
	else
	{
		waitpid(child, NULL, 0);
		parrent_process(general, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_general	*general;

	general = NULL;
	if (argc == 5)
	{
		general = (t_general *)malloc(sizeof(*general));
		if (!general)
			ft_error(general, "Malloc error");
		general->paths = NULL;
		general->cmd1 = NULL;
		general->cmd2 = NULL;
		general->infile_fd = open_file(argv[1], 1);
		general->outfile_fd = open_file(argv[argc - 1], 0);
		if (general->infile_fd < 0
			|| general->outfile_fd < 0)
			ft_error(general, "Cannot open files");
		pipex(general, argv, env);
	}
	else
		ft_error(general, "Invalid number of arguments");
	clear_data(general);
	free(general);
	exit(EXIT_SUCCESS);
}
