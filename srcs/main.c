/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:32:07 by bchaleil          #+#    #+#             */
/*   Updated: 2017/01/09 19:06:52 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
t_fdf_data fdf_data;

t_vector	**rasterize_map(t_vector **map, int size)
{
	static t_3d	camera[4][4] = {{0.871214, 0, -0.490904, 0}, {-0.192902, 0.919559, -0.342346, 0}, {0.451415, 0.392953, 0.801132, 0}, {14.777467, 29.361945, 27.993464, 1}};
	static t_3d	s[4][4] = {{1, 0, 0, 0}, {0, -0.44807361612, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	t_3d		**world_to_camera;
	t_vector	**raster_map;
	int			i;

	i = 0;
	if (!(raster_map = (t_vector**)malloc(sizeof(t_vector) * size)))
		return (NULL);
	world_to_camera = matrix_inverse(matrix_mult(matrix_create(camera), matrix_create(s)));
	while (i < size)
	{
		raster_map[i] = rasterize(map[i], world_to_camera);
		i++;
	}
	return (raster_map);
}

void	render(t_fdf_map *fdf)
{
	t_vector	**raster_map;
	int			i;
	int			size;

	i = 0;
	size = fdf->max_x * fdf->max_y;
	raster_map = rasterize_map(fdf->map, size);
	while (i < size - 1)
	{
//		printf("x0 %d y0 %d x1 %d y1 %d",(int)raster_map[i]->x, (int)raster_map[i]->y,(int)raster_map[i + 1]->x, (int)raster_map[i + 1]->y);
		if (i % fdf->max_x != 0)
			drawline(fdf_data,(int)raster_map[i]->x, (int)raster_map[i]->y,(int)raster_map[i + 1]->x, (int)raster_map[i + 1]->y);
		if (i < size - fdf->max_x)
			drawline(fdf_data,(int)raster_map[i]->x, (int)raster_map[i]->y,(int)raster_map[i + fdf->max_x]->x, (int)raster_map[i + fdf->max_x]->y);
		i++;
	}
}


int	main(int ac, char **av)
{
	int			fd;
	t_fdf_map	*fdf;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		fdf = parse_map(fd);
	}
	void	*win1;
	void	*img;

	if (!(fdf_data.mlx = mlx_init()))
	{
		ft_putendl("MLX INIT FAIL");
		exit(0);
	}
	if (!(win1 = mlx_new_window(fdf_data.mlx, WIDTH, HEIGHT,"fdf")))
	{
		ft_putendl("NEW WINDOW FAIL");
		exit(0);
	}
	if (!(img = mlx_new_image(fdf_data.mlx, WIDTH, HEIGHT)))
	{
		ft_putendl("NEW IMAGE FAIL");
		exit(0);
	}
	fdf_data.data = mlx_get_data_addr(img, &(fdf_data.bpp), &(fdf_data.sl), &(fdf_data.endian));
	render(fdf);
	mlx_put_image_to_window(fdf_data.mlx, win1, img, 0, 0);

	sleep(20);
	return (0);
}
