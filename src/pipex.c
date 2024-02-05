/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:26:07 by octoross          #+#    #+#             */
/*   Updated: 2024/02/05 20:13:04 by octoross         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	int	len;
	int	i;
	char	*concatenated;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len ++;
	printf("len path : %d\n", len);
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
		return (ft_printf(STDERR_FILENO, ERR_FAIL, "malloc"), free(path), NULL);
	if (access(argv[0], F_OK | X_OK) == 0)
		return (argv);
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
				return (ft_printf(STDERR_FILENO, ERR_FAIL, "malloc"), NULL); // TODO ft_printf
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (ft_printf(STDERR_FILENO, ERR_FAIL, "malloc"), NULL);
			return (paths);
		}
		i++;
	}
	return (ft_printf(STDERR_FILENO, ERR_PATH), NULL);
}

int	ft_set_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->path = ft_get_path(envp);
	if (!pipex->path)
		return (1);
	pipex->limiter = NULL;
	if (!strcmp(argv[1], "here_doc"))
	{
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
	}
	else
		pipex->here_doc = 0;
	if (argc < 5 + pipex->here_doc)
			return (ft_printf(STDERR_FILENO, ERR_INF_ARGS), 1);
	pipex->nbr_cmds = argc - 3 - pipex->here_doc;
	pipex->envp = envp;
	if (pipex->here_doc)
		pipex->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipex->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->fd2 < 0)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		perror(argv[argc - 1]);
	}
	return (0);
}

void	ft_do_cmd(char *cmd, t_pipex pipex)
{
	char	**argv;
	int		i;

	argv = ft_get_cmd(cmd, pipex.path);
	if (!argv)
	{
		ft_free_until((void **)pipex.path, -1);
		exit(1);
	}
	i = 0;
	while (argv[i])
	{
		if (i > 0)
			ft_printf(STDERR_FILENO, "   ");
		ft_printf(STDERR_FILENO, "%s\n", argv[i ++]);

	}
	execve(argv[0], argv, pipex.envp);
	ft_free_until((void **)pipex.path, -1);
	ft_printf(STDERR_FILENO, ERR_FAIL, "execve");
	ft_free_until((void **)argv, -1);
	exit(1);
}

void	ft_exit(char *error, t_pipex pipex)
{
	ft_printf(STDERR_FILENO, ERR_FAIL, "fork");
	// tout free
	exit(1);
}

void	ft_cmd(int i, char *cmd, t_pipex pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit("fork", pipex);
	if (!pid)
	{
		
	}
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
				return (ft_printf(STDERR_FILENO, ERR_FAIL, "pipe"), 1);
			close(utility_pipe[1]);
			dup2(utility_pipe[0], STDIN_FILENO);
			close(utility_pipe[0]);
			i ++;
		}
		else
			dup2(fd1, STDIN_FILENO);
	}
	if (fd2 < 0)
	{
		while (wait(NULL) != -1)
			;
		ft_free_until((void **)pipex.path, -1);
		return (1);
	}
	waitpid(last, &status, 0);
	while (wait(NULL) != -1)
		;
	ft_free_until((void **)pipex.path, -1);
	close(fd2);
	return (WEXITSTATUS(status));
}
