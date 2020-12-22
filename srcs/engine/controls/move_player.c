/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:34:18 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 12:49:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	move_forward(t_all *a)
{
	if (a->map.worldmap[(int)(a->d.pos_x + a->d.dir_x * (SPEED + a->sprint))]
													[(int)(a->d.pos_y)] != 1)
		a->d.pos_x += a->d.dir_x * (SPEED + a->sprint);
	if (a->map.worldmap[(int)(a->d.pos_x)][(int)(a->d.pos_y + a->d.dir_y *
													(SPEED + a->sprint))] != 1)
		a->d.pos_y += a->d.dir_y * (SPEED + a->sprint);
}

void	move_back(t_all *a)
{
	if (a->map.worldmap[(int)(a->d.pos_x - a->d.dir_x * (SPEED))]
													[(int)(a->d.pos_y)] != 1)
		a->d.pos_x -= a->d.dir_x * (SPEED + (a->crouch ? a->sprint : 0));
	if (a->map.worldmap[(int)(a->d.pos_x)]
								[(int)(a->d.pos_y - a->d.dir_y * (SPEED))] != 1)
		a->d.pos_y -= a->d.dir_y * (SPEED + (a->crouch ? a->sprint : 0));
}

void	move_right(t_all *a)
{
	a->d.pos_x += a->d.dir_y * (SPEED / 2);
	a->d.pos_y -= a->d.dir_x * (SPEED / 2);
	if (a->map.worldmap[(int)(a->d.pos_x)][(int)(a->d.pos_y)] == 1)
	{
		a->d.pos_x -= a->d.dir_y * (SPEED / 2);
		a->d.pos_y += a->d.dir_x * (SPEED / 2);
	}
}

void	move_left(t_all *a)
{
	a->d.pos_x -= a->d.dir_y * (SPEED / 2);
	a->d.pos_y += a->d.dir_x * (SPEED / 2);
	if (a->map.worldmap[(int)(a->d.pos_x)][(int)(a->d.pos_y)] == 1)
	{
		a->d.pos_x += a->d.dir_y * (SPEED / 2);
		a->d.pos_y -= a->d.dir_x * (SPEED / 2);
	}
}
