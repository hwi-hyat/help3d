/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:16:06 by cclaude           #+#    #+#             */
/*   Updated: 2023/05/16 12:11:02 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ext(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int	check_surrounding(t_info *s, int y, int x)
{
	int	ty;
	int	tx;
	int	i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		ty = i + y;
		j = -1;
		while (j <= 1)
		{
			tx = j + x;
			if (ty < 0 || tx < 0 || ty >= s->map.y || tx >= s->map.x)
				return (0);
			if (!(s->map.tab[ty][tx] == '1' || s->map.tab[ty][tx] == '0'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(t_info *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (s->map.tab[i][j] == '0')
				if (check_surrounding(s, i, j) == 0)
					return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_elements(t_info *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (print_error(-14));
	else if (s->tex.n == NULL || s->tex.s == NULL
		|| s->tex.e == NULL || s->tex.w == NULL)
		return (print_error(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (print_error(-16));
	else if (s->err.p == 0)
		return (print_error(-17));
	else if (s->err.p > 1)
		return (print_error(-18));
	else if (check_map(s) == -1)
		return (print_error(-19));
	return (1);
}
