/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:11 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 18:04:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	ft_free_until(void **tab, int index);
int		ft_strcmp(const char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split_argv(char const *s);
char	**ft_split(char const *s, char c);

#endif
