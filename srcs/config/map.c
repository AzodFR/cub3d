/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:47:27 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/18 13:35:42 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void free_line_exit(char **line, int error, char *reasons, t_params *p)
{
	free(*line);
	ft_exit(error, reasons, p, NULL);
}

void	set_map(int *n, char *line, t_params *p)
{
	char	*tmp;
	tmp = joinnfree(p->map, line);
	p->map = joinnfree(tmp,"\n");
	*n += 1;
}

int		forward_map(int i, int *found, t_params p)
{
	while ((p.map[i] >= 9 && p.map[i] <= 13) || p.map[i] == ' ')
		i++;
	if (p.map[i] != '1')
		ft_exit(1, "Invalid Map.", &p, NULL);
	while (p.map[--i] != '\n')
	{
		while (p.map[i] == '1')
			i--;
		if (p.map[i] != ' ')
			ft_exit(1, "Invalid Map.", &p, NULL);
	}
	ft_memset(p.map, '\n', i);
	*found = 1;
	return (i);
}

int		is_player(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->p_facing)
			map->error = 1;
		else
			map->p_facing = c;
		map->pos[0]= x + 0.5;
		map->pos[1]= y + 0.5;
		dprintf(1, "x: %d y: %d\n",x,y);
		return (1);
	}
	if (c != '0' && c != '1' && c != '2')
		map->error = 1;
	return (0);
}

t_map	get_map(t_params p)
{
	t_map 	m;
	int		i;
	int		found;
	int		end;
	int		j;

	i = -1;
	found = 0;
	end = ft_strlen(p.map);
	while (p.map[++i])
		if (!found)
			i = forward_map(i, &found, p);
	i--;
	while ((p.map[i] >= 9 && p.map[i] <= 13) || p.map[i] == ' ')
		i--;
	if (p.map[i] != '1')
		ft_exit(1, "Invalid Map.", &p, NULL);
	ft_memset(p.map + i + 1, '\n', end - i);
	m.map = ft_split(p.map, '\n');
	i = -1;
	m.p_facing = 0;
	m.error = 0;
	while (m.map[++i])
		;
	m.worldmap = malloc(i*sizeof(int*));
	i = -1;
	while (m.map[++i])
	{
		j = -1;
		while (m.map[i][++j])
			;
		m.worldmap[i] = malloc(j*sizeof(int));
		j = -1;
		while (m.map[i][++j])
			m.worldmap[i][j] = m.map[i][j] == ' ' ? -1 : is_player(m.map[i][j], &m, i, j) ? 0 : m.map[i][j] - '0';
	}
	i = -1;
	return m;
}