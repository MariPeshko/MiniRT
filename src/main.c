#include "../inc/miniRT.h"

void cleanup_mlx(void *mlx, void *win, t_config *cf)
{
    if (win)
        mlx_destroy_window(mlx, win);  // Free the window
    if (mlx)
        mlx_destroy_display(mlx);  // Destroy the mlx display
    clean_exit(cf, SUCCESS);  // Perform any other cleanup and exit
}

int handle_close(t_config *cf)
{
    cleanup_mlx(cf->mlx, cf->win, cf);  // Free resources and exit
    return (0);  // Required return for mlx_hook callbacks
}

int main(int argc, char **argv)
{
    t_mini_rt rt;

    if (argc != 2)
        arg_error(argc);

    open_config(argv[1], &rt.cf);  // Load the configuration

    // Initialize mlx and window
    void *mlx = mlx_init();
    if (!mlx)
        clean_exit(&rt.cf, MEMORY);  // Handle error and exit if mlx_init fails

    void *win = mlx_new_window(mlx, 800, 600, "42 MinilibX Window");
    if (!win)
        cleanup_mlx(mlx, NULL, &rt.cf);  // Free resources if window creation fails

    rt.cf.mlx = mlx;  // Save mlx reference in config
    rt.cf.win = win;  // Save window reference in config

    // Correctly pass rt.cf into the hook, do NOT call handle_close directly
    mlx_hook(win, 17, 0, (int (*)(void *))handle_close, &rt.cf);

    // Start the event loop
    mlx_loop(mlx);

    // Cleanup resources before exit
    cleanup_mlx(mlx, win, &rt.cf);

    return (SUCCESS);
}
