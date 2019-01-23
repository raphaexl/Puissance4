/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:24:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/23 18:36:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/connect4.h"


int		ft_sdl_init(t_ptr *ptr, int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, " Initialisation : %s", SDL_GetError());
		return (-1);
	}
	if (!(ptr->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)))
	{
		fprintf(stderr, "Window Creation : %s", SDL_GetError());
		return (-1);
	}
		if (!(ptr->renderer = SDL_CreateRenderer(ptr->window, -1, SDL_RENDERER_PRESENTVSYNC\
			| SDL_RENDERER_ACCELERATED)))
	{
		fprintf(stderr, "Renderer Creation : %s", SDL_GetError());
		return (-1);
	}
	if (!(ptr->texture = ft_sdl_load_texture(ptr->renderer, "background.png")))
	{
		fprintf(stderr,"SDL_CreateTexture : %s", SDL_GetError());
		return (-1);
	}
	return (0);
}

SDL_Texture		*ft_sdl_load_texture(SDL_Renderer *renderer, const char *file_name)
{
	SDL_Surface	*surf;
	SDL_Texture	*img;

	surf = SDL_LoadBMP(file_name);
	img = NULL;
	if (surf)
	{
		img = SDL_CreateTextureFromSurface(renderer, surf);
		if (!img)
			perror(SDL_GetError());
	}
	return (img);
}

void	ft_sdl_quit(t_ptr *ptr)
{
	if (ptr->texture)
		SDL_DestroyTexture(ptr->texture), ptr->texture = NULL;
	if (ptr->window)
		SDL_DestroyWindow(ptr->window), ptr->window = NULL;
	if (ptr->renderer)
		SDL_DestroyRenderer(ptr->renderer), ptr->renderer = NULL;
	SDL_Quit();
}
