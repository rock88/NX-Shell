#include "common.h"
#include "SDL_helper.h"

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderClear(renderer);
}

void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SDL_SetRenderDrawColor(RENDERER, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(RENDERER, &rect);
}

void SDL_DrawCircle(SDL_Renderer *renderer, int x, int y, int r, SDL_Color colour)
{
	filledCircleRGBA(renderer, x, y, r, colour.r, colour.g, colour.b, colour.a);
	return;
}

void SDL_DrawText(TTF_Font *font, int x, int y, SDL_Color colour, const char *text)
{
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, colour, 1280);
	SDL_SetSurfaceAlphaMod(surface, colour.a);
	SDL_Rect position = {x, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, WINDOW_SURFACE, &position);
	SDL_FreeSurface(surface);
}

void SDL_DrawTextf(TTF_Font *font, int x, int y, SDL_Color colour, const char* text, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, 256, text, args);
	SDL_DrawText(font, x, y, colour, buffer);
	va_end(args);
}

void SDL_LoadImage(SDL_Renderer *renderer, SDL_Texture **texture, char *path)
{
	SDL_Surface *loaded_surface = NULL;
	loaded_surface = IMG_Load(path);

	if (loaded_surface)
	{
		Uint32 colorkey = SDL_MapRGB(loaded_surface->format, 0, 0, 0);
		SDL_SetColorKey(loaded_surface, SDL_TRUE, colorkey);
		*texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	}

	SDL_FreeSurface(loaded_surface);
}

void SDL_LoadImageBuf(SDL_Renderer *renderer, SDL_Texture **texture, void *mem, int size)
{
	SDL_Surface *loaded_surface = NULL;
	SDL_RWops *rw = SDL_RWFromMem(mem, size);
	loaded_surface = IMG_Load_RW(rw, 1);

	if (loaded_surface)
	{
		Uint32 colorkey = SDL_MapRGB(loaded_surface->format, 0, 0, 0);
		SDL_SetColorKey(loaded_surface, SDL_TRUE, colorkey);
		*texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	}

	SDL_FreeSurface(loaded_surface);
}

void SDL_DrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect position;
	position.x = x; position.y = y; position.w = w; position.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &position);
}