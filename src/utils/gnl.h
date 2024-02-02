/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:48 by octoross          #+#    #+#             */
/*   Updated: 2024/02/01 05:27:55 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	int				size;
	char			*content;
	int				eof;
	int				eol;
	int				len;
	int				start;
	struct s_list	*next;
}		t_gnl;

void	ft_clear_leftovers(t_gnl **leftovers);
void	ft_clean_and_next_lst(t_gnl **line);

char	*get_next_line(int fd);

#endif