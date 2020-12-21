/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 18:37:29 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/21 19:15:20 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	take_screenshot(t_all a)
{
	int		fd;
	static unsigned char header[54] = {66,77,0,0,0,0,0,0,0,0,54,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,1,0,24};;
	(void)a;
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd,header,54);
	close(fd);
}