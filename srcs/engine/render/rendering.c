/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:57:09 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/04 15:07:36 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	step(t_display *d)
{
	if (d->raydir_x < 0)
	{
		d->step_x = -1;
		d->sidedist_x = (d->pos_x - d->map_x) * d->deltadist_x;
	}
	else
	{
		d->step_x = 1;
		d->sidedist_x = (d->map_x + 1.0 - d->pos_x) * d->deltadist_x;
	}
	if (d->raydir_y < 0)
	{
		d->step_y = -1;
		d->sidedist_y = (d->pos_y - d->map_y) * d->deltadist_y;
	}
	else
	{
		d->step_y = 1;
		d->sidedist_y = (d->map_y + 1.0 - d->pos_y) * d->deltadist_y;
	}
}

int		hit(t_display *d, int **worldmap, int or)
{
	while (d->hit == 0)
	{
		if (d->sidedist_x < d->sidedist_y && !(d->side = 0))
		{
			d->sidedist_x += d->deltadist_x;
			d->map_x += d->step_x;
			or = d->raydir_x < 0 ? 0 : 1;
		}
		else
		{
			d->sidedist_y += d->deltadist_y;
			d->map_y += d->step_y;
			or = d->raydir_y > 0 ? 2 : 3;
			d->side = 1;
		}
		if (is_wall(worldmap[d->map_x][d->map_y]))
			d->hit = 1;
	}
	if (d->side == 0)
		d->perpwall_dist = (d->map_x - d->pos_x + (1 - d->step_x) / 2)
			/ d->raydir_x;
	else
		d->perpwall_dist = (d->map_y - d->pos_y + (1 - d->step_y) / 2)
			/ d->raydir_y;
	return (or);
}

void	define_startend(t_display *d, t_params *p, t_all *all)
{
	d->draw_start = (-d->lineheight / 2 + p->win_y / 2) - all->crouch;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = (d->lineheight / 2 + p->win_y / 2) - all->crouch;
	if (d->draw_end >= p->win_y)
		d->draw_end = p->win_y - 1;
	if (d->side == 0)
		d->wall_x = d->pos_y + d->perpwall_dist * d->raydir_y;
	else
		d->wall_x = d->pos_x + d->perpwall_dist * d->raydir_x;
}

void	get_texture(t_display *d, t_params *p, t_all *all, int or)
{
	d->tex_x = (int)(d->wall_x * (double)all->text[or].info[1]);
	if (d->side == 0 && d->raydir_x > 0)
		d->tex_x = all->text[or].info[1] - d->tex_x - 1;
	if (d->side == 1 && d->raydir_y < 0)
		d->tex_x = all->text[or].info[1] - d->tex_x - 1;
	d->step = 1.0 * all->text[or].info[2] / d->lineheight;
	d->tex_pos = (d->draw_start - p->win_y / 2 + d->lineheight / 2) * d->step;
}

void	print_img(t_display *d, t_params *p, t_all *all, int *array)
{
	int		x;
	int		**worldmap;
	int		or;

	worldmap = all->map.worldmap;
	x = 0;
	while (x < p->win_x)
	{
		init_variables(d, p, x);
		step(d);
		or = hit(d, worldmap, or);
		d->lineheight = (int)(p->win_y / d->perpwall_dist);
		define_startend(d, p, all);
		d->wall_x -= floor((d->wall_x));
		get_texture(d, p, all, or);
		print_ceil(array, d, p, x);
		print_wall(array, all, x, or);
		print_floor(array, d, p, x);
		d->zbuff[x] = d->perpwall_dist;
		x++;
	}
	all->map.sprite = sort_sprite(all->map.sprite, all->map.nbsprite, all);
	print_sprite(array, all, d);
	if (all->p.screen == 1)
		ft_init_bmp(all, all->p.win_x, all->p.win_y, array);
}
