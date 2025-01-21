/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:39:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/02 13:47:45 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && i < len)
	{
		if (big[i + j] == little[j] && i + j < len)
			j++;
		else
		{
			j = 0;
			i++;
		}
		if (little[j] == 0 && j != 0)
			return ((char *)(big + i));
	}
	return (0);
}

/* #include <string.h>
int main ()
{
	printf("Original:%s \n", strnstr("Hallo Sepp stehst", "Sepp", 0));
  	printf("Fake:%s \n", ft_strnstr("Hallo Sepp stehst", "Sepp", 0));
} */
