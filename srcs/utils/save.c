/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:37:29 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 17:03:32 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	take_screenshot(t_all a)
{
	int		fd;

	(void)a;
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "BM", 54);
	close(fd);
}
