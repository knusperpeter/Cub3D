/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:38:42 by caigner           #+#    #+#             */
/*   Updated: 2024/07/19 14:29:37 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

bool	ft_new_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (ft_error("mlx_new_image failed\n", game), false);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, \
			&game->line_length, &game->endian);
	if (!game->addr)
		return (ft_error("mlx_get_data_addr", game), false);
	return (true);
}

void	draw_background(t_game *game, int x, int y, unsigned int color)
{
	char	*dest;

	dest = game->addr + (WINDOW_WIDTH * y + x) * (game->bits_per_pixel / 8);
	*(unsigned int *)dest = color;
}

void	ft_background(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT / 2)
			draw_background(game, x, y++, game->c_color);
		x++;
	}
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = WINDOW_HEIGHT / 2;
		while (y < WINDOW_HEIGHT)
			draw_background(game, x, y++, game->f_color);
		x++;
	}
}

int	render(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	handle_input(game, move_x, move_y);
	if (!ft_new_image(game))
		ft_error("Failed to render new image", game);
	ft_background(game);
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}
