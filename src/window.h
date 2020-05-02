#pragma once

#include "bounds.h"

#include "debug.h"

#include <SDL.h>

namespace Camera
{
	extern float zoom;
	extern vec pos;
}

namespace Window
{
	extern SDL_Window* window;
	extern SDL_Renderer* renderer;
	extern bool focus;

	constexpr const int GAME_HEIGHT = 420;
	constexpr const int GAME_WIDTH = 828;
	constexpr const char* WINDOW_TITLE = "LD46";

	void ResetViewport();
}

namespace Camera
{
	inline vec GetSize()
	{
		return vec(Window::GAME_WIDTH / zoom, Window::GAME_HEIGHT / zoom);
	}

	inline void SetTopLeft(const vec& center)
	{
		pos = center;
	}

	inline void SetTopLeft(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	inline vec GetTopLeft()
	{
		return pos;
	}

	inline void SetCenter(const vec& center)
	{
		pos = center - GetSize()/2.f;
	}

	inline void SetCenter(float x, float y) { SetCenter(vec(x, y)); }

	inline vec GetCenter()
	{
		return pos + GetSize()/2.f;
	}

	inline Bounds GetBounds()
	{
		//return Bounds::fromCenter(GetCenter(), GetSize());
		return Bounds(pos, GetSize());
	}

	inline void ClampCameraTo(const Bounds& limit)
	{
		vec c = GetCenter();

		vec screenSize(Window::GAME_HEIGHT, Window::GAME_HEIGHT);
		screenSize /= zoom;
		float halfScreenWidth = screenSize.x / 2.f;
		float halfScreenHeight = screenSize.y / 2.f;

		//TODO: Center if viewport is bigger than limits
		if (c.x + halfScreenWidth > limit.Right()) c.x = limit.Right() - halfScreenWidth;
		if (c.x - halfScreenWidth < limit.Left()) c.x = limit.Left() + halfScreenWidth;
		if (c.y + halfScreenHeight > limit.Bottom()) c.y = limit.Bottom() - halfScreenHeight;
		if (c.y - halfScreenHeight < limit.Top()) c.y = limit.Top() + halfScreenHeight;

		SetCenter(c);
	}

	// if preserve_center is false, we will zoom from the top-left corner
	inline void SetZoom(float z, bool preserve_center = true)
	{
		vec c = GetCenter();
		zoom = z;
		Window::ResetViewport();
		if (preserve_center) {
			SetCenter(c);
		}
	}

	inline float GetZoom()
	{
		return zoom;
	}

	//Useful for debug pourposes
	void MoveCameraWithArrows(float velocity, float dt);
	void ChangeZoomWithPlusAndMinus(float zoomVel, float dt);
}


struct IntRect : SDL_Rect {
	IntRect() {}
	constexpr IntRect(int x, int y, int width, int height) : SDL_Rect({x, y, width, height }) {}
	constexpr IntRect(int x, int y, int size) : IntRect(x,y,size,size) { }
	constexpr explicit IntRect(const Bounds& b) : IntRect(b.top,b.left,b.width,b.height) {}
};

namespace Window
{
	void Init();
	void ProcessEvents();
	inline void ResetViewport() {
		SDL_RenderSetLogicalSize(Window::renderer, Window::GAME_WIDTH, Window::GAME_HEIGHT);
		float x, y;
		SDL_RenderGetScale(Window::renderer, &x, &y);
		SDL_RenderSetScale(Window::renderer, x*Camera::zoom, y*Camera::zoom);
	}

	inline bool HasFocus() { return focus; }
	bool IsMouseInsideWindow();

	inline vec GetSize() {
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		return vec(w,h);
	}
	inline Bounds GetBounds() { return Bounds(vec::Zero, GetSize()); }

	inline void Clear(uint8_t r, uint8_t g, uint8_t b) {
		SDL_SetRenderDrawColor(Window::renderer, r, g, b, 255);
		SDL_RenderClear(Window::renderer);
	}

