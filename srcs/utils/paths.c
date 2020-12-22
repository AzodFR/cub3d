/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:55 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 18:55:23 by thjacque         ###   ########lyon.fr   */
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
	else
		return (p.text_sprite2);
}

int		is_wall(int i)
{
	return (i == 1 || i == 4);
}

int		lx(int life)
{
	return (-90 * (5 - life));
}
