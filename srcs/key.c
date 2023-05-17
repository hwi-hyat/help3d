/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:50:12 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 14:42:00 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exterminate(t_info *s, int win)
{
	int	i;

	i = 0;
	while (i < s->map.y)
		free(s->map.tab[i++]);
	free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	exit(0);
	return (1);
}

void	move(t_info *s, double dir)
{
	s->pos.x += dir * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.x -= dir * (s->dir.x * SPEED / 100);
	s->pos.y += dir * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.y -= dir * (s->dir.y * SPEED / 100);
}

void	shift(t_info *s, double dir)
{
	s->pos.x -= dir * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.x += dir * (s->dir.y * SPEED / 100);
	s->pos.y += dir * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.y -= dir * (s->dir.x * SPEED / 100);
}

void	rotate(t_info *s, double dir)
{
	double	dist;

	s->dir.x = s->dir.x * cos(dir * TURN) - s->dir.y * sin(dir * TURN);
	s->dir.y = s->dir.y * cos(dir * TURN) + s->dir.x * sin(dir * TURN);
	dist = hypot(s->dir.x, s->dir.y);
	s->dir.x /= dist;
	s->dir.y /= dist;
}

int	ft_key(int key, void *arg)
{
	if (key == ESC)
		exterminate(arg, 1);
	else if (key == W)
		move(arg, 1);
	else if (key == A)
		shift(arg, -1);
	else if (key == S)
		move(arg, -1);
	else if (key == D)
		shift(arg, 1);
	else if (key == LEFT)
		rotate(arg, -1);
	else if (key == RIGHT)
		rotate(arg, 1);
	display_init(arg);
	return (1);
}
