/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:31:34 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 20:52:29 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_do_child(char *cmd, t_pipex *pipex, int *pipes, char **envp)
{
	close(pipes[0]);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		close(pipex->fd1);
		close(pipes[1]);
		ft_exit_with_fail("dup2", pipex->path);
	}
	close(pipes[1]);
	ft_do_cmd(cmd, pipex, envp);
}

void	ft_do_parent(t_pipex *pipex, int *pipes)
{
	close(pipes[1]);
	if (dup2(pipes[0], STDIN_FILENO) == -1)
	{
		close(pipex->fd1);
		close(pipes[0]);
		ft_exit_with_fail("dup2", pipex->path);
	}
	close(pipes[0]);
}

void	ft_do_pipe(char *cmd, t_pipex *pipex, char **envp)
{
	pid_t	pid;
	int		pipes[2];

	if (pipe(pipes) == -1)
	{
		close(pipex->fd1);
		ft_exit_with_fail("pipe", pipex->path);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipex->fd1);
		close(pipes[0]);
		close(pipes[1]);
		ft_exit_with_fail("fork", pipex->path);
	}
	if (!pid)
		ft_do_child(cmd, pipex, pipes, envp);
	ft_do_parent(pipex, pipes);
}
