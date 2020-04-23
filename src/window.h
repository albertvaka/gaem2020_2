#pragma once

#include "bounds.h"

#include <SDL.h>

#include "debug.h"

namespace Camera
{
	extern float zoom;
	extern vec cam;
}

namespace Window
{
	extern SDL_Window* window;
	extern SDL_Renderer* renderer;
	extern bool focus;

	const int GUI_ZOOM = 1;
	const int GAME_ZOOM = 2;
	const int WINDOW_HEIGHT = 420 * GAME_ZOOM;
	const int WINDOW_WIDTH = 828 * GAME_ZOOM;
	constexpr const char* WINDOW_TITLE = "LD46";
}

namespace Camera
{

	inline void SetCenter(const vec& center)
	{
		cam = center*zoom-vec(Window::WINDOW_WIDTH/2, Window::WINDOW_HEIGHT/2);
	}

	inline void SetCenter(float x, float y) { SetCenter(vec(x, y)); }

	inline vec GetCenter()
	{
		return cam * zoom +vec(Window::WINDOW_WIDTH/2, Window::WINDOW_HEIGHT/2);
	}

	inline vec GetSize()
	{
		return vec(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
	}

	inline Bounds GetBounds()
	{
		return Bounds(GetCenter(), GetSize());
	}

	inline void ClampCameraTo(const Bounds& limit)
	{
		vec c = GetCenter();

		vec screenSize(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);
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

	inline void SetZoom(float z)
	{
		vec c = GetCenter();
		zoom = z;
		SDL_RenderSetScale(Window::renderer, z, z);
		SetCenter(c);
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
	IntRect(int _x, int _y, int width, int height) { x = _x; y = _y; w = width; h = height; }
	IntRect(int _x, int _y, int size) : IntRect(x,y,size,size) { }
};

struct PartialDraw {
	SDL_Texture* t;
	SDL_FRect dest;
	SDL_Rect src;
	SDL_FPoint center;
	SDL_FPoint* centerp = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	float rotation = 0;
	vec scale = vec(1.f,1.f);

	PartialDraw(PartialDraw&& o) noexcept : t(o.t), dest(std::move(o.dest)) {}

	PartialDraw(SDL_Texture* t, const vec& pos) : t(t), dest({ pos.x, pos.y, 0, 0 }), src({ 0,0,0,0 }) { SDL_QueryTexture(t, NULL, NULL, &src.w, &src.h); }

	PartialDraw& withRect(int x, int y, int w, int h) {
		src = { x, y, w, h };
		return *this;
	}

	PartialDraw& withRect(IntRect r) {
		src = r;
		return *this;
	}

	PartialDraw& withColor(int r, int g, int b) {
		SDL_SetTextureColorMod(t, r, g, b);
		return *this;
	}

	PartialDraw& withAlpha(int a) {
		SDL_SetTextureAlphaMod(t, a);
		return *this;
	}

	PartialDraw& withOrigin(float x, float y) {
		center.x = x;
		center.y = y;
		centerp = &center;
		return *this;
	}

	PartialDraw& withOrigin(const vec& o) {
		center.x = o.x;
		center.y = o.y;
		centerp = &center;
		return *this;
	}

	PartialDraw& withRotation(float r) {
		rotation = r;
		return *this;
	}

	PartialDraw& withScale(float s) {
		scale = vec(s,s);
		return *this;
	}

	PartialDraw& withScale(float x, float y) {
		scale = vec(x, y);
		return *this;
	}

	PartialDraw& withScale(const vec& v) {
		scale = v;
		return *this;
	}

	PartialDraw& withFlip(bool h, bool v = false) {
		if (v) {
			flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);
		}
		if (h) {
			flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
		}
		return *this;
	}

	~PartialDraw() {
		if (centerp) {
			center.x *= scale.x;
			center.y *= scale.y;
			dest.x -= center.x;
			dest.y -= center.y;
		}
		dest.x -= Camera::cam.x;
		dest.y -= Camera::cam.y;
		dest.w = src.w * scale.x;
		dest.h = src.h * scale.y;
		SDL_RenderCopyExF(Window::renderer, t, &src, &dest, rotation, centerp, flip);
		SDL_SetTextureColorMod(t, 255, 255, 255);
		SDL_SetTextureAlphaMod(t, 255);
	};
};


namespace Window
{
	void Init();
	void ProcessEvents();

	inline bool HasFocus() { return focus; }
	bool IsMouseInsideWindow();

	inline vec GetWindowSize() { return vec(WINDOW_WIDTH, WINDOW_HEIGHT); }
	inline Bounds GetWindowBounds() { return Bounds(vec::Zero, GetWindowSize()); }

	inline PartialDraw Draw(SDL_Texture* t, const vec& pos) { return PartialDraw(t, pos); }
	inline void Clear(int r, int g, int b) {
		SDL_SetRenderDrawColor(Window::renderer, r, g, b, 0xFF);
		SDL_RenderClear(renderer); 
	}
}

void _ProcessWindowEvents();