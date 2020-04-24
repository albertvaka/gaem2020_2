#pragma once

#include <SDL.h>

struct Text
{

	TTF_Font* font;
	TTF_Font* font_outline;
	std::string str;
	SDL_Color color = { 255,255,255 };
	SDL_Color outline_color = { 255,255,255 };

	SDL_Texture* cached = nullptr;

	Text(TTF_Font* font, TTF_Font* font_outline = nullptr) : font(font), font_outline(font_outline) {}
	~Text() {
		if (cached) { 
			SDL_DestroyTexture(cached); 
		}
	}
	operator SDL_Texture*() {
		if (cached == nullptr) {
			SDL_Surface* surface = Render();
			cached = SDL_CreateTextureFromSurface(Window::renderer, surface);
			SDL_FreeSurface(surface);
			if (!cached) {
				printf("Unable to create text texture. SDL Error: %s\n", SDL_GetError());
			}
		}
		return cached;
	};

	Text& setString(const std::string& text) {
		Invalidate();
		str = text;
		return *this;
	}

	Text& setFillColor(int r, int g, int b) {
		Invalidate();
		color.r = r;
		color.g = g;
		color.b = b;
		return *this;
	}

	Text& setOutlineColor(int r, int g, int b) {
		Invalidate();
		outline_color.r = r;
		outline_color.g = g;
		outline_color.b = b;
		return *this;
	}

	vec getSize() {
		int w, h;
		SDL_QueryTexture(*this, NULL, NULL, &w, &h);
		return vec(w, h);
	}
private:
	
	void Invalidate() {
		if (cached) {
			SDL_DestroyTexture(cached);
			cached = nullptr;
		}
	}

	SDL_Surface* Render() {
		SDL_Surface* fg_surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);
		if (!fg_surface) {
			printf("Unable to create text surface. SDL Error: %s\n", TTF_GetError());
		}
		if (!font_outline) {
			return fg_surface;
		}

		SDL_Surface* bg_surface = TTF_RenderText_Blended(font_outline, str.c_str(), outline_color);
		if (!bg_surface) {
			printf("Unable to create text surface. SDL Error: %s\n", TTF_GetError());
		}

		int outline = TTF_GetFontOutline(font_outline);
		SDL_Rect rect = { outline, outline, fg_surface->w, fg_surface->h };

		// blit text onto its outline
		SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
		SDL_FreeSurface(fg_surface);
		
		return bg_surface;
	}
};

