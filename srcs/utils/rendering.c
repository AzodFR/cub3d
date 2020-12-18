/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:57:09 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/18 17:13:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void 	print_img(t_display *d, t_params *p, t_all *all, int *array)
{
	int		x;
	int		y;
	int		**worldmap;
	long	color;
	int		i;
	int or;

	worldmap = all->map.worldmap;
	x = 0;
	while (x < p->win_x)
	{
		//calculate ray position and direction
		d->cameraX = (2 * x / (double)p->win_x - 1); //x-coordinate in camera space
		d->rayDirX = d->dirX + d->planeX * d->cameraX;
		d->rayDirY = d->dirY + d->planeY * d->cameraX;

		//which box of the map we're in
		d->mapX = (int)d->posX;
		d->mapY = (int)d->posY;


		//length of ray from one x or y-side to next x or y-side
		d->deltaDistX = fabs(1 / d->rayDirX);
		d->deltaDistY = fabs(1 / d->rayDirY);

		d->hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if(d->rayDirX < 0)
		{
			d->stepX = -1;
			d->sideDistX = (d->posX - d->mapX) * d->deltaDistX;
		}
		else
		{
			d->stepX = 1;
			d->sideDistX = (d->mapX + 1.0 - d->posX) * d->deltaDistX;
		}
		if(d->rayDirY < 0)
		{
			d->stepY = -1;
			d->sideDistY = (d->posY - d->mapY) * d->deltaDistY;
		}
		else
		{
			d->stepY = 1;
			d->sideDistY = (d->mapY + 1.0 - d->posY) * d->deltaDistY;
		}
		//perform DDA
		while (d->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(d->sideDistX < d->sideDistY)
			{
				d->sideDistX += d->deltaDistX;
				d->mapX += d->stepX;
				or = d->rayDirX < 0 ? 0 : 1;
				d->side = 0;
			}
			else
			{
				d->sideDistY += d->deltaDistY;
				d->mapY += d->stepY;
				or = d->rayDirY > 0 ? 2 : 3;
				d->side = 1;
			}
			//Check if ray has hit a wall
			if(worldmap[d->mapX][d->mapY] > 0)
				d->hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(d->side == 0)
			d->perpWallDist = (d->mapX - d->posX + (1 - d->stepX) / 2) / d->rayDirX;
		else
			d->perpWallDist = (d->mapY - d->posY + (1 - d->stepY) / 2) / d->rayDirY;

		//Calculate height of line to draw on screen
		d->lineHeight = (int)(p->win_y / d->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		d->drawStart = (-d->lineHeight / 2 + p->win_y / 2 ) - all->crouch;
		if(d->drawStart < 0)
			d->drawStart = 0;
		d->drawEnd = (d->lineHeight / 2 + p->win_y / 2) - all->crouch;
		if(d->drawEnd >= p->win_y)
			d->drawEnd = p->win_y - 1;

		//calculate value of wallX
		if(d->side == 0)
			d->wallX = d->posY + d->perpWallDist * d->rayDirY;
		else
			d->wallX = d->posX + d->perpWallDist * d->rayDirX;
		d->wallX -= floor((d->wallX));


		d->texX = (int)(d->wallX * (double)all->text[or].info[1]);
		if(d->side == 0 && d->rayDirX > 0)
			d->texX = all->text[or].info[1] - d->texX - 1;
		if(d->side == 1 && d->rayDirY < 0)
			d->texX = all->text[or].info[1] - d->texX - 1;


		d->step = 1.0 * all->text[or].info[2] / d->lineHeight;
		d->texPos = (d->drawStart - p->win_y / 2 + d->lineHeight / 2) * d->step;
		y = d->drawStart;
		i = -1;
		color = p->c[2] + p->c[1]*16*16 + p->c[0]*16*16*16*16;
		while (++i <= d->drawStart)
				array[i * p->win_x + x] = color;
		while(y < d->drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			d->texY = (int)d->texPos & (all->text[or].info[2] - 1);
			d->texPos += d->step;
			color = all->text[or].array[all->text[or].info[2] * d->texY + d->texX];
			if(d->sideDistY > 5 && d->sideDistX > 5)
				color = (color >> 1) & 8355711;
			array[y * p->win_x + x] = color;
			y++;
		}
		i = d->drawEnd;
		color = p->f[2] + p->f[1]*16*16 + p->f[0]*16*16*16*16;
		while (i <= (p->win_y - 1))
			array[i++ * p->win_x + x] = color;
		x++;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->main, 0,0);
}

void	check_move(t_all *a)
{
	double oldDirX;
	double oldPlaneX;
	if (a->key_w)
	{
		if(a->map.worldmap[(int)(a->d.posX + a->d.dirX * (0.13 + a->sprint))][(int)(a->d.posY)] < 1)
			a->d.posX += a->d.dirX * (0.13 + a->sprint);
		if(a->map.worldmap[(int)(a->d.posX)][(int)(a->d.posY + a->d.dirY * (0.13 + a->sprint))] < 1)
			a->d.posY += a->d.dirY * (0.13 + a->sprint);
	}
	if (a->left)
	{
		oldDirX = a->d.dirX;
		a->d.dirX = a->d.dirX * cos(3.14 / 50) - a->d.dirY * sin(3.14 / 50);
		a->d.dirY = oldDirX * sin(3.14 / 50) + a->d.dirY * cos(3.14 / 50);
		oldPlaneX = a->d.planeX;
		a->d.planeX = a->d.planeX * cos(3.14 / 50) - a->d.planeY * sin(3.14 / 50);
		a->d.planeY = oldPlaneX * sin(3.14 / 50) + a->d.planeY * cos(3.14 / 50);
	}
	if (a->right)
	{
		oldDirX = a->d.dirX;
		a->d.dirX = a->d.dirX * cos(-3.14 / 50) - a->d.dirY * sin(-3.14 / 50);
		a->d.dirY = oldDirX * sin(-3.14 / 50) + a->d.dirY * cos(-3.14 / 50);
		oldPlaneX = a->d.planeX;
		a->d.planeX = a->d.planeX * cos(-3.14 / 50) - a->d.planeY * sin(-3.14 / 50);
		a->d.planeY = oldPlaneX * sin(-3.14 / 50) + a->d.planeY * cos(-3.14 / 50);
	}
	if (a->key_s)
	{
		if(a->map.worldmap[(int)(a->d.posX - a->d.dirX * (0.13))][(int)(a->d.posY)] < 1)
			a->d.posX -= a->d.dirX * (0.13 + (a->crouch ? a->sprint : 0));
		if(a->map.worldmap[(int)(a->d.posX)][(int)(a->d.posY - a->d.dirY * (0.13))] < 1)
			a->d.posY -= a->d.dirY * (0.13 + (a->crouch ? a->sprint : 0));
	}
}