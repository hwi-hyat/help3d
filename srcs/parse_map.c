/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:50:28 by siykim            #+#    #+#             */
/*   Updated: 2023/05/17 13:26:57 by siykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	import_xpm(t_info *s, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];

	if (check_ext(file, "xpm") == 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int	parse_tex(t_info *s, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	if (s->err.m == 1)
		return (-13);
	(*i) += 2;
	ws_pass(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	file = malloc(sizeof(char) * (*i - j + 1));
	if (!file)
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = import_xpm(s, adr, file);
	free(file);
	if (j == -1)
		return (-9);
	return (0);
}

int	line_len(char *line)
{
	int	count;

	count = 0;
	while (line[count] != '\0')
		count++;
	return (count);
}

char	*line_to_map(char *line, int *i)
{
	char	*slab;
	int		j;

	slab = malloc(sizeof(char) * (line_len(line) + 1));
	if (!slab)
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| line[*i] == 'E' || line[*i] == 'W' || line [*i] == 'S'
			|| line [*i] == ' ')
			slab[j++] = line[*i];
		else
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int	map(t_info *s, char *line, int *i)
{
	char	**tmp;
	int		j;

	*i = 0;
	s->err.m = 1;
	tmp = malloc(sizeof(char *) * (s->map.y + 2));
	if (!tmp)
		return (-11);
	j = -1;
	while (++j < s->map.y)
		tmp[j] = s->map.tab[j];
	tmp[s->map.y] = line_to_map(line, i);
	if (tmp[s->map.y] == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.y++;
	if (s->map.x < line_len(line))
		s->map.x = line_len(line);
	return (0);
}
