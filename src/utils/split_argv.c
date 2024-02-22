/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:35:04 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 16:25:09 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// size_t	ft_nbr_words(char const *s, char c)
// {
// 	size_t	nbr_words;
// 	size_t	i;

// 	nbr_words = 0;
// 	i = 0;
// 	while (s[i] && s[i] == c)
// 		i ++;
// 	while (s[i])
// 	{
// 		nbr_words ++;
// 		while (s[i] && s[i] != c)
// 			i ++;
// 		while (s[i] && s[i] == c)
// 			i ++;
// 	}
// 	return (nbr_words);
// }

// char	*ft_next_word(const char *s, size_t *i, char c)
// {
// 	char	*word;
// 	int		len;

// 	len = 0;
// 	while (s[*i + len] && s[*i + len] != c)
// 		len ++;
// 	word = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!word)
// 		return (0);
// 	word[len] = '\0';
// 	len = 0;
// 	while (s[*i] && s[*i] != c)
// 		word[len++] = s[(*i)++];
// 	while (s[*i] && s[*i] == c)
// 		(*i)++;
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	nbr_words;
// 	size_t	i;
// 	char	**splited;

// 	if (!s)
// 		return (0);
// 	nbr_words = ft_nbr_words(s, c);
// 	splited = (char **)malloc(sizeof(char *) * (nbr_words + 1));
// 	if (!splited)
// 		return (0);
// 	splited[nbr_words] = 0;
// 	nbr_words = 0;
// 	i = 0;
// 	while (s[i] && s[i] == c)
// 		i ++;
// 	while (s[i])
// 	{
// 		splited[nbr_words] = ft_next_word(s, &i, c);
// 		if (!splited[nbr_words])
// 			return (ft_free_until((void **)splited, nbr_words), NULL);
// 		nbr_words ++;
// 	}
// 	return (splited);
// }

void	ft_update_nests(char c, int *nest_one, int *nest_two)
{
	if (*nest_one >= 0)
	{
		
	}
	if (c == '\'' && !(*nest_one) && (*nest_two < 0))
		(*nest_one) ++;
	else if (c == '\'')
		(*nest_one) --;
	else if (c == '"' && !(*nest_two))
		(*nest_two) ++;
	else if (c == '"')
		(*nest_two) --;
}

size_t	ft_nbr_words(char const *s)
{
	size_t	nbr_words;
	size_t	i;
	int		nest_one;
	int		nest_two;

	nbr_words = 0;
	nest_one = -1;
	nest_two = -1;
	i = 0;
	while (s[i] && s[i] == ' ')
		i ++;
	while (s[i])
	{
		nbr_words ++;
		while (s[i] && (s[i] != ' ' || nest_one || nest_two))
			ft_update_nests(s[i ++], &nest_one, &nest_two);
		while (s[i] && s[i] == ' ')
			i ++;
	}
	return (nbr_words);
}

char	*ft_next_word(const char *s, size_t *i)
{
	char	*word;
	int		len;
	int		nest_one;
	int		nest_two;

	nest_one = -1;
	nest_two = -1;
	len = 0;
	while (s[*i + len] && (s[*i + len] != ' ') || (nest_one > 0) || (nest_two > 0))
	{
		ft_update_nests(s[*i + (len ++)], &nest_one, &nest_two);
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word[len] = '\0';
	len = 0;
	nest_one = 0;
	nest_two = 0;
	while (s[*i] && (s[*i] != ' ' || nest_one || nest_two))
	{
		if ()
		word[len ++] = s[*i];
		ft_update_nests(s[(*i)++], &nest_one, &nest_two);
	}
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	return (word);
}

void	ft_free_until(void **tab, int index)
{
	int		i;
	char	**strs;

	i = 0;
	while (i < index)
		free(tab[i ++]);
	if (index < 0)
	{
		strs = (char **)tab;
		while (strs[i])
			free(strs[i ++]);
	}
	free(tab);
}

char	**ft_split_argv(char const *s)
{
	size_t	nbr_words;
	size_t	i;
	char	**splited;

	if (!s)
		return (0);
	nbr_words = ft_nbr_words(s);
	splited = (char **)malloc(sizeof(char *) * (nbr_words + 1));
	if (!splited)
		return (0);
	splited[nbr_words] = 0;
	nbr_words = 0;
	i = 0;
	while (s[i] && s[i] == ' ')
		i ++;
	while (s[i])
	{
		splited[nbr_words] = ft_next_word(s, &i);
		if (!splited[nbr_words])
			return (ft_free_until((void **)splited, nbr_words), NULL);
		nbr_words ++;
	}
	return (splited);
}
#include <stdio.h>


int	main(int argc, char **argv)
{
	char 	**splited;
	int		i;

	printf("argv : %s\n", argv[1]);
	splited = ft_split_argv(argv[1]);
	if (!splited)
		return (printf("(null)"), 0);
	i = 0;
	while (splited[i])
	{
		printf("%d : '%s'\n", i, splited[i]);
		free(splited[i]);
		i ++;
	}
	free(splited);
	return (0);
}
