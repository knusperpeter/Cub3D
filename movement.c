/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:43:54 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/18 21:30:38 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_helper(t_game *game, double dir_x, double dir_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + dir_x * game->move_speed;
	new_y = game->player.y + dir_y * game->move_speed;
	if ((int)new_y >= 6 && (int)new_y < game->rows && (int)new_x >= 0 && \
		(int)new_x < (int)ft_strlen(game->map[(int)new_y]))
	{
		if (game->map[(int)new_y][(int)game->player.x] != WALL && \
			game->map[(int)new_y][(int)game->player.x] != DOOR)
			game->player.y = new_y;
		if (game->map[(int)game->player.y][(int)new_x] != WALL && \
			game->map[(int)game->player.y][(int)new_x] != DOOR)
			game->player.x = new_x;
	}
}

void	rotate(t_game *game, t_player *player, int key)
{
	double	rot_speed;
	double	cos_rot;
	double	sin_rot;
	double	old_dir_x;
	double	old_plane_x;

	if (key == ARROWLEFT)
		rot_speed = -game->rot_speed;
	else
		rot_speed = game->rot_speed;
	cos_rot = cos(rot_speed);
	sin_rot = sin(rot_speed);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos_rot - player->dir_y * sin_rot;
	player->dir_y = old_dir_x * sin_rot + player->dir_y * cos_rot;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_rot - player->plane_y * sin_rot;
	player->plane_y = old_plane_x * sin_rot + player->plane_y * cos_rot;
}

void	calc_move(double *x, double *y, t_game *game, int num)
{
	if (num == 0)
	{
		*x += game->player.dir_x;
		*y += game->player.dir_y;
	}
	else if (num == 1)
	{
		*x -= game->player.dir_x;
		*y -= game->player.dir_y;
	}
	else if (num == 2)
	{
		*x -= game->player.plane_x;
		*y -= game->player.plane_y;
	}
	else if (num == 3)
	{
		*x += game->player.plane_x;
		*y += game->player.plane_y;
	}
}

void	handle_input(t_game *g, double move_x, double move_y)
{
	double	length;

	if (g->key_state[W] || g->key_state[ARROWUP])
		calc_move(&move_x, &move_y, g, 0);
	if (g->key_state[S] || g->key_state[ARROWDOWN])
		calc_move(&move_x, &move_y, g, 1);
	if (g->key_state[A])
		calc_move(&move_x, &move_y, g, 2);
	if (g->key_state[D])
		calc_move(&move_x, &move_y, g, 3);
	if (move_x != 0 && move_y != 0)
	{
		length = sqrt(move_x * move_x + move_y * move_y);
		move_x /= length;
		move_y /= length;
	}
	move_helper(g, move_x, move_y);
	if (g->key_state[ARROWLEFT])
		rotate(g, &g->player, ARROWLEFT);
	if (g->key_state[ARROWRIGHT])
		rotate(g, &g->player, ARROWRIGHT);
	if (g->key_state[ESC])
		free_exit(g);
}
