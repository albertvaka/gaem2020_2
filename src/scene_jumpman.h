#pragma once

#include "mates.h"
#include "tilemap.h"
#include "jumpman.h"
#include "scene_manager.h"
#include "transition.h"
#include "npc.h"
#include "input.h"
#include "rototext.h"
#include "richtext.h"


struct JumpScene : Scene {

	TileMap map;
	Npc npc;
	RotoText rototext;

	bool lost = false;
	int moneys = 150;
	int cantbuyTimer = 0;

	//sfe::RichText moneyText;
	float moneyTextTimer = 0;
	int current_music = 0;
	float timerDoggo = 0;

	GameKeys contextActionButton = GameKeys::NONE;

	JumpScene();
	void EnterScene() override;
	void ExitScene() override;
	void Update(float dt) override;
	void Draw() override;

};
