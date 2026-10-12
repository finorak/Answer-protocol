#include "main_utils.h"

t_signal val_exec(int client_fd, char *buf, t_world *world)
{
	t_signal	sign;
	t_command	test;

	test = validation_1(buf);
	if (test.is_valid == 0)
	{
		strcpy(sign.message, test.message);
		return (sign);
	}
	else
	{
		test = validation_2(test);
		if (test.is_valid == 0)
		{
			strcpy(sign.message, test.message);
			return (sign);
		}
		else
			return (execution(test, client_fd, world));
	}
}
