/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:35:04 by octoross          #+#    #+#             */
/*   Updated: 2024/01/31 18:14:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_nbr_words(char const *s, char c)
{
	size_t	nbr_words;
	size_t	i;

	nbr_words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (s[i])
	{
		nbr_words ++;
		while (s[i] && s[i] != c)
			i ++;
		while (s[i] && s[i] == c)
			i ++;
	}
	return (nbr_words);
}

char	*ft_next_word(const char *s, size_t *i, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len ++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word[len] = '\0';
	len = 0;
	while (s[*i] && s[*i] != c)
		word[len++] = s[(*i)++];
	while (s[*i] && s[*i] == c)
		(*i)++;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	nbr_words;
	size_t	i;
	char	**splited;

	if (!s)
		return (0);
	nbr_words = ft_nbr_words(s, c);
	splited = (char **)malloc(sizeof(char *) * (nbr_words + 1));
	if (!splited)
		return (0);
	splited[nbr_words] = 0;
	nbr_words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (s[i])
	{
		splited[nbr_words] = ft_next_word(s, &i, c);
		if (!splited[nbr_words])
			return (ft_free_until((void **)splited, nbr_words), NULL);
		nbr_words ++;
	}
	return (splited);
}
