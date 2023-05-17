/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:49:26 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 14:50:54 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_by_line(t_info *s, char *line)
{
	int		i;

	i = 0;
	ws_pass(line, &i);
	if ((str_len(line) == 0 || str_len(line) == c_ws(line)) && s->err.m == 1)
		return (print_error(-12));
	else if ((line[i] == '1' || s->err.m == 1) && line[i] != '\0')
		s->err.n = map(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = parse_tex(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = parse_tex(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = parse_tex(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = parse_tex(s, &s->tex.e, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = set_color(s, &s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = set_color(s, &s->tex.c, line, &i);
	if (ws_pass(line, &i) && s->err.n == 0 && line[i] != '\0')
		return (print_error(-10));
	if (s->err.n < 0)
		return (print_error(s->err.n));
	return (0);
}

int	check_error_gnl(char **line, int read_size, char **stock)
{
	if (!(line))
		return (-3);
	if (read_size == 0)
		free(*stock);
	if (read_size == 0)
		return (0);
	*stock = stock_trim(*stock);
	if (!stock)
		return (-3);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0)
		return (-3);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		read_size = read(fd, buf, 4095);
		if ((read_size) == -1)
			return (-3);
		buf[read_size] = '\0';
		stock = buf_join(stock, buf);
		if (!stock)
			return (-3);
	}
	*line = get_line(stock);
	return (check_error_gnl(line, read_size, &stock));
}

int	parse(t_info *s, char *mapname)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		return (print_error(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line_by_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (print_error(ret + 1));
	set_pos(s);
	return (check_elements(s));
}
