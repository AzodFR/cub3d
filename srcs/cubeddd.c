/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:36:23 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/18 17:07:40 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"
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



int		img(t_all *all)
{
	int	*array;
	int v;
	//int h;
	//void *life;
	all->main = mlx_new_image(all->mlx.ptr, all->p.win_x, all->p.win_y);
	array = (int *)mlx_get_data_addr(all->main, &v, &v, &v);
	check_move(all);
	print_img(&(all->d), &(all->p), all, array);
	//life = mlx_xpm_file_to_image(all->mlx.ptr, "txt/PixelArt.xpm", &v, &h);
	//mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, life,0, all->p.win_y - h -50);
	mlx_destroy_image(all->mlx.ptr, all->main);
	//mlx_destroy_image(all->mlx.ptr, life);
	return (1);
}

t_display		init_display(t_map map)
{
	t_display d;
	double rota;
	d.posX = map.pos[0];
	d.posY = map.pos[1];
	rota = 0;
	if (map.p_facing == 'W')
		rota = -1.57;
	if (map.p_facing == 'S')
		rota = -3.14;
	if (map.p_facing == 'E')
		rota = -4.71;
	double oldirx;
	double oldplane;
	d.dirX = -1;
	d.dirY = 0;
	oldirx = d.dirX;
	d.dirX = d.dirX * cos(-rota) - d.dirY * sin(-rota);
	d.dirY = oldirx * sin(-rota) + d.dirY * cos(-rota);
	d.planeX = 0;
	d.planeY = 0.66;
	oldplane = d.planeX;
	d.planeX = d.planeX * cos(-rota) - d.planeY * sin(-rota);
	d.planeY = oldplane * sin(-rota) + d.planeY * cos(-rota);
	return (d);
}

t_all init_texture(t_params p, t_all a)
{
	t_texture		t;
	int		i;
	int w;
	int h;
	int sizeline;

	i = -1;
	while (++i < 4)
	{
		t.ptr = mlx_xpm_file_to_image(a.mlx.ptr, p.text_no, &w, &h);
		if (i == 1)
			t.ptr = mlx_xpm_file_to_image(a.mlx.ptr, p.text_so, &w, &h);
		else if (i == 2)
			t.ptr = mlx_xpm_file_to_image(a.mlx.ptr, p.text_ea, &w, &h);
		else if (i == 3)
			t.ptr = mlx_xpm_file_to_image(a.mlx.ptr, p.text_we, &w, &h);
		t.info[1] = w;
		t.info[2] = h;
		t.array = (int *)mlx_get_data_addr(t.ptr, &w, &sizeline, &h);
		t.info[0] = sizeline;
		t.info[3] = w;
		a.text[i] = t;
	}
	return (a);
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
		all.d = init_display(all.map);
		all.mlx.ptr = mlx_init();
		all = init_texture(all.p, all);
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