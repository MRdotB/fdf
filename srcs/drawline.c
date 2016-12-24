#include "fdf.h"

static void	buffer_plot(t_fdf_data fdf_data, int x, int y) {
	int opp;
	int pos;
	int color;
	
	opp = fdf_data.bpp / 8;
	color = mlx_get_color_value(fdf_data.mlx, 65535);
	pos = y * fdf_data.sl + x * opp;
	fdf_data.data[pos] = color;
}

void		drawline(t_fdf_data fdf_data, int x0, int y0, int x1, int y1)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;

	dx = ABS(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = ABS(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		buffer_plot(fdf_data, x0, y0);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}
