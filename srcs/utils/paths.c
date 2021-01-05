/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:55 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 10:57:46 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

char	*get_path(int i, t_params p)
{
	if (i == 0)
		return (p.text_no);
	else if (i == 1)
		return (p.text_so);
	else if (i == 2)
		return (p.text_ea);
	else if (i == 3)
		return (p.text_we);
	else if (i == 4)
		return (p.text_sprite1);
	else if (i == 5)
		return (p.text_sprite2);
	else
		return (p.text_sprite3);
}

int		is_wall(int i)
{
	return (i == 1 || i == 4);
}

int		is_sprite(char c)
{
	return (c == '2' || c == '3' || c == '5');
}

int		lx(int life)
{
	return (-90 * (5 - life));
}
