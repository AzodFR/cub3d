/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:58:55 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 13:20:07 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

t_map	treat_sprite(t_map map, int i, int j)
{
	map.sprite[map.nbsprite].x = i;
	map.sprite[map.nbsprite].y = j;
	map.sprite[map.nbsprite].type = map.map[i][j] - '0' - 1;
	if (map.sprite[map.nbsprite].type > 2)
		--map.sprite[map.nbsprite].type;
	map.nbsprite += 1;
	return (map);
}
