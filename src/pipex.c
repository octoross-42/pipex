/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:38:18 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 20:52:54 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_do_cmd(char *cmd, t_pipex *pipex, char **envp)
{
	char	**argv;

	argv = ft_get_cmd(cmd, pipex->path);
	if (!argv)
	{
		ft_free_until((void **)pipex->path, -1);
		close(pipex->fd1);
		exit(1);
	}
	execve(argv[0], argv, envp);
	ft_printf(STDERR_FILENO, ERR_FAIL, "execve");
	ft_free_until((void **)pipex->path, -1);
	ft_free_until((void **)argv, -1);
	close(pipex->fd1);
	exit(1);
}

int	ft_do_last_cmd(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pid_t	last;
	int		status;

	last = fork();
	if (last == -1)
	{
		ft_printf(STDERR_FILENO, ERR_FAIL, "fork");
		close(STDIN_FILENO);
		ft_free_until((void **)pipex->path, -1);
		while (wait(NULL) != -1)
			;
		return (1);
	}
	if (!last)
		ft_do_cmd(argv[argc - 2], pipex, envp);
	close(STDIN_FILENO);
	waitpid(last, &status, 0);
	while (wait(NULL) != -1)
		;
	ft_free_until((void **)pipex->path, -1);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	if (ft_set_pipex(argc, argv, envp, &pipex))
		return (1);
	i = 0;
	if (pipex.here_doc)
		ft_here_doc(&pipex);
	else
		ft_open_infile(&pipex, argv, &i);
	while (i < pipex.nbr_cmds - 1)
		ft_do_pipe(argv[2 + pipex.here_doc + (i ++)], &pipex, envp);
	if (pipex.fd1 >= 0)
		close(pipex.fd1);
	ft_open_outfile(&pipex, argc, argv);
	return (ft_do_last_cmd(&pipex, argc, argv, envp));
}