	namespace DrawPrimitive {

		void Pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		inline void Pixel(vec v, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { Pixel(v.x, v.y, r, g, b, a); }

		// pass thickness = -1 to draw a filled rectangle
		void Rectangle(float x1, float y1, float x2, float y2, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		inline void Rectangle(const Bounds& box, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Rectangle(box.Left(), box.Top(), box.Right(), box.Bottom(), thickness, r, g, b, a);
		}

		void Line(float x1, float y1, float x2, float y2, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		inline void Line(const vec& v1, const vec& v2, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Line(v1.x, v1.y, v2.x, v2.y, thickness, r, g, b, a);
		}

		void Circle(float x, float y, int radius, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		inline void Circle(const vec& v, int radius, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Circle(v.x, v.y, radius, thickness, r, g, b, a);
		}
		inline void Circle(const CircleBounds& bounds, int thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Circle(bounds.pos, bounds.radius, thickness, r, g, b, a);
		}

	}

	struct Draw {
		SDL_Texture* t;
		SDL_FRect dest;
		SDL_Rect src;
		SDL_FPoint center;
		SDL_Rect* srcp = nullptr;
		SDL_FPoint* centerp = nullptr;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		float rotation = 0;
		vec scale = vec(1.f, 1.f);

		constexpr Draw(SDL_Texture* t, const vec& pos) : t(t), dest({ pos.x, pos.y, 0, 0 }), src({ 0,0,0,0 }), center({0,0}) {
		}

		constexpr Draw& withRect(int x, int y, int w, int h) {
			src = { x, y, w, h };
			srcp = &src;
			return *this;
		}

		constexpr Draw& withRect(IntRect r) {
			src = r;
			srcp = &src;
			return *this;
		}

		Draw& withColor(uint8_t r, uint8_t g, uint8_t b) {
			SDL_SetTextureColorMod(t, r, g, b);
			return *this;
		}

		Draw& withAlpha(uint8_t a) {
			SDL_SetTextureAlphaMod(t, a);
			return *this;
		}

		constexpr Draw& withOrigin(float x, float y) {
			center.x = x;
			center.y = y;
			centerp = &center;
			return *this;
		}

		constexpr Draw& withOrigin(const vec& o) {
			center.x = o.x;
			center.y = o.y;
			centerp = &center;
			return *this;
		}

		constexpr Draw& withRotation(float r) {
			rotation = r;
			return *this;
		}

		constexpr Draw& withScale(float s) {
			scale = vec(s, s);
			return *this;
		}

		constexpr Draw& withScale(float x, float y) {
			scale = vec(x, y);
			return *this;
		}

		constexpr Draw& withScale(const vec& v) {
			scale = v;
			return *this;
		}

		constexpr Draw& withFlip(bool h, bool v = false) {
			if (v) {
				flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);
			}
			if (h) {
				flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
			}
			return *this;
		}

		~Draw() {
			if (centerp) {
				center.x *= scale.x;
				center.y *= scale.y;
				dest.x -= center.x;
				dest.y -= center.y;
			}
			dest.x -= Camera::pos.x;
			dest.y -= Camera::pos.y;
			if (!srcp) {
				SDL_QueryTexture(t, NULL, NULL, &src.w, &src.h);
			}
			dest.w = src.w * scale.x;
			dest.h = src.h * scale.y;
			SDL_RenderCopyExF(Window::renderer, t, srcp, &dest, rotation, centerp, flip);
			SDL_SetTextureColorMod(t, 255, 255, 255);
			SDL_SetTextureAlphaMod(t, 255);
		};
	};


}


inline std::ostream& operator<<(std::ostream& os, const IntRect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_Point& rhs)
{
	os << rhs.x << "," << rhs.y;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_FPoint& rhs)
{
	os << rhs.x << "," << rhs.y;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_Rect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_FRect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}
