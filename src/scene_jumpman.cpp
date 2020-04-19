#include "scene_jumpman.h"
#include "plant.h"
#include "input.h"
#include "imgui.h"
#include "assets.h"
#include "simplexnoise.h"
#include "savestation.h"
#include "debug.h"

extern sf::Clock mainClock;

const int kInitialMoney = 120;
const int kMoneySellTomatoes = 25;
const int kMoneyBuyPlant = 100; //Super const, actually

JumpScene::JumpScene()
	: map(TiledMap::map_size.x, TiledMap::map_size.y)
	, moneyText(Assets::font)
{
	moneyText.setScale(0.45f, 0.45f);
	map.LoadFromTiled();

	Camera::SetZoom(Window::GAME_ZOOM);
	Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 4));
}

void JumpScene::EnterScene() 
{
	player.Reset();
	player.pos = TiledEntities::spawn;

#ifdef _DEBUG
	new Plant(vec(8.0f, 8.0f) + TileMap::alignToTiles(310.0f, 260.0f));
#endif

	moneys = kInitialMoney;

	cistell.carrier = nullptr;
	cistell.pos = vec(550,355);

	npc.Reset();

	player.Carry(JumpMan::Holdable::None);
	Assets::sceneMusic[current_music].stop();
	Assets::sceneMusic[current_music].play();
}

void JumpScene::ExitScene()
{
	Plant::deleteAll();
}

