/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:28:47 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 20:38:45 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (ft_printf(STDERR_FILENO, ERR_FAIL, "malloc"), NULL);
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
	pipex->fd1 = -1;
	if (!pipex->path)
		return (1);
	return (0);
}

char	**ft_get_cmd(char *cmd, char **paths)
{
	int		i;
	char	**argv;
	char	*path;

	argv = ft_split_argv(cmd);
	if (!argv)
		return (ft_printf(STDERR_FILENO, ERR_FAIL, "malloc"), NULL);
	if (access(argv[0], F_OK | X_OK) == 0)
		return (argv);
	i = 0;
	while (paths[i])
	{
		path = ft_path_of(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free(argv[0]), argv[0] = path, argv);
		free(path);
		i ++;
	}
	ft_printf(STDERR_FILENO, ERR_CMD, argv[0]);
	ft_free_until((void **)argv, -1);
	return (NULL);
}

static int	ft_len_executable(char const *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len ++;
	return (len);
}

char	*ft_path_of(char const *path, char const *cmd)
{
	int		len;
	int		i;
	char	*concatenated;

	len = ft_len_executable(cmd) + ft_strlen(path) + 1;
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
