/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillpaths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:31:23 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/21 17:31:24 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_north_path(t_global *gl, char *buff, int c)
{
	buff = dup_tex(gl->map.n_path, -1, buff);
	while (*buff == ' ' || *buff == '\t')
		buff++;
	(*buff == '.' || *buff == '/' || *buff == 'p') ? 0 :
		print_error("Error\nPaths must start with . or /\n");
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

void	fill_east_path(t_global *gl, char *buff, int c)
{
	buff = dup_tex(gl->map.e_path, -1, buff);
	while (*buff == ' ' || *buff == '\t')
		buff++;
	(*buff == '.' || *buff == '/' || *buff == 'p') ? 0 :
		print_error("Error\nPaths must start with . or /\n");
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

void	fill_west_path(t_global *gl, char *buff, int c)
{
	buff = dup_tex(gl->map.w_path, -1, buff);
	while (*buff == ' ' || *buff == '\t')
		buff++;
	(*buff == '.' || *buff == '/' || *buff == 'p') ? 0 :
		print_error("Error\nPaths must start with . or /\n");
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
