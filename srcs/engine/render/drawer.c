/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:12:12 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 16:03:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	print_ceil(int *array, t_display *d, t_params *p, int x)
{
	long	color;
	int		i;

	i = -1;
	color = p->c[2] + p->c[1] * 16 * 16 + p->c[0] * 16 * 16 * 16 * 16;
	while (++i <= d->draw_start)
		array[i * p->win_x + x] = color;
}

void	print_floor(int *array, t_display *d, t_params *p, int x)
{
	long	color;
	int		i;

	i = d->draw_end;
	color = p->f[2] + p->f[1] * 16 * 16 + p->f[0] * 16 * 16 * 16 * 16;
	while (i <= (p->win_y - 1))
		array[i++ * p->win_x + x] = color;
}

void	print_wall(int *array, t_all *all, int x, int or)
{
	int			y;
	t_display	*d;
	t_params	*p;
	long		color;

	d = &(all->d);
	p = &(all->p);
	y = d->draw_start;
	while (y < d->draw_end)
	{
		d->tex_y = (int)d->tex_pos & (all->text[or].info[2] - 1);
		d->tex_pos += d->step;
		color = all->text[or].array[all->text[or].info[2] *
		d->tex_y + d->tex_x];
		array[y * p->win_x + x] = color;
		y++;
	}
}
