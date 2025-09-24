#include "../include/cub3d.h"

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

int	isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	else
		return (0);
}

// int	parse_num(const char *s, int *i)
// {
// 	int	val;
// 	int	saw;

// 	val = 0;
// 	saw = 0;
// 	while (s[*i] && isnum(s[*i]))
// 	{
// 		saw = 1;
// 		val = val * 10 + (s[*i] - '0');
// 		(*i)++;
// 		if (val > 255)
// 			return (-1);
// 	}
// 	if (!saw)
// 		return (-1);
// 	return (val);
// }

int	parse_rgb(const char *s, t_rgb *out)
{
	int	i;
	int	v;

	if (!s || !out)
		return (-1);
	i = 0;
	while (s[i] && is_ws(s[i]))
		i++;
	if (!isalpha(s[i]))
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;
	if (!s[i])
		return (-1);

	/* R */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->r = v;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] != ',')
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;

	/* G */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->g = v;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] != ',')
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;

	/* B */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->b = v;
	while (s[i] && is_ws(s[i]))
		i++;
    if (s[i])
        return (-1);
    return (0);
}

// int main()
// {
//     t_rgb out;
//     char *s[] = {
//     "F 255,255,255",
//     "F 256,10,10",
//     "F 10,,10",
//     "F 10,10",
//     "F 10,10,10,10",
//     "F 001, 002, 003"
//     };

//     int j = 0;
//     while (j < 6)
//     {
//         int i = 0;
//         printf("Test#%i\n", j);
//         i = parse_rgb(s[j], &out);
//         if (i == -1)
//             printf("Functions Returns!\n");
//         else
//             printf("r = %i\ng = %i\nb = %i\n", out.r, out.g, out.b);
//         printf("-----------------------\n");
//         j++;
//     }
//     return 0;
// }