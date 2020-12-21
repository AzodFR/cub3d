/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:36:23 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 13:36:10 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	debug(t_params p, t_map m)
{
	int		i;
	int		j;

	i = -1;
	dprintf(1, "Resolution |%d x %d|\n", p.win_x, p.win_y);
	dprintf(1, "NO |%s|\n", p.text_no);
	dprintf(1, "SO |%s|\n", p.text_so);
	dprintf(1, "WE |%s|\n", p.text_we);
	dprintf(1, "EA |%s|\n", p.text_ea);
	dprintf(1, "SPRITE |%s|\n", p.text_sprite);
	dprintf(1, "Floor |%d - %d - %d|\n", p.f[0], p.f[1], p.f[2]);
	dprintf(1, "Ceil |%d - %d - %d|\n", p.c[0], p.c[1], p.c[2]);
	dprintf(1, "Map:\n");
	while (m.map[++i])
		dprintf(1, "%s|%d|\n", m.map[i], (int)ft_strlen(m.map[i]));
	i = -1;
	dprintf(1, "INT Map:\n");
	while (m.map[++i])
	{
		j = -1;
		while (m.map[i][++j])
			dprintf(1, "%d", m.worldmap[i][j]);
		dprintf(1, "\n");
	}
}

int		closed(t_all *a)
{
	ft_exit(0, "Window closed.", &(a->p), a);
	return (1);
}

int		gameloop(t_all *all)
{
	int	*array;
	int v;

	all->main = mlx_new_image(all->mlx.ptr, all->p.win_x, all->p.win_y);
	array = (int *)mlx_get_data_addr(all->main, &v, &v, &v);
	check_move(all);
	print_img(&(all->d), &(all->p), all, array);
	mlx_destroy_image(all->mlx.ptr, all->main);
	return (1);
}

int		main(int ac, char **av)
{
	t_all		all;

	if (ac < 2 || ac > 3)
		ft_exit(1, "No map were provided.", NULL, NULL);
	else
	{
		all = parser(av[1], 0);
		debug(all.p, all.map);
		all.d = init_display(all.map);
		all.mlx.ptr = mlx_init();
		all = init_texture(all.p, all);
		all.mlx.win = mlx_new_window(all.mlx.ptr,
					all.p.win_x, all.p.win_y, av[1]);
		all = init_key(all);
		mlx_hook(all.mlx.win, 02, 1L << 0, key_press, &all);
		mlx_hook(all.mlx.win, 03, 1L << 1, key_release, &all);
		mlx_hook(all.mlx.win, 17, 1L << 0, closed, &all);
		mlx_loop_hook(all.mlx.ptr, gameloop, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}
