#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_gpu.h"
#include <string>
#include <vector>
#include "vector.h"

class Text
{
	TTF_Font* font;
	TTF_Font* font_outline;
	std::string str;
	SDL_Color color = { 255,255,255 };
	SDL_Color outline_color = { 0,0,0 };
	int spacing = 0;
	int empty_line_spacing = 12;
	GPU_Image* cached = nullptr;

public:
	Text(TTF_Font* font = nullptr, TTF_Font* font_outline = nullptr) : font(font), font_outline(font_outline) {}
	~Text() {
		if (cached) { 
			GPU_FreeImage(cached); 
		}
	}

	operator GPU_Image* () {
		return getImage();
	}

	GPU_Image* getImage() {
		if (cached == nullptr) {
			SDL_Surface* surface = MultiLineRender();
			cached = GPU_CopyImageFromSurface(surface);
			GPU_SetImageFilter(cached, GPU_FILTER_NEAREST);
			SDL_FreeSurface(surface);
			if (!cached) {
				printf("Unable to create text texture. SDL Error: %s\n", SDL_GetError());
			}
		}
		return cached;
	};

	Text& setFont(TTF_Font* newfont, TTF_Font* newfont_outline = nullptr) {
		if (newfont != font || font_outline != newfont_outline) {
			font_outline = newfont_outline;
			font = newfont;
			Invalidate();
		}
		return *this;
	}

	Text& setSpacing(int pixels) {
		if (pixels != spacing) {
			spacing = pixels;
			Invalidate();
		}
		return *this;
	}

	Text& setEmptyLineSpacing(int pixels) {
		if (pixels != empty_line_spacing) {
			empty_line_spacing = pixels;
			Invalidate();
		}
		return *this;
	}

	Text& setString(const std::string& newstr) {
		if (newstr != str) {
			str = newstr;
			Invalidate();
		}
		return *this;
	}

	Text& setFillColor(uint8_t r, uint8_t g, uint8_t b) {
		if (r != color.r || g != color.g || b != color.b) {
			color.r = r;
			color.g = g;
			color.b = b;
			Invalidate();
		}
		return *this;
	}

	Text& setOutlineColor(uint8_t r, uint8_t g, uint8_t b) {
		if (r != outline_color.r || g != outline_color.g || b != outline_color.b) {
			outline_color.r = r;
			outline_color.g = g;
			outline_color.b = b;
			Invalidate();
		}
		return *this;
	}

	vec getSize() {
		GPU_Image* image = getImage();
		return vec(image->texture_w, image->texture_h);
	}
private:
	
	void Invalidate() {
		if (cached) {
			GPU_FreeImage(cached);
			cached = nullptr;
		}
	}

	SDL_Surface* Render() {
		SDL_Surface* fg_surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);
		if (!fg_surface) {
			printf("Unable to create text surface. SDL Error: %s\n", TTF_GetError());
			return nullptr;
		}
		if (!font_outline) {
			return fg_surface;
		}

		SDL_Surface* bg_surface = TTF_RenderUTF8_Blended(font_outline, str.c_str(), outline_color);
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

	SDL_Surface* MultiLineRender() {
		std::vector<SDL_Surface*> surfaces;
		int totalHeight = 0;
		int maxWidth = 0;
		std::stringstream ss(str);
		while (std::getline(ss, str, '\n')) {
			if (str.empty()) {
				surfaces.push_back(NULL);
				totalHeight += empty_line_spacing;
				continue;
			}
			SDL_Surface* s = Render();
			totalHeight += s->h + spacing;
			maxWidth = std::max(maxWidth, s->w);
			surfaces.push_back(s);
		}

		if (surfaces.size() == 1) {
			return surfaces[0];
		}

		SDL_Surface* final = SDL_CreateRGBSurfaceWithFormat(0, maxWidth, totalHeight, 32, SDL_PIXELFORMAT_ARGB8888);
		totalHeight = 0;
		for (SDL_Surface* surface : surfaces) {
			if (!surface) {
				totalHeight += empty_line_spacing;
				continue;
			}
			SDL_Rect dest = { 0,totalHeight,surface->w,surface->h };
			totalHeight += surface->h + spacing;
			SDL_BlitSurface(surface, NULL, final, &dest);
			SDL_FreeSurface(surface);
		}

		return final;
	}
};

