/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:24:56 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/01 20:24:57 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->b_p_p / 8));
	*(unsigned int*)dst = color;
}

int			convert_rgb(long r, long g, long b)
{
	int		rgb;

	if (r > 255 || g > 255 || b > 255)
		print_error("Error\nThe maximum RGB value is 255\n");
	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void		get_floor_rgb(t_global *gl, char *buff)
{
	if (*buff == 'F')
	{
		buff = dup_tex(NULL, gl->floor.rgb, buff);
		while (*buff == ' ' || *buff == '\t')
			buff++;
		if (*buff == '-')
			print_error("Error\nThe minimum RGB value is 0\n");
		if (ft_isdigit(*buff) == 0)
			print_error("Error\nInvalid character in F path\n");
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->floor.r = ft_atoi(buff);
		buff = skip_spaces(buff);
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->floor.g = ft_atoi(buff);
		buff = skip_spaces(buff);
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->floor.b = ft_atoi(buff);
		while (*buff >= '0' && *buff <= '9')
			buff++;
		while (*buff == ' ' || *buff == '\t')
			buff++;
		gl->floor.rgb = convert_rgb(gl->floor.r, gl->floor.g, gl->floor.b);
		check_after_path(gl, buff, gl->floor.rgb, "a");
		gl->map.values++;
	}
}

void		get_sky_rgb(t_global *gl, char *buff)
{
	if (*buff == 'C')
	{
		buff = dup_tex(NULL, gl->sky.rgb, buff);
		while (*buff == ' ' || *buff == '\t')
			buff++;
		if (*buff == '-')
			print_error("Error\nThe minimum RGB value is 0\n");
		if (ft_isdigit(*buff) == 0)
			print_error("Error\nInvalid character in C path\n");
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->sky.r = ft_atoi(buff);
		buff = skip_spaces(buff);
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->sky.g = ft_atoi(buff);
		buff = skip_spaces(buff);
		ft_atoi_check(buff) < 0 ? print_error("Error\nCol") : 0;
		gl->sky.b = ft_atoi(buff);
		while (*buff >= '0' && *buff <= '9')
			buff++;
		while (*buff == ' ' || *buff == '\t')
			buff++;
		gl->sky.rgb = convert_rgb(gl->sky.r, gl->sky.g, gl->sky.b);
		check_after_path(gl, buff, gl->sky.rgb, "a");
		gl->map.values++;
	}
}

char		*skip_spaces(char *buff)
{
	while (*buff >= '0' && *buff <= '9')
		buff++;
	while (*buff != ',' && (*buff == ' ' || *buff == '\t'))
	{
		if (*buff >= '0' && *buff <= '9')
			print_error("Error\nError between RGB values\n");
		buff++;
	}
	if (*buff == ',')
		buff++;
	else
		print_error("Error\nComa missing between RGB values\n");
	while (*buff == ' ' || *buff == '\t')
		buff++;
	if (*buff == '-')
		print_error("Error\nThe minimum RGB value is 0\n");
	return (buff);
}
