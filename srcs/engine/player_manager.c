/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:47:56 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 18:51:43 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	check_life(t_all *a)
{
	if (a->life == 0)
		ft_exit(0, "You are died !", &(a->p), a);
}

void	check_trap(t_all *a)
{
	int		i;
	int		x;
	int		y;
	int		life;

	x = (int)a->d.pos_x;
	y = (int)a->d.pos_y;
	if (a->map.worldmap[x][y] == 3 ||
		(a->life < 5 && a->map.worldmap[x][y] == 2))
	{
		life = a->map.worldmap[x][y] == 3 ? -1 : 1;
		i = -1;
		a->map.worldmap[x][y] = 0;
		while (++i < a->map.nbsprite)
		{
			if (a->map.sprite[i].x == x && a->map.sprite[i].y == y)
			{
				a->map.sprite[i].x = -1;
				a->map.sprite[i].y = -1;
			}
		}
		a->life += life;
		check_life(a);
	}
}
