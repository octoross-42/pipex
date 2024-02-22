/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:32:18 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 20:46:08 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit_with_fail(char *fail, char **path)
{
	if (fail)
		ft_printf(STDERR_FILENO, ERR_FAIL, fail);
	else
		ft_printf(STDERR_FILENO, ERR_HERE_DOC);
	ft_free_until((void **)path, -1);
	exit (1);
}

void	ft_read_here_doc(t_pipex *pipex, int *pipes)
{
	char	*doc;

	close(pipes[0]);
	doc = gnl_here_doc();
	if (!doc)
	{
		close(pipes[1]);
		ft_exit_with_fail(NULL, pipex->path);
	}
	while (ft_strncmp(doc, pipex->limiter, ft_strlen(pipex->limiter))
		|| (doc[ft_strlen(pipex->limiter)] != '\n'))
	{
		ft_printf(pipes[1], doc);
		free(doc);
		doc = gnl_here_doc();
		if (!doc)
		{
			close(pipes[1]);
			ft_exit_with_fail(NULL, pipex->path);
		}
	}
	free(doc);
	close(pipes[1]);
	ft_free_until((void **)pipex->path, -1);
	exit(0);
}

void	ft_here_doc(t_pipex *pipex)
{
	pid_t	pid;
	int		pipes[2];

	if (pipe(pipes) == -1)
		ft_exit_with_fail("pipe", pipex->path);
	pid = fork();
	if (pid == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		ft_exit_with_fail("fork", pipex->path);
	}
	if (!pid)
		ft_read_here_doc(pipex, pipes);
	close(pipes[1]);
	if (dup2(pipes[0], 0) == -1)
	{
		wait(NULL);
		close(pipes[0]);
		ft_exit_with_fail("dup2", pipex->path);
	}
	close(pipes[0]);
	wait(NULL);
}

void	ft_open_infile(t_pipex *pipex, char **argv, int *i)
{
	int		utility_pipe[2];

	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		perror(argv[1]);
		if (pipe(utility_pipe) == -1)
			ft_exit_with_fail("pipe", pipex->path);
		close(utility_pipe[1]);
		if (dup2(utility_pipe[0], STDIN_FILENO) == -1)
		{
			close(utility_pipe[0]);
			ft_exit_with_fail("dup2", pipex->path);
		}
		close(utility_pipe[0]);
		(*i)++;
	}
	else if (dup2(pipex->fd1, STDIN_FILENO) == -1)
	{
		close(pipex->fd1);
		ft_exit_with_fail("dup2", pipex->path);
	}
}

void	ft_open_outfile(t_pipex *pipex, int argc, char **argv)
{
	int	fd2;

	if (pipex->here_doc)
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		perror(argv[argc - 1]);
		close(STDIN_FILENO);
		ft_free_until((void **)pipex->path, -1);
		while (wait(NULL) != -1)
			;
		exit (1);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		close(STDIN_FILENO);
		close(fd2);
		while (wait(NULL) != -1)
			;
		ft_exit_with_fail("dup2", pipex->path);
	}
	close(fd2);
}
