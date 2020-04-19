#pragma once

#include "mates.h"
#include "tilemap.h"
#include "jumpman.h"
#include "scene_manager.h"
#include "transition.h"
#include "screen.h"
#include "npc.h"
#include "input.h"
#include "cistell.h"

struct JumpScene : Scene {

	TileMap map;
	JumpMan player;
	PartSys bulletPartSys;
	Npc npc;
	Cistell cistell;
	int moneys = 0;

	GameKeys contextActionButton = GameKeys::NONE;

	JumpScene();
	void EnterScene() override;
	void ExitScene() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

};
