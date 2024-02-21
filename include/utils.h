/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:11 by octoross          #+#    #+#             */
/*   Updated: 2024/02/21 19:39:10 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H

# define LIBFT_H

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split_argv(char const *s);

#endif