/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:03:33 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/16 09:57:21 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	set_texture(char *line, t_params *p, int face)
{
	char	*path;

	line[0] = ' ';
	line[1] = ' ';
	path = ft_strtrim(line, " ");
	if (face == 0)
		p->text_sprite = ft_strdup(path);
	if (face == 1)
		p->text_no = ft_strdup(path);
	if (face == 2)
		p->text_so = ft_strdup(path);
	if (face == 3)
		p->text_we = ft_strdup(path);
	if (face == 4)
		p->text_ea = ft_strdup(path);
	free (path);
}

void	set_rgb_array(int red, int green, int blue, t_params *p, int floor)
{
	if (floor)
	{
		p->f[0] = red;
		p->f[1] = green;
		p->f[2] = blue;
	}
	else
	{
		p->c[0] = red;
		p->c[1] = green;
		p->c[2] = blue;
	}
}

void	set_rgb(char *line, t_params *p, int floor, int i)
{
	char	*rgb;
	int		red;
	int		green;
	int		blue;

	line[0] = ' ';
	rgb = ft_strtrim(line, " ");
	red = 0;
	green = 0;
	blue = 0;
	while (ft_isdigit(rgb[++i]))
		red = (red * 10) + (rgb[i] - '0');
	if (rgb[i] != ',')
		ft_exit(1, "Invalid character in RGB", p, NULL);
	while (ft_isdigit(rgb[++i]))
		green = (green * 10) + (rgb[i] - '0');
	if (rgb[i] != ',')
		ft_exit(1, "Invalid character in RGB", p, NULL);
	while (ft_isdigit(rgb[++i]))
		blue = (blue * 10) + (rgb[i] - '0');
	if (floor)
		set_rgb_array(red, green, blue, p, 1);
	else
		set_rgb_array(red, green, blue, p, 0);
	free (rgb);
}