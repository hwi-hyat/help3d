/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:50:32 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 15:13:54 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ws_comma_pass(char *line, int *i)
{
	int	comma;

	comma = 0;
	while (line[*i] == ' ' || line[*i] == ',')
	{
		if (line[*i] == ',')
			comma++;
		(*i)++;
	}
	if (comma != 1)
		return (-1);
	return (1);
}

int	set_color(t_info *s, unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	if (s->err.m == 1)
		return (-13);
	(*i)++;
	r = a_to_i(line, i);
	if (ws_comma_pass(line, i) == -1)
		return (-6);
	g = a_to_i(line, i);
	if (ws_comma_pass(line, i) == -1)
		return (-6);
	b = a_to_i(line, i);
	ws_pass(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

void	set_dir(t_info *s, char c)
{
	if (c == 'N')
	{
		s->dir.x = 0;
		s->dir.y = -1;
	}
	else if (c == 'E')
	{
		s->dir.x = 1;
		s->dir.y = 0;
	}
	else if (c == 'S')
	{
		s->dir.x = 0;
		s->dir.y = 1;
	}
	else if (c == 'W')
	{
		s->dir.x = -1;
		s->dir.y = 0;
	}
}

void	set_pos(t_info *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (s->map.tab[++i])
	{
		while (s->map.tab[i][++j])
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				set_dir(s, c);
				s->err.p++;
				s->map.tab[i][j] = '0';
			}
		}
		j = -1;
	}
}
