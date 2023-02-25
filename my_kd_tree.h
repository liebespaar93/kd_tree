#ifndef MY_KD_TREE_H
# define MY_KD_TREE_H

typedef struct s_kd_tree t_kd_tree;

typedef struct s_kd_tree
{
    double		position[3];
    int			deep;
	void		*data;

	double		min[3];
	double		max[3];

	t_kd_tree	*left;
	t_kd_tree	*right;	
} t_kd_tree;

typedef	struct s_queue	t_queue;

typedef	struct s_queue
{
	t_kd_tree	*data;
	t_queue		*next;
}t_queue;
t_queue *ft_new_queue(t_kd_tree *data);
void	ft_queue_free(t_queue **ptr);
t_queue *ft_queue_add(t_queue *head, t_queue *new);

t_kd_tree *ft_test();
#endif

