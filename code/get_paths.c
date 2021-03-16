/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:55:05 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/02 16:55:06 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_north_texture_path(t_global *gl, char *buff, int c)
{
	if (*buff == 'N')
	{
		buff++;
		if (*buff == 'O')
		{
			buff++;
			while (*buff == ' ' || *buff == '\t')
				buff++;
			(*buff == '.') ? 0 :
				print_error("Error\nPaths must start with ./\n");
			if (!(gl->map.n_path = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				print_error("Error\nCan't allocate the north texture\n");
			while (*buff)
			{
				if (*buff == ' ' || *buff == '\t' || *buff == '\0')
					break ;
				gl->map.n_path[c] = *buff;
				c++;
				buff++;
			}
			gl->map.n_path[c] = '\0';
			check_after_path(gl, buff, -1, gl->map.n_path);
			gl->map.values++;
		}
	}
}

void		get_south_texture_path(t_global *gl, char *buff, int c)
{
	if (*buff == 'S')
	{
		buff++;
		if (*buff == 'O')
		{
			buff = fill_south_path(gl, buff, c);
			check_after_path(gl, buff, -1, gl->map.s_path);
			gl->map.values++;
		}
		else
			get_sprite_texture(gl, buff, c);
	}
}

void		get_east_texture_path(t_global *gl, char *buff, int c)
{
	if (*buff == 'E')
	{
		buff++;
		if (*buff == 'A')
		{
			buff++;
			while (*buff == ' ' || *buff == '\t')
				buff++;
			(*buff == '.') ? 0 :
				print_error("Error\nPaths must start with ./\n");
			if (!(gl->map.e_path = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				print_error("Error\nCan't allocate the east texture\n");
			while (*buff)
			{
				if (*buff == ' ' || *buff == '\t' || *buff == '\0')
					break ;
				gl->map.e_path[c] = *buff;
				c++;
				buff++;
			}
			gl->map.e_path[c] = '\0';
			check_after_path(gl, buff, -1, gl->map.e_path);
			gl->map.values++;
		}
	}
}

void		get_west_texture_path(t_global *gl, char *buff, int c)
{
	if (*buff == 'W')
	{
		buff++;
		if (*buff == 'E')
		{
			buff++;
			while (*buff == ' ' || *buff == '\t')
				buff++;
			(*buff == '.') ? 0 :
				print_error("Error\nPaths must start with ./\n");
			if (!(gl->map.w_path = malloc(sizeof(char) * ft_strlen(buff) + 1)))
				print_error("Error\nCan't allocate the west texture\n");
			while (*buff)
			{
				if (*buff == ' ' || *buff == '\t' || *buff == '\0')
					break ;
				gl->map.w_path[c] = *buff;
				c++;
				buff++;
			}
			gl->map.w_path[c] = '\0';
			check_after_path(gl, buff, -1, gl->map.w_path);
			gl->map.values++;
		}
	}
}

void		get_sprite_texture(t_global *gl, char *buff, int c)
{
	while (*buff == ' ' || *buff == '\t')
		buff++;
	(*buff == '.') ? 0 : print_error("Error\nPaths must start with ./\n");
	if (!(gl->map.sprite = malloc(sizeof(char) * ft_strlen(buff) + 1)))
		print_error("Error\nCan't allocate the sprite texture\n");
	while (*buff)
	{
		if (*buff == ' ' || *buff == '\t' || *buff == '\0')
			break ;
		gl->map.sprite[c] = *buff;
		c++;
		buff++;
	}
	gl->map.sprite[c] = '\0';
	check_after_path(gl, buff, -1, gl->map.sprite);
	gl->map.values++;
}
