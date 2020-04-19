#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "input.h"
#include "richtext.h"
#include "assets.h"

struct StatsTracker {
  static void Restart() {
    tomatoes_collected = 0;
    tomatoes_delivered = 0;
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

  static sfe::RichText DumpStats() {
    sfe::RichText text(Assets::font);
    text.setScale(0.5f, 0.5f);
    text << sf::Color::Black << "Stats:" << "\n"
      << "Time alive: " << std::to_string(time_played) << "\n"
      << "Tomatoes sold: " << std::to_string(tomatoes_delivered) << "\n"
      << "Tomatoes collected: " << std::to_string(tomatoes_collected) << "\n"
      << "Tomatoes fed to Doggo: " << std::to_string(doggos_fed) << "\n"
      << "Plants purchased: " << std::to_string(plants_purchased) << "\n"
      << "Plants watered: " << std::to_string(plant_watered) << "\n"
      << "Plants picked up: " << std::to_string(plant_pickedup) << "\n"
      << "Baskets picked up: " << std::to_string(basked_pickedup) << "\n";
    text.setPosition(vec(0.33f* Window::WINDOW_WIDTH, 0.5f* Window::WINDOW_HEIGHT)/(Window::GAME_ZOOM));
    return text;
  }

  static void Stop() {
    time_played = time_played_clock.getElapsedTime().asSeconds();
    time_played_clock.restart();
  }

  static float time_played;
  static int tomatoes_delivered;
  static int tomatoes_collected;
  static int doggos_fed;
  static int plants_purchased;
  static int plant_watered;
  static int plants_died;
  static int plant_pickedup;
  static int basked_pickedup;
  static int jumps_done;
  static int walljumps_done;
  static sf::Clock time_played_clock;
};
