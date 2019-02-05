/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 21:36:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/05 19:10:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

void	ft_nb_align_series(t_grille *g, int *x, int *y, int n)
{
	int		i;
	int		j;
	t_point	p;
	bool	finished;

	finished = true;
	i = -1;
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				p.x = j;
				p.y = i;
				n = ft_grille_count(g, p, 1, 1);
				n = ft_max(n, ft_grille_count(g, p, 1, -1));
				n = ft_max(n, ft_grille_count(g, p, 1, 0));
				n = ft_max(n, ft_grille_count(g, p, 0, 1));
				if (g->tab[i][j] == YELLOW)
					*x = n;
				else
					*y = n;
			}
		}
	}
}

int		ft_evaluate(t_grille *g)
{
	int		i;
	int		j;
	t_point	p;
	bool	finished;

	finished = false;
	i = -1;
	while (++i < L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				p.x = j;
				p.y = i;
				if (ft_grille_count(g, p, 1, 1) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 1, -1) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 1, 0) >= 4)
					finished = true;
				if (ft_grille_count(g, p, 0, 1) >= 4)
					finished = true;
			}
			if (finished)
				return ((g->tab[i][j] == YELLOW) ? (10) : (-10));
		}
	}
	puts("Here");
	return (0);
}


int		ft_minmax(int depth, t_grille *g, bool max)
{
	int		score;
	int		best;
	int		i;
	int		j;

	score = ft_evaluate(g);
	if (score == -10)
	{
		return (-10);
	}
	if (score == 10)
		return (10);
	if (max)
	{
		best = MIN;
		i = L;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = YELLOW;
					best = ft_max(best, ft_minmax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
	else
	{
		best = MAX;
		i = L;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = RED;
					best = ft_min(best, ft_minmax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
}

t_point		ft_best_move(t_grille *g)
{
	int		i;
	int		j;
	int		best;
	int		eval;
	t_point	move = {-1, -1};

	best = MIN;
	i = L;
	while (--i >= 0)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] == EMPTY)
			{
				g->tab[i][j] = YELLOW;
				eval = ft_minmax(0, g, 0);
				g->tab[i][j] = EMPTY;
				if (eval > best)
				{
					move.x = j;
					move.y = i;
					best = eval;
				}

			}
		}
	}
	return (move);
}

