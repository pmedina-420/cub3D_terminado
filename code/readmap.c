/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:18:09 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/03 17:18:11 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			readmap(t_global *gl, char *str)
{
	int		fd;
	int		num;
	int		f;

	fd = 0;
	num = 0;
	f = -1;
	set_pos(gl);
	path_check(gl, fd, str);
	(!(gl->arr = (t_arr_sp *)malloc(sizeof(t_arr_sp) * (gl->sp.num))))
		? print_error("Error\nCan't allocate gl->arr.") : 0;
	(!(gl->me.worldmap = (char **)malloc(sizeof(char *) * gl->map.size_y + 1)))
		? print_error("Error\nCan't allocate the map\n") : 0;
	(!(gl->me.fakemap = (char **)malloc(sizeof(char *) * gl->map.size_y + 1)))
		? print_error("Error\nCan't allocate the map\n") : 0;
	fd = open(str, O_RDONLY);
	(fd < 0) ? print_error("Error\nInvalid map\n") : 0;
	map_check(gl, fd);
	map_err_check(gl, num);
	while (++f < gl->map.size_y)
		free(gl->me.fakemap[f]);
	free(gl->me.fakemap);
	return (0);
}

void		path_check(t_global *gl, int fd, char *str)
{
	char	*buff;
	int		c;

	fd = open(str, O_RDONLY);
	(fd < 0) ? print_error("Error\nInvalid map\n") : 0;
	while ((gl->map.ret = (get_next_line(fd, &buff))) >= 0)
	{
		gl->map.p = buff;
		c = 0;
		while (*buff == ' ' || *buff == '\t')
			buff++;
		check_path_char(buff);
		get_sizes(gl, buff);
		get_north_texture_path(gl, buff, c);
		get_south_texture_path(gl, buff, c);
		get_east_texture_path(gl, buff, c);
		get_west_texture_path(gl, buff, c);
		get_floor_rgb(gl, buff);
		get_sky_rgb(gl, buff);
		missing_paths(gl, buff);
		free(gl->map.p);
		if (gl->map.ret == 0)
			break ;
	}
}

void		get_sizes(t_global *gl, char *buff)
{
	if (*buff == '0' && ft_strchr(buff, '1') == 0)
		print_error("Error\nInvalid character in map file\n");
	if (*buff == '1' || ((*buff == '0' && ft_strchr(buff, '1') != 0)))
	{
		gl->map.size_y++;
		gl->map.size_x = ((int)ft_strlen(buff) > gl->map.size_x) ?
			ft_strlen(buff) : gl->map.size_x;
		while (*buff && ft_strchr(buff, '2') != 0)
		{
			if (*buff == '2')
				gl->sp.num++;
			buff++;
		}
	}
	if (*buff == 'R')
	{
		buff = get_resolution(gl, buff);
		check_after_path(gl, buff, gl->map.size_y, "0");
		gl->map.values++;
	}
}

void		map_check(t_global *gl, int fd)
{
	char	*buff;
	int		s;

	s = 0;
	while ((gl->map.ret = (get_next_line(fd, &buff))) >= 0)
	{
		gl->map.p = buff;
		check_values(gl, buff);
		if ((*buff == '1' || *buff == '0' || *buff == ' ') && gl->map.size_x > 0
			&& gl->map.size_y > 0 && s < gl->map.size_y && gl->map.values == 0)
		{
			gl->map.c = 0;
			gl->map.countx = 0;
			gl->map.county++;
			check_map_char(buff);
			fillmap(gl, gl->map.c, s++, buff);
			get_player_pos(gl, buff);
		}
		else if (gl->map.county >= 0 && gl->map.county < gl->map.size_y - 1)
			(*buff == '\0') ? print_error("Error\nEmpty lines in map\n")
				: check_map_char(buff);
		free(gl->map.p);
		if (gl->map.ret == 0)
			break ;
	}
}

void		fillmap(t_global *gl, int c, int s, char *buff)
{
	(!(gl->me.worldmap[s] = (char *)malloc(sizeof(char) * ft_strlen(buff)
		+ 1))) ? print_error("Error\nCan't allocate the map\n") : 0;
	while (buff[c])
	{
		if (buff[c] == 'N' || buff[c] == 'S' || buff[c] == 'E' ||
			buff[c] == 'W' || buff[c] == ' ')
			gl->me.worldmap[s][c] = '0';
		else
			gl->me.worldmap[s][c] = buff[c];
		c++;
	}
	gl->me.worldmap[s][c] = '\0';
	gl->me.fakemap[s] = ft_strdup(gl->me.worldmap[s]);
}
