#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "richtext.h"
#include "assets.h"
#include "richtext.h"

struct StatsTracker {
  static void Restart() {
    tomatoes_collected = 0;
    tomatoes_delivered = 0;
    doggos_in_game = 0;
    doggos_fed = 0;
    plants_died = 0;
    plants_purchased = 0;
    plant_watered = 0;
    plant_pickedup = 0;
    basked_pickedup = 0;
    jumps_done = 0;
    walljumps_done = 0;
    time_played = 0;
  }

  static void DrawStats(sf::RenderTarget& window) {
    window.draw(statsRect);
    window.draw(statsText);
  }

  static void Stop() {
    time_played = time_played_clock.getElapsedTime().asSeconds();
    time_played_clock.restart();
    sfe::RichText text(Assets::font);
    int min= time_played / 60;
    int sec = int(time_played)%60;
    text.setScale(0.4f, 0.4f);
    text << sf::Color::Black << "Stats:" << "\n\n"
      << "Time alive: " << std::to_string(min) << "m " << std::to_string(sec) << "s\n"
      << "Tomatoes sold: " << std::to_string(tomatoes_delivered) << "\n"
      << "Tomatoes collected: " << std::to_string(tomatoes_collected) << "\n"
      << "Doggos in game: " << std::to_string(doggos_in_game) << "\n"
      << "Tomatoes fed to Doggo: " << std::to_string(doggos_fed) << "\n"
      << "Plants purchased: " << std::to_string(plants_purchased) << "\n"
      << "Plants watered: " << std::to_string(plant_watered) << "\n"
      << "Plants picked up: " << std::to_string(plant_pickedup) << "\n"
      << "Baskets picked up: " << std::to_string(basked_pickedup) << "\n"
      << "Jumps done: " << std::to_string(jumps_done) << "\n"
      << "Walljumps done: " << std::to_string(walljumps_done) << "\n"
      << "\nPress ESC to play again!\n";
    text.setPosition(vec(0.33f* Window::WINDOW_WIDTH, 0.5f* Window::WINDOW_HEIGHT)/(Window::GAME_ZOOM));
    sf::FloatRect rect = text.getGlobalBounds();
    statsText = text;
    const float margin = 10.0f;
    statsRect = sf::RectangleShape({rect.width+2*margin, rect.height+2*margin});
    statsRect.setPosition({rect.left-margin, rect.top-margin});
		statsRect.setFillColor(sf::Color(255, 255, 200, 128));
		statsRect.setOutlineColor(sf::Color::Black);
		statsRect.setOutlineThickness(4.0f);
  }

  static float time_played;
  static int tomatoes_delivered;
  static int tomatoes_collected;
  static int doggos_in_game;
  static int doggos_fed;
  static int plants_purchased;
  static int plant_watered;
  static int plants_died;
  static int plant_pickedup;
  static int basked_pickedup;
  static int jumps_done;
  static int walljumps_done;
  static sf::Clock time_played_clock;
  static sfe::RichText statsText;
  static sf::RectangleShape statsRect;
};
