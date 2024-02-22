/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:11 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 17:04:33 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H

# define LIBFT_H

#include <stdlib.h>

void	ft_free_until(void **tab, int index);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split_argv(char const *s);
char	**ft_split(char const *s, char c);

#endif