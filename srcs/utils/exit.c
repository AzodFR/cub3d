/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:55:36 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/15 18:01:48 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void free_params(t_params *p)
{
	if (p->text_no != NULL && ft_isprint(p->text_no[0]))
		free(p->text_no);
	if (p->text_so != NULL && ft_isprint(p->text_so[0]))
		free(p->text_so);
	if (p->text_we != NULL && ft_isprint(p->text_we[0]))
		free(p->text_we);
	if (p->text_ea != NULL && ft_isprint(p->text_ea[0]))
		free(p->text_ea);
	if (p->text_sprite != NULL && ft_isprint(p->text_sprite[0]))
		free(p->text_sprite);
	/*if (p->map != NULL && ft_isprint(p->map[0]))
		free(p->map);*/
}

void	ft_exit(int status, char *reason, t_params *p)
{
	if (p != NULL)
		free_params(p);
	ft_printf("PROGRAM EXITED (%d)\nREASON: %s\n", status, reason);
	exit(status);
}