void JumpScene::Update(float dt)
{
	if (Keyboard::IsKeyJustPressed(GameKeys::NEXT_TRACK)) {
		Assets::sceneMusic[current_music].stop();
		current_music = 1-current_music;
		Assets::sceneMusic[current_music].play();
	}
	if (Keyboard::IsKeyJustPressed(GameKeys::MUTE)) {
		bool static muted = false;
		muted = !muted;
		if (muted) Assets::sceneMusic[current_music].pause();
		else Assets::sceneMusic[current_music].play();
	}

	//Camera::MoveCameraWithArrows(50, dt);
	if (Keyboard::IsKeyJustPressed(GameKeys::RESTART)) {
		ExitScene();
		EnterScene();
	}
	
	player.Update(dt);

	Camera::ChangeZoomWithPlusAndMinus(20.f, dt);
	//Debug::out << Camera::GetCameraCenter();

	contextActionButton = GameKeys::NONE;

	npc.Update(dt);
	cistell.Update(dt);


	if (player.IsCarrying(JumpMan::Holdable::Basket) && cistell.contents == Cistell::TOMATOES && Collide(player.bounds(), TiledAreas::truck)) {
		contextActionButton = GameKeys::ACTIVATE;
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
			moneys += kMoneySellTomatoes;
			if (GoodRandom::roll_flipcoin()) {
				Assets::soundSell1.play();
			}
			else {
				Assets::soundSell2.play();
			}
			moneyText.clear();
			moneyTextTimer = 0.5f;
			moneyText << sfe::Outline(sf::Color::Black, 1) << sf::Color::Green << "$" << std::to_string(kMoneySellTomatoes);
			cistell.contents = Cistell::EMPTY;
		}
	}


	bool player_had_empty_hands = player.CanCarry();
  if (Collide(cistell.bounds(), player.bounds())) {
		bool can_carry = !cistell.IsBeingCarried() && player_had_empty_hands;
		bool can_drop = cistell.IsCarriedBy(&player) && player.grounded;

		// Agafar tomàquets.
		for (auto* plant : Plant::getAll()) {
      if (Collide(plant->bounds(), cistell.bounds()) && cistell.IsBeingCarried()) {
				// Agafar Tomàeuts.
        if ((!cistell.contents) && plant->HasTomato()) {
          // TODO: Treure això si la collita passa automaticament.
          contextActionButton = GameKeys::ACTIVATE;
          if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			  Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
            plant->PickTomato();
            cistell.contents = Cistell::TOMATOES;
			Assets::soundBucketTomatoes.play();
            can_drop = false;
            // Agafar tomàquets té prioritat per sobre deixar anar la cistella.
          }
        }
				// Regar plantes.
				else if (cistell.contents == Cistell::WATER) {
					// TODO: Agafar la planta que necessiti més aigua?
          contextActionButton = GameKeys::ACTIVATE;
          if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			  Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
            plant->SetHitByWater();
            cistell.contents = Cistell::EMPTY;
			Assets::soundWater.play();
            can_drop = false;
          }
				}

			}
		}
		// Agafar aigua.
		if (Collide(TiledAreas::water, cistell.bounds()) && cistell.IsBeingCarried() && (!cistell.contents)) {
			contextActionButton = GameKeys::ACTIVATE;
			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.contents = Cistell::WATER;
				Assets::soundBucketWater.play();
			}
			can_drop = false;
		}

		if (can_carry) {
			contextActionButton = GameKeys::ACTIVATE;
		}
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			if (can_drop) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.Drop();
				player.Carry(JumpMan::Holdable::None);
				Assets::soundPickupDrop.play();
			} else if (can_carry) {
				Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
				cistell.PickUpBy(&player);
				player.Carry(JumpMan::Holdable::Basket);
				Assets::soundPickupDrop.play();
			}
		}
  }

	for (auto* plant : Plant::getAll()) {
		if (Collide(plant->bounds(), player.bounds())) {
			bool can_carry = !plant->IsBeingCarried() && player.CanCarry() && player_had_empty_hands;
			bool can_drop = plant->IsCarriedBy(&player) && player.grounded;
			if (can_carry) {
				contextActionButton = GameKeys::ACTIVATE;
			}
			if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
				if (can_drop) {
					Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
					plant->Drop();
					player.Carry(JumpMan::Holdable::None);
					Assets::soundPickupDrop.play();
				} else if (can_carry) {
					Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
					plant->PickUpBy(&player);
					player.Carry(JumpMan::Holdable::Plant);
					Assets::soundPickupDrop.play();
				}
			}
		}
		plant->SetHitByLight(Collide(plant->bounds(), TiledAreas::sun));

		plant->Update(dt);

	}


	if (npc.isSelling() && Collide(player.bounds(), TiledAreas::npc) && player.IsCarrying(JumpMan::Holdable::None)) {
		contextActionButton = GameKeys::ACTIVATE;
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTIVATE)) {
			Keyboard::ConsumeJustPressed(GameKeys::ACTIVATE);
			if (moneys >= kMoneyBuyPlant) {
				moneys -= kMoneyBuyPlant;
				moneyText.clear();
				moneyTextTimer = 0.5f;
				moneyText << sfe::Outline(sf::Color::Black, 1) << sf::Color::Red << "-$" << std::to_string(kMoneyBuyPlant);
				(new Plant(vec()))->PickUpBy(&player);
				player.Carry(JumpMan::Holdable::Plant);
				Assets::soundBuy.play();
			}
			else {
				cantbuyTimer = mainClock.getElapsedTime().asMilliseconds() + 1000;
			}
		}
	}

	moneyTextTimer -= dt;

	if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_GET_MONEY)) {
		moneys += 100;
		moneyText.clear();
		moneyTextTimer = 0.5f;
		moneyText << sfe::Outline(sf::Color::Black, 1) << sf::Color::Green << "$100";
	}

}

// El sol
// <-0s---------------------------------------------------13s------>15s
// |<-----------Sol0--------->                             |
// |                   <--------Sol1----------->           |
// |                                    <--------Sol2------+------->
// +--Sol2--->                                             |
static const float SunLimits[4][2] = 
{
  {0.0f, 7.0f},
  {4.0f, 11.0f},
  {8.0f, 15.0f},
  {-4.0f, 3.0f}, // Repetir Sol2 per al principi
};

