/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:39:34 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/22 19:13:32 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubeddd.h"

int		not_valid(int **map, int i, int j)
{
	return (map[i][j] == -1);
}

int		**set_map_and_len(t_map m, int i, int *len)
{
	*len = ft_strlen(m.map[i]) - 1;
	return (m.worldmap);
}

int		check_zero(t_map m, int i, int j, int high)
{
	int		**map;
	int		len;

	map = set_map_and_len(m, i, &len);
	if (j == 0 || (j > 0 && not_valid(map, i, j - 1)))
		return (0);
	if (j == len || (j < len && not_valid(map, i, j + 1)))
		return (0);
	if (i == 0 || (i > 0 && not_valid(map, i - 1, j)))
		return (0);
	if (i == high || (i < high && not_valid(map, i + 1, j)))
		return (0);
	if (i > 0 && j > 0 && not_valid(map, i - 1, j - 1))
		return (0);
	if (i > 0 && j >= (int)ft_strlen(m.map[i - 1]) - 1)
		return (0);
	if (i > 0 && j < len && not_valid(map, i - 1, j + 1))
		return (0);
	if (i < high && j > 0 && not_valid(map, i + 1, j - 1))
		return (0);
	if (i < high && j == (int)ft_strlen(m.map[i + 1]) - 1)
		return (0);
	if (i < high && j < len && not_valid(map, i + 1, j + 1))
		return (0);
	return (1);
}

t_map	get_high(t_map map, int *j)
{
	int	high;
	int	i;

	high = -1;
	i = -1;
	map.nbsprite = 0;
	while (map.map[++high] && (i = -1))
		while (map.map[high][++i])
			if (map.map[high][i] == '2' || map.map[high][i] == '3')
				map.nbsprite += 1;
	*j = high;
	return (map);
}

t_map	check_map(t_map map, t_params *p)
{
	int		i;
	int		j;
	int		high;

	map = get_high(map, &high);
	high--;
	if (!(map.sprite = malloc(map.nbsprite * sizeof(t_sprite))))
		ft_exit(1, "Malloc error.", p, NULL);
	i = -1;
	map.nbsprite = 0;
	while (map.map[++i])
	{
		j = 0;
		while (map.map[i][j] != '0' && map.map[i][j])
			j++;
		while (map.map[i][j])
		{
			if (map.map[i][j] == '0' && !check_zero(map, i, j, high))
				ft_exit(1, "Invalid Map.", p, NULL);
			else if (map.map[i][j] == '2' || map.map[i][j] == '3')
				map = treat_sprite(map, i, j);
			j++;
		}
	}
	return (map);
}
