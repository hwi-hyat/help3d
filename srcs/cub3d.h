/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:49:32 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 15:06:42 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define NONE 0xFF000000
# define BLACK 0x00000000
# define WIDTH 640
# define HEIGHT 480

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define SPEED 15
# define TURN 0.05

typedef struct s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
}				t_img;

typedef struct s_err
{
	int				n;
	int				m;
	int				p;
}				t_err;

typedef struct s_map
{
	char			**tab;
	int				x;
	int				y;
}				t_map;

typedef struct s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}				t_ray;

typedef struct s_hit
{
	double			x;
	double			y;
	double			d;
}				t_hit;

typedef struct s_info
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
}				t_info;

void			initiate(t_info *f);
int				game(t_info *f, char *mapname);
void			display_init(t_info *f);

int				parse(t_info *s, char *mapname);
int				get_next_line(int fd, char **line);
int				line_by_line(t_info *s, char *line);

int				map(t_info *s, char *line, int *i);
char			*line_to_map(char *line, int *i);
int				line_len(char *line);
int				parse_tex(t_info *s, unsigned int **adr, char *line, int *i);
int				import_xpm(t_info *s, unsigned int **adr, char *file);

void			set_pos(t_info *s);
int				set_color(t_info *s, unsigned int *color, char *line, int *i);

int				check_ext(char *arg, char *ext);
int				check_surrounding(t_info *s, int y, int x);
int				check_map(t_info *s);
int				check_elements(t_info *s);

int				ft_key(int key, void *arg);
void			rotate(t_info *s, double c);
void			shift(t_info *s, double c);
void			move(t_info *s, double c);
int				exterminate(t_info *s, int win);

void			display(t_info *s);
void			set_ray(t_info *s);
void			set_ambig_ray_dir(t_info *s);
void			vertical_hit(t_info *s);
void			horizontal_hit(t_info *s);

int				distort_adj(t_info *s);
void			printing_column(t_info *s, int start);
unsigned int	get_pixel(t_info *s, double i);

char			*error(char *stock);
int				newline_check(char *stock, int read_size);
char			*buf_join(char *stock, char *buf);
char			*stock_trim(char *stock);
char			*get_line(char *stock);

int				a_to_i(char *line, int *i);
int				ws_pass(char *line, int *i);
int				print_error(int code);
int				valid_pos(t_info *f, int y, int x);

int				str_len(char *str);
int				c_ws(char *line);

#endif
