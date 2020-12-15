#include <stdio.h>
#include "cubeddd.h"

void	debug(t_params p, t_map m)
{
	int		i;

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
		dprintf(1,"%s\n",m.map[i]);
}

int		key_hook(int keycode, t_all *a)
{
    printf("KEY: %d\n", keycode);
	if (keycode == ESC)
		ft_exit(0,"Window closed.", &a->p);
	else if (keycode == D)
	{
		mlx_clear_window(a->mlx.ptr, a->mlx.win);
		a->img.posx += a->img.posx + SPEED < a->p.win_x - a->img.x ? SPEED : 0;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->img.img, a->img.posx ,a->img.posy);
	}
	else if (keycode == A)
	{
		mlx_clear_window(a->mlx.ptr, a->mlx.win);
		a->img.posx -= a->img.posx - SPEED > 0 ? SPEED : 0;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->img.img, a->img.posx ,a->img.posy);
	}
	else if (keycode == W)
	{
		mlx_clear_window(a->mlx.ptr, a->mlx.win);
		a->img.posy -= a->img.posy - SPEED > 0 ? SPEED : 0;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->img.img, a->img.posx ,a->img.posy);
	}
	else if (keycode == S)
	{
		mlx_clear_window(a->mlx.ptr, a->mlx.win);
		a->img.posy += a->img.posy + SPEED < a->p.win_x - a->img.y ? SPEED : 0;
		mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->img.img, a->img.posx ,a->img.posy);
	}
	return (keycode);
}

int		closed(int keycode, t_all *a)
{
	ft_exit(0,"Window closed.", &(a->p));
	return (keycode);
}

int main(int ac, char **av)
{
	t_all		all;
	if (ac < 2 || ac > 3)
		ft_exit(1, "No map were provided.", NULL);
	else
	{
		all = parser(av[1],0);
		debug(all.p, all.map);
		all.mlx.ptr = mlx_init();
		all.mlx.win = mlx_new_window(all.mlx.ptr, all.p.win_x, all.p.win_y, av[1]);
		all.img.img = mlx_xpm_file_to_image(all.mlx.ptr, all.p.text_sprite, &all.img.x, &all.img.y);
		mlx_put_image_to_window(all.mlx.ptr, all.mlx.win, all.img.img, all.img.posx ,all.img.posy);
		mlx_hook(all.mlx.win, 2, 0, key_hook, &all);
		mlx_hook(all.mlx.win, 3, 0, key_hook, &all);
		mlx_hook(all.mlx.win, 17, 1L<<0, closed, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}