/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:47:27 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 15:33:27 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

void		set_map(int *n, char *line, t_params *p)
{
	char	*tmp;

	tmp = joinnfree(p->map, line);
	p->map = joinnfree(tmp, "\n");
	*n += 1;
}

int			forward_map(int i, int *found, t_params p)
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

int			is_player(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->p_facing)
			map->error = 1;
		else
			map->p_facing = c;
		map->pos[0] = x;
		map->pos[1] = y;
		return (1);
	}
	if (c != '0' && c != '1' && c != '2' && c != '3')
		map->error = 1;
	return (0);
}

t_map		map_to_int(t_map m, int i, t_params *p)
{
	int		j;

	while (m.map[++i])
		;
	if (!(m.worldmap = malloc(i * sizeof(int *))))
		ft_exit(1, "Malloc error.", p, NULL);
	i = -1;
	while (m.map[++i])
	{
		j = -1;
		while (m.map[i][++j])
			;
		if (!(m.worldmap[i] = malloc(j * sizeof(int))))
			ft_exit(1, "Malloc error.", p, NULL);
		j = -1;
		while (m.map[i][++j])
		{
			if (m.map[i][j] == ' ')
				m.worldmap[i][j] = -1;
			else
				m.worldmap[i][j] = is_player(m.map[i][j], &m, i, j) ?
				0 : m.map[i][j] - '0';
		}
	}
	return (m);
}

t_map		get_map(t_params p)
{
	t_map	m;
	int		i;
	int		found;
	int		end;

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
	m.p_facing = 0;
	m.error = 0;
	m = map_to_int(m, -1, &p);
	m = check_map(m, &p);
	return (m);
}