static void DrawSun(sf::RenderTarget& window)
{
	static sf::Clock sun_clock;
	auto time = sun_clock.getElapsedTime().asSeconds();
  if (time > 13.0f) {
    sun_clock.restart();
  }
	const float max_alpha = 128.0f;
	for (int i = 0; i < 4; ++i) {
		if (time >= SunLimits[i][0] && time <= SunLimits[i][1]) {
			const float mid = (SunLimits[i][0] + SunLimits[i][1]) / 2.0f;
			const float half_size = (SunLimits[i][1] - SunLimits[i][0])/2.0f;
      float ratio = (time < mid ? (time-SunLimits[i][0])/half_size : 1.0f-(time-mid)/half_size);
			assert(ratio >= 0 && ratio <= 1.0f);
      auto& spr = Assets::sunSprites[std::min(i, 2)];
			spr.setColor(sf::Color(255, 255, 255, 50*ratio));
			window.draw(spr);
		}
	}
}

void JumpScene::Draw(sf::RenderTarget& window)
{
	window.clear(sf::Color(34, 32, 52));

	window.draw(Assets::casaSprite);

	if (Debug::Draw) {
		map.Draw(window);
	}

	int globalMillis = mainClock.getElapsedTime().asMilliseconds();

	//Fountain
	sf::Sprite& spr = Assets::spritesSprite;
	spr.setPosition(413, 329);
	spr.setOrigin(0, 0);
	spr.setScale(1.8f, 1.45f);
	spr.setTextureRect(Animation::AnimFrame(FOUNTAIN, globalMillis));
	window.draw(spr);
	spr.setScale(1.f, 1.f);

	npc.Draw(window);

	for (auto* plant : Plant::getAll()) {
		plant->Draw(window);
	}
	
	cistell.Draw(window);
	player.Draw(window);


	if (cistell.IsBeingCarried()) {
		cistell.Draw(window);
	}
	for (auto* plant : Plant::getAll()) {
		if (plant->IsBeingCarried()) {
			plant->Draw(window);
			break;
		}
	}


	//Truck
	spr.setPosition(702, 297);
	spr.setOrigin(0, 0);
	spr.setTextureRect(sf::IntRect(0, 8 * 16, 11 * 16 + 4, 72));
	window.draw(spr);

	// Sunny sun.
  DrawSun(window);

	if (contextActionButton != GameKeys::NONE) {
		sf::Sprite& spr = Assets::hospitalSprite;
		spr.setPosition(player.bounds().TopRight() + vec(2, -6));
		AnimationType anim = BUTTON_A_PRESS; // TODO: switch depending on the key
		spr.setTextureRect(Animation::AnimFrame(anim, globalMillis));
		window.draw(spr);
	}

	sfe::RichText text(Assets::font);
	text.setPosition(10, 10);
	text.setScale(0.8f, 0.8f);

	if (cantbuyTimer > globalMillis && (globalMillis/100)%2) {
		text << sf::Color::Red;
	}
	else {
		text << sf::Color::Cyan;
	}
	text << sfe::Outline(sf::Color::Black, 2) << "$" << std::to_string(moneys);
	window.draw(text);

	if (moneyTextTimer > 0) {
		moneyText.setPosition(player.bounds().Center() - vec(moneyText.getLocalBounds().width/4, player.bounds().height/2 + moneyText.getLocalBounds().height - 35*moneyTextTimer));
		window.draw(moneyText);
	}
	
	if (Debug::Draw) {
		Bounds(TiledAreas::sun).Draw(window);
		Bounds(TiledAreas::npc).Draw(window);
		Bounds(TiledAreas::truck).Draw(window);
		Bounds(TiledAreas::water).Draw(window);

		player.bounds().Draw(window);
		for (const auto& plant : Plant::getAll()) {
			plant->bounds().Draw(window);
		}
		//player.pos.Debuggerino(sf::Color::White);
		//player.bounds().Center().Debuggerino(sf::Color::Magenta);
	}

	//player.polvito.DrawImGUI("Polvito");
}


