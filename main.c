#include "mlx.h"
#include "mlx_int.h"

int main(void)
{
	void *mlx;
	void *mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "My custom window");
	mlx_pixel_put(mlx, mlx_window, 250, 250, 0x00ffffff);
	mlx_key_hook(mlx_window, &mlx_clear_window, 27);
	mlx_loop(mlx);
	//mlx_key_hook(mlx_window, &mlx_close_window, 27);
	return (0);
}
