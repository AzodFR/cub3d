/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:54:20 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 18:28:02 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void			init_variables(t_display *d, t_params *p, int x)
{
	d->camera_x = (2 * x / (double)p->win_x - 1);
	d->raydir_x = d->dir_x + d->plane_x * d->camera_x;
	d->raydir_y = d->dir_y + d->plane_y * d->camera_x;
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	d->deltadist_x = fabs(1 / d->raydir_x);
	d->deltadist_y = fabs(1 / d->raydir_y);
	d->hit = 0;
}

t_all			init_texture(t_params p, t_all a, int i)
{
	t_texture		t;
	int				w;
	int				h;
	int				sizeline;

	while (++i < 6)
	{
		t.ptr = mlx_xpm_file_to_image(a.mlx.ptr, get_path(i, p), &w, &h);
		t.info[1] = w;
		t.info[2] = h;
		t.array = (int *)mlx_get_data_addr(t.ptr, &w, &sizeline, &h);
		t.info[0] = sizeline;
		t.info[3] = w;
		a.text[i] = t;
	}
	return (a);
}

t_all			init_key(t_all all)
{
	all.key.w = 0;
	all.key.a = 0;
	all.key.s = 0;
	all.key.d = 0;
	all.key.right = 0;
	all.key.left = 0;
	all.sprint = 0;
	all.crouch = 0;
	all.life = 4;
	return (all);
}

t_display		init_display(t_map map)
{
	t_display	d;
	double		rota;
	double		oldir_x;
	double		oldplane;

	d.pos_x = map.pos[0] + 0.5;
	d.pos_y = map.pos[1] + 0.5;
	rota = 0;
	if (map.p_facing == 'W')
		rota = -1.57;
	if (map.p_facing == 'S')
		rota = -3.14;
	if (map.p_facing == 'E')
		rota = -4.71;
	d.dir_x = -1;
	d.dir_y = 0;
	oldir_x = d.dir_x;
	d.dir_x = d.dir_x * cos(-rota) - d.dir_y * sin(-rota);
	d.dir_y = oldir_x * sin(-rota) + d.dir_y * cos(-rota);
	d.plane_x = 0;
	d.plane_y = 0.66;
	oldplane = d.plane_x;
	d.plane_x = d.plane_x * cos(-rota) - d.plane_y * sin(-rota);
	d.plane_y = oldplane * sin(-rota) + d.plane_y * cos(-rota);
	return (d);
}
