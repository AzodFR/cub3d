/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:37:29 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/04 15:06:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	ft_fill_bmp_header(t_all *a, int *array)
{
	int		i;

	ft_memmove(a->bmp->header, "BM", 2);
	ft_memmove(a->bmp->header + 2, &a->bmp->file_s, 4);
	ft_memmove(a->bmp->header + 10, &a->bmp->header_s, 4);
	ft_memmove(a->bmp->header + 14, &a->bmp->bytes_s, 4);
	ft_memmove(a->bmp->header + 18, &a->bmp->w, 4);
	ft_memmove(a->bmp->header + 22, &a->bmp->height, 4);
	ft_memmove(a->bmp->header + 26, &a->bmp->biplanes, 4);
	ft_memmove(a->bmp->header + 28, &a->bmp->bytes_number, 4);
	ft_memmove(a->bmp->header + 34, &a->bmp->image_s, 4);
	a->bmp->fd = open("./save.bmp", O_TRUNC | O_WRONLY | O_CREAT, 0777);
	i = a->bmp->height;
	write(a->bmp->fd, a->bmp->header, 54);
	while (i != 0)
		write(a->bmp->fd, array + (i-- * a->bmp->w), a->bmp->w * 4);
	close(a->bmp->fd);
	ft_exit(0, "Screenshoted !", &(a->p), a);
}

void	ft_init_bmp(t_all *a, int width, int height, int *array)
{
	if (!(a->bmp = malloc(sizeof(t_bmp))))
		ft_exit(1, "Malloc Error.", &(a->p), a);
	ft_bzero(a->bmp->header, 54);
	a->bmp->w = width;
	a->bmp->height = height;
	a->bmp->bytes_number = 32;
	a->bmp->width_bytes = ((a->bmp->w * a->bmp->bytes_number + 31) / 32) * 4;
	a->bmp->image_s = a->bmp->width_bytes * a->bmp->height;
	a->bmp->bytes_s = 40;
	a->bmp->header_s = 54;
	a->bmp->file_s = 54 + a->bmp->image_s;
	a->bmp->biplanes = 1;
	ft_fill_bmp_header(a, array);
}
