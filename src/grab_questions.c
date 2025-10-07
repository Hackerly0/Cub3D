/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_questions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:33:38 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/06 15:00:46 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
# include "../libft/libft.h"
#include "../GNL/get_next_line.h"
// #include "../include/cub3d.h"
static int	is_blank_line(const char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

static void	rtrim(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'
			|| s[n - 1] == ' ' || s[n - 1] == '\t'))
	{
		n--;
		s[n] = '\0';
	}
}

static void	trim_fields(char **qa)
{
	int		i;
	size_t	n;

	if (!qa)
		return ;
	i = 0;
	while (qa[i])
	{
		n = ft_strlen(qa[i]);
		while (n > 0 && (qa[i][n - 1] == '\n' || qa[i][n - 1] == '\r'
				|| qa[i][n - 1] == ' ' || qa[i][n - 1] == '\t'))
		{
			n--;
			qa[i][n] = '\0';
		}
		i++;
	}
}

static int	count_nonblank(const char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_blank_line(line))
			count++;
		free(line);
	}
	close(fd);
	return (count);
}

static char	*get_kth_nonblank(const char *path, int k)
{
	int		fd;
	int		idx;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	idx = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_blank_line(line))
		{
			if (idx == k)
				break ;
			idx++;
		}
		free(line);
	}
	close(fd);
	return (line);
}

static void	seed_once(void)
{
	static int	seeded;

	if (!seeded)
	{
		srand((unsigned int)time(NULL));
		seeded = 1;
	}
}

char	**grab_questions(void)
{
	const char	*path = "questions";
	int			total;
	int			target;
	char		*line;
	char		**qa;

	total = count_nonblank(path);
	if (total <= 0)
		return (NULL);
	seed_once();
	target = rand() % total;
	line = get_kth_nonblank(path, target);
	if (!line)
		return (NULL);
	rtrim(line);
	qa = ft_split(line, ',');
	free(line);
	if (!qa)
		return (NULL);
	trim_fields(qa);
	return (qa);
}

void print_qa(char **qa)
{
	int	i;

	if (!qa)
		return ;
	i = 0;
	while (qa[i])
	{
		write(1, qa[i], ft_strlen(qa[i]));
		write(1, "\n", 1);
		i++;
	}
}
