/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:24:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/23 17:27:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/connect4.h"

void		ft_update_event(t_input *in)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		if (event.type == SDL_KEYDOWN)
			in->keys[event.key.keysym.scancode] = SDL_TRUE;
		if (event.type == SDL_KEYUP)
			in->keys[event.key.keysym.scancode] = SDL_FALSE;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[event.button.button] = SDL_TRUE;
		if (event.type == SDL_MOUSEBUTTONUP)
			in->mouse[event.button.button] = SDL_FALSE;
		if (event.type == SDL_MOUSEMOTION)
		{
			in->mousex = event.motion.x;
			in->mousey = event.motion.y;
			in->mousexrel = event.motion.xrel;
			in->mouseyrel = event.motion.yrel;
		}
		if (event.type == SDL_MOUSEWHEEL)
		{
			in->xwheel = event.wheel.x;
			in->ywheel = event.wheel.y;
		}
	}
}
