/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:36:23 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/17 19:29:05 by thjacque         ###   ########lyon.fr   */
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
		  or = d->rayDirX < 0 ? 1 : 2;
          d->side = 0;
        }
        else
        {
          d->sideDistY += d->deltaDistY;
          d->mapY += d->stepY;
		  or = d->rayDirY > 0 ? 3 : 4;
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

      //texturing calculations
      //d->texNum = worldmap[d->mapX][d->mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      if(d->side == 0)
	  	d->wallX = d->posY + d->perpWallDist * d->rayDirY;
      else
	  	d->wallX = d->posX + d->perpWallDist * d->rayDirX;
      d->wallX -= floor((d->wallX));

      //x coordinate on the texture
      d->texX = (int)(d->wallX * (double)all->texture.i1[1]);
      if(d->side == 0 && d->rayDirX > 0)
	  	d->texX = all->texture.i1[1] - d->texX - 1;
      if(d->side == 1 && d->rayDirY < 0)
	  	d->texX = all->texture.i1[1] - d->texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      d->step = 1.0 * all->texture.i1[2] / d->lineHeight;
      // Starting texture coordinate
      d->texPos = (d->drawStart - p->win_y / 2 + d->lineHeight / 2) * d->step;
	  y = d->drawStart;
	  i = -1;
	  color = p->c[2] + p->c[1]*16*16 + p->c[0]*16*16*16*16;
	  while (++i < d->drawStart)
			array[i * p->win_x + x] = color;
      while(y < d->drawEnd)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        d->texY = (int)d->texPos & (all->texture.i1[2] - 1);
        d->texPos += d->step;
		color = all->texture.t1p[all->texture.i1[2] * d->texY + d->texX];
		if (or == 2)
        	color = all->texture.t2p[all->texture.i2[2] * d->texY + d->texX];
		if (or == 4)
        	color = all->texture.t4p[all->texture.i4[2] * d->texY + d->texX];
		if (or == 3)
        	color = all->texture.t3p[all->texture.i3[2] * d->texY + d->texX];
		//dprintf(1, "ORIENTAION: %d\n", or);
		 if(d->sideDistY > 5 && d->sideDistX > 5)
		 	color = (color >> 1) & 8355711;
		array[y * p->win_x + x] = color;
		y++;
      }
	  i = d->drawEnd;
	  color = p->f[2] + p->f[1]*16*16 + p->f[0]*16*16*16*16;
	  while (i < (p->win_y - 1))
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
			a->d.posX -= a->d.dirX * (0.13);
		if(a->map.worldmap[(int)(a->d.posX)][(int)(a->d.posY - a->d.dirY * (0.13))] < 1)
			a->d.posY -= a->d.dirY * (0.13);
	}
}

int		img(t_all *all)
{
	int	*array;
	int v;
	int h;
	void *life;
	all->main = mlx_new_image(all->mlx.ptr, all->p.win_x, all->p.win_y);
	array = (int *)mlx_get_data_addr(all->main, &v, &v, &v);
	check_move(all);
	print_img(&(all->d), &(all->p), all, array);
	life = mlx_xpm_file_to_image(all->mlx.ptr, "txt/PixelArt.xpm", &v, &h);
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, life,0, all->p.win_y - h -50);
	mlx_destroy_image(all->mlx.ptr, all->main);
	mlx_destroy_image(all->mlx.ptr, life);
	return (1);
}

t_display		init_display(void)
{
	t_display d;

	d.posX = 5;
	d.posY = 6;
	d.dirX = -1;
	d.dirY = 1;
	d.planeX = 0.66;
	d.planeY = 0.33;
	return (d);
}

t_texture init_texture(t_params p, t_all a)
{
	t_texture		t;
	void	*ptr;
	int v;
	int w;
	int h;
	int sizeline;

	ptr = a.mlx.ptr;
	t.t1 = mlx_xpm_file_to_image(ptr, p.text_no, &w, &h);
	t.i1[1] = w;
	t.i1[2] = h;
	t.t2 = mlx_xpm_file_to_image(ptr, p.text_so, &w, &h);
	t.i2[1] = w;
	t.i2[2] = h;
	t.t3 = mlx_xpm_file_to_image(ptr, p.text_ea, &w, &h);
	t.i3[1] = w;
	t.i3[2] = h;
	t.t4 = mlx_xpm_file_to_image(ptr, p.text_we, &w, &h);
	t.i4[1] = w;
	t.i4[2] = h;
	t.t1p = (int *)mlx_get_data_addr(t.t1, &h, &sizeline, &v);
	t.i1[0] = sizeline;
	t.i1[3] = h;
	t.t2p = (int *)mlx_get_data_addr(t.t2, &h, &sizeline, &v);
	t.i2[0] = sizeline;
	t.i2[3] = h;
	t.t3p = (int *)mlx_get_data_addr(t.t3, &h, &sizeline, &v);
	t.i3[0] = sizeline;
	t.i3[3] = h;
	t.t4p = (int *)mlx_get_data_addr(t.t4, &h, &sizeline, &v);
	t.i4[0] = sizeline;
	t.i4[3] = h;
	return (t);
}

int key_press(int keycode,t_all *a)
{
	dprintf(1,"%f -- %f\n%f .. %f\n",a->d.dirX, a->d.dirY,a->d.sideDistX, a->d.sideDistY);
	if (keycode == 53)
		ft_exit(0,"Window closed.", &(a->p), a);
	else if (keycode == W)
		a->key_w = 1;
	else if (keycode == A)
		a->key_a = 1;
	else if (keycode == S)
		a->key_s = 1;
	else if (keycode == D)
		a->key_d = 1;
	else if (keycode == RIGHT)
		a->right = 1;
	else if (keycode == LEFT)
		a->left = 1;
	else if (keycode == SHIFT)
	{
		if(!a->crouch)
			a->sprint = 0.1;
	}
	else if (keycode == CTRL)
	{
		if (!a->sprint)
		{
			a->sprint = -0.1;
			a->crouch = 100;
		}
	}
	
	return (keycode);
}

int key_release(int keycode,t_all *a)
{
	t_display *d;

	d = &(a->d);
	if (keycode == 53)
		ft_exit(0,"Window closed.", &(a->p), a);
	else if (keycode == W)
		a->key_w = 0;
	else if (keycode == A)
		a->key_a = 0;
	else if (keycode == S)
		a->key_s = 0;
	else if (keycode == D)
		a->key_d = 0;
	else if (keycode == RIGHT)
		a->right = 0;
	else if (keycode == LEFT)
		a->left = 0;
	else if (keycode == SHIFT)
		a->sprint = 0;
	else if (keycode == CTRL)
	{
		a->sprint = 0;
		a->crouch = 0.5;
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
		all.d = init_display();
		all.mlx.ptr = mlx_init();
		all.texture = init_texture(all.p, all);
		all.mlx.win = mlx_new_window(all.mlx.ptr, all.p.win_x, all.p.win_y, av[1]);
		all.key_w = 0;
		all.key_a = 0;
		all.key_s = 0;
		all.key_d = 0;
		all.right = 0;
		all.left = 0;
		all.sprint = 0;
		all.crouch = 0;
		mlx_hook(all.mlx.win, 02, 1L<<0, key_press, &all);
		mlx_hook(all.mlx.win, 03, 1L<<1, key_release, &all);
		mlx_hook(all.mlx.win, 17, 1L<<0, closed, &all);
		mlx_loop_hook(all.mlx.ptr, img, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}