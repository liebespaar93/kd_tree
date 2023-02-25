/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:41:15 by kyoulee           #+#    #+#             */
/*   Updated: 2022/09/03 20:34:11 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vector.h>
#include <ft_math.h>

t_vec2	ft_vector_2(float x, float y)
{
	t_vec2	new;

	new.x = x;
	new.y = y;
	new.color = 0x00FFFFFF;
	return (new);
}

t_vec2	ft_vec2_sum(t_vec2 v2_1, t_vec2 v2_2)
{
	v2_1.x += v2_2.x;
	v2_1.y += v2_2.y;
	return (v2_1);
}

t_vec2	ft_vec2_mult(t_vec2 v2, float scalar)
{
	v2.x *= scalar;
	v2.y *= scalar;
	return (v2);
}

float	ft_vec2_length(t_vec2 v2)
{
	float	temp;

	temp = ft_sqrt(v2.x * v2.x + v2.y * v2.y);
	return (temp);
}

t_vec2	ft_vec2_normalize(t_vec2 v2)
{
	float	length;

	length = ft_vec2_length(v2);
	v2.x = v2.x / length;
	v2.y = v2.y / length;
	return (v2);
}
