#include "mlx/mlx.h"
#include <stdlib.h>

int key(int keycode, void *window, void *mlx)
{
	mlx_destroy_window(window, mlx);
	exit (0);
}

int main()
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "hello");
	mlx_hook(window, 17, 0, key, mlx);
	mlx_loop(mlx);
}
