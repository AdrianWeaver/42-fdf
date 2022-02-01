#include "mlx.h"
#include "mlx_int.h"

int main(void)
{
	void *mlx;
	void *mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 500, 500, "My custom window");
	mlx_loop(mlx);
	return (0);
}
