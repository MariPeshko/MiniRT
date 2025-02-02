#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		arg_error(argc);
	open_config(argv[1]);
    return (0);
}
