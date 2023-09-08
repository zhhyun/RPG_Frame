#include	"GameObject.h"
#include	"Game.h"
#include	"Component.h"
#include	"InputSystem.h"
#include	"SpriteComponent.h"


namespace GameFrame {
	GameObject::GameObject(Game* game, const std::string& name, const std::string& id) :
		mGame(game),
		ID(id),
		mState(State::EActive)
	{
		mGame->AddGameObject(this,name);
	}

	GameObject::GameObject(Game* game):
		mGame(game),
		mState(State::EActive)
	{
	}

	GameObject::~GameObject()
	{ 
		mGame->RemoveGameObject(this);
		while (mComponents.empty()) 
		{
			delete mComponents.back();
		}
	}
	void GameObject::update()
	{
		if (mState == GameObject::State::EActive) {
			for (auto component : mComponents) {
				component->update();
			}
		}
	}
	void GameObject::ProcessInput(InputSystem* keystate)
	{
	}
	void GameObject::AddComponent(Component* component)
	{
		mComponents.emplace_back(component);
	}
	void GameObject::RemoveComponent(Component* compoent)
	{
	}
	void GameObject::AddSpriteComponent(SpriteComponent* spritecomponent)
	{
		mSpriteComponents.emplace_back(spritecomponent);
	}
	void GameObject::RemoveSpriteComponent(SpriteComponent* spritecomponent)
	{
	}
	GameObject::State GameObject::GetState() const
	{
		return mState;
	}
	void GameObject::SetState(State state) 
	{
		mState = state;
	}

	class Game* GameObject::GetGame() const
	{
		return mGame;
	}

	void GameObject::Draw(SDL_Renderer* renderer)
	{
		for (auto iter : mSpriteComponents) {
			iter->Draw(renderer);
		}
	}

	Vector2 GameObject::GetMidllePoint()
	{
		Vector2 vec;
		vec.x = ObjectPosion.x + Width / 2;
		vec.y = ObjectPosion.y + Height / 2;
		return vec;
	}


	Vector2 GameObject::WinVecTransToMapVec(Vector2 Winvec)
	{
		Vector2 tansVec;
		auto camera = GetGame()->GetCamera();
		tansVec.x = Winvec.x + camera->GetImageRect().x;
		tansVec.y = Winvec.y + camera->GetImageRect().y;
		return tansVec;
	}

	Vector2 GameObject::MapVecTransToWinVec(int MapW, int MapH, Vector2 vecInmap)
	{
		Vector2 tansVec;
		auto camera = GetGame()->GetCamera();

		if (MapW < SCREEN_W) {
			SDL_Rect RectArea = { 0,0,SCREEN_W, SCREEN_H };
			//调整绘制目的坐标，确保对于尺寸小于屏幕的场景居中对其
			if (camera->GetImageRect().w < RectArea.w) {
				RectArea.w = camera->GetImageRect().w;
				//RectArea.x是小地图在窗口中的横坐标
				RectArea.x += 0.5 * (SCREEN_W - camera->GetImageRect().w);
			}

			tansVec.x = vecInmap.x + RectArea.x;
		}
		else {
			tansVec.x = vecInmap.x - camera->GetImageRect().x;
		}


		if (MapH < SCREEN_H) {
			SDL_Rect RectArea = { 0,0,SCREEN_W, SCREEN_H };
			if (camera->GetImageRect().h < RectArea.h) {
				RectArea.h = camera->GetImageRect().h;
				RectArea.y += 0.5 * (SCREEN_H - camera->GetImageRect().h);
			}

			tansVec.y = vecInmap.y + RectArea.y;
		}
		else {
			tansVec.y = vecInmap.y - camera->GetImageRect().y;
		}
		return tansVec;
	}
}
