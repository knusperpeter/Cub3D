/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:29:22 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:02:27 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_newline(char *str)
{
	if (str && ft_strlen(str) > 0 \
		&& str[ft_strlen(str) - 1] == '\n')
		return (0);
	else
		return (1);
}

void	double_free(char *s1, char *s2, int fd, t_game *game)
{
	free(s1);
	free(s2);
	while (1)
	{
		s1 = get_next_line(fd);
		if (s1 != NULL)
			free(s1);
		else
			break ;
	}
	ft_error("Invalid map!!", game);
}

void	single_free(char *s1, t_game *game)
{
	free(s1);
	ft_error("Invalid map", game);
}

char	*get_map_temp(t_game *game, char *map_temp, int fd)
{
	char	*line_temp;
	char	*tmp;
	bool	map_start;

	map_start = false;
	while (1)
	{
		line_temp = get_next_line(fd);
		if (!line_temp)
			single_free(map_temp, game);
		handle_nl_in_map(game, map_temp, line_temp, &map_start);
		tmp = ft_strjoin(map_temp, line_temp);
		if (!tmp)
			double_free(map_temp, line_temp, fd, game);
		free(map_temp);
		map_temp = tmp;
		if (check_for_newline(line_temp) == 1)
		{
			free(line_temp);
			break ;
		}
		free(line_temp);
		line_temp = 0;
	}
	return (map_temp);
}

void	init_map(t_game *game, char *argv)
{
	char	*map_temp;

	if (right_fileextension(argv, ".cub"))
	{
		game->fd = open(argv, O_RDONLY);
		if (game->fd < 0)
			ft_error("Couldn't read map!", game);
		map_temp = ft_strdup("");
		if (!map_temp)
			ft_error("Error!", game);
		map_temp = get_map_temp(game, map_temp, game->fd);
		if (!map_temp)
			single_free(map_temp, game);
		if (close(game->fd))
			single_free(map_temp, game);
		game->map = ft_split(map_temp, '\n');
		if (game->map == NULL)
			single_free(map_temp, game);
		free(map_temp);
	}
	else
		ft_error("Error!", game);
}
