/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:53:16 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/02 13:33:24 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	sign(long n, char *str, int *i)
{
	if (n > 9)
	{
		sign(n / 10, str, i);
		sign(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long long	nbr;

	nbr = n;
	str = malloc(sizeof(char) * (intlen(nbr) + 1));
	if (str == 0)
		return (0);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr = -nbr;
	}
	sign(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
