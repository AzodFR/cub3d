/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:50:26 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/05 10:59:25 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void		check_walls(t_params *p)
{
	int		fd;

	if ((fd = open(p->text_no, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the north's texture.", p, NULL);
	close(fd);
	if ((fd = open(p->text_so, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the south's texture.", p, NULL);
	close(fd);
	if ((fd = open(p->text_we, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the west's texture.", p, NULL);
	close(fd);
	if ((fd = open(p->text_ea, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the east's texture.", p, NULL);
	close(fd);
}

void		check_sprites(t_params *p)
{
	int		fd;

	if ((fd = open(p->text_sprite1, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the sprite's texture.", p, NULL);
	close(fd);
	if ((fd = open(p->text_sprite2, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the sprite's texture.", p, NULL);
	close(fd);
	if ((fd = open(p->text_sprite3, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the sprite's texture.", p, NULL);
	close(fd);
}
