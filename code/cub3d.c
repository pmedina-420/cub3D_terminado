/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caca.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:50:55 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/16 20:16:41 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int argc, char **argv)
{
	t_global	gl;

	check_arguments(&gl, argc, argv);
	if (argc == 2)
	{
		readmap(&gl, argv[1]);
		gl.cub.mlx_p = mlx_init();
		gl.cub.win_p = mlx_new_window(gl.cub.mlx_p, gl.cub.size_x,
			gl.cub.size_y, "cub3D");
		gl.img.img = mlx_new_image(gl.cub.mlx_p, gl.cub.size_x, gl.cub.size_y);
		gl.img.addr = mlx_get_data_addr(gl.img.img, &gl.img.b_p_p,
			&gl.img.line_length, &gl.img.endian);
		loadtextures(&gl);
		mlx_hook(gl.cub.win_p, 02, (0L << 0), key_pressed, &gl);
		mlx_hook(gl.cub.win_p, 03, (1L << 1), key_released, &gl);
		mlx_hook(gl.cub.win_p, 17, (1L << 17), x_pressed, &gl);
		mlx_loop_hook(gl.cub.mlx_p, raycasting, &gl);
		mlx_loop(gl.cub.mlx_p);
	}
}

void			check_arguments(t_global *gl, int argc, char **argv)
{
	(argc == 1) ? print_error("Error\nNo map specified\n") : 0;
	(argc >= 4) ? print_error("Error\nToo many arguments\n") : 0;
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
			print_error("Error\nThe second argument is not '--save'\n");
		readmap(gl, argv[1]);
		screenshot(gl);
	}
}

void			print_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

void			set_pos(t_global *gl)
{
	gl->cub.size_x = -1;
	gl->cub.size_y = -1;
	gl->key.w_key = 0;
	gl->key.a_key = 0;
	gl->key.s_key = 0;
	gl->key.d_key = 0;
	gl->key.l_key = 0;
	gl->key.r_key = 0;
	gl->me.drawstart = 0;
	gl->me.drawend = 0;
	gl->me.movespeed = 0.07;
	gl->me.rotspeed = 0.06;
	gl->sp.num = 0;
	gl->me.worldmap = NULL;
	gl->map.player = 0;
	gl->map.size_y = 0;
	gl->map.size_x = 0;
	gl->map.county = -1;
	gl->map.countx = 0;
	gl->floor.rgb = -1;
	gl->sky.rgb = -1;
}

char			*dup_tex(char *tex, int num, char *buff)
{
	(tex != NULL) ? print_error("Error\nTexture duplicated\n")
		: 0;
	(num != -1) ? print_error("Error\nTexture duplicated\n")
		: 0;
	buff++;
	return (buff);
}
