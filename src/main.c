/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:40:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/07 17:14:37 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "fcntl.h"

int	dbg; // remove

char	**g_map = NULL;
int		g_h;
int		g_w;
char	g_symbol;
char	g_symbol_op;
t_piece	*g_p;
int		g_min_dist;
int		g_x;
int		g_y;

# define DL(X, Y) (X > Y) ? X - Y : Y - X
# define MIN(X, Y) (X < Y) ? X : Y

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
//ft_dprintf(dbg, "Check at (%d, %d)\n", y, x);

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
//ft_dprintf(dbg, "Placing at (%d, %d)\n", i, j);
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


void	debug() {
	ft_dprintf(dbg, " ------------------- NEW TURN -----------------\n");
	ft_dprintf(dbg, "My symbol:       %c\n", g_symbol); //
	ft_dprintf(dbg, "Opponent symbol: %c\n", g_symbol_op); //
	// print map
	ft_dprintf(dbg, "Map size: %dx%d\n", g_h, g_w); //
	for (int i=0; i<g_h; i++)
		ft_dprintf(dbg, "%s\n", g_map[i]);
	// print piece
	ft_dprintf(dbg, "Piece size: %dx%d\n", g_p->h, g_p->w); //
	for (int i=0; i<g_p->h; i++)
		ft_dprintf(dbg, "%s\n", g_p->map[i]);
	ft_dprintf(dbg, "x: %d-%d, y: %d-%d\n",
			g_p->min_x, g_p->max_x, g_p->min_y, g_p->max_y);
	int	x;
	int	y;

	ft_dprintf(dbg, "-- Normmalized piece --\n");
	y = g_p->min_y;
	while (y <= g_p->max_y)
	{
		x = g_p->min_x;
		while (x <= g_p->max_x)
		{
			ft_dprintf(dbg, "[%d][%d]=", y, x);
			ft_dprintf(dbg, "%c\n", g_p->map[y][x++]);
		}
		ft_dprintf(dbg, "\n");
		y++;
	}
}

int main(void)
{
dbg = open("/Users/mpetruno/Projects/filler/debug",	O_WRONLY|O_CREAT|O_TRUNC);
	char	*inp;

	g_map = NULL;
	g_p = NULL;
	if (get_next_line(0, &inp) > 0)
		g_symbol = inp[10] == '1' ? 'o' : 'x';
	g_symbol_op = g_symbol == 'o' ? 'x' : 'o';
	free((void *)inp);
ft_dprintf(dbg, "\n=============| Symbol = %c |=============\n", g_symbol);
	while (read_next())
	{
if (0)
debug(); //////////////////////////////////////////////////////////////////
		place_piece();
		free_map();
		free_piece();
//ft_dprintf(dbg, "================================================\n");
	}
// Pring leaks to debug file
char *dbg_str = ft_itoa(dbg);
ft_dprintf(dbg, "DEBUG FD: %s\n", dbg_str);
char *str = ft_strjoin("leaks mpetruno.filler 1>&", dbg_str);
ft_dprintf(dbg, "%s\n", str);
system(str);
close(dbg);
// ---------------------------
	return (0);
}
