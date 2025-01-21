/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:25:24 by caigner           #+#    #+#             */
/*   Updated: 2024/07/18 16:09:06 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_ray_struct(t_game *game, t_raycast *r, int x)
{
	r->cam_x = 2 * x / (double)WINDOW_WIDTH - 1;
	r->pos_x = (int)game->player.x;
	r->pos_y = (int)game->player.y;
	r->dir_x = game->player.dir_x + game->player.plane_x * r->cam_x;
	r->dir_y = game->player.dir_y + game->player.plane_y * r->cam_x;
	if (r->dir_x == 0.0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1 / r->dir_x);
	if (r->dir_y == 0.0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1 / r->dir_y);
}

void	get_side_dist(t_game *game, t_raycast *r)
{
	if (r->dir_x >= 0)
	{
		r->side_dist_x = (r->pos_x + 1.0 - game->player.x) * r->delta_x;
		r->step_x = 1;
	}
	else
	{
		r->side_dist_x = (game->player.x - r->pos_x) * r->delta_x;
		r->step_x = -1;
	}
	if (r->dir_y >= 0)
	{
		r->side_dist_y = (r->pos_y + 1.0 - game->player.y) * r->delta_y;
		r->step_y = 1;
	}
	else
	{
		r->side_dist_y = (game->player.y - r->pos_y) * r->delta_y;
		r->step_y = -1;
	}
}

void	calculate_dist(t_raycast *r, char **map)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->pos_x += r->step_x;
			r->side = X;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->pos_y += r->step_y;
			r->side = Y;
		}
		if (map[r->pos_y][r->pos_x] == WALL || map[r->pos_y][r->pos_x] == DOOR)
			r->hit = 1;
	}
}

void	calculate_height(t_raycast *r)
{
	if (r->side == X)
		r->perp_wall_dist = r->side_dist_x - r->delta_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_y;
	r->line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dist);
	r->line_start = WINDOW_HEIGHT / 2 - r->line_height / 2;
	if (r->line_start < 0)
		r->line_start = 0;
	r->line_end = WINDOW_HEIGHT / 2 + r->line_height / 2;
	if (r->line_end >= WINDOW_HEIGHT)
		r->line_end = WINDOW_HEIGHT;
}
