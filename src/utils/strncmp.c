/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:23:10 by octoross          #+#    #+#             */
/*   Updated: 2024/02/21 19:38:54 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && i < n && s1[i] == s2[i])
		i ++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
