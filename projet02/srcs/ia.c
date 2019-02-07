/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:42:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/07 20:39:33 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

int		ft_evaluate(t_grille *g)
{
	int		i;
	int		j;
	bool	finished;
	t_point	p;

	i = L;
	finished = false;
	while (--i >= 0)
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
			{
				if (g->tab[i][j] == YELLOW)
					return (+10000);
				else
					return (-10000);
			}
		}
	}
	return (0);
}

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

int		ft_minimax(int depth, t_grille *g, int max)
{
	int		score;
	int		i;
	int		j;
	int		best;

	score = ft_evaluate(g);
	if (score == 1000)
		return (score);
	if (score == -1000)
		return (score);
	if (ft_grille_full(g))
		return (0);
	if (depth == 3)
		return ((!max ? ft_heuristic(g) : -ft_heuristic(g)));
	if (max)
	{
		i = L;
		best = -10000;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = YELLOW;
					best = ft_max(best, ft_minimax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
	else
	{
		best = 10000;
		i = L;
		while (--i >= 0)
		{
			j = -1;
			while (++j < C)
			{
				if (g->tab[i][j] == EMPTY)
				{
					g->tab[i][j] = RED;
					best = ft_min(best, ft_minimax(depth + 1, g, !max));
					g->tab[i][j] = EMPTY;
				}
			}
		}
		return (best);
	}
}

t_point		ft_best_move(t_grille *g)
{
	int		best;
	t_point	move;
	int		i;
	int		j;
	int		eval;

	best = -10000;
	move.x = -1;
	move.y = -1;
	i = L;
	while (--i >= 0)
	{
		j = -1;
		while (++j < C)
		{
			if (g->tab[i][j] == EMPTY)
			{
				g->tab[i][j] = YELLOW;
				eval = ft_minimax(0, g, 0);
				g->tab[i][j] = EMPTY;
				if (eval > best)
				{
					printf("\n EVAL %d ", eval);
					move.x = j;
					move.y = i;
					best = eval;
				}
			}
		}
	}
	return (move);
}
