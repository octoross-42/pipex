/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:35:04 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 21:23:20 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "pipex.h"

static void	ft_update_nests(char const *s, int *nest_one, int *nest_two)
{
	int	i;

	if (*nest_one >= 0)
	{
		if (s[0] == '\'' && *nest_one > 0)
			(*nest_one)--;
	}
	else if (*nest_two >= 0)
	{
		if (s[0] == '"' && *nest_two > 0)
			(*nest_two)--;
	}
	else if (s[0] == '\'' || s[0] == '"')
	{
		i = 1;
		while (s[i] && (*nest_one < 0) && (*nest_two < 0))
		{
			if (s[i] == '\'' && s[0] == '\'')
			{
				*nest_one = 1;

				ft_printf(STDERR_FILENO, "one\n");
			}
			else if (s[i] == '"' && s[0] == '"')
			{
				ft_printf(STDERR_FILENO, "two\n");
				*nest_two = 1;
			}
			i ++;
		}
	}
}

static int	ft_nbr_words(char const *s)
{
	int	nbr_words;
	int	i;
	int	nest_one;
	int	nest_two;

	nbr_words = 0;
	nest_one = -1;
	nest_two = -1;
	i = 0;
	while (s[i] && s[i] == ' ')
		i ++;
	while (s[i])
	{
		nbr_words ++;
		while (s[i] && (s[i] != ' ' || (nest_one > 0) || (nest_two > 0)))
			ft_update_nests(&s[i ++], &nest_one, &nest_two);
		while (s[i] && s[i] == ' ')
			i ++;
	}
	return (nbr_words);
}

static int	ft_len_word(const char *s)
{
	int	j;
	int	len;
	int	nest_one;
	int	nest_two;

	nest_one = -1;
	nest_two = -1;
	j = 0;
	len = 0;
	while (s[j] && ((s[j] != ' ')
			|| (nest_one > 0) || (nest_two > 0)))
	{
		ft_update_nests(&s[j], &nest_one, &nest_two);
		if (!((s[j] == '\'' && (nest_one >= 0))
				|| (s[j] == '"' && (nest_two >= 0))))
			len ++;
		j ++;
	}
	return (len);
}

static char	*ft_next_word(const char *s, int *i)
{
	char	*word;
	int		len;
	int		nest_one;
	int		nest_two;

	len = ft_len_word(&s[*i]);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word[len] = '\0';
	len = 0;
	nest_one = -1;
	nest_two = -1;
	while (s[*i] && (s[*i] != ' ' || (nest_one > 0) || (nest_two > 0)))
	{
		ft_update_nests(&s[*i], &nest_one, &nest_two);
		if (!((s[*i] == '\'' && (nest_one >= 0))
				|| (s[*i] == '"' && (nest_two >= 0))))
			word[len ++] = s[*i];
		(*i)++;
	}
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	return (word);
}

char	**ft_split_argv(char const *s)
{
	int		nbr_words;
	int		i;
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
