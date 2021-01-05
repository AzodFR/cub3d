/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:55:36 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 10:14:31 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	free_line_exit(char **line, int error, char *reasons, t_params *p)
{
	free(*line);
	ft_exit(error, reasons, p, NULL);
}

void	free_params(t_params *p)
{
	if (p->text_no != NULL && ft_isprint(p->text_no[0]))
		free(p->text_no);
	if (p->text_so != NULL && ft_isprint(p->text_so[0]))
		free(p->text_so);
	if (p->text_we != NULL && ft_isprint(p->text_we[0]))
		free(p->text_we);
	if (p->text_ea != NULL && ft_isprint(p->text_ea[0]))
		free(p->text_ea);
	if (p->text_sprite1 != NULL && ft_isprint(p->text_sprite1[0]))
		free(p->text_sprite1);
	if (p->text_sprite2 != NULL && ft_isprint(p->text_sprite2[0]))
		free(p->text_sprite2);
	if (p->text_sprite3 != NULL && ft_isprint(p->text_sprite3[0]))
		free(p->text_sprite3);
}

void	free_all(t_all *a)
{
	int		i;

	i = -1;
	if (a->map.map != NULL && ft_isprint(a->map.map[0][0]))
	{
		while (a->map.map[++i])
			free(a->map.worldmap[i]);
		free(a->map.worldmap);
		i = -1;
		while (a->map.map[++i])
			if (a->map.map[i] != NULL && ft_isprint(a->map.map[i][0]))
				free(a->map.map[i]);
		free(a->map.map);
	}
	if (a->map.nbsprite)
		free(a->map.sprite);
}

void	ft_exit(int status, char *reason, t_params *p, t_all *a)
{
	if (p != NULL)
		free_params(p);
	if (status == -1)
		status = 0;
	else if (a != NULL)
		free_all(a);
	if (status == 1)
		ft_printf("Error\n");
	ft_printf("PROGRAM EXITED (%d)\nREASON: %s\n", status, reason);
	exit(status);
}
