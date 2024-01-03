#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <assert.h>

#include "Window.hpp"
#include "GameObject.hpp"
#include "Math.hpp"

/* WINDOW DIMENSIONS */
int Window::s_width = 1280;
int Window::s_height = 720;

/* TEXTURE RESOURCES INSTANCES */
TextureResource* Window::playerTexture;
TextureResource* Window::projectileTexture;

Window::Window(const char* title)
    :m_window(nullptr), m_renderer(nullptr)
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);
    if (!m_window){
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << std::endl;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    delete playerTexture;
    delete projectileTexture;
}

TextureResource* Window::LoadTexture(const char* name, const Vector2& dim, const char* filePath){
    SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, filePath);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return new TextureResource(name, dim, texture);
}

void Window::Clear(){
    SDL_SetRenderDrawColor(m_renderer, 0xF, 0xF, 0xF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void Window::Display(){
    SDL_RenderPresent(m_renderer);
}