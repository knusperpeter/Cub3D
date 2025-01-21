/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:04:18 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 13:41:09 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	triple_free(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

bool	get_number(t_game *game, char *str)
{
	int		hex;
	char	**num;

	num = ft_split(str + 2, ',');
	if (!num)
		return (false);
	if (!num[0])
		return (free_map(num), false);
	if (!num[1])
		return (free_map(num), false);
	if (!num[2])
		return (free_map(num), false);
	hex = rgb_to_hex(ft_atoi(num[0]), ft_atoi(num[1]), ft_atoi(num[2]));
	if (str[0] == 'F')
		game->f_color = hex_to_dec(hex);
	else if (str[0] == 'C')
		game->c_color = hex;
	triple_free(num[0], num[1], num[2]);
	free(num);
	return (true);
}

//rgb to hex
int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

//hex to decimal
int	hex_to_dec(int hex)
{
	int	dec;
	int	r;
	int	g;
	int	b;

	r = (hex >> 16) & 0xFF;
	g = (hex >> 8) & 0xFF;
	b = hex & 0xFF;
	dec = r * 65536 + g * 256 + b;
	return (dec);
}
