#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_mini_rt	rt;

	if (argc != 2)
		arg_error(argc);
	if (open_config(argv[1], &rt.cf) == FAILURE)
		cleanup(&rt.cf);
	// Keep running
	cleanup(&rt.cf);
	return (SUCCESS);
}
