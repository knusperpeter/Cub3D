/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:11:01 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:10:58 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_dir(t_game *game, char *str)
{
	if (len_until_sc(str, ' ') != 2)
		return (false);
	if (!ft_strncmp(str, "NO", 2))
	{
		game->param.no = true;
		return (true);
	}
	else if (!ft_strncmp(str, "WE", 2))
	{
		game->param.we = true;
		return (true);
	}
	else if (!ft_strncmp(str, "SO", 2))
	{
		game->param.so = true;
		return (true);
	}
	else if (!ft_strncmp(str, "EA", 2))
	{
		game->param.ea = true;
		return (true);
	}
	return (false);
}

bool	is_fc(t_game *game, char *str)
{
	int	len;

	len = len_until_sc(str, ' ');
	if (len != 1)
		return (false);
	if (ft_strchr(str, 'F'))
	{
		game->param.f = true;
		return (true);
	}
	else if (ft_strchr(str, 'C'))
	{
		game->param.c = true;
		return (true);
	}
	return (false);
}

bool	check_texture(t_game *game, char *str)
{
	int		i;
	char	*dir;
	char	*path;

	i = 0;
	dir = NULL;
	path = NULL;
	if (!dir)
	{
		dir = ft_substr(str, i, 2);
		if (!dir)
			return (false);
		i += 3;
	}
	if (!path)
	{
		path = ft_substr(str, i, ft_strlen(str + i));
		if (!path)
			return (free(dir), false);
	}
	if (!valid_texture(game, path, dir))
		return (free(dir), free(path), false);
	return (free(dir), free(path), true);
}

bool	valid_texture(t_game *game, char *path, char *dir)
{
	if (!ft_strncmp(dir, "NO", 2) && right_path(path))
	{
		game->texture[NORTH].path = ft_strdup(path);
		if (game->texture[NORTH].path)
			return (game->map_param++, true);
	}
	else if (!ft_strncmp(dir, "SO", 2) && right_path(path))
	{
		game->texture[SOUTH].path = ft_strdup(path);
		if (game->texture[SOUTH].path)
			return (game->map_param++, true);
	}
	else if (!ft_strncmp(dir, "WE", 2) && right_path(path))
	{
		game->texture[WEST].path = ft_strdup(path);
		if (game->texture[WEST].path)
			return (game->map_param++, true);
	}
	else if (!ft_strncmp(dir, "EA", 2) && right_path(path))
	{
		game->texture[EAST].path = ft_strdup(path);
		if (game->texture[EAST].path)
			return (game->map_param++, true);
	}
	return (game->map_param++, false);
}

bool	valid_color(t_game *game, char *str)
{
	int		i;
	char	*number;
	int		num;
	int		len;

	i = 2;
	number = NULL;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		len = len_until_sc(str + i, ',');
		number = ft_substr(str, i, len);
		if (!number)
			return (false);
		if (str[i + len] == ',')
			i += len + 1;
		else
			i += len;
		num = ft_atoi(number);
		free(number);
		if (num > 255 || num < 0)
			return (false);
	}
	return (game->map_param++, true);
}
