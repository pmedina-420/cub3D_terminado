/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:38:47 by pmedina-          #+#    #+#             */
/*   Updated: 2021/01/07 19:38:54 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

typedef struct		s_cub
{
	void			*mlx_p;
	void			*win_p;
	long			size_y;
	long			size_x;
}					t_cub;

typedef	struct		s_img
{
	void			*img;
	char			*addr;
	int				b_p_p;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_map
{
	int				size_x;
	int				size_y;
	char			*n_path;
	char			*e_path;
	char			*w_path;
	char			*s_path;
	int				player;
	char			*sprite;
	double			county;
	double			countx;
	char			*p;
	int				ret;
	int				values;
	int				c;
}					t_map;

typedef struct		s_tex
{
	int				tex_x;
	int				tex_y;
	int				wid;
	int				hei;
	int				texnum;
	double			wallx;
	double			step;
	double			texpos;
	int				color;
	unsigned int	*buffer;
}					t_tex;

typedef struct		s_ntex
{
	void			*tex;
	int				b_p_p;
	int				line_length;
	int				endian;
	int				hei;
	int				wid;
}					t_ntex;

typedef struct		s_stex
{
	void			*tex;
	int				b_p_p;
	int				line_length;
	int				endian;
	int				hei;
	int				wid;
}					t_stex;

typedef struct		s_etex
{
	void			*tex;
	int				b_p_p;
	int				line_length;
	int				endian;
	int				hei;
	int				wid;
}					t_etex;

typedef struct		s_wtex
{
	void			*tex;
	int				b_p_p;
	int				line_length;
	int				endian;
	int				hei;
	int				wid;
}					t_wtex;

typedef struct		s_floor
{
	int				r;
	int				g;
	int				b;
	int				rgb;
}					t_floor;

typedef struct		s_sky
{
	int				r;
	int				g;
	int				b;
	int				rgb;
}					t_sky;

typedef struct		s_sprite
{
	void			*tex;
	void			*sprite;
	unsigned int	*buffer;
	double			*zbuffer;
	int				wid;
	int				hei;
	int				s_x;
	int				s_y;
	int				num;
	int				b_p_p;
	int				line_length;
	int				endian;
	int				drawstartx;
	int				drawendx;
	int				drawstarty;
	int				drawendy;
	double			invdet;
	double			transformx;
	double			transformy;
	double			spx;
	double			spy;
	int				sp_screenx;
	int				vmovescreen;
	double			dist;
	int				*order;
	int				texx;
	int				texy;
	int				d;
	int				color;
}					t_sprite;

typedef struct		s_arr_sp
{
	double			tmp;
	double			x;
	double			y;
}					t_arr_sp;

typedef struct		s_player
{
	char			**worldmap;
	char			**fakemap;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			movespeed;
	double			rotspeed;
	double			sidistx;
	double			sidisty;
	double			deltadistx;
	double			deltadisty;
	double			raylen;
	int				hit;
	double			stepx;
	double			stepy;
	int				side;
	int				drawstart;
	int				drawend;
	double			oldplanex;
	double			oldirx;
	double			draw;

}					t_player;

typedef struct		s_keys
{
	int				w_key;
	int				a_key;
	int				s_key;
	int				d_key;
	int				l_key;
	int				r_key;
}					t_keys;

typedef	struct		s_global
{
	t_img			img;
	t_cub			cub;
	t_player		me;
	t_keys			key;
	t_map			map;
	t_tex			tex;
	t_ntex			n_tex;
	t_stex			s_tex;
	t_etex			e_tex;
	t_wtex			w_tex;
	t_sprite		sp;
	t_arr_sp		*arr;
	t_floor			floor;
	t_sky			sky;
}					t_global;

int					main(int argc, char **argv);
void				print_error(char *str);
void				check_arguments(t_global *gl, int argc, char **argv);
void				screenshot(t_global *gl);
int					readmap(t_global *gl, char *str);
void				set_pos(t_global *gl);
void				path_check(t_global *gl, int fd, char *str);
void				check_path_char(char *buff);
void				get_sizes(t_global *gl, char *buff);
char				*get_resolution(t_global *gl, char *buff);
void				get_north_texture_path(t_global *gl, char *buff, int c);
void				get_south_texture_path(t_global *gl, char *buff, int c);
char				*fill_south_path(t_global *gl, char *buff, int c);
void				get_sprite_texture(t_global *gl, char *buff, int c);
void				get_east_texture_path(t_global *gl, char *buff, int c);
void				get_west_texture_path(t_global *gl, char *buff, int c);
void				get_floor_rgb(t_global *gl, char *buff);
void				get_sky_rgb(t_global *gl, char *buff);
void				missing_paths(t_global *gl, char *buff);
char				*skip_spaces(char *buff);
void				check_after_path(t_global *gl, char *buff, int i, char *s);
void				check_values(t_global *gl, char *buff);
void				map_check(t_global *gl, int fd);
void				get_player_pos(t_global *gl, char *buff);
void				check_map_char(char *buff);
void				fillmap(t_global *gl, int c, int s, char *buff);
void				north_pos(t_global *gl, char *buff);
void				south_pos(t_global *gl, char *buff);
void				east_pos(t_global *gl, char *buff);
void				west_pos(t_global *gl, char *buff);
void				map_err_check(t_global *gl, int num);
void				floodfill(t_global *gl, int x, int y, int *num);
void				loadtextures(t_global *gl);
void				resize_textures(t_global *gl);
int					key_pressed(int keycode, t_global *gl);
int					key_released(int keycode, t_global *gl);
int					x_pressed(t_global *gl);
int					raycasting(t_global *gl);
void				mall_sp(t_global *gl);
void				set_raycasting_values(t_global *gl, int sizex);
void				set_raylen(t_global *gl);
void				set_draw(t_global *gl);
void				get_textures(t_global *gl);
void				set_textures(t_global *gl);
void				draw_textures(t_global *gl, int sizex);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				raycasting_sprites(t_global *gl);
void				sort_sprites(t_global *gl);
void				sort_values(t_global *gl, int a, int t);
void				set_sprite_values(t_global *gl, int s);
int					convert_rgb(int r, int g, int b);
void				get_side_textures(t_global *gl);
void				draw_sprites(t_global *gl);
void				keymove(t_global *gl);
void				rot_left(t_global *gl);
void				rot_right(t_global *gl);
void				move_left(t_global *gl);
void				move_right(t_global *gl);

#endif
