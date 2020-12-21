/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:34:18 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 12:02:36 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	move_forward(t_all *a)
{
	if (a->map.worldmap[(int)(a->d.pos_x + a->d.dir_x * (0.13 + a->sprint))]
													[(int)(a->d.pos_y)] < 1)
		a->d.pos_x += a->d.dir_x * (0.13 + a->sprint);
	if (a->map.worldmap[(int)(a->d.pos_x)][(int)(a->d.pos_y + a->d.dir_y *
													(0.13 + a->sprint))] < 1)
		a->d.pos_y += a->d.dir_y * (0.13 + a->sprint);
}

void	move_back(t_all *a)
{
	if (a->map.worldmap[(int)(a->d.pos_x - a->d.dir_x * (0.13))]
													[(int)(a->d.pos_y)] < 1)
		a->d.pos_x -= a->d.dir_x * (0.13 + (a->crouch ? a->sprint : 0));
	if (a->map.worldmap[(int)(a->d.pos_x)]
								[(int)(a->d.pos_y - a->d.dir_y * (0.13))] < 1)
		a->d.pos_y -= a->d.dir_y * (0.13 + (a->crouch ? a->sprint : 0));
}
