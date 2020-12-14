/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:10:32 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/14 17:10:35 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBEDDD_H
# define CUBEDDD_H
# include "mlx.h"
# include <fcntl.h>
# include "ft_printf.h"

typedef struct		s_params
{
	int		win_x;
	int		win_y;
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	char	*text_sprite;
	int		f[3];
	int		c[3];
}					t_params;
typedef struct		s_mlx
{
	void		*ptr;
	void		*win;
}					t_mlx;
typedef struct		s_all
{
	struct s_params		p;
	struct s_mlx		mlx;
}					t_all;
void		ft_exit(int status, char *reason, t_params *p);
void		set_resolution(char *line, t_params *p);
void		set_texture(char *line, t_params *p, int face);
void		set_rgb(char *line, t_params *p, int floor, int i);
t_params	parser(char *file);
#endif