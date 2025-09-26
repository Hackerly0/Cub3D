#include <cub3d.h>

int is_ws(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}
int	isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	perr(const char *msg)
{
	if (msg)
		printf("Error\n%s\n", msg);
	else
		printf("Error\n");
	return (1);
}
