/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:48 by octoross          #+#    #+#             */
/*   Updated: 2024/02/01 05:05:07 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
	int				eof;
}		t_gnl;

char	*get_next_line(int fd);
void	ft_lstadd_back(t_gnl **lst, t_gnl *new);

void	ft_lstdelone(t_gnl *lst, void (*del)(void *));
int		ft_lstsize(t_gnl *lst);
char	*ft_lstclear(t_gnl **lst, void (*del)(void *));

int		ft_append(char *str, char *to_add);
char	*ft_strdup(char *str);
int		find_eol(char *str);

t_gnl	*ft_lstnew(void);

#endif