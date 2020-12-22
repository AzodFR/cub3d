/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:03:33 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 14:37:15 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void	set_texture(char *line, t_params *p, int face)
{
	char	*path;
	char	*tmp;

	line[0] = ' ';
	line[1] = ' ';
	tmp = ft_strtrim(line, " ");
	path = ft_strtrim(tmp, "\t");
	free(tmp);
	if (face == 0 && !p->text_sprite1)
		p->text_sprite1 = ft_strdup(path);
	else if (face == 5 && !p->text_sprite2)
		p->text_sprite2 = ft_strdup(path);
	else if (face == 1 && !p->text_no)
		p->text_no = ft_strdup(path);
	else if (face == 2 && !p->text_so)
		p->text_so = ft_strdup(path);
	else if (face == 3 && !p->text_we)
		p->text_we = ft_strdup(path);
	else if (face == 4 && !p->text_ea)
		p->text_ea = ft_strdup(path);
	else
	{
		free(path);
		ft_exit(1, "Duplicate texture section", p, NULL);
	}
	free(path);
}

void	set_floor_rgb(int red, int green, int blue, t_params *p)
{
	p->f[0] = red;
	p->f[1] = green;
	p->f[2] = blue;
}

void	set_ceil_rgb(int red, int green, int blue, t_params *p)
{
	p->c[0] = red;
	p->c[1] = green;
	p->c[2] = blue;
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
		set_floor_rgb(red, green, blue, p);
	else
		set_ceil_rgb(red, green, blue, p);
	free(rgb);
}
