/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:46:48 by pmedina-          #+#    #+#             */
/*   Updated: 2021/03/02 16:46:50 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left(t_global *gl)
{
	if (gl->key.l_key == 1)
	{
		gl->me.oldirx = gl->me.dirx;
		gl->me.dirx = gl->me.dirx * cos(gl->me.rotspeed) -
			gl->me.diry * sin(gl->me.rotspeed);
		gl->me.diry = gl->me.oldirx * sin(gl->me.rotspeed) +
			gl->me.diry * cos(gl->me.rotspeed);
		gl->me.oldplanex = gl->me.planex;
		gl->me.planex = gl->me.planex * cos(gl->me.rotspeed) -
			gl->me.planey * sin(gl->me.rotspeed);
		gl->me.planey = gl->me.oldplanex * sin(gl->me.rotspeed) +
			gl->me.planey * cos(gl->me.rotspeed);
	}
}

void	rot_right(t_global *gl)
{
	if (gl->key.r_key == 1)
	{
		gl->me.oldirx = gl->me.dirx;
		gl->me.dirx = gl->me.dirx * cos(-gl->me.rotspeed) -
			gl->me.diry * sin(-gl->me.rotspeed);
		gl->me.diry = gl->me.oldirx * sin(-gl->me.rotspeed) +
			gl->me.diry * cos(-gl->me.rotspeed);
		gl->me.oldplanex = gl->me.planex;
		gl->me.planex = gl->me.planex * cos(-gl->me.rotspeed) -
			gl->me.planey * sin(-gl->me.rotspeed);
		gl->me.planey = gl->me.oldplanex * sin(-gl->me.rotspeed) +
			gl->me.planey * cos(-gl->me.rotspeed);
	}
}

void	move_left(t_global *gl)
{
	if (gl->key.a_key == 1)
	{
		gl->me.posy += (gl->me.worldmap[(int)gl->me.posx]
			[(int)(gl->me.posy + gl->me.dirx * gl->me.movespeed)] ==
			'0') ? (gl->me.dirx * gl->me.movespeed) : 0;
		gl->me.posx -= (gl->me.worldmap[(int)(gl->me.posx -
			gl->me.diry * gl->me.movespeed)][(int)gl->me.posy] ==
			'0') ? (gl->me.diry * gl->me.movespeed) : 0;
	}
}

void	move_right(t_global *gl)
{
	if (gl->key.d_key == 1)
	{
		gl->me.posy -= (gl->me.worldmap[(int)gl->me.posx]
			[(int)(gl->me.posy - gl->me.dirx * gl->me.movespeed)]
				== '0') ? (gl->me.dirx * gl->me.movespeed) : 0;
		gl->me.posx += (gl->me.worldmap[(int)(gl->me.posx +
			gl->me.diry * gl->me.movespeed)][(int)(gl->me.posy)]
				== '0') ? (gl->me.diry * gl->me.movespeed) : 0;
	}
}

void	map_start(t_global *gl, char *buff)
{
	if ((*buff == '\0' || ft_strchr(buff, '1') == 0) && gl->map.values != -1)
		gl->map.lines++;
}