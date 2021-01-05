/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:04:03 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 14:51:35 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	clear_resolution(t_params *p)
{
	if (p->win_x > 2560)
		p->win_x = 2560;
	if (p->win_x < 640)
		p->win_x = 640;
	if (p->win_y > 1440)
		p->win_y = 1440;
	if (p->win_y < 640)
		p->win_y = 640;
}

void	set_resolution(char *line, t_params *p)
{
	int		i;

	i = 1;
	if (p->win_x > 0 || p->win_y > 0)
		ft_exit(1, "Duplicate resolution section.", p, NULL);
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		p->win_x = (p->win_x * 10) + (line[i++] - '0');
	if (ft_isalpha(line[i]))
		ft_exit(1, "Invalid character in resolution section.", p, NULL);
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		p->win_y = (p->win_y * 10) + (line[i++] - '0');
	if (ft_isalpha(line[i]))
		ft_exit(1, "Invalid character in resolution section.", p, NULL);
	clear_resolution(p);
}
