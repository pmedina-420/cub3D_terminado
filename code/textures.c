/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:11:51 by pmedina-          #+#    #+#             */
/*   Updated: 2021/02/15 18:11:53 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loadtextures(t_global *gl)
{
	if (!(gl->n_tex.tex = mlx_xpm_file_to_image(gl->cub.mlx_p, gl->map.n_path,
		&gl->n_tex.wid, &gl->n_tex.hei)))
		print_error("Error\nInvalid north texture\n");
	if (!(gl->s_tex.tex = mlx_xpm_file_to_image(gl->cub.mlx_p, gl->map.s_path,
		&gl->s_tex.wid, &gl->s_tex.hei)))
		print_error("Error\nInvalid south texture\n");
	if (!(gl->e_tex.tex = mlx_xpm_file_to_image(gl->cub.mlx_p, gl->map.e_path,
		&gl->e_tex.wid, &gl->e_tex.hei)))
		print_error("Error\nInvalid east texture\n");
	if (!(gl->w_tex.tex = mlx_xpm_file_to_image(gl->cub.mlx_p, gl->map.w_path,
		&gl->w_tex.wid, &gl->w_tex.hei)))
		print_error("Error\nInvalid west texture\n");
	gl->sp.tex = mlx_xpm_file_to_image(gl->cub.mlx_p, gl->map.sprite,
		&gl->sp.wid, &gl->sp.hei);
	if (!(gl->sp.zbuffer = (double *)malloc(sizeof(double) *
		gl->cub.size_x + 1)))
		print_error("Error\nCan't allocate zbuffer\n");
	resize_textures(gl);
	(gl->map.n_path != NULL) ? free(gl->map.n_path) : 0;
	(gl->map.s_path != NULL) ? free(gl->map.s_path) : 0;
	(gl->map.e_path != NULL) ? free(gl->map.e_path) : 0;
	(gl->map.w_path != NULL) ? free(gl->map.w_path) : 0;
}

void	get_textures(t_global *gl)
{
	if (gl->me.side == 0 && gl->me.stepx == -1)
	{
		gl->tex.hei = gl->n_tex.hei;
		gl->tex.wid = gl->n_tex.wid;
		gl->tex.buffer = (unsigned int *)mlx_get_data_addr(gl->n_tex.tex,
			&gl->n_tex.b_p_p, &gl->n_tex.line_length, &gl->n_tex.endian);
	}
	if (gl->me.side == 0 && gl->me.stepx == 1)
	{
		gl->tex.hei = gl->s_tex.hei;
		gl->tex.wid = gl->s_tex.wid;
		gl->tex.buffer = (unsigned int *)mlx_get_data_addr(gl->s_tex.tex,
			&gl->s_tex.b_p_p, &gl->s_tex.line_length, &gl->s_tex.endian);
	}
	get_side_textures(gl);
	gl->sp.buffer = (unsigned int *)mlx_get_data_addr(gl->sp.tex,
			&gl->sp.b_p_p, &gl->sp.line_length, &gl->sp.endian);
}

void	get_side_textures(t_global *gl)
{
	if (gl->me.side == 1 && gl->me.stepy == 1)
	{
		gl->tex.hei = gl->e_tex.hei;
		gl->tex.wid = gl->e_tex.wid;
		gl->tex.buffer = (unsigned int *)mlx_get_data_addr(gl->e_tex.tex,
			&gl->e_tex.b_p_p, &gl->e_tex.line_length, &gl->e_tex.endian);
	}
	else if (gl->me.side == 1 && gl->me.stepy == -1)
	{
		gl->tex.hei = gl->w_tex.hei;
		gl->tex.wid = gl->w_tex.wid;
		gl->tex.buffer = (unsigned int *)mlx_get_data_addr(gl->w_tex.tex,
			&gl->w_tex.b_p_p, &gl->w_tex.line_length, &gl->w_tex.endian);
	}
}

void	set_textures(t_global *gl)
{
	gl->tex.texnum = gl->me.worldmap[gl->me.mapx][gl->me.mapy];
	gl->tex.wallx = (gl->me.side == 0) ? (gl->me.posy + gl->me.raylen *
		gl->me.raydiry) : (gl->me.posx + gl->me.raylen * gl->me.raydirx);
	gl->tex.wallx -= floor((gl->tex.wallx));
	gl->tex.tex_x = (int)(gl->tex.wallx * (double)gl->tex.wid);
	gl->tex.tex_x = (gl->me.side == 0 && gl->me.raydirx > 0) ?
		(gl->tex.wid - gl->tex.tex_x - 1) : gl->tex.tex_x;
	gl->tex.tex_x = (gl->me.side == 1 && gl->me.raydiry < 0) ?
		(gl->tex.wid - gl->tex.tex_x - 1) : gl->tex.tex_x;
	gl->tex.step = 1.0 * gl->tex.hei / gl->me.draw;
	gl->tex.texpos = (gl->me.drawstart - gl->cub.size_y / 2 +
		gl->me.draw / 2) * gl->tex.step;
}

void	draw_textures(t_global *gl, int sizex)
{
	int y;

	y = -1;
	while (y++ < gl->me.drawstart)
		my_mlx_pixel_put(&gl->img, sizex, y, gl->sky.rgb);
	y = gl->me.drawstart;
	y--;
	while (y++ < gl->me.drawend)
	{
		gl->tex.tex_y = (int)gl->tex.texpos;
		gl->tex.texpos += gl->tex.step;
		gl->tex.color = (int)gl->tex.buffer[gl->tex.wid *
			gl->tex.tex_y + gl->tex.tex_x];
		my_mlx_pixel_put(&gl->img, sizex, y, gl->tex.color);
	}
	while (y++ < gl->cub.size_y - 1)
		my_mlx_pixel_put(&gl->img, sizex, y, gl->floor.rgb);
}
