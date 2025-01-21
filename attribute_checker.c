/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:43:05 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:33:09 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_type(t_game *game, char *str)
{
	int	len;

	len = len_until_sc(str, ' ');
	if (len > 2)
		return (false);
	if (is_fc(game, str))
	{
		if (!valid_color(game, str))
			return (false);
		if (!get_number(game, str))
			return (false);
	}
	else if (is_dir(game, str))
	{
		if (!check_texture(game, str))
			return (false);
	}
	return (true);
}

bool	correct_params(t_game *game)
{
	if (!game->param.c || !game->param.f)
		return (false);
	if (!game->param.ea || !game->param.no || !game->param.we \
		|| !game->param.so)
		return (false);
	if (game->map_param != 6)
		return (false);
	return (true);
}

bool	check_attributes(t_game *game)
{
	int		i;
	char	*norm_input;

	i = 0;
	norm_input = NULL;
	while (i < 6)
	{
		if (!game->map[i])
			ft_error("Map is missing!", game);
		norm_input = norm_line(game, game->map[i]);
		if (!norm_input)
			ft_error("Malloc fail!", game);
		if (!check_type(game, norm_input))
		{
			free(norm_input);
			return (false);
		}
		free(norm_input);
		i++;
	}
	if (!correct_params(game))
		return (false);
	return (true);
}

//check if correct file
bool	right_path(char *path)
{
	int	fd;

	if (!right_fileextension(path, ".xpm"))
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	else
	{
		if (close(fd) == -1)
			return (false);
		return (true);
	}
}
