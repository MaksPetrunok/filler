/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:40:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/07 18:02:33 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	**g_map = NULL;
int		g_h;
int		g_w;
char	g_symbol;
char	g_symbol_op;
t_piece	*g_p;
int		g_min_dist;
int		g_x;
int		g_y;

int		dist(int i, int j)
{
	int	x;
	int	y;
	int	md;

	md = 9999;
	y = -1;
	while (++y < g_h)
	{
		x = -1;
		while (++x < g_w)
		{
			if (g_map[y][x] == g_symbol_op ||
				g_map[y][x] == g_symbol_op - ('a' - 'A'))
			{
				md =
			MIN(md, ((DL((i + g_p->min_y), y)) + (DL((j + g_p->min_x), x))));
			}
		}
	}
	return (md);
}

int		put(int i, int j)
{
	int	count;
	int	x;
	int	y;

	y = g_p->min_y - 1;
	count = 0;
	while (++y <= g_p->max_y)
	{
		x = g_p->min_x - 1;
		while (++x <= g_p->max_x)
		{
			if (g_p->map[y][x] == '*' && (g_map[i + y][j + x] == g_symbol_op ||
				g_map[i + y][j + x] == g_symbol_op - ('a' - 'A')))
				return (0);
			if (g_p->map[y][x] == '*' && (g_map[i + y][j + x] == g_symbol ||
				g_map[i + y][j + x] == g_symbol - ('a' - 'A')))
				count++;
			if (count > 1)
				return (0);
		}
	}
	return (count);
}

void	place_piece(void)
{
	int	i;
	int	j;
	int	md;

	i = 0 - g_p->min_y;
	while (i < g_h - g_p->max_y)
	{
		j = 0 - g_p->min_x;
		while (j < g_w - g_p->max_x)
		{
			if (put(i, j) == 1 && (md = dist(i, j)) < g_min_dist)
			{
				g_min_dist = md;
				g_y = i;
				g_x = j;
			}
			j++;
		}
		i++;
	}
	ft_printf("%d %d\n", g_y, g_x);
}

int		read_next(void)
{
	if (!read_map() || !read_piece())
	{
		free_map();
		free_piece();
		return (0);
	}
	g_min_dist = 999999;
	g_x = 0;
	g_y = 0;
	return (1);
}

int		main(void)
{
	char	*inp;

	g_map = NULL;
	g_p = NULL;
	if (get_next_line(0, &inp) > 0)
		g_symbol = inp[10] == '1' ? 'o' : 'x';
	g_symbol_op = g_symbol == 'o' ? 'x' : 'o';
	free((void *)inp);
	while (read_next())
	{
		place_piece();
		free_map();
		free_piece();
	}
	return (0);
}
