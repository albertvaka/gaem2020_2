#pragma once

#include "vector.h"
#include "input.h"
#include "assets.h"
#include "window.h"
#include "text.h"

extern float mainClock;

class RotoText : public Text
{
	float messageTime;
	float scale;
	float rotation;
public:

	RotoText() : Text(Assets::font_30, Assets::font_30_outline) {
		setFillColor(255,255,255);
		setOutlineColor(0,0,0);
		messageTime = -1;
	}

	void ShowMessage(sf::String msg) {
	
		setString(msg);
		
		messageTime = 0.01f;
		Update(0);

	}

	float GetElapsedTime() {
		return messageTime;
	}

	void Update(float dt) {
		
		if (messageTime >= 0) {

			messageTime += dt/5;

			float ang = sin(mainClock*2)*10;
			float sc = 1;
			if(messageTime < 0.2)
			{
				sc = 1+(0.2-messageTime)*10;
				ang -= (0.2-messageTime)*600;
			}
			
			rotation = ang;

			if(messageTime < 0.2) {
				sc = messageTime / 0.2;
			}
			scale = sc;

		}

	}

	void Draw() {
		if (messageTime < 0) {
			return;
		}

		vec s = getSize();
		Window::Draw(*this, vec(0.5f * Window::WINDOW_WIDTH, 0.33f * Window::WINDOW_HEIGHT) / (Window::GAME_ZOOM))
			.withOrigin(s.x / 2.0f, s.y / 2.0f)
			.withScale(scale)
			.withRotation(rotation);
	}

};


