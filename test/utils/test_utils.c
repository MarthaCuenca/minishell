#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>

void	eval_result (int result, char verbose, char *name_func)
{
	if (result > 0)
	{
		if (verbose >= '2')
			printf("\t✅ Test %s\n", name_func);
	}
	else
	{
		if (verbose >= '2')
			printf("\t❌ Test %s\n", name_func);
		exit(1);
	}
}
