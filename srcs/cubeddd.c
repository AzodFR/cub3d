/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 10:36:23 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 14:26:02 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

int		closed(t_all *a)
{
	ft_exit(0, "Window closed.", &(a->p), a);
	return (1);
}

int		can_loop(t_all *all)
{
	return ((all->map.win == 0 ||
		(all->keys < all->map.win && all->map.win > 0)) &&
			all->life > 0);
}

int		gameloop(t_all *all)
{
	int		*array;
	int		v;

	if (can_loop(all))
	{
		all->main = mlx_new_image(all->mlx.ptr, all->p.win_x, all->p.win_y);
		array = (int *)mlx_get_data_addr(all->main, &v, &v, &v);
		check_move(all);
		check_trap(all);
		print_img(&(all->d), &(all->p), all, array);
		mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->main, 0, 0);
		if (all->key.hud)
			render_hud(all);
		mlx_destroy_image(all->mlx.ptr, all->main);
	}
	else
		check_state(all);
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
		if (ac == 3 && !ft_strncmp(av[2], "--save", 7))
			all.p.screen = 1;
		all = init_all(all);
		if (!all.p.screen)
		{
			all.mlx.win = mlx_new_window(all.mlx.ptr,
					all.p.win_x, all.p.win_y, av[1]);
			mlx_hook(all.mlx.win, 02, 1L << 0, key_press, &all);
			mlx_hook(all.mlx.win, 03, 1L << 1, key_release, &all);
			mlx_hook(all.mlx.win, 17, 1L << 0, closed, &all);
		}
		mlx_loop_hook(all.mlx.ptr, gameloop, &all);
		mlx_loop(all.mlx.ptr);
	}
	return (0);
}
