/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 21:36:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/03 20:21:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"


int		ft_heuristic(t_grille *g)
{
	t_point	p;
	int		result;
	int		i;
	int		j;

	result = 0;
	i = -1;
	while (++i < L)
	{
		j = -1;
		while (++j <= C - 4)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 1, 0);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 1, 0);
		}
	}
	i = -1;
	while (++i <= L - 4)
	{
		j = -1;
		while (++j < C)
		{
			p.x = j;
			p.y = i;
			if (g->tab[i][j] != YELLOW)
				result += ft_grille_count(g, p, 0, 1);
			if (g->tab[i][j] != RED)
				result -= ft_grille_count(g, p, 0, 1);
		}
	}
	return (result);
}


int		ft_evaluate(t_grille *g)
{
	int		i;
	int		j;
	t_point	p;
	bool	finished;

	finished = false;
	i = -1;
	while (++i <= L)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] != EMPTY)
			{
				p.x = j;
				p.y = i;
				if (i <= L - 4 && j <= C - 4 && ft_grille_count(g, p, 1, 1) >= 4)
					finished = true;
				if (i > 2 && j < C - 4 && ft_grille_count(g, p, -1, 1) >= 4)
					finished = true;
				if (i < L - 4 && ft_grille_count(g, p, 1, 0) >= 4)
					finished = true;
				if (j <= C - 4 && ft_grille_count(g, p, 0, 1) >= 4)
					finished = true;
			}
			if (finished)
				return ((g->tab[i][j] == YELLOW) ? (10) : (-10));
		}
	}
	return (0);
}


int		ft_minmax(int depth, t_grille *g, bool max)
{
	int		score;
	int		best;
	int		i;
	int		j;

	score = ft_evaluate(g);
	if (ft_grille_full(g))
		return (0);
	if (score == -10)
		return (-10);
	if (score == 10)
		return (10);
	if (depth == 3)
		return ((!max ? ft_heuristic(g) : -ft_heuristic(g)));
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

