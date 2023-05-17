/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:50:39 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 14:53:40 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ws_pass(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int	a_to_i(char *line, int *i)
{
	int	num;

	num = 0;
	ws_pass(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

void	print_error2(int code)
{
	if (code == -10)
		write(2, "Error\n: Invalid line in file\n", 30);
	else if (code == -11)
		write(2, "Error\n: Memory allocation failed (map table)\n", 46);
	else if (code == -12)
		write(2, "Error\n: Invalid map\n", 21);
	else if (code == -13)
		write(2, "Error\n: Map info provided in wrong order\n", 42);
	else if (code == -15)
		write(2, "Error\n: Missing texture\n", 25);
	else if (code == -16)
		write(2, "Error\n: Missing floor/ceiling color\n", 37);
	else if (code == -17)
		write(2, "Error\n: No starting position\n", 30);
	else if (code == -18)
		write(2, "Error\n: Multiple starting positions\n", 37);
	else if (code == -19)
		write(2, "Error\n: Map isn't surrounded by walls\n", 39);
}

int	print_error(int code)
{
	if (code <= -10)
		print_error2(code);
	else if (code == -1)
		write(2, "Error\n: CANNOT OPEN FILE: FD\n", 29);
	else if (code == -2)
		write(2, "Error\n: Error\nOCCURED IN GNL\n", 30);
	else if (code == -5)
		write(2, "Error\n: Floor/ceiling specified twice\n", 39);
	else if (code == -6)
		write(2, "Error\n: Invalid floor/ceiling line\n", 36);
	else if (code == -7)
		write(2, "Error\n: Texture path specified twice\n", 38);
	else if (code == -8)
		write(2, "Error\n: Memory allocation failed (texture path)\n", 48);
	else if (code == -9)
		write(2, "Error\n: Invalid texture image\n", 31);
	return (-1);
}

int	valid_pos(t_info *f, int y, int x)
{
	int	xlen;

	if (y < 0 || y >= f->map.y)
		return (0);
	xlen = 0;
	while (f->map.tab[y][xlen])
		xlen++;
	if (x < 0 || x >= xlen)
		return (0);
	return (1);
}
