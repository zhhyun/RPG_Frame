#include	"MapObject.h"
#include	"MapSpriteComponent.h"
#include	"Game.h"

GameFrame::MapObject::MapObject(Game* game, const char* fileName, const std::string& name):
	MapW(ScreenW),
	MapH(ScreenH),
	GameObject(game,name)
{
	MapSpriteComponent* map = new MapSpriteComponent(this, 0, fileName);
	PhysWorld* phys = new PhysWorld();
	Pw = phys;
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

void GameFrame::PhysWorld::AddBox(CollisionComponent* box)
{
	mBox.emplace_back(box);
}

void GameFrame::PhysWorld::RemoveBox(CollisionComponent* box)
{
}
