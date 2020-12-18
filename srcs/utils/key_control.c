/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:43:14 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/18 16:44:01 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

int key_press(int keycode,t_all *a)
{
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
		a->crouch = 0;
	}
	return (keycode);
}