#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <assert.h>

#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include "Math.hpp"

SDL_Texture* RenderWindow::playerTexture;
SDL_Texture* RenderWindow::projectileTexture;

RenderWindow::RenderWindow(const char* title, const Vector2& windowDimensions)
    :m_window(nullptr), m_renderer(nullptr), m_windowDimensions(windowDimensions)
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowDimensions.x, windowDimensions.y, SDL_WINDOW_SHOWN);
    if (!m_window){
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << std::endl;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath){
    SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, filePath);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::Clear(){
    SDL_SetRenderDrawColor(m_renderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void RenderWindow::Display(){
    SDL_RenderPresent(m_renderer);
}