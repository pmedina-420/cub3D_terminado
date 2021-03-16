/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:12:26 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/11 18:12:27 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_resolution(t_global *gl, char *buff)
{
	buff++;
	while (*buff == ' ' || *buff == '\t')
		buff++;
	gl->cub.size_x = ft_atoi(buff) > 2560 ? 2560 : ft_atoi(buff);
	while (*buff >= '0' && *buff <= '9')
		buff++;
	while (*buff == ' ' || *buff == '\t')
		buff++;
	gl->cub.size_y = ft_atoi(buff) > 1440 ? 1440 : ft_atoi(buff);
	while (*buff >= '0' && *buff <= '9')
		buff++;
	return (buff);
}

char	*fill_south_path(t_global *gl, char *buff, int c)
{
	buff++;
	while (*buff == ' ' || *buff == '\t')
		buff++;
	(*buff == '.') ? 0 :
		print_error("Error\nPaths must start with ./\n");
	if (!(gl->map.s_path = (char *)malloc(sizeof(char)
		* ft_strlen(buff) + 1)))
		print_error("Error\nCan't allocate the south texture\n");
	while (*buff)
	{
		if (*buff == ' ' || *buff == '\t' || *buff == '\0')
			break ;
		gl->map.s_path[c] = *buff;
		c++;
		buff++;
	}
	gl->map.s_path[c] = '\0';
	return (buff);
}

void	missing_paths(t_global *gl, char *buff)
{
	if ((*buff == '1' || *buff == ' ' || *buff == '0' || *buff == '2')
		&& (gl->map.n_path == NULL || gl->map.s_path == NULL ||
		gl->map.e_path == NULL || gl->map.w_path == NULL ||
		gl->map.sprite == NULL || gl->sky.rgb == -1 ||
		gl->floor.rgb == -1))
		print_error("Error\nMap must be at the end of the file\n");
}

void	get_player_pos(t_global *gl, char *buff)
{
	north_pos(gl, buff);
	south_pos(gl, buff);
	east_pos(gl, buff);
	west_pos(gl, buff);
}

void	resize_textures(t_global *gl)
{
	(gl->n_tex.wid > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->n_tex.hei > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->s_tex.wid > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->s_tex.hei > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->e_tex.wid > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->e_tex.hei > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->w_tex.wid > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->w_tex.hei > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->sp.wid > 64) ? print_error("Error\nInvalid texture size\n") : 0;
	(gl->sp.hei > 64) ? print_error("Error\nInvalid texture size\n") : 0;
}
