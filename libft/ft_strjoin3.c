/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:35 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/17 12:28:18 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*joined1;
	char	*joined2;

	joined1 = ft_strjoin(s1, s2);
	joined2 = ft_strjoin(joined1, s3);
	free(joined1);
	return (joined2);
}
