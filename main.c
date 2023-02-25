#include <mlx.h>
#include <ft_param.h>


#include <my_kd_tree.h>


void    ft_line_make(t_kd_tree *test, t_param *param, int deep)
{
    t_vec2 a;
    t_vec2 b;
    
    
    if (deep % 3 == 0)
    {
        a.x = test->position[0];
        a.y = test->min[1];
        b.x = test->position[0];
        b.y = test->max[1];
        ft_scanline(a, b, param, 0x0000ff00);
    }
    else if (deep % 3 == 1)
    {
        a.x = test->min[0];
        a.y = test->position[1];
        b.x = test->max[0];
        b.y = test->position[1];
        ft_scanline(a, b, param, 0x00ff0000);

    }
    else if (deep % 3 == 2)
    {
        a.x = test->position[0] - 10;
        a.y = test->position[1];
        b.x = test->position[0] + 10;
        b.y = test->position[1];
        ft_scanline(a, b, param, 0x00ffffff);
        a.x = test->position[0];
        a.y = test->position[1] - 10;
        b.x = test->position[0];
        b.y = test->position[1] + 10;
        ft_scanline(a, b, param, 0x00ffffff);

    }
}

void ft_circle_make(double test[3], t_param *param, int deep)
{
    t_vec2 a;
    t_vec2 b;
    int x, y;
    int color;


    x = y = -5;

    if (deep % 3 == 0)
    {
        while (x < 5)
        {
            y = -5;
            while (y < 5)
            {
                ft_backbuffer_put_pixel(test[0] + x, test[1] + y, 0x00ff3333, param); 
                y++;
            }
            x++;
        }
    }
    else if (deep % 3 == 1)
    {
        while (x < 5)
        {
            y = -5;
            while (y < 5)
            {
                // color = ((255 / deep) << 24) + ((255 / deep) << 16) + ((255 / deep) << 8);
                ft_backbuffer_put_pixel(test[0] + x, test[1] + y, 0x0033ff33, param); 
                y++;
            }
            x++;
        }
    }
    else if (deep % 3 == 2)
    {
        while (x < 5)
        {
            y = -5;
            while (y < 5)
            {
                ft_backbuffer_put_pixel(test[0] + x, test[1] + y, 0x003333ff, param); 
                y++;
            }
            x++;
        }
    }
}

#include <unistd.h>

#include <stdio.h>

void	ft_testss(t_kd_tree *head, t_param *param)
{
	t_queue *queue;
	int			i;
	int			deep;

	queue = ft_new_queue(head);
	i = 0;
	deep = 0;
	while (queue)
	{
		if (deep != queue->data->deep)
		{
			deep++;
		}
        i++;
        ft_circle_make(queue->data->position, param, deep);
        ft_line_make(queue->data, param, deep);
		if (queue->data->left)
        {
			ft_queue_add(queue, ft_new_queue(queue->data->left));
        }
		if (queue->data->right)
        {
			ft_queue_add(queue, ft_new_queue(queue->data->right));
        }
		ft_queue_free(&queue);
	}
}
#include <stdlib.h>
 #include <strings.h>
int    ft_loop(t_param *param)
{

    return (0);
}


int main(int argc, char const *argv[])
{
    /* code */
    t_param param;

    param.mlx_ptr = mlx_init();
    param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "test");
    param.img_ptr = mlx_new_image(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    param.buffer = mlx_get_data_addr(param.img_ptr, &param.bits_per_pixel, &param.size_line, &param.endian);

    t_kd_tree *test = ft_test();

    t_vec2 a;
    t_vec2 b;

    a.x = 0;
    a.y = 0;
    b.x = WIN_WIDTH;
    b.y = WIN_HEIGHT;
    
    ft_scanline(a,b, &param, 0x00ffffff);
    a.x = WIN_WIDTH;
    a.y = 0;
    b.x = 0;
    b.y = WIN_HEIGHT;
    ft_scanline(a,b, &param, 0x00ffffff);
    param.data = test;

    ft_testss(param.data, &param);

    mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, param.img_ptr, CANVAS_X, CANVAS_Y);
	// mlx_loop_hook(param.mlx_ptr, ft_loop, &param);
    mlx_loop(param.mlx_ptr);


    return 0;
}
