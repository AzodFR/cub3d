/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:55:36 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/14 14:47:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void free_params(t_params *p)
{
	if (p->text_no != NULL)
		free(p->text_no);
	if (p->text_so != NULL)
		free(p->text_so);
	if (p->text_we != NULL)
		free(p->text_we);
	if (p->text_ea != NULL)
		free(p->text_ea);
	if (p->text_sprite != NULL)
		free(p->text_sprite);
}

void	ft_exit(int status, char *reason, t_params *p)
{
	if (p != NULL)
		free_params(p);
	ft_printf("PROGRAM EXITED (%d)\nREASON: %s\n", status, reason);
	exit(status);
}