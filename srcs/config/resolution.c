/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:04:03 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/14 14:53:09 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	set_resolution(char *line, t_params *p)
{
	int		i;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13 ) || line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		p->win_x = (p->win_x * 10) + (line[i++] - '0');
	if (ft_isalpha(line[i]))
		ft_exit(1, "Invalid character in resolution section.", p);
	while ((line[i] >= 9 && line[i] <= 13 ) || line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		p->win_y = (p->win_y * 10) + (line[i++] - '0');
	if (ft_isalpha(line[i]))
		ft_exit(1, "Invalid character in resolution section.", p);
}