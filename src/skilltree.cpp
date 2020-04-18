#include "skilltree.h"

#include <vector>
#include "assets.h"
#include "input.h"
#include "debug.h"

std::vector<bool> unlocked;

 std::vector< std::vector<SkillTree::Skill>> needs = {
	{},
	{SkillTree::BREAK},
	{SkillTree::BREAK},
	{SkillTree::BOUNCY},
	{SkillTree::BOUNCY, SkillTree::RANGE_1},
	{SkillTree::RANGE_1},
};

 std::vector< sf::IntRect> img = {
	{8*16,11*16,16,16},
	{10*16,11*16,16,16},
	{5*16,10*16,16,16},
	{7*16,11*16,16,16},
	{9*16,11*16,16,16},
	{6*16,10*16,16,16},
};

 std::vector< std::vector<int>> tree = {
	{-1,               -1,                 SkillTree::RAPID_FIRE},
	{-1,               SkillTree::BOUNCY,  -1},
	{SkillTree::BREAK, -1,                 SkillTree::DMG_1},
	{-1,               SkillTree::RANGE_1, -1},
	{-1,               -1,                 SkillTree::RANGE_2},
};

sf::Vector2i posInTree(SkillTree::Skill s) {
	for (int i = 0; i < tree.size(); i++) {
		for (int j = 0; j < tree[i].size(); j++) {
			if (tree[i][j] == s) {
				return { j,i };
			}
		}
	}

	Debug::out << "Not found";
	return { 0,0 };

}

vec posInTreeToPosInScreen(sf::Vector2i p) {
	auto size = Camera::GetCameraSize();
	vec div = vec(size.x / (tree[0].size()), (size.y / (tree.size())));
	return Camera::GetCameraBounds().TopLeft() + (p * (div / 2)) + vec(div.x/2, div.y);
}

SkillTree::SkillTree() {
	//index = prevIndex = posInTree(SkillTree::BREAK);
};

void SkillTree::Update(float dt) {
	if (Keyboard::IsKeyJustPressed(GameKeys::START)) {
		open = !open;
	}
	if (!open) {
		return;
	}
	if (Keyboard::IsKeyJustPressed(GameKeys::LEFT)) {
		index.x -= 1;
	}
	if (Keyboard::IsKeyJustPressed(GameKeys::RIGHT)) {
		index.x += 1;
	}
	if (Keyboard::IsKeyJustPressed(GameKeys::UP)) {
		index.y -= 1;
	}
	if (Keyboard::IsKeyJustPressed(GameKeys::DOWN)) {
		index.y += 1;
		//if ()
	}
}
void SkillTree::DrawOverlay(sf::RenderTarget& window) const {
	sf::Sprite& sprite = Assets::marioSprite;
	if (gunpoints > 0) {
		//draw "press start to open menu"
	}
}


void SkillTree::DrawMenu(sf::RenderTarget& window) const {
	//Assets::menuBgSprite.setScale(1.f / GameData::GAME_ZOOM, 1.f / GameData::GAME_ZOOM);

	sf::Sprite& sprite = Assets::marioSprite;

	Assets::menuBgSprite.setPosition(Camera::GetCameraBounds().TopLeft());
	window.draw(Assets::menuBgSprite);

	sf::VertexArray lines(sf::Lines);

	for (int i = 0; i < needs.size(); i++) {
		if (!needs[i].empty()) {
			vec from = posInTreeToPosInScreen(posInTree(Skill(i)));
			for (int j = 0; j < needs[i].size(); j++) {
				vec to = posInTreeToPosInScreen(posInTree(Skill(needs[i][j])));
				lines.append(from);
				lines.append(to);
			}
		}
	}
	window.draw(lines);

	sprite.setOrigin(8, 8);
	for (int i = 0; i < tree.size(); i++) {
		for (int j = 0; j < tree[i].size(); j++) {
			if (tree[i][j] != -1) {
				sprite.setPosition(posInTreeToPosInScreen({ j,i }));
				sprite.setTextureRect(img[tree[i][j]]);

				bool canpick = true;
				//for (int j = 0; j < needs[i].size(); j++) {
				//	needs[i][j]
				//}
				sprite.setColor(sf::Color(100, 100, 250, 255));
				window.draw(sprite);
			}
		}
	}

	sprite.setColor(sf::Color(255, 255, 255, 255));
	

}
