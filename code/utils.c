/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:26:01 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/01 20:26:03 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_path_char(char *buff)
{
	if (*buff != 'N' && *buff != 'S' && *buff != 'W' && *buff != 'E' &&
		*buff != 'R' && *buff != 'C' && *buff != 'F' && *buff != '0' &&
		*buff != '1' && *buff != ' ' && *buff != '\0')
		print_error("Error\nInvalid character in map file\n");
}

void	check_after_path(t_global *gl, char *buff, int i, char *s)
{
	if (i == gl->map.size_x)
	{
		while (*buff == ' ' || *buff == '\t')
			buff++;
		(*buff != '\0') ? print_error("Error\nInvalid character in R path\n")
			: 0;
	}
	if (i == gl->sky.rgb || i == gl->floor.rgb)
	{
		while (*buff == ' ' || *buff == '\t')
			buff++;
		(*buff != '\0') ?
			print_error("Error\nInvalid character in C/F path\n") : 0;
	}
	if (s == gl->map.n_path || s == gl->map.s_path || s == gl->map.sprite ||
		s == gl->map.e_path || s == gl->map.w_path)
	{
		while (*buff == ' ' || *buff == '\t')
			buff++;
		(*buff != '\0') ? print_error("Error\nInvalid character in Tex path\n")
			: 0;
	}
}

void	check_values(t_global *gl, char *buff)
{
	if (*buff != '\0' && gl->map.values > 0)
	{
		while (*buff == ' ' || *buff == '\t')
			buff++;
		if (*buff != '1' && *buff != '0' && *buff != '\0')
			gl->map.values--;
	}
}

void	check_map_char(char *buff)
{
	int c;

	c = -1;
	while (buff[++c])
		if (buff[c] != 'N' && buff[c] != 'S' && buff[c] != 'E' &&
			buff[c] != 'W' && buff[c] != ' ' && buff[c] != '1' &&
			buff[c] != '2' && buff[c] != '0')
			print_error("Error\nInvalid character in map\n");
}

void	map_err_check(t_global *gl, int num)
{
	if (gl->map.player > 1)
		print_error("Error\nToo many players in the map.");
	else if (gl->map.player == 0)
		print_error("Error\nThere's no player in the map.");
	floodfill(gl, (int)gl->me.posx, (int)gl->me.posy, &num);
	(gl->map.size_x < 3 || gl->map.size_y < 3) ?
		print_error("Error\nThe map is too small\n") : 0;
	(gl->cub.size_x < 1 || gl->cub.size_y < 1) ?
		print_error("Error\nThe resolution is too small\n") : 0;
}
