#include "scene_jumpman.h"
#include "plant.h"
#include "input.h"
#include "imgui.h"
#include "assets.h"
#include "simplexnoise.h"
#include "debug.h"
#include "doggo.h"
#include "stats_tracker.h"

extern sf::Clock mainClock;

const int kInitialMoney = 120;
const int kMoneySellTomatoes = 30;
const int kMoneyBuyPlant = 100; //Super const, actually
const float kDoggoInterval = 90; //seconds
const float kinitialDoggoInterval = 40; //seconds

static JumpMan* AddPlayer(int id) {
	auto* player = new JumpMan(id);
	player->pos = TiledEntities::spawn;
	player->Carry(new Cistell());
	return player;
}

JumpScene::JumpScene(int first_player)
	: map(TiledMap::map_size.x, TiledMap::map_size.y)
	, moneyText(Assets::font)
	, first_player(first_player)
{
	moneyText.setScale(0.45f, 0.45f);
	map.LoadFromTiled();

	Camera::SetZoom(Window::GAME_ZOOM);
	Camera::SetCameraCenter(vec(Window::WINDOW_WIDTH / 4, Window::WINDOW_HEIGHT / 4));

}

void JumpScene::EnterScene() 
{
	lost = false;
	for (int i = 0; i < PlayerInput::kMaxPlayers; ++i) {
		players[i] = nullptr;
	}
	auto* player = new JumpMan(first_player);
	player->pos = TiledEntities::spawn;
	players[first_player] = player;

	StatsTracker::Restart();

#ifdef _DEBUG
	new Plant(vec(8.0f, 8.0f) + TileMap::alignToTiles(310.0f, 260.0f));
#endif

	moneys = kInitialMoney;

	timerDoggo = kDoggoInterval - kinitialDoggoInterval;

	auto* cistell = new Cistell();
	cistell->carrier = nullptr;
	cistell->pos = vec(550,355);

	npc.Reset();

	Assets::sceneMusic[current_music].play();
}

