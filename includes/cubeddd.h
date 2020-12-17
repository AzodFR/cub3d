/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubeddd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:10:32 by thjacque          #+#    #+#             */
/*   Updated: 2020/12/17 19:16:36 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBEDDD_H
# define CUBEDDD_H
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf.h"
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define SHIFT 257
# define CTRL 256

typedef struct		s_params
{
	int		win_x;
	int		win_y;
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	char	*text_sprite;
	char	*map;
	int		f[3];
	int		c[3];
}					t_params;
typedef struct		s_mlx
{
	void		*ptr;
	void		*win;
}					t_mlx;
typedef struct		s_map
{
	char		p_facing;
	char		**map;
	int			**worldmap;
}					t_map;
typedef struct		s_img
{
	void		*img;
	int			x;
	int			y;
	int			posx;
	int			posy;
}					t_img;
typedef struct		s_display
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double oldcameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int hit;
	int stepX;
	int stepY;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double texPos;
	int texNum;
	int texX;
	int texY;
	double step;
	double wallX;
	double floorXWall;
	double floorYWall;
	double distWall;
	double distPlayer;
	double currentDist;
	double currentFloorX;
	double currentFloorY;
	double weight;
	int floorTexX;
	int floorTexY;
}					t_display;
typedef struct		s_texture
{
	void	*t1;
	int		*t1p;
	int		i1[4];
	void	*t2;
	int		*t2p;
	int		i2[4];
	void	*t3;
	int		*t3p;
	int		i3[4];
	void	*t4;
	int		*t4p;
	int		i4[4];

}					t_texture;
typedef struct		s_all
{
	struct s_params		p;
	struct s_mlx		mlx;
	struct s_map		map;
	struct s_img		img;
	struct s_display	d;
	struct s_texture	texture;
	void				*main;
	int					key_w;
	int					key_a;
	int					key_s;
	int					key_d;
	int					right;
	int					left;
	double				sprint;
	double				crouch;
}					t_all;
void		ft_exit(int status, char *reason, t_params *p, t_all *a);
void		set_resolution(char *line, t_params *p);
void		set_texture(char *line, t_params *p, int face);
void		set_rgb(char *line, t_params *p, int floor, int i);
void		set_map(int *n, char *line, t_params *p);
void		free_line_exit(char **line, int error, char *reasons, t_params *p);
t_map		get_map(t_params p);
t_all		parser(char *file, int ret);
#endif