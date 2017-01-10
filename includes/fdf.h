/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:33:06 by bchaleil          #+#    #+#             */
/*   Updated: 2017/01/08 18:59:15 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define WIDTH 512
# define HEIGHT 512

# define CONTENT(p) (((t_vector*)(el->content))->p)

struct				s_fdf_map
{
	t_vector		**map;
	int				max_x;
	int				max_y;
};

typedef struct s_fdf_map t_fdf_map;

struct				s_fdf_data
{
	void			*mlx;
	char			*data;
	int				bpp;
	int				sl;
	int				endian;
	int				type;
};

typedef struct s_fdf_data	t_fdf_data;

void		drawline(t_fdf_data fdf_data, int x0, int y0, int x1, int y1);
void		buffer_plot(t_fdf_data fdf_data, int x, int y);
t_fdf_map	*parse_map(int fd);

#endif
