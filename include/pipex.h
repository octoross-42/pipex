/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:38:43 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 20:47:37 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "gnl.h"
# include "printf.h"
# include "utils.h"

# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# define ERR_CMD "pipex: command not found: %s\n"
# define ERR_INF_ARGS "Error: not enough arguments for pipex\n"
# define ERR_PATH "Error: PATH not found\n"
# define ERR_FAIL "Error: %s failed\n"
# define ERR_HERE_DOC "Error : gnl failed when reading STDIN_FILENO\n"

void	ft_exit_with_fail(char *fail, char **path);

char	*ft_path_of(char const *path, char const *cmd);
char	**ft_get_cmd(char *cmd, char **paths);

typedef struct s_pipex
{
	int		nbr_cmds;
	char	**path;
	char	**envp;
	int		here_doc;
	int		fd2;
	char	*limiter;
	int		fd1;
}				t_pipex;

int		ft_set_pipex(int argc, char **argv, char **envp, t_pipex *pipex);

void	ft_do_cmd(char *cmd, t_pipex *pipex, char **envp);
void	ft_do_pipe(char *cmd, t_pipex *pipex, char **envp);
void	ft_here_doc(t_pipex *pipex);
void	ft_open_infile(t_pipex *pipex, char **argv, int *i);
void	ft_open_outfile(t_pipex *pipex, int argc, char **argv);

#endif