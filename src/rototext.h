#pragma once

#include <SFML/Graphics.hpp>

#include "vector.h"
#include "input.h"
#include "assets.h"

extern sf::Clock mainClock;

class RotoText : public sf::Text
{
	float messageTimeStart;
	float messageTime;

public:

	RotoText() : sf::Text("NO TEXT",Assets::font, 58) {
		setFillColor(sf::Color::White);
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(3);
		messageTime = -1;
	}

	void ShowMessage(sf::String msg) {
	
		setString(msg);
		
		sf::FloatRect textRect = getLocalBounds();
		setOrigin(textRect.left + textRect.width/2.0f,
						textRect.top  + textRect.height/2.0f);

		messageTime = 0.01;
		Update(0);

	}

	float GetElapsedTime() {
		return messageTime;
	}

	void Update(float dt) {
		
		if (messageTime >= 0) {

			messageTime += dt/5;

			float ang = sin(mainClock.getElapsedTime().asSeconds()*2)*10;
			float sc = 1;
			if(messageTime < 0.2)
			{
				sc = 1+(0.2-messageTime)*10;
				ang -= (0.2-messageTime)*600;
			}
			
			setRotation(ang);

			if(messageTime < 0.2) {
				sc = messageTime / 0.2;
			}
			setScale(sc, sc);

		}

	}

	void Draw(sf::RenderTarget& rt) {
		if (messageTime >= 0) {
			setPosition(vec(0.5f*Window::WINDOW_WIDTH, 0.33f*Window::WINDOW_HEIGHT)/ (Window::GAME_ZOOM));
			rt.draw(*this);
		}
	}

};



