/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:47:27 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/15 14:42:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void free_line_exit(char **line, int error, char *reasons, t_params *p)
{
	free(*line);
	ft_exit(error, reasons, p);
}

void	set_map(int *n, char *line, t_params *p)
{
	char	*tmp;

	if (*n > 8 && !ft_strlen(line))
		free_line_exit(&line, 1, "Error in map.", p);
	if (ft_strlen(line))
	{
		tmp = joinnfree(p->map, line);
		p->map = joinnfree(tmp,"\n");
		*n += 1;
	}
}