#include "fdf.h"
#include <stdio.h>

static void		parse_map_line(t_dlist **head, char	*line)
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
//		printf("[ %d, %d, %d ]\n", x, y, ft_atoi(*split));
		el = vector_create(x, y, ft_atoi(*split));
		ft_dlstpush(head, ft_dlstnew((void*)el, sizeof(el)));
		x++;
		free(*split);
		split++;
	}
	free(split_ptr);
	y++;
}

static t_dlist	*parse_map_str(char *map)
{
	t_dlist	*head;
	char	**lines;
	char	**lines_ptr;

	head = NULL;
	lines = ft_strsplitstr(map, "\n\0");
	lines_ptr = lines;
	while(*lines)
	{
		parse_map_line(&head, *lines);
		free(*lines);
		lines++;
	}
	free(lines_ptr);
	free(map);
	return (head);
}

t_dlist			*parse_map(int fd)
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
