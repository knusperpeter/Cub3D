/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:55:26 by caigner           #+#    #+#             */
/*   Updated: 2024/07/02 13:48:03 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;
	int			i;

	i = 0;
	while (s[i])
		i++;
	p = s + i;
	while (p >= s)
	{
		if ((char)c == *p)
			return ((char *)p);
		p--;
	}
	return (0);
}
