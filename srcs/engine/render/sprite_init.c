/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:12:02 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 17:33:15 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

int		get_type(t_all *all, t_display *d, int i)
{
	d->spritex = all->map.sprite[i].x - d->pos_x + 0.5;
	d->spritey = all->map.sprite[i].y - d->pos_y + 0.5;
	d->invdet = 1.0 / (d->plane_x * d->dir_y - d->dir_x * d->plane_y);
	d->transform_x = d->invdet *
		(d->dir_y * d->spritex - d->dir_x * d->spritey);
	d->transform_y = d->invdet *
		(-d->plane_y * d->spritex + d->plane_x * d->spritey);
	d->spritescreen_x = (int)((all->p.win_x / 2) *
		(1 + d->transform_x / d->transform_y));
	d->spriteheight = abs((int)(all->p.win_y / (d->transform_y)));
	d->drawstart_y = -d->spriteheight / 2 + all->p.win_y / 2;
	return (all->map.sprite[i].type);
}

void	check_start_end(t_all *all, t_display *d)
{
	if (d->drawstart_y < 0)
		d->drawstart_y = 0;
	d->drawend_y = d->spriteheight / 2 + all->p.win_y / 2;
	if (d->drawend_y >= all->p.win_y)
		d->drawend_y = all->p.win_y - 1;
	d->spritewidth = abs((int)(all->p.win_y / (d->transform_y)));
	d->drawstart_x = -d->spritewidth / 2 + d->spritescreen_x;
	if (d->drawstart_x < 0)
		d->drawstart_x = 0;
	d->drawend_x = d->spritewidth / 2 + d->spritescreen_x;
	if (d->drawend_x >= all->p.win_x)
		d->drawend_x = all->p.win_x - 1;
}

void	draw_sprite(t_all *all, t_display *d, int type, int *array)
{
	int		dc;
	int		y;

	d->sprite_tex_x = (int)(256 * (d->stripe - (-d->spritewidth / 2 +
	d->spritescreen_x)) * all->text[3 + type].info[1] / d->spritewidth) / 256;
	y = d->drawstart_y;
	if (d->transform_y > 0 && d->stripe > 0 && d->stripe < all->p.win_x
		&& d->transform_y < d->zbuff[d->stripe])
	{
		while (y < d->drawend_y)
		{
			dc = y * 256 - all->p.win_y * 128 + d->spriteheight * 128;
			d->sprite_tex_y = ((dc * all->text[3 + type].info[2]) /
					d->spriteheight) / 256;
			d->sprite_color = all->text[3 + type].array
					[all->text[3 + type].info[1] *
						d->sprite_tex_y + d->sprite_tex_x];
			if (d->sprite_color != 9961608)
				array[y * all->p.win_x + d->stripe] = d->sprite_color;
			y++;
		}
	}
	d->stripe += 1;
}
