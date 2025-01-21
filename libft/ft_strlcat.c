/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:55:38 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/02 13:44:58 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srclen;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	while (dest[i] && i < size)
		i++;
	if (size == i)
		return (i + srclen);
	while (src[j] && i + j < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + srclen);
}

/* #include <stdio.h>
int main ()
{
	char dest[] = "Hallo ich heiße";
	const char src[] = " Jakob";
	ft_strlcat(dest, src, 82);

	printf("%s \n", dest);
}  */