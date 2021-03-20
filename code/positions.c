/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:12:30 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/03 18:12:31 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_pos(t_global *gl, char *buff)
{
	if (ft_strchr(buff, 'N') != 0)
	{
		gl->map.player++;
		while (*buff != 'N')
		{
			buff++;
			gl->map.countx++;
		}
		gl->me.posx = gl->map.county + 0.5;
		gl->me.posy = gl->map.countx + 0.5;
		gl->me.dirx = -1;
		gl->me.diry = 0;
		gl->me.planex = 0;
		gl->me.planey = 0.66;
		buff++;
		if (ft_strchr(buff, 'N') != 0 || ft_strchr(buff, 'S') != 0 ||
			ft_strchr(buff, 'E') != 0 || ft_strchr(buff, 'W') != 0)
			gl->map.player++;
	}
}

void	south_pos(t_global *gl, char *buff)
{
	if (ft_strchr(buff, 'S') != 0)
	{
		gl->map.player++;
		while (*buff != 'S')
		{
			buff++;
			gl->map.countx++;
		}
		gl->me.posx = gl->map.county + 0.5;
		gl->me.posy = gl->map.countx + 0.5;
		gl->me.dirx = 1;
		gl->me.diry = 0;
		gl->me.planex = 0;
		gl->me.planey = -0.66;
		buff++;
		if (ft_strchr(buff, 'N') != 0 || ft_strchr(buff, 'S') != 0 ||
			ft_strchr(buff, 'E') != 0 || ft_strchr(buff, 'W') != 0)
			gl->map.player++;
	}
}

void	east_pos(t_global *gl, char *buff)
{
	if (ft_strchr(buff, 'E') != 0)
	{
		gl->map.player++;
		while (*buff != 'E')
		{
			buff++;
			gl->map.countx++;
		}
		gl->me.posx = gl->map.county + 0.5;
		gl->me.posy = gl->map.countx + 0.5;
		gl->me.dirx = 0;
		gl->me.diry = 1;
		gl->me.planex = 0.66;
		gl->me.planey = 0;
		buff++;
		if (ft_strchr(buff, 'N') != 0 || ft_strchr(buff, 'S') != 0 ||
			ft_strchr(buff, 'E') != 0 || ft_strchr(buff, 'W') != 0)
			gl->map.player++;
	}
}

void	west_pos(t_global *gl, char *buff)
{
	if (ft_strchr(buff, 'W') != 0)
	{
		gl->map.player++;
		while (*buff != 'W')
		{
			buff++;
			gl->map.countx++;
		}
		gl->me.posx = gl->map.county + 0.5;
		gl->me.posy = gl->map.countx + 0.5;
		gl->me.dirx = 0.0;
		gl->me.diry = -1;
		gl->me.planex = -0.66;
		gl->me.planey = 0.0;
		buff++;
		if (ft_strchr(buff, 'N') != 0 || ft_strchr(buff, 'S') != 0 ||
			ft_strchr(buff, 'E') != 0 || ft_strchr(buff, 'W') != 0)
			gl->map.player++;
	}
}

void	floodfill(t_global *gl, int x, int y, int *num)
{

	if (x < 0 || y < 0 || y >= gl->map.size_x || x >= gl->map.size_y)
		printf("Error\nOpen map\n");
	if ((ft_strchr(" 02NESW", gl->me.fakemap[x][y]) != NULL))
	{
		if (gl->me.fakemap[x][y] == '2')
		{
			gl->arr[*num].x = x + 0.5;
			gl->arr[*num].y = y + 0.5;
			*num = *num + 1;
		}
		gl->me.fakemap[x][y] = '*';
		floodfill(gl, x + 1, y, num);
		floodfill(gl, x, y + 1, num);
		floodfill(gl, x - 1, y, num);
		floodfill(gl, x, y - 1, num);
	}
}
