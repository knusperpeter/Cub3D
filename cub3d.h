/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:24:55 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/21 15:34:44 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>

////////////////////////////////////////////
///////////////////MACROS//////////////////
//////////////////////////////////////////

# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1000
# define NUM_TEXTURES 4
# define FOV 0.66
# define MOVEMENT 0.03
# define ROTATION 0.03
# define X 0
# define Y 1
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define PLAYERPOS "NSWE"

//Keys

# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define ARROWLEFT 65361
# define ARROWUP 65362
# define ARROWRIGHT 65363
# define ARROWDOWN 65364
# define ESC 65307
# define KEY_NUMS 65365

////////////////////////////////////////////
//////////////////STRUCTS//////////////////
//////////////////////////////////////////

typedef struct s_texture
{
	void	*img;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_texture;

typedef struct s_raycast
{
	double			cam_x;
	int				pos_x; // current x or y player
	int				pos_y;
	double			dir_x; // ray direction
	double			dir_y;
	double			side_dist_x; // distance between player and next x or y
	double			side_dist_y;
	double			delta_x; // distance between two x or y
	double			delta_y;
	double			perp_wall_dist;
	int				step_x; // -1 or 1
	int				step_y;
	int				hit;
	int				side; // 0 = X, 1 = Y
	int				line_height;
	int				line_start;
	int				line_end;
	t_texture		*texture;
	double			wall_x;
	unsigned int	color;
}	t_raycast;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	double	old_dir_x;
	double	old_plane_x;
}	t_player;

typedef struct s_param
{
	bool	f;
	bool	c;
	bool	no;
	bool	we;
	bool	ea;
	bool	so;
}	t_param;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				map_param;
	t_texture		texture[NUM_TEXTURES]; //N, S, E, W
	int				f_color;
	int				c_color;	
	t_player		player;
	t_raycast		raycast;
	t_param			param;
	double			move_speed;
	double			rot_speed;
	int				fd;
	int				rows;
	char			**map;
	bool			m_start;
	int				player_amount;
	int				key_state[KEY_NUMS];
}	t_game;

////////////////////////////////////////////
/////////////////FUNCTIONS/////////////////
//////////////////////////////////////////

//cub3d.c

//init.c
void	init_var(t_game *game);
bool	init_window(t_game *cub);
void	init_texture(t_game *game);
int		xpm_to_img(void *mlx, char *path, void **img);
int		init_img(t_game *game);

//check_file.c
bool	right_fileextension(char *file, char *end);
int		check_file(t_game *game, char *argv);
void	get_rows(t_game *game);

//map_checker.c
bool	only_allowed_chars(char *str);
bool	only_walls(char *str);
bool	check_row(t_game *game, char **map);
bool	check_surr(t_game *game, int y, int x);
bool	check_pos(t_game *game);

//map_utils_check.c
bool	check_texture(t_game *game, char *str);
bool	valid_texture(t_game *game, char *path, char *dir);
bool	is_dir(t_game *game, char *str);
bool	is_fc(t_game *game, char *str);
bool	valid_color(t_game *game, char *str);

//norm_map.c
int		len_until_sc(char *str, char c);
char	*norm_line(t_game *game, char *str);
void	norm_map(t_game *game);
bool	is_empty(char *str);
void	concat_string(char **result, char **tmp2, char *tmp, t_game *game);

//attribute_checker.c
bool	right_path(char *path);
bool	check_attributes(t_game *game);
int		check_type(t_game *game, char *str);

//color_calc.c
void	triple_free(char *s1, char *s2, char *s3);
bool	get_number(t_game *game, char *str);
int		rgb_to_hex(int r, int g, int b);
int		hex_to_dec(int hex);

//read_map.c
int		check_for_newline(char *str);
void	double_free(char *s1, char *s2, int fd, t_game *game);
void	single_free(char *s1, t_game *game);
char	*get_map_temp(t_game *game, char *map_temp, int fd);
void	init_map(t_game *game, char *argv);

//free.c
int		ft_error(char *str, t_game *game);
int		free_map(char **map);
void	destroy_mlx(t_game *game);
int		free_exit(t_game *game);
void	free_all(t_game *game);

//utils_1.c
int		print_td_array(char **str);
bool	skip_spaces(char *str, int *j);
void	count_player(t_game *game, char *str);
bool	is_empty(char *str);
void	free_norm_map(t_game *game, char **map);

//utils_2.c
void	add_plane_and_dir_vector(t_game *game, char c);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
void	ft_texture_to_mlx(t_game *game);
void	handle_nl_in_map(t_game *game, char *s1, char *s2, bool *ms);

//render.c
bool	ft_new_image(t_game *game);
void	draw_background(t_game *game, int x, int y, unsigned int color);
void	ft_background(t_game *game);
int		render(t_game *game);

//raycaster_1.c
void	determine_texture(t_game *game, t_raycast *r);
void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color);
void	draw_line(t_game *game, int x, t_raycast *r);
void	raycaster(t_game *game);

//raycaster_2.c
void	init_ray_struct(t_game *game, t_raycast *r, int i);
void	get_side_dist(t_game *game, t_raycast *r);
void	calculate_dist(t_raycast *r, char **map);
void	calculate_height(t_raycast *r);

//movement.c
void	handle_input(t_game *g, double move_x, double move_y);

#endif