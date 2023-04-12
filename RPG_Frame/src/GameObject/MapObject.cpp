#include	"MapObject.h"
#include	"MapSpriteComponent.h"
#include	"Game.h"

GameFrame::MapObject::MapObject(Game* game, const char* fileName, const std::string& name):
	GameObject(game,name)
{
	/*for (int i = 0; i < ScreenW/32; i++) {
		for (int j = 0; j < ScreenH/32; j++) {
			map[i][j] = 0;
			RunMap[i][j] = map[i][j];
		}
	}*/
	MapSpriteComponent* map = new MapSpriteComponent(this, 0, fileName);
	//SDL_Texture* tex = GetGame()->GetTexture("block");
	//map->SetTexture(tex);
}



GameFrame::MapObject::~MapObject()
{
}

void GameFrame::MapObject::update()
{
}

void GameFrame::MapObject::Draw(SDL_Renderer* renderer)
{
	for (auto iter : mSpriteComponents) {
		iter->Draw(renderer);
	}
	for (auto iter : mMapObjects) {
		iter->Draw(renderer);
	}
}

void GameFrame::MapObject::AddMapObject(GameObject* gameobject)
{
	mMapObjects.emplace_back(gameobject);
}

void GameFrame::MapObject::RemoveMapObject(GameObject* gameobject)
{
	auto iter = std::find(mMapObjects.begin(), mMapObjects.end(), gameobject);
	if (iter != mMapObjects.end()) {
		std::iter_swap(iter, mMapObjects.end() - 1);
		mMapObjects.pop_back();
	}
}
