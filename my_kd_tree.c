/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_kd_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:30:05 by kyoulee           #+#    #+#             */
/*   Updated: 2023/02/25 13:00:52 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>


#include "my_kd_tree.h"

t_queue *ft_new_queue(t_kd_tree *data)
{
	t_queue *new;

	new = malloc(sizeof(t_queue));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

t_queue *ft_queue_add(t_queue *head, t_queue *new)
{
	t_queue	*temp;

	if (!head)
		return (new);
	temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	return (head);
}

void	ft_queue_free(t_queue **ptr)
{
	t_queue	*temp;

	if (ptr)
	{
		if (*ptr)
		{
			temp = *ptr;
			*ptr = (*ptr)->next;
			free(temp);
		}
	}
}

#include <ft_param.h>

t_kd_tree   *ft_kd_tree_new(double vec[3], void *data)
{
	t_kd_tree	*new;

	new = malloc(sizeof(t_kd_tree));
	if (!new)
		return (NULL);
	new->data = data;
	new->position[0] = vec[0];
	new->position[1] = vec[1];
	new->position[2] = vec[2];
	new->left = NULL;
	new->right = NULL;
	new->min[0] = 0;
	new->min[1] = 0;
	new->min[2] = 0;
	new->max[0] = WIN_WIDTH;
	new->max[1] = WIN_HEIGHT;
	new->max[2] = WIN_WIDTH;
	return (new);
}

void	ft_kd_tree_free(t_kd_tree *kd_tree)
{
	if (kd_tree)
	{
		if (kd_tree->left)
			ft_kd_tree_free(kd_tree->left);
		if (kd_tree->right)
			ft_kd_tree_free(kd_tree->right);
		/// kd_tree->data 특별히 필요한경우?
		free(kd_tree);
	}
}

t_kd_tree *ft_kd_tree_middle_kd_tree(t_queue *q, double value, int deep)
{
	t_kd_tree	*middle;
	double		dist;

	dist = 10e12;

	while (q)
	{
		if (dist > fabs(value - q->data->position[deep % 3]))
			middle = q->data;
		q = q->next;
	}
	return (middle);
}

t_queue	*ft_queue_pop_middle(t_queue *q, t_kd_tree *middle, int deep, t_queue **q_left_ptr, t_queue **q_right_ptr)
{
	t_queue	*q_temp;
	t_queue	*q_left;
	t_queue	*q_right;
	
	q_left = NULL;
	q_right = NULL;
	while (q)
	{
		if (q->data == middle)
		{
			ft_queue_free(&q);
		}
		else if (q->data->position[deep % 3] < middle->position[deep % 3])
		{
			q_left = ft_queue_add(q_left, q);
			q_temp = q;
			q = q->next;
			q_temp->next = NULL;
		}
		else
		{
			q_right = ft_queue_add(q_right, q);
			q_temp = q;
			q = q->next;
			q_temp->next = NULL;
		}
	}
	*q_left_ptr = q_left;
	*q_right_ptr = q_right;
	return (q);
}

t_queue	*ft_queue_sort(t_queue *q, int deep, int index)
{
	t_queue *q_head;
	t_queue *q_temp;
	t_queue *q_temp_prev;
	
	q_head = NULL;
	while (q)
	{
		q_temp = q_head;
		q_temp_prev = NULL;
		if (!q_temp)
		{
			q_temp = q;
			q = q->next;
			q_temp->next = q_head;
			q_head = q_temp;
		}
		else
		{
			while (q_temp && q_temp->data->position[deep % 3] < q->data->position[deep % 3])
			{
				q_temp_prev = q_temp;
				q_temp = q_temp->next;
			}
			if (!q_temp_prev)
			{
				q_temp = q;
				q = q->next;
				q_temp->next = q_head;
				q_head = q_temp;
			}
			else
			{
				q_temp_prev->next = q;
				q = q->next;
				q_temp_prev->next->next = q_temp;
			}
		}
	}
	return (q_head);
}

int	ft_queue_len(t_queue *q)
{
	int index;

	index = 0;
	while (q)
	{
		q = q->next;
		index++;
	}
	return (index);
}

#include <stdio.h>
t_kd_tree	*ft_kd_tree_middle(t_queue *q_ptr, int deep, t_queue **q_left, t_queue **q_right)
{
	int			index;
	int			i;
	t_kd_tree	*middle;
	t_queue		*q_sort;

	if (!q_ptr)
		return (NULL);
	index = ft_queue_len(q_ptr);
	q_sort = ft_queue_sort(q_ptr, deep, index);
	i = 0;
	if (index == 1)
	{
		middle = q_sort->data;
		free(q_sort);
		return (middle);
	}
	*q_left = q_sort;
	while (q_sort)
	{
		i++;
		if (index / 2 == i)
		{
			middle = q_sort->next->data;
			*q_right = q_sort->next->next;
			free(q_sort->next);
			q_sort->next = NULL;
			break;
		}
		q_sort = q_sort->next;
	}
	return (middle);
}

void	ft_kd_tree_max_set(t_queue * q_left, t_kd_tree *middle, int deep)
{
	while (q_left)
	{
		q_left->data->max[deep % 3] = middle->position[deep % 3];
		q_left = q_left->next;
	}
}

void	ft_kd_tree_min_set(t_queue * q_right, t_kd_tree *middle, int deep)
{
	while (q_right)
	{
		q_right->data->min[deep % 3] = middle->position[deep % 3];
		q_right = q_right->next;
	}
}
t_kd_tree	*ft_kd_tree_insert(t_queue *q, int deep)
{
	t_kd_tree	*middle;
	t_queue		*q_left;
	t_queue		*q_right;

	if (!q)
		return (NULL);
	q_left = NULL;
	q_right = NULL;
	middle = ft_kd_tree_middle(q, deep, &q_left, &q_right);
	middle->deep = deep;
	if (q_left)
	{
		ft_kd_tree_max_set(q_left, middle, deep);
		middle->left = ft_kd_tree_insert(q_left, deep + 1);
	}
	if (q_right)
	{
		ft_kd_tree_min_set(q_right, middle, deep);
		middle->right = ft_kd_tree_insert(q_right, deep + 1);
	}
	return (middle);
}

t_kd_tree	*ft_kd_tree_set(t_queue *q)
{
	t_kd_tree	*head;

	head = NULL;
	head = ft_kd_tree_insert(q, 0);
	
	return (head);
}

#include <stdio.h>

void	ft_print_kd_tree(t_kd_tree *head)
{
	t_queue *queue;
	int			i;
	int			deep;

	queue = ft_new_queue(head);
	i = 0;
	deep = 0;

	printf("\n\nprint all \n");
	while (queue)
	{
		if (deep != queue->data->deep)
		{
			printf("\n\ndeep[%d] \n", deep);
			deep++;
		}
		printf("(%.2f %.2f %.2f) \t", queue->data->position[0], queue->data->position[1], queue->data->position[2]);
		fflush(stdout);
		if (queue->data->left)
			ft_queue_add(queue, ft_new_queue(queue->data->left));
		if (queue->data->right)
			ft_queue_add(queue, ft_new_queue(queue->data->right));
		ft_queue_free(&queue);
	}
}


t_kd_tree *ft_test()
{
	t_kd_tree *head;
	t_kd_tree *new;
	t_queue		*q;
	
	int i;
	q = NULL;
	for(i=-20; i<20; i++) {
		float x, y, z;
		// x = ((float)rand() / RAND_MAX) * 500.0;
		// y = ((float)rand() / RAND_MAX) * 500.0;
		// z = ((float)rand() / RAND_MAX) * 500.0;
		x = i * 30 + (WIN_WIDTH / 2);
		y = i * 30 + (WIN_HEIGHT / 2);
		z = i * 30 + (WIN_WIDTH / 2);
		new = ft_kd_tree_new((double [3]){x, y, z}, NULL);
		q = ft_queue_add(q, ft_new_queue(new));
	}
	head = ft_kd_tree_set(q);	
	ft_print_kd_tree(head);
	return head;
}
