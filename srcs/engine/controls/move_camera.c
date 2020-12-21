/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:40:24 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 17:27:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	turn_right(t_all *a)
{
	double	olddir_x;
	double	oldplane_x;
	double	cospy;
	double	sinpy;

	olddir_x = a->d.dir_x;
	cospy = cos(-3.14 / SENSIVITY);
	sinpy = sin(-3.14 / SENSIVITY);
	a->d.dir_x = a->d.dir_x * cospy - a->d.dir_y * sinpy;
	a->d.dir_y = olddir_x * sinpy + a->d.dir_y * cospy;
	oldplane_x = a->d.plane_x;
	a->d.plane_x = a->d.plane_x * cospy - a->d.plane_y * sinpy;
	a->d.plane_y = oldplane_x * sinpy + a->d.plane_y * cospy;
}

void	turn_left(t_all *a)
{
	double	olddir_x;
	double	oldplane_x;
	double	cospy;
	double	sinpy;

	olddir_x = a->d.dir_x;
	cospy = cos(3.14 / SENSIVITY);
	sinpy = sin(3.14 / SENSIVITY);
	a->d.dir_x = a->d.dir_x * cospy - a->d.dir_y * sinpy;
	a->d.dir_y = olddir_x * sinpy + a->d.dir_y * cospy;
	oldplane_x = a->d.plane_x;
	a->d.plane_x = a->d.plane_x * cospy - a->d.plane_y * sinpy;
	a->d.plane_y = oldplane_x * sinpy + a->d.plane_y * cospy;
}
