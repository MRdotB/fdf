#include "fdf.h"
#include <stdio.h>

static void		parse_map_line(t_fdf_map *fdf, char *line)
{
	char		**split;
	char		**split_ptr;
	int			x;
	static int	y = 0;
	t_vector	*el;

	x = 0;
	split = ft_strsplitstr(line, " ");
	split_ptr = split;
	while (*split)
	{
		//printf("[ %d, %d, %d ]\n", x, y, ft_atoi(*split));
		el = vector_create(x, y, ft_atoi(*split) / 2);
		fdf->map[x + y * fdf->max_x] = el;
		x++;
		free(*split);
		split++;
	}
	free(split_ptr);
	y++;
}
static t_fdf_map	*init_fdf_map(char **lines)
{
	t_fdf_map	*fdf;
	char		**split;
	int			x;
	int			y;

	if (!(fdf = (t_fdf_map*)malloc(sizeof(t_fdf_map))))
		return (NULL);
	x = 0;
	y = 0;
	split = ft_strsplitstr(*lines, " ");
	while(split[x])
		free(split[x++]);
	free(split);
	while(lines[y])
		y++;
	fdf->map = (t_vector**)malloc(sizeof(t_vector) * x * y);
	fdf->max_x = x;
	fdf->max_y = y;
	return (fdf);
}

static t_fdf_map	*parse_map_str(char *map)
{
	t_fdf_map	*fdf;
	char		**lines;
	char		**lines_ptr;

	lines = ft_strsplitstr(map, "\n\0");
	fdf = init_fdf_map(lines);
	lines_ptr = lines;
	while(*lines)
	{
		parse_map_line(fdf, *lines);
		free(*lines);
		lines++;
	}
	free(lines_ptr);
	free(map);
	return (fdf);
}

t_fdf_map			*parse_map(int fd)
{
	int		ret;
	char	tmp[2048];
	char	*map;
	char	*old_map;

	map = NULL;
	while ((ret = read(fd, tmp, 2048)) > 0)
	{
		tmp[ret] = '\0';
		if (map == NULL)
			map = ft_strdup(tmp);
		else
		{
			old_map = map;
			map = ft_strjoin(map, tmp);
			free(old_map);
		}
	}
	return (parse_map_str(map));
}
