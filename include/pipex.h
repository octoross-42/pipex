/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:38:43 by octoross          #+#    #+#             */
/*   Updated: 2024/02/02 23:18:07 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "gnl.h"
# include "printf.h"

# include <stdio.h>
# include <sys/wait.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# define ERR_PIPE "Error: pipe failed\n"
# define ERR_FORK "Error: fork failed\n"
# define ERR_DUP2 "Error: dup2 failed\n"
# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_CLOSE "Error: close failed\n"
# define ERR_CMD "%s: command not found\n"
# define ERR_INF_ARGS "Error: not enough arguments for pipex\n"
# define ERR_PATH "Error: PATH not found\n"
# define ERR_EXEC "Error: execve failed\n"

typedef struct s_pipex
{
	int		nbr_cmds;
	char	**path;
	int		here_doc;
	char	*limiter;
}				t_pipex;

char	**ft_split(char const *s, char c);
void	ft_free_until(void **tab, int index);

#endif