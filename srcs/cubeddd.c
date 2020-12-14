#include <stdio.h>
#include "cubeddd.h"

void	debug(t_params p)
{
	dprintf(1,"Resolution |%d x %d|\n", p.win_x, p.win_y);
	dprintf(1,"NO |%s|\n", p.text_no);
	dprintf(1,"SO |%s|\n", p.text_so);
	dprintf(1,"WE |%s|\n", p.text_we);
	dprintf(1,"EA |%s|\n", p.text_ea);
	dprintf(1,"SPRITE |%s|\n", p.text_sprite);
	dprintf(1,"Floor |%d - %d - %d|\n", p.f[0], p.f[1], p.f[2]);
	dprintf(1,"Ceil |%d - %d - %d|\n", p.c[0], p.c[1], p.c[2]);
}

int		key_hook(int keycode, t_all *a)
{
    printf("KEY: %d\n", keycode);
	if (keycode == 53)
		ft_exit(0,"Window closed.", &a->p);
	return (keycode);
}

int		closed(int keycode, t_all *a)
{
	printf("KEY: %d\n", keycode);
	ft_exit(0,"Window closed.", &(a->p));
	exit(0);
	return (keycode);
}

int main(int ac, char **av)
{
	t_all		all;
	if (ac < 2 || ac > 3)
		ft_exit(1, "No map were provided.", NULL);
	else
	{
		all.p = parser(av[1]);
		debug(all.p);
		all.mlx.ptr = mlx_init();
		all.mlx.win = mlx_new_window(all.mlx.ptr, all.p.win_x, all.p.win_y, av[1]);
		mlx_key_hook(all.mlx.win, key_hook, &all);
		mlx_hook(all.mlx.win, 17, 0L, closed, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}