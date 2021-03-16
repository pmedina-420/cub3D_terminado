/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:10:12 by pmedina-          #+#    #+#             */
/*   Updated: 2021/01/07 18:10:13 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			x_pressed(t_global *gl)
{
	int i;

	i = -1;
	while (++i < gl->map.size_y)
		free(gl->me.worldmap[i]);
	free(gl->me.worldmap);
	mlx_destroy_image(gl->cub.mlx_p, gl->img.img);
	mlx_clear_window(gl->cub.mlx_p, gl->cub.win_p);
	mlx_destroy_window(gl->cub.mlx_p, gl->cub.win_p);
	exit(0);
	return (0);
}

int			key_released(int keycode, t_global *gl)
{
	gl->key.w_key = (keycode == W && gl->key.w_key == 1) ? 0 : gl->key.w_key;
	gl->key.a_key = (keycode == A && gl->key.a_key == 1) ? 0 : gl->key.a_key;
	gl->key.s_key = (keycode == S && gl->key.s_key == 1) ? 0 : gl->key.s_key;
	gl->key.d_key = (keycode == D && gl->key.d_key == 1) ? 0 : gl->key.d_key;
	gl->key.l_key = (keycode == LEFT && gl->key.l_key == 1) ? 0 : gl->key.l_key;
	gl->key.r_key = (keycode == RIGHT && gl->key.r_key == 1) ?
		0 : gl->key.r_key;
	return (0);
}

int			key_pressed(int keycode, t_global *gl)
{
	int i;

	gl->key.w_key = (keycode == W && gl->key.w_key == 0) ? 1 : gl->key.w_key;
	gl->key.a_key = (keycode == A && gl->key.a_key == 0) ? 1 : gl->key.a_key;
	gl->key.s_key = (keycode == S && gl->key.s_key == 0) ? 1 : gl->key.s_key;
	gl->key.d_key = (keycode == D && gl->key.d_key == 0) ? 1 : gl->key.d_key;
	gl->key.l_key = (keycode == LEFT && gl->key.l_key == 0) ? 1 : gl->key.l_key;
	gl->key.r_key = (keycode == RIGHT && gl->key.r_key == 0) ?
		1 : gl->key.r_key;
	if (keycode == ESC)
	{
		i = -1;
		while (++i < gl->map.size_y)
			free(gl->me.worldmap[i]);
		free(gl->me.worldmap);
		mlx_clear_window(gl->cub.mlx_p, gl->cub.win_p);
		mlx_destroy_window(gl->cub.mlx_p, gl->cub.win_p);
		exit(0);
	}
	return (0);
}

void		keymove(t_global *gl)
{
	if (gl->key.w_key == 1)
	{
		gl->me.posx += (gl->me.worldmap[(int)(gl->me.posx +
			gl->me.dirx * gl->me.movespeed)][(int)gl->me.posy] ==
			'0') ? (gl->me.dirx * gl->me.movespeed) : 0;
		gl->me.posy += (gl->me.worldmap[(int)gl->me.posx]
			[(int)(gl->me.posy + gl->me.diry * gl->me.movespeed)] ==
			'0') ? (gl->me.diry * gl->me.movespeed) : 0;
	}
	if (gl->key.s_key == 1)
	{
		gl->me.posx -= (gl->me.worldmap[(int)(gl->me.posx -
			gl->me.dirx * gl->me.movespeed)][(int)gl->me.posy] ==
			'0') ? (gl->me.dirx * gl->me.movespeed) : 0;
		gl->me.posy -= (gl->me.worldmap[(int)gl->me.posx]
			[(int)(gl->me.posy - gl->me.diry * gl->me.movespeed)]
			== '0') ? (gl->me.diry * gl->me.movespeed) : 0;
	}
	move_right(gl);
	rot_left(gl);
	rot_right(gl);
	move_left(gl);
}
