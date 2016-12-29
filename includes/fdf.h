/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:33:06 by bchaleil          #+#    #+#             */
/*   Updated: 2016/12/16 19:36:48 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define WIDTH 400
# define HEIGHT 400

# define CONTENT(p) (((t_vector*)(el->content))->p)

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
t_dlist		*parse_map(int fd);

#endif
