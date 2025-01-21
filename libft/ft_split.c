/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/02 13:39:29 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	if (s[i] == 0)
		return (0);
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	ft_free(char **result, int wc)
{
	int	i;

	i = 0;
	while (i < wc)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	split_words(char **result, char const *s, char c, int word)
{
	int		start;
	int		end;

	end = 0;
	start = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			result[word] = malloc(sizeof(char) * (end - start + 2));
			if (!result[word])
			{
				ft_free(result, word);
				return (0);
			}
			ft_strlcpy(result[word], (s + start), end - start + 2);
			word++;
		}
		end++;
	}
	result[word] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	if (!split_words(result, s, c, 0))
		return (NULL);
	return (result);
}

/* #include <string.h>
#include <stdio.h>
int main ()
{
	char *test = "     Wie    viele Wörter hat dieser String?    ";
	
	//printf("Dieser String hat %li Wörter\n", count_words(test, ' ')); 
	//printf("Das erste Wort ist %li lang", wordlen(test, ' ')); 
	printf("%s", *ft_split(test, ' '));
	
} */