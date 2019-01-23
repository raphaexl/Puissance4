/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:22:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/23 22:55:01 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect4.h"

int		main(void)
{
	t_grille	g;
	t_ptr		ptr;
	t_input		in;

	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	ft_grille_init(&g);
	if (ft_sdl_init(&ptr, SCR_WIDTH, SCR_HEIGHT, "1337"))
		goto Quit;
	ft_play(&ptr, &in, &g);
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_game_display(&ptr, &g);
	}
Quit:
	ft_sdl_quit(&ptr);
	return (0);
}
