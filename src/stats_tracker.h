#pragma once

#include <SFML/System/Clock.hpp>

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
    time_played = 0;
  }

  static void Stop() {
    time_played = time_played_clock.getElapsedTime().asSeconds();
    time_played_clock.restart();
  }

  static int tomatoes_collected;
  static int tomatoes_delivered;
  static int doggos_fed;
  static int plants_died;
  static int plants_purchased;
  static int plant_watered;
  static int plant_pickedup;
  static int basked_pickedup;
  static float time_played;
  static sf::Clock time_played_clock;
};
