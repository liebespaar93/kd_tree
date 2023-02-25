/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 00:18:18 by kyoulee           #+#    #+#             */
/*   Updated: 2022/09/03 20:34:09 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vector.h>
#include <ft_math.h>
#include <ft_mlx_color.h>

t_vec3	ft_vector_3(float x, float y, float z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.color = 0x00FFFFFF;
	return (new);
}

t_vec3	ft_vec3_sum(t_vec3 v3_1, t_vec3 v3_2)
{
	v3_1.x += v3_2.x;
	v3_1.y += v3_2.y;
	v3_1.z += v3_2.z;
	return (v3_1);
}

t_vec3	ft_vec3_mult(t_vec3 v3, float scalar)
{
	v3.x *= scalar;
	v3.y *= scalar;
	v3.z *= scalar;
	return (v3);
}

float	ft_vec3_length(t_vec3 v3)
{
	float	temp;

	temp = ft_sqrt(v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
	return (temp);
}

t_vec3	ft_vec3_normalize(t_vec3 v3)
{
	float	length;

	length = ft_vec3_length(v3);
	v3.x = v3.x / length;
	v3.y = v3.y / length;
	v3.z = v3.z / length;
	return (v3);
}
