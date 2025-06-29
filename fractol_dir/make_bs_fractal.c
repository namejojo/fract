/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bs_fractal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:13:21 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/21 13:50:45 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	get_color(t_mlx_data *data, float ind)
{
	if (data->col == XK_1 || data->col == XK_2 || data->col == XK_3)
		return ((((int)(((ind / data->sc)) * 255))) <<
		(8 * (data->col == XK_2) + 16 * (data->col == XK_3)));
	else if (data->col == XK_4)
		return ((ind / data->sc) * 16777216);
	else if (data->col == XK_5)
		return ((1 - (ind / data->sc)) * 16777216);
	return (data->a + data->b * cos(2 * 3.14159 * \
			(data->c * (ind / 100) + data->d)));
}

int	bs_fractol_formula(t_mlx_data *data)
{
	double	ind;
	double	real;

	ind = 0;
	while (ind++ < data->sc)
	{
		data->n.z_i = (data->n.z_i) * ((data->n.z_i > 0) - (data->n.z_i < 0));
		data->n.z_r = (data->n.z_r) * ((data->n.z_r > 0) - (data->n.z_r < 0));
		real = (data->n.z_r * data->n.z_r) - \
		(data->n.z_i * data->n.z_i) + data->n.c_r;
		data->n.z_i = (data->n.z_r * data->n.z_i * 2) + data->n.c_i;
		data->n.z_r = real;
		if ((data->n.z_r * data->n.z_r) + (data->n.z_i * data->n.z_i) > 4)
			return (get_color(data, ind));
	}
	return (0);
}

void	burning_ship(t_mlx_data *data)
{
	double	x;
	double	y;
	double	w;
	double	h;

	y = -1;
	w = WIDTH;
	h = HIGHT;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			data->n.z_r = 0;
			data->n.z_i = 0;
			data->n.c_r = (((w - x) * data->x_mult / w)) - data->x_cords;
			data->n.c_i = data->y_cords - (((h - y) * data->y_mult) / h);
			my_put_pixel(&data->img, x, y, bs_fractol_formula(data));
		}
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}

void	burning_ship_go(t_mlx_data *data, double x)
{
	if (x == 1)
		data->x_cords += data->x_mult / 10;
	if (x == 0)
		data->x_cords -= data->x_mult / 10;
	if (x == 3)
		data->y_cords += data->y_mult / 10;
	if (x == 2)
		data->y_cords -= data->y_mult / 10;
	return (burning_ship(data));
}
