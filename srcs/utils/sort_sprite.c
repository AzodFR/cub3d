/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 09:52:15 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/04 15:10:52 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

t_sprite		*swap_sprite(t_sprite *sprite, int i, int j)
{
	int		x;
	int		y;
	int		type;

	x = sprite[i].x;
	y = sprite[i].y;
	type = sprite[i].type;
	sprite[i].x = sprite[j].x;
	sprite[i].y = sprite[j].y;
	sprite[i].type = sprite[j].type;
	sprite[j].x = x;
	sprite[j].y = y;
	sprite[j].type = type;
	return (sprite);
}

t_sprite		*sort_sprite(t_sprite *sprite, int max, t_all *all)
{
	int			i;
	int			j;
	double		*dist;

	i = -1;
	if (!(dist = malloc(max * sizeof(double))))
		ft_exit(1, "Malloc error.", &(all->p), all);
	while (++i < max)
		dist[i] = ((all->d.pos_x - sprite[i].x) * (all->d.pos_x - sprite[i].x) +
		(all->d.pos_y - sprite[i].y) * (all->d.pos_y - sprite[i].y));
	i = -1;
	while (++i < max)
	{
		j = i;
		while (++j < max)
			if (j != i && dist[i] > dist[j])
				sprite = swap_sprite(sprite, i, j);
	}
	free(dist);
	return (sprite);
}
