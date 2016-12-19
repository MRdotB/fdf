/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:32:07 by bchaleil          #+#    #+#             */
/*   Updated: 2016/12/16 19:35:10 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

#define WIDTH 400
#define HEIGHT 400

void	color_map_2(char *mlx, unsigned char *data,int bpp,int sl,int w,int h,int endian, int type)
{
	int	x;
	int	y;
	int	opp;
	int	dec;
	int	color;
	int	color2;
	unsigned char *ptr;

	opp = bpp/8;
	printf("(opp : %d) %d %d",opp, endian, type);
	y = h;
	x = w;
	color = (x * 255) / w + ((((w - x) * 255) / w) <<16) + (((y * 255) / h) << 8);
	printf("color = %d\n", color);
	while (y--)
	{
//		printf("y = %d\n", y);
		ptr = data+y*sl;
		x = w;
		while (x--)
		{
			color2 = mlx_get_color_value(mlx ,color);
			dec = opp;
			while (dec--)
				*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
		}
	}
}
void	buffer_pixel_put(char *mlx, unsigned char *data, int bpp, int sl, unsigned int x, unsigned int y) {
	int opp;
	int pos;
	int color;
	
	opp = bpp / 8;
	color = mlx_get_color_value(mlx, 65535);
	pos = y * sl + x * opp;
	data[pos] = color;
}

int	main(void)
{
	void	*mlx;
	void	*win1;
	void	*img;
	char	*data;
	int		bpp;
	int		sl;
	int		endian;

	if (!(mlx = mlx_init()))
	{
		ft_putendl("MLX INIT FAIL");
		exit(0);
	}
	if (!(win1 = mlx_new_window(mlx, WIDTH, HEIGHT,"fdf")))
	{
		ft_putendl("NEW WINDOW FAIL");
		exit(0);
	}
	if (!(img = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		ft_putendl("NEW IMAGE FAIL");
		exit(0);
	}
	data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	printf("OK (bpp %d, sizeline %d endian %d type %d)\n", bpp, sl, endian,((t_img *)img)->type);
//	color_map_2(mlx, (unsigned char*)data, bpp, sl, WIDTH, HEIGHT, endian, ((t_img *)img)->type);
	buffer_pixel_put(mlx, (unsigned char*)data, bpp, sl, 0, 0);
	buffer_pixel_put(mlx, (unsigned char*)data, bpp, sl, 0, 1);
	buffer_pixel_put(mlx, (unsigned char*)data, bpp, sl, 0, 2);
	mlx_put_image_to_window(mlx, win1, img, 0, 0);

	sleep(10);
	return (0);
}
