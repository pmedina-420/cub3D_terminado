/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:50:30 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/01 20:50:31 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		raycasting(t_global *gl)
{
	int	sizex;

	sizex = -1;
	mall_sp(gl);
	while (++sizex < gl->cub.size_x)
	{
		gl->me.hit = 0;
		gl->me.mapx = (int)gl->me.posx;
		gl->me.mapy = (int)gl->me.posy;
		set_raycasting_values(gl, sizex);
		set_raylen(gl);
		set_draw(gl);
		get_textures(gl);
		set_textures(gl);
		draw_textures(gl, sizex);
		gl->sp.zbuffer[sizex] = gl->me.raylen;
	}
	raycasting_sprites(gl);
	free(gl->sp.order);
	mlx_put_image_to_window(gl->cub.mlx_p, gl->cub.win_p, gl->img.img, 0, 0);
	keymove(gl);
	return (1);
}

void	set_raycasting_values(t_global *gl, int sizex)
{
	gl->me.camerax = 2 * sizex / (double)gl->cub.size_x - 1;
	gl->me.raydirx = gl->me.dirx + gl->me.planex * gl->me.camerax;
	gl->me.raydiry = gl->me.diry + gl->me.planey * gl->me.camerax;
	gl->me.deltadistx = fabs(1 / gl->me.raydirx);
	gl->me.deltadisty = fabs(1 / gl->me.raydiry);
	if (gl->me.raydirx < 0)
	{
		gl->me.stepx = -1;
		gl->me.sidistx = (gl->me.posx - gl->me.mapx) * gl->me.deltadistx;
	}
	else
	{
		gl->me.stepx = 1;
		gl->me.sidistx = (gl->me.mapx + 1.0 - gl->me.posx) * gl->me.deltadistx;
	}
	if (gl->me.raydiry < 0)
	{
		gl->me.stepy = -1;
		gl->me.sidisty = (gl->me.posy - gl->me.mapy) * gl->me.deltadisty;
	}
	else
	{
		gl->me.stepy = 1;
		gl->me.sidisty = (gl->me.mapy + 1.0 - gl->me.posy) * gl->me.deltadisty;
	}
}

void	set_raylen(t_global *gl)
{
	while (gl->me.hit == 0)
	{
		if (gl->me.sidistx < gl->me.sidisty)
		{
			gl->me.sidistx += gl->me.deltadistx;
			gl->me.mapx += gl->me.stepx;
			gl->me.side = 0;
		}
		else
		{
			gl->me.sidisty += gl->me.deltadisty;
			gl->me.mapy += gl->me.stepy;
			gl->me.side = 1;
		}
		if (gl->me.worldmap[gl->me.mapx][gl->me.mapy] == '1')
			gl->me.hit = 1;
	}
	if (gl->me.side == 0)
		gl->me.raylen = (gl->me.mapx - gl->me.posx + (1 - gl->me.stepx)
			/ 2) / gl->me.raydirx;
	else
		gl->me.raylen = (gl->me.mapy - gl->me.posy + (1 - gl->me.stepy)
			/ 2) / gl->me.raydiry;
}

void	set_draw(t_global *gl)
{
	gl->me.draw = (gl->cub.size_y / gl->me.raylen);
	gl->me.drawstart = -gl->me.draw / 2 + gl->cub.size_y / 2;
	gl->me.drawstart = (gl->me.drawstart < 0) ? 0 : gl->me.drawstart;
	gl->me.drawend = gl->me.draw / 2 + gl->cub.size_y / 2;
	gl->me.drawend = (gl->me.drawend >= gl->cub.size_y) ?
		gl->cub.size_y - 1 : gl->me.drawend;
}

void	raycasting_sprites(t_global *gl)
{
	int	i;
	int s;

	if (gl->sp.num > 0)
	{
		i = -1;
		while (++i < gl->sp.num)
		{
			gl->sp.order[i] = i;
			gl->arr[i].tmp = ((gl->me.posy - gl->arr[i].y) *
			(gl->me.posy - gl->arr[i].y) + (gl->me.posx -
			gl->arr[i].x) * (gl->me.posx - gl->arr[i].x));
		}
		sort_sprites(gl);
		s = -1;
		while (++s < gl->sp.num)
		{
			set_sprite_values(gl, s);
			draw_sprites(gl);
		}
	}
}
