/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:30:57 by kyoulee           #+#    #+#             */
/*   Updated: 2023/02/24 15:05:31 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <ft_vector.h>
#include "ft_param.h"

int	ft_sign(float num)
{
	if (num < 0)
		return (-1);
	return (1);
}


void	ft_backbuffer_put_pixel(int x, int y, int color, t_param *param)
{
	*(int *)(param->buffer + (x * 4) + (y * param->size_line)) = color;
}


void	ft_scanline_x(t_vec2 standard, t_vec2 next, t_param *param, int color)
{
	float	norm_titl;
	float	error;
	float	sign;
	t_vec2	current;
	int		mix_color;

	norm_titl = fabs((next.y - standard.y) / (next.x - standard.x));
	error = 0;
	sign = ft_sign(next.y - standard.y);
	current = standard;
	while (current.x <= next.x)
	{
		if (0 <= current.x && current.x < CANVAS_X + CANVAS_WIDTH && \
			0 <= current.y && current.y < CANVAS_Y + CANVAS_HEIGHT)
			ft_backbuffer_put_pixel(current.x, current.y, color, param);
		error += norm_titl;
		if (error >= 0.5 && error--)
			current.y += sign;
		current.x++;
	}
}

void	ft_scanline_y(t_vec2 standard, t_vec2 next, t_param *param, int color)
{
	float	norm_titl;
	float	error;
	float	sign;
	t_vec3	current;
	int		mix_color;

	norm_titl = fabs((next.x - standard.x) / (next.y - standard.y));
	error = 0;
	sign = ft_sign(next.x - standard.x);
	current.x = standard.x;
	current.y = standard.y;
	current.z = 0;
	while (current.y <= next.y)
	{
		if (0 <= current.x && current.x < CANVAS_X + CANVAS_WIDTH && \
			0 <= current.y && current.y < CANVAS_Y + CANVAS_HEIGHT)
			ft_backbuffer_put_pixel(current.x, current.y, color, param);
		error += norm_titl;
		if (error >= 0.5 && error--)
			current.x += sign;
		current.y++;
	}
}

void	ft_scanline(t_vec2 standard, t_vec2 next, t_param *param, int color)
{
	if (fabs(next.y - standard.y) < fabs(next.x - standard.x))
	{
		if (standard.x < next.x)
			ft_scanline_x(standard, next, param, color);
		else
			ft_scanline_x(next, standard, param, color);
	}
	else
	{
		if (standard.y < next.y)
			ft_scanline_y(standard, next, param, color);
		else
			ft_scanline_y(next, standard, param, color);
	}
}
