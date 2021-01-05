/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_died.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:48:45 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 12:41:32 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	check_state(t_all *all)
{
	if ((all->keys >= all->map.win && all->map.win > 0))
	{
		mlx_clear_window(all->mlx.ptr, all->mlx.win);
		mlx_string_put(all->mlx.ptr, all->mlx.win, all->p.win_x / 2.3,
		all->p.win_y / 2, 255 * 16 * 16, "GG EZ");
	}
	else if (all->life <= 0)
	{
		mlx_clear_window(all->mlx.ptr, all->mlx.win);
		mlx_string_put(all->mlx.ptr, all->mlx.win, all->p.win_x / 2.3,
		all->p.win_y / 2, 255 * 16 * 16 * 16 * 16, "You died !");
	}
}

void	render_hud(t_all *all)
{
	char	*life;

	life = ft_strjoin("Keys: ", " / ");
	life[6] = all->keys + '0';
	life[8] = all->map.win + '0';
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.win, all->life_txt,
				lx(all->life), 0);
	mlx_string_put(all->mlx.ptr, all->mlx.win, all->p.win_x - 100, 20,
				2552552, life);
	free(life);
}
