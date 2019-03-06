/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:40:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/06 23:08:20 by mpetruno         ###   ########.fr       */
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

int		count_intersect(int i, int j)
{
	int	count;
	int	x;
	int	y;

	y = g_p->min_y;
	count = 0;
	while (y <= g_p->max_y)
	{
		x = g_p->min_x;
		while (x <= g_p->max_x)
		{
			if (g_map[y][x] == '*' &&
				(g_map[i + y][j + x] == g_symbol_op ||
				 g_map[i + y][j + x] == g_symbol_op -('a' - 'A')))
				return (0);

ft_dprintf(dbg, "Check: p(%d, %d)=%c, ",
y, x, g_p->map[y][x]);
ft_dprintf(dbg, "map(%d, %d)=%c, ",
i + y, j + x, g_map[i+y][j+x]);

			count += (g_p->map[x][y] == '*' &&
				(g_map[i + y][j + x] == g_symbol ||
				 g_map[i + y][j + x] == g_symbol - ('a' - 'A')));

ft_dprintf(dbg, " count=%d\n", count);

			x++;
		}
		y++;
	}
	return (count);
}

void	place_piece(void)
{
	int	i;
	int	j;

	i = 0 - g_p->min_y;
	while (i < g_h - g_p->max_y)
	{
		j = 0 - g_p->min_x;
		while (j < g_w - g_p->max_x)
		{
ft_dprintf(dbg, "Placing at (%d, %d)\n", i, j);
			if (count_intersect(i, j) == 1)
			{
				ft_printf("%d %d\n", i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_printf("0 0\n");
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
}

int main(void)
{
dbg = open("/Users/mpetruno/Projects/filler/debug",	O_WRONLY|O_CREAT|O_APPEND);
	char	*inp;

	if (get_next_line(0, &inp) > 0)
		g_symbol = inp[10] == '1' ? 'o' : 'x';
	g_symbol_op = g_symbol == 'o' ? 'x' : 'o';
	if (!init_map())
		ft_dprintf(2, "allocation error\n");
	while (read_next())
	{
debug(); //////////////////////////////////////////////////////////////////
		place_piece();
		free_map();
		free_piece();
ft_dprintf(dbg, "================================================\n");
	}
	free((void *)g_map);
close(dbg);
	return (0);
}
