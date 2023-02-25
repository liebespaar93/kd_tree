
#ifndef FT_PARAM_H
# define FT_PARAM_H

# define WIN_WIDTH   1500
# define WIN_HEIGHT  1500

# define CANVAS_X		0
# define CANVAS_Y		0
# define CANVAS_WIDTH	WIN_WIDTH
# define CANVAS_HEIGHT	WIN_HEIGHT

typedef struct s_param	t_param;

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*buffer;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*data;
} t_param;

#include "ft_vector.h"

void	ft_scanline(t_vec2 standard, t_vec2 next, t_param *param, int color);

void	ft_backbuffer_put_pixel(int x, int y, int color, t_param *param);
#endif
