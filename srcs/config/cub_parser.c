/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:48:56 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/15 15:02:53 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

t_params	init_params(void)
{
	t_params p;

	p.win_x = 0;
	p.win_y = 0;
	p.text_no = NULL;
	p.text_so = NULL;
	p.text_we = NULL;
	p.text_ea = NULL;
	p.text_sprite = NULL;
	p.map = ft_strdup("");
	p.f[0] = 0;
	p.f[1] = 0;
	p.f[2] = 0;
	p.c[0] = 0;
	p.c[1] = 0;
	p.c[2] = 0;
	return (p);
}

void treat_line(char *line, t_params *p, int *n)
{
	if (*n >= 8 )
		set_map(n, line, p);
	else if (line[0] == 'R' && (*n += 1))
		set_resolution(line, p);
	else if (!ft_strncmp(line, "NO", 2) && (*n += 1))
		set_texture(line, p, 1);
	else if (!ft_strncmp(line, "SO", 2) && (*n += 1))
		set_texture(line, p, 2);
	else if (!ft_strncmp(line, "WE", 2) && (*n += 1))
		set_texture(line, p, 3);
	else if (!ft_strncmp(line, "EA", 2) && (*n += 1))
		set_texture(line, p, 4);
	else if (!ft_strncmp(line, "S ", 2) && (*n += 1))
		set_texture(line, p, 0);
	else if (!ft_strncmp(line, "F ", 2) && (*n += 1))
		set_rgb(line, p, 1, -1);
	else if (!ft_strncmp(line, "C ", 2) && (*n += 1))
		set_rgb(line, p, 0, -1);
	free(line);
}

void	check_params(t_params *p)
{
	int fd;

	if ((fd = open(p->text_no, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the north's texture.", p);
	close(fd);
	if ((fd = open(p->text_so, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the south's texture.", p);
	close(fd);
	if ((fd = open(p->text_we, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the west's texture.", p);
	close(fd);
	if ((fd = open(p->text_ea, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the south's texture.", p);
	close(fd);
	if ((fd = open(p->text_sprite, O_RDONLY)) < 0)
		ft_exit(1, "Cannot found the sprite's texture.", p);
	close(fd);
	if (p->f[0] > 255 || p->f[1] > 255 || p->f[2] > 255)
		ft_exit(1, "RGB not valid for the floor.", p);
	if (p->c[0] > 255 || p->c[1] > 255 || p->c[2] > 255)
		ft_exit(1, "RGB not valid for the ceil.", p);
}

void	check_extension(char *file)
{
	int		i;

	i = ft_strlen(file);
	if (i < 4)
		ft_exit(1, "Incorrect filename.", NULL);
	if(file[i - 1] != 'b' || file[i - 2] != 'u' ||
	file[i - 3] != 'c' || file[i - 4] != '.')
		ft_exit(1, "Incorrect filename.", NULL);
}

t_all	parser(char *file, int ret)
{
	t_params	p;
	t_all		all;
	char		*line;
	int			fd;
	int			n;

	check_extension(file);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_exit(1, "Cannot open the file.", NULL);
	p = init_params();
	n = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
		treat_line(line, &p, &n);
	treat_line(line, &p, &n);
	if (ret == -1)
		ft_exit(1, "Error while reading the file.", &p);
	close(fd);
	check_params(&p);
	all.p = p;
	all.map.map = ft_split(all.p.map, '\n');
	free(all.p.map);
	return (all);
}