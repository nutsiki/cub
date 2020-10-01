#include "minilibx/mlx.h"

int	main()
{
	void	*mlx_ptr;
	void 	*win_ptr;
	void 	*img_ptr;
	int		size_x;
	int 	size_y;
	char 	*title;
	int 	width;
	int 	height;
	int i;
	int j;
	int id;

	size_x = 500;
	size_y = 500;
	width = 300;
	height = 300;
	title = "Test";
	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title)))
		return (-1);
	if (!(img_ptr = mlx_new_image(mlx_ptr, width, height)))
		return (-1);
	int *kk = (int *)mlx_get_data_addr(img_ptr, &id, &id, &id);
	j = height;
	while (j--)
	{
		i = -1;
		while (++i<width)
		{
			*kk++ = 0xBFAA8F;
		}
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
