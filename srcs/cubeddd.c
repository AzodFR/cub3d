/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:36:23 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/16 18:29:19 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"
#include <math.h>
#define mapWidth 9
#define mapHeight 4

void	debug(t_params p, t_map m)
{
	int		i;
	int		j;

	i = -1;
	dprintf(1,"Resolution |%d x %d|\n", p.win_x, p.win_y);
	dprintf(1,"NO |%s|\n", p.text_no);
	dprintf(1,"SO |%s|\n", p.text_so);
	dprintf(1,"WE |%s|\n", p.text_we);
	dprintf(1,"EA |%s|\n", p.text_ea);
	dprintf(1,"SPRITE |%s|\n", p.text_sprite);
	dprintf(1,"Floor |%d - %d - %d|\n", p.f[0], p.f[1], p.f[2]);
	dprintf(1,"Ceil |%d - %d - %d|\n", p.c[0], p.c[1], p.c[2]);
	dprintf(1,"Map:\n");
	while (m.map[++i])
		dprintf(1,"%s|%d|\n",m.map[i], (int)ft_strlen(m.map[i]));
	i = -1;
	dprintf(1,"INT Map:\n");
	while (m.map[++i])
	{
		j = -1;
		while (m.map[i][++j])
			dprintf(1,"%d",m.worldmap[i][j]);
		dprintf(1, "\n");
	}
}

int		closed(t_all *a)
{
	ft_exit(0,"Window closed.", &(a->p), a);
	return (1);
}


int		aff(t_all *a)
{
	t_params p;
	t_map	map;
	t_mlx mlx;
	t_display d;

	mlx = a->mlx;
	p = a->p;
	map = a->map;
	d = a->d;
	mlx_clear_window(mlx.ptr, mlx.win);
	int w = p.win_x;
	int h = p.win_y;
	int **worldmap;
	worldmap = map.worldmap;
	int x = 0;
	int i;
	while (x < w)
	{
		d.hit = 0;
		d.cameraX = 2 * x / (double)w - 1;
		d.rayDirX = d.dirX + d.planeX * d.cameraX;
		d.rayDirY = d.dirY + d.planeY * d.cameraX;
		d.mapX= (int)d.posX;
		d.mapY = (int)d.posY;
		
		d.deltaDistX = fabs(1 / d.rayDirX);
		d.deltaDistY = fabs(1 / d.rayDirY);
		d.hit = 0;
		if(d.rayDirX < 0)
		{
			d.stepX = -1;
			d.sideDistX = (d.posX - d.mapX) * d.deltaDistX;
		}
		else
		{
			d.stepX = 1;
			d.sideDistX = (d.mapX + 1.0 - d.posX) * d.deltaDistX;
		}
		if(d.rayDirY < 0)
		{
			d.stepY = -1;
			d.sideDistY = (d.posY - d.mapY) * d.deltaDistY;
		}
		else
		{
			d.stepY = 1;
			d.sideDistY = (d.mapY + 1.0 - d.posY) * d.deltaDistY;
		}
		while (d.hit == 0)
		{
			if(d.sideDistX < d.sideDistY)
			{
				d.sideDistX += d.deltaDistX;
				d.mapX += d.stepX;
				d.side = 0;
			}
			else
			{
				d.sideDistY += d.deltaDistY;
				d.mapY += d.stepY;
				d.side = 1;
			}
			if(worldmap[d.mapX][d.mapY] > 0)
				d.hit = 1;
		}
		if(d.side == 0)
			d.perpWallDist = (d.mapX - d.posX + (1 - d.stepX) / 2) / d.rayDirX;
		else
			d.perpWallDist = (d.mapY - d.posY + (1 - d.stepY) / 2) / d.rayDirY;
		d.lineHeight = (int)(h / d.perpWallDist);
		d.drawStart = -d.lineHeight / 2 + h / 2;
		if(d.drawStart < 0)
			d.drawStart = 0;
		d.drawEnd = d.lineHeight / 2 + h / 2;
		if(d.drawEnd >= h)
			d.drawEnd = h - 1;
		
		i= -1;
		int color;
		color = 255 + 16*16*0 + 16*16*16*16*0;
		int white;
		white = 127 + 16*16*127 + 16*16*16*16*127;
		while (++i < d.drawStart)
			mlx_pixel_put(mlx.ptr, mlx.win,x, i, color);
		while (d.drawStart < d.drawEnd)
		{
			d.side = worldmap[d.mapX][d.mapY];
			if (d.side == 1)
				mlx_pixel_put(mlx.ptr, mlx.win,x, d.drawStart, 000255000000);
			else if (d.side == 2)
				mlx_pixel_put(mlx.ptr, mlx.win,x, d.drawStart, 000255000);
			d.drawStart++;
		}
		while (d.drawEnd < (p.win_y - 1))
			mlx_pixel_put(mlx.ptr, mlx.win,x, d.drawEnd++, white);
		d.drawEnd = 0;
		d.drawStart = 0;
		x++;
	}
	return (1);
}

