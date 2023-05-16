/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2023/05/16 23:45:07 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_init(t_info *s)
{
	s->ray.x = 0;
	s->ray.y = 0;
	s->ray.i = 0;
	s->ray.v = 0;
	s->ray.w = 0;
	s->hit.x = 0;
	s->hit.y = 0;
	s->hit.d = 0;

	display(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int	game(t_info *s, char *mapname)
{
	s->mlx.ptr = mlx_init();
	if (parse(s, mapname) == -1)
		return (exterminate(s, 0));
	// rotate(s, 1);
	// move(s, 1);
	// rotate(s, -1);
	// move(s, -1);
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3D");
	display_init(s);
	mlx_hook(s->win.ptr, 2, 0, ft_key, s);
	mlx_hook(s->win.ptr, 17, 0, exterminate, s);
	mlx_loop(s->mlx.ptr);
	return (1);
}

void	initiate(t_info *s)
{
	s->mlx.ptr = NULL;
	s->win.ptr = NULL;
	s->win.x = WIDTH;
	s->win.y = HEIGHT;
	s->img.ptr = NULL;
	s->img.adr = NULL;
	s->img.fsh = 0;
	s->err.n = 0;
	s->err.m = 0;
	s->err.p = 0;
	s->map.tab = NULL;
	s->map.x = 0;
	s->map.y = 0;
	s->tex.n = NULL;
	s->tex.s = NULL;
	s->tex.e = NULL;
	s->tex.w = NULL;
	s->tex.c = NONE;
	s->tex.f = NONE;
	s->pos.x = 0;
	s->pos.y = 0;
	s->dir.x = 0;
	s->dir.y = 0;
	s->spr = NULL;
	//s->stk = NULL;
}

int	main(int argc, char **argv)
{
	t_info	s;

	if (argc == 2 && check_ext(argv[1], "cub"))
	{
		initiate(&s);
	}
	else
		write(2, "Error : Invalid arguments\n", 26);
	game(&s, argv[1]);
	return (0);
}
