/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:38:18 by octoross          #+#    #+#             */
/*   Updated: 2024/02/02 23:16:41 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	ft_first_command(t_pipex pipex, char **envp)
// {
// 	char	**argv;
// 	int		fd1;

// 	close(pipex.pipe[0]);
// 	fd1 = open(pipex.file1, O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		ft_free_until(pipex.path, -1);
// 		free(pipex.cmds);
// 		close(pipex.pipe[0]);
// 		close(pipex.pipe[1]);
// 		write(STDERR_FILENO, "bash: ", 6);
// 		perror(pipex.file1);
// 		exit(1);
// 	}
// 	argv = ft_get_cmd(pipex, pipex.cmds[0]);
// 	ft_free_until(pipex.path, -1);
// 	free(pipex.cmds);
// 	if (!argv)
// 	{
// 		close(pipex.pipe[0]);
// 		close(pipex.pipe[1]);
// 		close(fd1);
// 		exit(1);
// 	}
// 	dup2(fd1, STDIN_FILENO);
// 	dup2(pipex.pipe[1], STDOUT_FILENO);
// 	if (execve(argv[0], argv, envp) == -1)
// 	{
// 		write(STDERR_FILENO, ERR_EXEC, strlen(ERR_EXEC));
// 		ft_free_until(argv, -1);
// 		close(fd1);
// 		close(pipex.pipe[1]);
// 		exit(1);
// 	}
// }

// void	ft_do_cmd_ex(int i, t_pipex pipex, char **envp)
// {
// 	char	**argv;
// 	int		fd1;
// 	int		fd2;
// 	int		pid;
// 	// char	c;
// 	int		j;
// 	char	*before_limiter;
// 	int		status;
	
// 	if (i < pipex.nbr_cmds - 1 + pipex.here_doc)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			printf(ERR_FORK);
// 			exit(1);
// 		} //TODO frees
// 		if (pid)
// 			ft_do_cmd(i + 1, pipex, envp);
// 		waitpid(pid, &status, 0);
// 	}
// 	if (i == 0 && pipex.here_doc)
// 	{
// 		j = 0;
// 		while (j < pipex.nbr_cmds - 1 + pipex.here_doc)
// 		{
// 			if (j != i - 1)
// 				close(pipex.pipes[j][0]);
// 			if (j != i)
// 				close(pipex.pipes[j][1]);
// 			j ++;
// 		}
// 		printf("lalallilalalal %d\n", STDIN_FILENO);
// 		before_limiter = get_next_line(STDIN_FILENO);
// 		printf("JEKFJEJDHFJ\n");
// 		while (before_limiter)
// 		{
// 			if (!strncmp(before_limiter, pipex.limiter, strlen(pipex.limiter)))
// 			{
// 				free(before_limiter);
// 				ft_free_until((void **)pipex.path, -1);
// 				free(pipex.cmds);
// 				free(pipex.pipes);
// 				exit(0);
// 			}
// 			write(pipex.pipes[0][1], before_limiter, strlen(before_limiter));
// 			free(before_limiter);
// 			before_limiter = get_next_line(STDIN_FILENO);
// 		}
// 	}
// 	else if (i == 0 && !pipex.here_doc)
// 	{
// 		fd1 = open(pipex.file1, O_RDONLY);
// 		if (fd1 < 0)
// 		{
// 			write(STDERR_FILENO, "bash: ", 6);
// 			perror(pipex.file1);
// 			ft_free_until((void **)pipex.path, -1);
// 			free(pipex.cmds);
// 			free(pipex.pipes);
// 			close(pipex.pipes[0][1]);
// 			exit(1);
// 		}
// 	}
// 	else
// 		fd1 = pipex.pipes[i - 1][0];
// 	if (i == pipex.nbr_cmds - 1 + pipex.here_doc)
// 	{
// 		if (pipex.here_doc)
// 			fd2 = open(pipex.file2, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		else
// 			fd2 = open(pipex.file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		if (fd2 < 0)
// 		{
// 			write(STDERR_FILENO, "bash: ", 6);
// 			perror(pipex.file2);
// 			ft_free_until((void **)pipex.path, -1);
// 			free(pipex.cmds);
// 			free(pipex.pipes);
// 			close(fd1);
// 			exit(1);
// 		}
// 	}
// 	else
// 		fd2 = pipex.pipes[i][1];
// 	// c = '0' + pipex.nbr_cmds;
// 	// write(STDERR_FILENO, "nbr_cmds = ", 11);
// 	// write(STDERR_FILENO, &c, 1);
// 	// write(STDERR_FILENO, "\n", 1);
// 	// c = '0' + i;
// 	// write(STDERR_FILENO, "i = ", 4);
// 	// write(STDERR_FILENO, &c, 1);
// 	// write(STDERR_FILENO, "\n", 1);
// 	// c = '0' + fd1;
// 	// write(STDERR_FILENO, "fd1 = ", 6);
// 	// write(STDERR_FILENO, &c, 1);
// 	// write(STDERR_FILENO, "\n", 1);
// 	// c = '0' + fd2;
// 	// write(STDERR_FILENO, "fd2 = ", 6);
// 	// write(STDERR_FILENO, &c, 1);
// 	// write(STDERR_FILENO, "\n", 1);
// 	argv = ft_get_cmd(pipex, pipex.cmds[i - pipex.here_doc]);
// 	ft_free_until((void **)pipex.path, -1);
// 	free(pipex.cmds);
// 	if (!argv)
// 	{
// 		free(pipex.pipes);
// 		close(fd1);
// 		close(fd2);
// 		exit(1);
// 	}
// 	dup2(fd1, STDIN_FILENO);
// 	dup2(fd2, STDOUT_FILENO);
// 	j = 0;
// 	while (j < pipex.nbr_cmds - 1 + pipex.here_doc)
// 	{
// 		if (j != i - 1)
// 			close(pipex.pipes[j][0]);
// 		if (j != i)
// 			close(pipex.pipes[j][1]);
// 		j ++;
// 	}
// 	execve(argv[0], argv, envp);
// 	write(STDERR_FILENO, ERR_EXEC, strlen(ERR_EXEC));
// 	ft_free_until((void **)argv, -1);
// 	free(pipex.pipes);
// 	close(fd1);
// 	close(fd2);
// 	exit(1);
// }


// void	ft_last_command(t_pipex pipex, char **envp)
// {
// 	char	**argv;
// 	int		fd2;

// 	close(pipex.pipe[1]);
// 	fd2 = open(pipex.file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fd2 == -1)
// 	{
// 		ft_free_until(pipex.path, -1);
// 		free(pipex.cmds);
// 		close(pipex.pipe[0]);
// 		close(pipex.pipe[1]);
// 		write(STDERR_FILENO, "bash: ", 6);
// 		perror(pipex.file2);
// 		exit(1);
// 	}
// 	argv = ft_get_cmd(pipex, pipex.cmds[pipex.nbr_cmds - 1]);
// 	ft_free_until(pipex.path, -1);
// 	free(pipex.cmds);
// 	if (!argv)
// 	{
// 		close(pipex.pipe[0]);
// 		close(pipex.pipe[1]);
// 		close(fd2);
// 		exit(1);
// 	}
// 	dup2(pipex.pipe[0], STDIN_FILENO);
// 	dup2(fd2, STDOUT_FILENO);
// 	if (execve(argv[0], argv, envp) == -1)
// 	{
// 		write(STDERR_FILENO, ERR_EXEC, strlen(ERR_EXEC));
// 		ft_free_until(argv, -1);
// 		close(fd2);
// 		close(pipex.pipe[0]);
// 		exit(1);
// 	}
// }

#include "pipex.h"

void	ft_free_until(void **tab, int index)
{
	int		i;
	char	**strs;

	i = 0;
	while (i < index)
		free(tab[i ++]);
	if (index < 0)
	{
		strs = (char **)tab;
		while (strs[i])
			free(strs[i ++]);
	}
	free(tab);
}

char	*ft_path_of(char const *path, char const *cmd)
{
	size_t	len;
	size_t	i;
	char	*concatenated;

	if (!path || !cmd)
		return (0);
	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len ++;
	len += strlen(path) + 1; // TODO ft_strlen
	concatenated = (char *)malloc(sizeof(char) * (len + 1));
	if (!concatenated)
		return (0);
	concatenated[len] = '\0';
	i = 0;
	while (path[i])
	{
		concatenated[i] = path[i];
		i ++;
	}
	concatenated[i] = '/';
	len = i;
	while (cmd[i - len] && cmd[i - len] != ' ')
	{
		concatenated[i + 1] = cmd[i - len];
		i ++;
	}
	return (concatenated);
}

char	**ft_get_cmd(char *cmd, char **paths)
{
	int		i;
	char	**argv;
	char	*path;

	argv = ft_split(cmd, ' ');
	if (!argv)
		return (write(STDERR_FILENO, ERR_MALLOC, 22), free(path), NULL);
	if (access(argv[0], F_OK | X_OK) == 0)
		return (write(STDERR_FILENO, argv[0], strlen(argv[0])), argv);
	i = 0;
	while (paths[i])
	{
		path = ft_path_of(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(argv[0]);
			argv[0] = path;
			return (argv);
		}
		free(path);
		i ++;
	}
	ft_free_until((void **)argv, -1);
	return (ft_printf(STDERR_FILENO, ERR_CMD, cmd), NULL);
}

char	**ft_get_path(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0) // TODO ft_strncmp
		{
			path = strdup(envp[i] + 5); // TODO ft_strdup
			if (!path)
				return (ft_printf(STDERR_FILENO, ERR_MALLOC), NULL); // TODO ft_printf
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (ft_printf(STDERR_FILENO, ERR_MALLOC), NULL);
			return (paths);
		}
		i++;
	}
	return (ft_printf(STDERR_FILENO, ERR_PATH), NULL);
}

int	ft_set_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{	
	if (argc < 5)
		return (ft_printf(STDERR_FILENO, ERR_INF_ARGS), 1);
	pipex->limiter = NULL;
	if (strcmp(argv[1], "here_doc") == 0)
	{
		pipex->here_doc = 1;
		if (argc < 6)
			return (ft_printf(STDERR_FILENO, ERR_INF_ARGS), 1);
		pipex->limiter = argv[2];
	}
	else
		pipex->here_doc = 0;
	pipex->nbr_cmds = argc - 3 - pipex->here_doc;
	pipex->path = ft_get_path(envp);
	if (!pipex->path)
		return (1);
	return (0);
}

void	ft_do_cmd(char *cmd, char **path, char **envp)
{
	char	**argv;
	int		send_null[2];

	argv = ft_get_cmd(cmd, path);
	if (!argv)
		exit(1);
	execve(argv[0], argv, envp);
	write(STDERR_FILENO, ERR_EXEC, strlen(ERR_EXEC));
	ft_free_until((void **)argv, -1);
	exit(1);
}

void	ft_do_pipe(char *cmd, char **path, char **envp)
{
	pid_t	pid;
	int		pipes[2];
	int		status;

	if (pipe(pipes) == -1)
	{
		ft_printf(STDERR_FILENO, ERR_PIPE);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf(STDERR_FILENO, ERR_FORK);
		exit(1);
	}
	if (!pid)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		ft_do_cmd(cmd, path, envp);
	}
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		fd1;
	int		fd2;
	int		i;
	int		utility_pipe[2];
	pid_t	last;
	int		status;

	if (ft_set_pipex(argc, argv, envp, &pipex))
		return (1);
	i = 0;
	if (pipex.here_doc)
		// ft_here_doc(argv);
		(void)fd1;
	else
	{
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 < 0)
		{
			write(STDERR_FILENO, "pipex: ", 7);
			perror(argv[1 + pipex.here_doc]);
			if (pipe(utility_pipe) == -1)
				return (ft_printf(STDERR_FILENO, ERR_PIPE), 1);
			close(utility_pipe[1]);
			dup2(utility_pipe[0], STDIN_FILENO);
			close(utility_pipe[0]);
			i ++;
		}
		else
			dup2(fd1, STDIN_FILENO);
	}
	while (i < pipex.nbr_cmds - 1)
		ft_do_pipe(argv[2 + pipex.here_doc + (i ++)], pipex.path, envp);
	if (pipex.here_doc)
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		perror(argv[argc - 1]);
		while (wait(NULL) != -1)
			;
		ft_free_until((void **)pipex.path, -1);
		return (1);
	}
	dup2(fd2, STDOUT_FILENO);
	last = fork();
	if (last < 0)
		return (write(STDERR_FILENO, ERR_FORK, 20), 1);
	if (!last)
	 	ft_do_cmd(argv[argc - 2], pipex.path, envp);
	waitpid(last, &status, 0);
	while (wait(NULL) != -1)
		;
	ft_free_until((void **)pipex.path, -1);
	return (WEXITSTATUS(status));
}
