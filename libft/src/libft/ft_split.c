/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:29:00 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 10:29:00 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_word_count(const char *s, char c)
{
	int	pos;
	int	wc;

	pos = 0;
	wc = 0;
	while (s[pos] != '\0')
	{
		if (!(s[pos] == c) && 
			(pos == 0 || (s[pos - 1] == c)))
			wc ++;
		pos ++;
	}
	return (wc);
}

static void	ft_free(char **splitted)
{
	int	pos;

	pos = 0;
	while (splitted[pos])
		pos++;
	while (pos >= 0)
	{
		free(splitted[pos]);
		pos --;
	}
	free(splitted);
}

static int	loop(const char *s, char c, char **splitted)
{
	int	wc;
	int	pos;
	int	pos2;

	wc = -1;
	pos = 0;
	while (s[pos])
	{
		pos2 = 1;
		if (s[pos] != c)
		{
			wc++;
			while (s[pos + pos2] != c && s[pos + pos2])
				pos2++;
			splitted[wc] = (char *) malloc ((pos2 + 1) * sizeof (char));
			if (!splitted[wc])
				return (0);
			ft_strlcpy(splitted[wc], s + pos, pos2 + 1);
		}
		pos = pos + pos2;
	}
	splitted[wc + 1] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**splitted;

	splitted = (char **)malloc((ft_word_count(s, c) + 1) * sizeof (char *));
	if (splitted == NULL)
		return (NULL);
	if (!(loop(s, c, splitted)))
	{
		ft_free(splitted);
		return (NULL);
	}
	return (splitted);
}
