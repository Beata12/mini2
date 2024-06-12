
#include "../../../incl/minishell.h"

void	memory_allocation_error(void)
{
	exit(printf(RED "Allocation failed\n" RE));
}