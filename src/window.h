#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "bounds.h"


namespace Window
{
	extern sf::RenderWindow* window;
	extern bool focus;

	const int GUI_ZOOM = 1;
	const int GAME_ZOOM = 2;
	const int WINDOW_HEIGHT = 420 * GAME_ZOOM;
	const int WINDOW_WIDTH = 828 * GAME_ZOOM;

}

struct IntRect {
	IntRect() {}
	IntRect(int x, int y, int width, int height) : x(x), y(y), w(width), h(height) { }
	IntRect(int x, int y, int size) : x(x), y(y), w(size), h(size) { }
	int x, y;
	int w, h;
};

struct PartialDraw {
	sf::Sprite sprite;
	PartialDraw(PartialDraw&& o) noexcept : sprite(std::move(o.sprite)) {}

	PartialDraw(const sf::Texture& t, const vec& pos) {
		sprite.setTexture(t);
		sprite.setPosition(pos);
	}

	PartialDraw& withRect(int x, int y, int w, int h) {
		sprite.setTextureRect(sf::IntRect(x, y, w, h));
		return *this;
	}

	PartialDraw& withRect(IntRect r) {
		sprite.setTextureRect(sf::IntRect(r.x, r.y, r.w, r.h));
		return *this;
	}

	PartialDraw& withColor(int r, int g, int b) {
		sprite.setColor(sf::Color(r,g,b,sprite.getColor().a));
		return *this;
	}
	PartialDraw& withAlpha(int a) {
		const sf::Color& c = sprite.getColor();
		sprite.setColor(sf::Color(c.r,c.g,c.b,a));
		return *this;
	}

	PartialDraw& withOrigin(float x, float y) {
		sprite.setOrigin(x, y);
		return *this;
	}

	PartialDraw& withOrigin(const vec& o) {
		sprite.setOrigin(o);
		return *this;
	}

	PartialDraw& withRotation(float r) {
		sprite.setRotation(r);
		return *this;
	}

	PartialDraw& withScale(float s) {
		sprite.setScale(s,s);
		return *this;
	}

	PartialDraw& withScale(float x, float y) {
		sprite.setScale(x, y);
		return *this;
	}

	PartialDraw& withScale(const vec& v) {
		sprite.setScale(v.x, v.y);
		return *this;
	}

	~PartialDraw() {
		Window::window->draw(sprite);
	};
};


namespace Window
{
	void SetWindowCaption(const std::string& s);
	bool WindowHasFocus();
	void CloseWindow();
	void SetWindowSize(sf::Vector2u size, bool centerCamera = true);
	sf::Vector2u GetWindowSize();
	Bounds GetWindowBounds();
	bool IsMouseInsideWindow();
	inline PartialDraw Draw(const sf::Texture& t, const vec& pos) { return PartialDraw(t, pos); }
	inline void Clear(int r, int g, int b) {window->clear(sf::Color(r, g, b)); }
}

void _ProcessWindowEvents();