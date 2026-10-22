*This project has been created as part of the 42 curriculum by finorako*

# Description
The printf function is one of the most used function in c, so here we implemented our own to do the tasks that we need for our need so that it can be expandable but still
act as the original print there are currently only those flags (cspduxX%) that are handled.

|%c|%s|%p|%d|%u|%x or %X|%%|
| :----:| :---:| :---: | :---: | :---: | :---: |:---:|
|print a character| print a string | print the address| print an integers | print an unsigned integers| print the hexadecimal value| print % |

# Instructions
To use this *ft_printf* you just have to follow the steps bellow:
	- you need all of this project's files.
	- run `make` on your terminal (we assume your current directory is the directory that contain all the ft_printf files)
	- include the *ft_printf.h* header into your project
	- here we have a concrete example, create a simple file named *main.c* and put the following code in it:
	```
	#include "ft_printf.h"

	int	main(void)
	{
		ft_printf("%s\n", "Hello, world");
		return (0);
	}
	```
	- compile with the following flag : `cc -Wall -Wextra -Werror main.c -L. -lftprintf` and run the executable to see the result.

# Ressources
- [Ctutor](https://pythontutor.com/c.html#) To view the 
- [Chatgpt](https://chatgpt.com/) as explained in the **AIusage** section.
- [francinette](https://github.com/Prashant-Bharaj/francinette) To test my project

## Ai usage
During the implementation of this project, i relied on Chatgpt to help me solve one of my biggest mess on this project, which is the print memory function.

# Explanation of the algorithm
The algorithm used in this project is pretty much straitforward, we just traverse the string (*str*) till we find a '%' character,
after finding that character, we just have to verify if it's in the available flags we implemented, if it is in it, we print it in the standard output
(to get the aproppriate argument we use the function va_arg, it will give us the correct argument)
otherwise we do nothing (because that's how the original printf work unless we double escape it).

## Justification
The Justification is probably because this way, i can easely expand my printf function as much as I need it.
