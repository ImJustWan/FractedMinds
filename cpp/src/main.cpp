/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibier <tgibier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:02:15 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/03 11:03:05 by tgibier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.hpp"
#include <iostream>
#include <complex>
#include <SDL.h>

int	main() {
	int width = 800, height = 800;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow(
		"fractol",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_HIDDEN
	);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	int	max_iter = 100;
	float min_re = -2.0;
	float max_re = 2.0;
	float min_im = -2.0;
	float max_im = 2.0;

	std::complex c(-0.8f, 0.2f);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::complex z( min_re + j * (max_re - min_re) / width, min_im + i * (max_im - min_im) / height);
			
			for (int step = 0; step < max_iter; step++)
			{
				if (z.real() * z.real() + z.imag() * z.imag() > 4)
				{
					float coef = 255.0f * (max_iter - step) / max_iter;
					SDL_SetRenderDrawColor(renderer, coef, coef, coef, 255);
					SDL_RenderDrawPoint(renderer, j, i);
					break;
				}
				z = z * z + c;
			}
			SDL_RenderDrawPoint(renderer, j, i);
		}
	}
	SDL_ShowWindow(window);
	SDL_RenderPresent(renderer);
	
	while (1)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			case SDL_QUIT:
					goto end;
				break;
			
			default:
				break;
			}
		}
	}
	end:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
