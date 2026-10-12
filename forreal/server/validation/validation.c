#include "../main_utils.h"

t_command	validation_1(char *buf)
{
	t_command	result;

	if (first_term(buf) == 0)
		one_word_parsing(buf, &result);
	else
	{
		first_word_parsing(buf, &result);
		restore_from_first_term(buf);
		not_first_term(buf);
		if (!strcmp(result.type, "ERROR"))
			return (result);
        strcpy(result.message, buf);
	}
	return (result);
}

t_command	validation_2(t_command test)
{
	t_command	result;

	if (!strcmp(test.message, "one column message"))
		return (test);
	else if (first_term(test.message) == 0)
		one_word_parsing_mess(test, &result);
	else
		first_word_parsing_mess(test, &result);
	return (result);
}
