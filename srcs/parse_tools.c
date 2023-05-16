/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 21:41:51 by cclaude           #+#    #+#             */
/*   Updated: 2023/05/16 12:49:55 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ws_comma_pass(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == ',')
		(*i)++;
	return (1);
}

int	set_color(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = a_to_i(line, i);
	ws_comma_pass(line, i);
	g = a_to_i(line, i);
	ws_comma_pass(line, i);
	b = a_to_i(line, i);
	ws_pass(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
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
				s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				s->dir.x *= (c == 'W') ? -1 : 1;
				s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				s->dir.y *= (c == 'N') ? -1 : 1;
				s->err.p++;
				s->map.tab[i][j] = '0';
			}
		}
		j = -1;
	}
}
