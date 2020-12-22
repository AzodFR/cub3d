/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:12:12 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 15:34:54 by thjacque         ###   ########lyon.fr   */
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
		//color = all->map.sprite.texture.array[all->map.sprite.texture.info[1] * d->tex_y + d->tex_x];
		array[y * p->win_x + x] = color;
		y++;
	}
}

void	print_sprite(int *array, t_all *all, t_display *d)
{
	double color;
	int		dc;
	int tex_y;
	int tex_x;
	int	y;
	int	i;
	int	type;

	i = -1;
	while (++i < all->map.nbsprite)
	{
		type = all->map.sprite[i].type;
		d->spritex = all->map.sprite[i].x - d->pos_x + 0.5;
		d->spritey = all->map.sprite[i].y - d->pos_y + 0.5;
		d->invdet = 1.0 / (d->plane_x * d->dir_y - d->dir_x * d->plane_y);
		d->transform_x = d->invdet * (d->dir_y * d->spritex - d->dir_x * d->spritey);
		d->transform_y = d->invdet * (-d->plane_y * d->spritex + d->plane_x * d->spritey);
		d->spritescreen_x = (int)((all->p.win_x / 2) * (1 + d->transform_x / d->transform_y));
		d->spriteheight = abs((int)(all->p.win_y / (d->transform_y)));
		d->drawstart_y = -d->spriteheight / 2 + all->p.win_y / 2;
		if (d->drawstart_y < 0)
			d->drawstart_y = 0;
		d->drawend_y = d->spriteheight / 2 + all->p.win_y / 2;
		if (d->drawend_y >= all->p.win_y)
			d->drawend_y = all->p.win_y - 1;
		d->spritewidth = abs((int)(all->p.win_y / (d->transform_y)));
		d->drawstart_x = -d->spritewidth / 2 + d->spritescreen_x;
		if(d->drawstart_x < 0)
			d->drawstart_x = 0;
		d->drawend_x = d->spritewidth / 2 + d->spritescreen_x;
		if(d->drawend_x >= all->p.win_x)
			d->drawend_x = all->p.win_x - 1;
		d->stripe = d->drawstart_x;
		while (d->stripe < d->drawend_x)
		{
			tex_x = (int)(256 * (d->stripe - (-d->spritewidth / 2 + d->spritescreen_x)) * all->text[3+type].info[1] / d->spritewidth) / 256;
			y = d->drawstart_y;
			if(d->transform_y > 0 && d->stripe > 0 && d->stripe < all->p.win_x && d->transform_y < d->zbuff[d->stripe])
			{
				while(y < d->drawend_y)
				{
					dc = y * 256 - all->p.win_y * 128 + d->spriteheight * 128; 
					tex_y = ((dc * all->text[3+type].info[2]) / d->spriteheight) / 256;
					color = all->text[3+type].array[all->text[3+type].info[1] * tex_y + tex_x];
					if(color != 9961608)
						array[y * all->p.win_x + d->stripe] = color;
					y++;
				}
			}
			d->stripe += 1;
		}
	}
}