void JumpScene::ExitScene()
{
	JumpMan::deleteAll();
	Cistell::deleteAll();
	Plant::deleteAll();
	Doggo::deleteAll();
	Doggo::ResetDestinations();
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
	for (auto* player : JumpMan::getAll()) {
    if (PlayerInput::IsActionJustPressed(player->id, GameKeys::RESTART)) {
      ExitScene();
      EnterScene();
		}
	}

	if (lost) {
		rototext.Update(dt);
		return;
	}

	for (int i = 0; i < 4; ++i) {
    contextActionButton[i] = GameKeys::NONE;
	}

	for (int i = 0; i < 4; ++i) {
    if (players[i] == nullptr && 
			(PlayerInput::IsActionJustPressed(i, GameKeys::ACTIVATE) || PlayerInput::IsActionJustPressed(i, GameKeys::START))) {
			PlayerInput::ConsumeJustPressed(i, GameKeys::ACTIVATE);
      players[i] = AddPlayer(i);
    }
	}

	if (Keyboard::IsKeyJustPressed(GameKeys::DEBUG_DOGGO)) {
		new Doggo();
	}
	
	for (auto* player : JumpMan::getAll()) {
    player->Update(dt);
	}
	for (Doggo* doggo : Doggo::getAll()) {
		for (auto* player : JumpMan::getAll()) {
			if (player->IsCarrying(JumpMan::Holdable::Basket) && player->cistell->contents == Cistell::TOMATOES && Collide(player->bounds(), doggo->bounds())) {
        contextActionButton[player->id] = GameKeys::ACTIVATE;
        if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
          PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
          // Assets::DoggoEatingSound.play();
          doggo->Feed();
          player->cistell->contents = Cistell::EMPTY;
          break;
        }
			}
		}

		doggo->Update(dt);
		if (doggo->menjar <= 0) {
			doggo->menjar = 1;
			lost = true;
			StatsTracker::Stop();
			rototext.ShowMessage("A DOGGO STARVED");
		}
	}

	Camera::ChangeZoomWithPlusAndMinus(20.f, dt);
	//Debug::out << Camera::GetCameraCenter();


	npc.Update(dt);
	for (auto* cistell : Cistell::getAll()) {
    cistell->Update(dt);
	}

	timerDoggo += dt;
	if (timerDoggo >= kDoggoInterval) {
		timerDoggo = 0;
		new Doggo();
	}

	// Sell tomatoes.
	for (auto* player : JumpMan::getAll()) {
    if (player->IsCarrying(JumpMan::Holdable::Basket) && player->cistell->contents == Cistell::TOMATOES && Collide(player->bounds(), TiledAreas::truck)) {
      contextActionButton[player->id] = GameKeys::ACTIVATE;
      if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
        PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
        moneys += kMoneySellTomatoes;
        ++StatsTracker::tomatoes_delivered;
        if (GoodRandom::roll_flipcoin()) {
          Assets::soundSell1.play();
        }
        else {
          Assets::soundSell2.play();
        }
        moneyText.clear();
        moneyTextTimer = 0.5f;
        moneyText << sfe::Outline(sf::Color::Black, 1) << sf::Color::Green << "$" << std::to_string(kMoneySellTomatoes);
        player->cistell->contents = Cistell::EMPTY;
      }
    }
	}


	// All actions with the Player already carrying a Bucket.
	for (auto* player : JumpMan::getAll()) {
		auto* cistell = player->cistell;
		if (cistell == nullptr) {
			continue;
		}

    for (auto* plant : Plant::getAll()) {
      // Agafar tom�quets.
      if (Collide(plant->bounds(), cistell->bounds())) {
        // Agafar Tom�euts.
        if ((!cistell->contents) && plant->HasTomato()) {
          // TODO: Treure aix� si la collita passa automaticament.
          contextActionButton[player->id] = GameKeys::ACTIVATE;
          if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
            PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
            plant->PickTomato();
            cistell->contents = Cistell::TOMATOES;
            Assets::soundBucketTomatoes.play();
          }
        }
        // Regar plantes.
        else if (cistell->contents == Cistell::WATER) {
          // TODO: Agafar la planta que necessiti m�s aigua?
          contextActionButton[player->id] = GameKeys::ACTIVATE;
          if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
            PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
            plant->SetHitByWater();
            cistell->contents = Cistell::EMPTY;
            Assets::soundWater.play();
          }
        }

      }
    }
    // Agafar aigua.
    if (Collide(TiledAreas::water, cistell->bounds()) && !cistell->contents) {
      contextActionButton[player->id] = GameKeys::ACTIVATE;
      if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
        PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
        cistell->contents = Cistell::WATER;
        Assets::soundBucketWater.play();
      }
    }
    // Drop Bucket
    if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE) && player->grounded) {
      PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
      player->DropItem();
      Assets::soundPickupDrop.play();
    }
	}


	// Pick up Bucket by Player
	for (auto* player : JumpMan::getAll()) {
		for (auto* cistell : Cistell::getAll()) {
			if (Collide(player->bounds(), cistell->bounds()) && player->CanCarry() && !cistell->IsBeingCarried()) {
        contextActionButton[player->id] = GameKeys::ACTIVATE;
        if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
					player->Carry(cistell);
          Assets::soundPickupDrop.play();
				}
			}
		}
	}

	for (auto* plant : Plant::getAll()) {
		// Check if any player can pick up the plant.
		for (auto* player : JumpMan::getAll()) {
      if (Collide(plant->bounds(), player->bounds())) {
        bool can_carry = !plant->IsBeingCarried() && player->CanCarry();
        bool can_drop = plant->IsCarriedBy(player) && player->grounded;
        if (can_carry) {
          contextActionButton[player->id] = GameKeys::ACTIVATE;
        }
        if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
          if (can_drop) {
            PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
            player->DropItem();
            Assets::soundPickupDrop.play();
          } else if (can_carry) {
            PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
            player->Carry(plant);
            Assets::soundPickupDrop.play();
          }
        }
      }
		}

		plant->SetHitByLight(Collide(plant->bounds(), TiledAreas::sun));
		plant->Update(dt);
	}


	// Buy plants from NPCs.
	for (auto* player : JumpMan::getAll()) {
    if (npc.isSelling() && Collide(player->bounds(), TiledAreas::npc) && player->IsCarrying(JumpMan::Holdable::None)) {
      contextActionButton[player->id] = GameKeys::ACTIVATE;
      if (PlayerInput::IsActionJustPressed(player->id, GameKeys::ACTIVATE)) {
        PlayerInput::ConsumeJustPressed(player->id, GameKeys::ACTIVATE);
        if (moneys >= kMoneyBuyPlant) {
          moneys -= kMoneyBuyPlant;
          moneyText.clear();
          moneyTextTimer = 0.5f;
          moneyText << sfe::Outline(sf::Color::Black, 1) << sf::Color::Red << "-$" << std::to_string(kMoneyBuyPlant);
          ++StatsTracker::plants_purchased;
          player->Carry(new Plant(vec()));
          Assets::soundBuy.play();
        }
        else {
          cantbuyTimer = mainClock.getElapsedTime().asMilliseconds() + 1000;
        }
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

	for (Doggo* doggo : Doggo::getAll()) {
		if (doggo->wantFood) {
			doggo->Draw(window);
		}
	}

	for (auto* plant : Plant::getAll()) {
		plant->Draw(window);
	}
	
	for (const auto* cistell : Cistell::getAll()) {
    cistell->Draw(window);
	}
	for (const auto* player : JumpMan::getAll()) {
    player->Draw(window);
	}
	for (const auto* cistell : Cistell::getAll()) {
    if (cistell->IsBeingCarried()) {
      cistell->Draw(window);
    }
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

	for (Doggo* doggo : Doggo::getAll()) {
		if (!doggo->wantFood) {
			doggo->Draw(window);
		}
	}

	// Sunny sun.
  DrawSun(window);

	// TODO: Do this properly for each player.
	for (auto* player : JumpMan::getAll()) {
    if (contextActionButton[player->id] != GameKeys::NONE) {
      sf::Sprite& spr = Assets::hospitalSprite;
      spr.setPosition(player->bounds().TopRight() + vec(2, -6));
      AnimationType anim = BUTTON_A_PRESS; // TODO: switch depending on the key
      spr.setTextureRect(Animation::AnimFrame(anim, globalMillis));
      window.draw(spr);
    }
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

	// TODO: Fix this for many players.
	for (const auto* player : JumpMan::getAll()) {
    if (moneyTextTimer > 0) {
      moneyText.setPosition(player->bounds().Center() - vec(moneyText.getLocalBounds().width/4, player->bounds().height/2 + moneyText.getLocalBounds().height - 35*moneyTextTimer));
      window.draw(moneyText);
    }
	}
	
	if (Debug::Draw) {
		Bounds(TiledAreas::sun).Draw(window);
		Bounds(TiledAreas::npc).Draw(window);
		Bounds(TiledAreas::truck).Draw(window);
		Bounds(TiledAreas::water).Draw(window);

		for (const auto* player : JumpMan::getAll()) {
      player->bounds().Draw(window);
      for (const auto& plant : Plant::getAll()) {
        plant->bounds().Draw(window);
      }
      //player.pos.Debuggerino(sf::Color::White);
      //player.bounds().Center().Debuggerino(sf::Color::Magenta);
		}
	}


	if (lost) {
		StatsTracker::DrawStats(window);
		rototext.Draw(window);
	}
	//player.polvito.DrawImGUI("Polvito");
}


