/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:53:58 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:34:19 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_td_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return (0);
}

//skip spaces
bool	skip_spaces(char *str, int *j)
{
	while (str[*j])
	{
		if (str[*j] == ' ')
			(*j)++;
		else
			return (false);
	}
	return (true);
}

//check parameter
void	count_player(t_game *game, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("NSWE", str[i]))
			game->player_amount++;
		i++;
	}
}

//delete lines with only spaces
bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

//free map
void	free_norm_map(t_game *game, char **map)
{
	free_map(map);
	ft_error("Creating normed map failed!", game);
}
