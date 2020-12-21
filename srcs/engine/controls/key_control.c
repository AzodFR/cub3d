/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:43:14 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 15:51:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

int		key_press(int keycode, t_all *a)
{
	if (keycode == 53)
		ft_exit(0, "Window closed.", &(a->p), a);
	else if (keycode == W)
		a->key.w = 1;
	else if (keycode == A)
		a->key.a = 1;
	else if (keycode == S)
		a->key.s = 1;
	else if (keycode == D)
		a->key.d = 1;
	else if (keycode == RIGHT)
		a->key.right = 1;
	else if (keycode == LEFT)
		a->key.left = 1;
	else if (keycode == SHIFT && !a->crouch)
		a->sprint = 0.1;
	else if (keycode == CTRL && !a->sprint)
	{
		a->sprint = -0.1;
		a->crouch = 100;
	}
	return (keycode);
}

int		key_release(int keycode, t_all *a)
{
	t_display *d;

	d = &(a->d);
	if (keycode == 53)
		ft_exit(0, "Window closed.", &(a->p), a);
	else if (keycode == W)
		a->key.w = 0;
	else if (keycode == A)
		a->key.a = 0;
	else if (keycode == S)
		a->key.s = 0;
	else if (keycode == D)
		a->key.d = 0;
	else if (keycode == RIGHT)
		a->key.right = 0;
	else if (keycode == LEFT)
		a->key.left = 0;
	else if (keycode == SHIFT)
		a->sprint = 0;
	else if (keycode == CTRL)
	{
		a->sprint = 0;
		a->crouch = 0;
	}
	return (keycode);
}

void	check_move(t_all *a)
{
	if (a->key.w)
		move_forward(a);
	if (a->key.left)
		turn_left(a);
	if (a->key.right)
		turn_right(a);
	if (a->key.s)
		move_back(a);
	if (a->key.d)
		move_right(a);
	if (a->key.a)
		move_left(a);
}