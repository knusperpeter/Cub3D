/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:59:43 by caigner           #+#    #+#             */
/*   Updated: 2024/07/19 14:28:17 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	determine_texture(t_game *game, t_raycast *r)
{
	if (r->side == X && r->dir_x > 0)
		r->texture = &game->texture[EAST];
	else if (r->side == X)
		r->texture = &game->texture[WEST];
	else if (r->side == Y && r->dir_y > 0)
		r->texture = &game->texture[SOUTH];
	else if (r->side == Y)
		r->texture = &game->texture[NORTH];
	r->texture->addr = mlx_get_data_addr(r->texture->img, \
				&r->texture->bits_per_pixel, &r->texture->line_length, \
				&r->texture->endian);
	if (!r->texture->addr)
		ft_error("Failed to get texture address", game);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color)
{
	char	*dest;

	dest = game->addr + (y * game->line_length + x * (game->bits_per_pixel \
		/ 8));
	*(unsigned int *)dest = color;
}

void	calc_wall_x(t_game *game, t_raycast *r, int *tex_x)
{
	if (r->side == X)
		r->wall_x = game->player.y + r->perp_wall_dist * r->dir_y;
	else
		r->wall_x = game->player.x + r->perp_wall_dist * r->dir_x;
	*tex_x = (int)(r->wall_x * r->texture->width) % r->texture->width;
	if ((r->side == X && r->dir_x < 0) || (r->side == Y && r->dir_y > 0))
		*tex_x = r->texture->width - *tex_x - 1;
}

void	draw_line(t_game *game, int x, t_raycast *r)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;

	calc_wall_x(game, r, &tex_x);
	step = 1.0 * r->texture->height / r->line_height;
	tex_pos = (r->line_start - WINDOW_HEIGHT / 2 + r->line_height / 2) * step;
	y = r->line_start;
	while (y < r->line_end)
	{
		tex_y = (int)tex_pos % r->texture->height;
		tex_pos += step;
		r->color = *(unsigned int *)(r->texture->addr + (tex_y \
					* r->texture->line_length + tex_x \
					* (r->texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(game, x, y, r->color);
		y++;
	}
}

/* 
	------ only colors no textures ------
		
void	draw_line(t_game *game, int x, t_raycast *r)
{
	int		y;

	y = r->line_start;
	while (y < r->line_end)
	{
		if (r->side)
			r->color = 13172854;
		else
			r->color = 16711885;
		my_mlx_pixel_put(game, x, y, r->color);
		y++;
	}
} */

void	raycaster(t_game *game)
{
	t_raycast	ray;
	int			x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_struct(game, &ray, x);
		get_side_dist(game, &ray);
		calculate_dist(&ray, game->map);
		calculate_height(&ray);
		determine_texture(game, &ray);
		draw_line(game, x, &ray);
		x++;
	}
}
