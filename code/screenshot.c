/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:52:04 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/01 19:52:06 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rgbit(unsigned char *s, int i)
{
	s[0] = (unsigned char)i;
	s[1] = (unsigned char)(i >> 8);
	s[2] = (unsigned char)(i >> 16);
	s[3] = (unsigned char)(i >> 24);
}

void	bmpheader(t_global *gl, int padsize, int fd)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (gl->cub.size_x * 3 * gl->cub.size_y) +
		(padsize * gl->cub.size_x);
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	rgbit(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	rgbit(header + 18, gl->cub.size_x);
	rgbit(header + 22, -gl->cub.size_y);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
	write(fd, gl->img.addr, gl->cub.size_y * gl->cub.size_x * 4);
}

void	screenshot(t_global *gl)
{
	int fd;
	int padsize;

	gl->cub.mlx_p = mlx_init();
	gl->cub.win_p = mlx_new_window(gl->cub.mlx_p, gl->cub.size_x,
		gl->cub.size_y, "cub3D");
	gl->img.img = mlx_new_image(gl->cub.mlx_p, gl->cub.size_x, gl->cub.size_y);
	gl->img.addr = mlx_get_data_addr(gl->img.img, &gl->img.b_p_p,
		&gl->img.line_length, &gl->img.endian);
	loadtextures(gl);
	raycasting(gl);
	if (!(fd = open("./cub3d.bmp", O_WRONLY | O_CREAT, S_IRWXU |
	O_TRUNC | O_APPEND)))
		print_error("Error\nThe .bmp file can't be created\n");
	padsize = (4 - (gl->cub.size_x * 3) % 4) % 4;
	bmpheader(gl, padsize, fd);
	close(fd);
	exit(0);
}
