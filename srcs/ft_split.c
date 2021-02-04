/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:43:44 by mraymun           #+#    #+#             */
/*   Updated: 2021/02/04 03:24:44 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int		ft_countwords(char const *s, char c)
{
	int		i;
	int		w;

	w = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w++;
		i++;
	}
	return (w);
}

static int		ft_wordlen(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void		*ft_leakprotect(char **ret, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (0);
}

static char		**ft_fill(char const *s, int w, char c, char **ret)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i < w)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		if (!(ret[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (ft_leakprotect(ret, i));
		j = 0;
		while (j < len)
			ret[i][j++] = *s++;
		ret[i][j] = '\0';
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char			**ft_split(char	const *s, char c)
{
	char	**ret;
	int		w;

	if (!s)
		return (0);
	w = ft_countwords(s, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (w + 1))))
		return (0);
	ret = ft_fill(s, w, c, ret);
	return (ret);
}