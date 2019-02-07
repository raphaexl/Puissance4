/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:22:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/03 19:08:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

int		main(void)
{
	t_type		p;
	t_grille	g;

	p = RED;
	ft_grille_init(&g);
	ft_play(&g, p);
	ft_putendl("Au revoir \n");
	return (0);
}
