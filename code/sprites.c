/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:58:13 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/03 16:58:14 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		mall_sp(t_global *gl)
{
	if (!(gl->sp.order = (int *)malloc(sizeof(int) * gl->sp.num + 1)))
		print_error("Error\nCan't allocate the sprites' order\n");
}

void		sort_sprites(t_global *gl)
{
	int		p;
	int		a;
	int		t;

	p = -1;
	a = -1;
	while (++p < gl->sp.num)
	{
		gl->sp.dist = sqrt((pow(gl->arr[p].x - gl->me.posx, 2.0)) +
			pow(gl->arr[p].y - gl->me.posy, 2.0));
		gl->arr[p].tmp = gl->sp.dist;
	}
	while (++a < gl->sp.num - 1)
	{
		t = a + 1;
		while (t < gl->sp.num)
		{
			sort_values(gl, a, t);
			t++;
		}
	}
}

void		sort_values(t_global *gl, int a, int t)
{
	int		tmp;

	if (gl->arr[gl->sp.order[a]].tmp < gl->arr[gl->sp.order[t]].tmp)
	{
		tmp = gl->sp.order[a];
		gl->sp.order[a] = gl->sp.order[t];
		gl->sp.order[t] = tmp;
	}
}

void		set_sprite_values(t_global *gl, int s)
{
	gl->sp.spx = gl->arr[gl->sp.order[s]].x - gl->me.posx;
	gl->sp.spy = gl->arr[gl->sp.order[s]].y - gl->me.posy;
	gl->sp.invdet = 1.0 / (gl->me.planex * gl->me.diry -
		gl->me.dirx * gl->me.planey);
	gl->sp.transformx = gl->sp.invdet * (gl->me.diry * gl->sp.spx -
		gl->me.dirx * gl->sp.spy);
	gl->sp.transformy = gl->sp.invdet * (-gl->me.planey * gl->sp.spx +
		gl->me.planex * gl->sp.spy);
	gl->sp.sp_screenx = (int)((gl->cub.size_x / 2) * (1 +
		gl->sp.transformx / gl->sp.transformy));
	gl->sp.s_y = abs((int)(gl->cub.size_y / gl->sp.transformy));
	gl->sp.drawstarty = -gl->sp.s_y / 2 + gl->cub.size_y / 2;
	gl->sp.drawstarty = (gl->sp.drawstarty < 0) ?
		0 : gl->sp.drawstarty;
	gl->sp.drawendy = gl->sp.s_y / 2 + gl->cub.size_y / 2;
	gl->sp.drawendy = (gl->sp.drawendy >= gl->cub.size_y) ?
		gl->cub.size_y : gl->sp.drawendy;
	gl->sp.s_x = abs((int)(gl->cub.size_y / gl->sp.transformy));
	gl->sp.drawstartx = -gl->sp.s_x / 2 + gl->sp.sp_screenx;
	gl->sp.drawstartx = (gl->sp.drawstartx < 0) ? 0 : gl->sp.drawstartx;
	gl->sp.drawendx = gl->sp.s_x / 2 + gl->sp.sp_screenx;
	gl->sp.drawendx = (gl->sp.drawendx >= gl->cub.size_x) ?
		gl->cub.size_x : gl->sp.drawendx;
}

void		draw_sprites(t_global *gl)
{
	int stripe;
	int r;

	stripe = gl->sp.drawstartx - 1;
	while (++stripe < gl->sp.drawendx)
	{
		gl->sp.texx = (int)(256 * (stripe - (-gl->sp.s_x / 2 +
			gl->sp.sp_screenx)) * gl->sp.wid / gl->sp.s_x) / 256;
		if (gl->sp.transformy > 0 && stripe > 0 && stripe < gl->cub.size_x
			&& gl->sp.transformy < gl->sp.zbuffer[stripe])
		{
			r = gl->sp.drawstarty - 1;
			while (++r < gl->sp.drawendy)
			{
				gl->sp.d = (r) * 256 - gl->cub.size_y * 128 + gl->sp.s_y * 128;
				gl->sp.texy = ((gl->sp.d * gl->sp.hei) / gl->sp.s_y) / 256;
				gl->sp.color = (int)gl->sp.buffer[gl->sp.hei *
					gl->sp.texy + gl->sp.texx];
				if (gl->sp.color != 0)
					my_mlx_pixel_put(&gl->img, stripe, r, gl->sp.color);
			}
		}
	}
}