int		key_hook(int keycode, t_all *a)
{
	double oldDirX;
	double oldPlaneX;
	ft_printf("KEY: %d\n", keycode);
	//debug(a->p, a->map);
	if (keycode == 53)
		ft_exit(0,"Window closed.", &(a->p), a);
	if (keycode == D)
	{
		oldDirX = a->d.dirX;
		a->d.dirX = a->d.dirX * cos(-3.14 / 4) - a->d.dirY * sin(-3.14 / 4);
		a->d.dirY = oldDirX * sin(-3.14 / 4) + a->d.dirY * cos(-3.14 / 4);
		oldPlaneX = a->d.planeX;
		a->d.planeX = a->d.planeX * cos(-3.14 / 4) - a->d.planeY * sin(-3.14 / 4);
		a->d.planeY = oldPlaneX * sin(-3.14 / 4) + a->d.planeY * cos(-3.14 / 4);
	}
	if (keycode == A)
	{
		oldDirX = a->d.dirX;
		a->d.dirX = a->d.dirX * cos(3.14 / 4) - a->d.dirY * sin(3.14 / 4);
		a->d.dirY = oldDirX * sin(3.14 / 4) + a->d.dirY * cos(3.14 / 4);
		oldPlaneX = a->d.planeX;
		a->d.planeX = a->d.planeX * cos(3.14 / 4) - a->d.planeY * sin(3.14 / 4);
		a->d.planeY = oldPlaneX * sin(3.14 / 4) + a->d.planeY * cos(3.14 / 4);
	}
	else if (keycode == W)
	{
		if(a->map.worldmap[(int)(a->d.posX + a->d.dirX * 5)][(int)(a->d.posY)] < 1)
			a->d.posX += a->d.dirX * 1;
		if(a->map.worldmap[(int)(a->d.posX)][(int)(a->d.posY + a->d.dirY * 5)] < 1)
			a->d.posY += a->d.dirY * 1;
	}
	return (keycode);
}

int main(int ac, char **av)
{
	t_all		all;
	if (ac < 2 || ac > 3)
		ft_exit(1, "No map were provided.", NULL, NULL);
	else
	{
		all = parser(av[1],0);
		debug(all.p, all.map);
		all.d.posX = 5;
		all.d.posY = 6;
		all.d.dirX = -1;
		all.d.dirY = 1;
		all.d.planeX = 0.66;
		all.d.planeY = 1;
		all.mlx.ptr = mlx_init();
		all.mlx.win = mlx_new_window(all.mlx.ptr, all.p.win_x, all.p.win_y, av[1]);
		mlx_key_hook(all.mlx.win, key_hook, &all);
		mlx_hook(all.mlx.win, 17, 1L<<0, closed, &all);
		mlx_loop_hook(all.mlx.ptr, aff, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}