#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"CollisionComponent.h"
#include	"Math2.h"
#include	"GameObject.h"

GameFrame::MoveComponent::MoveComponent(GameObject* gameobject):
	Component(gameobject)
{
}

void GameFrame::MoveComponent::ProcessInput(const SDL_Keycode key)
{
	if (mGameObject->GetMovingState() ){
	//	return;
	}
	else {
		mGameObject->SetMovingState(true);
		if (key == SDLK_w) {
			mGameObject->SetDir(GameObject::Dir::UP);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::up;
			mGameObject->SetPosition(newpos);
			//���⾯�棺��һ�ΰ�������4��
			SDL_Log("MOV_W");
		}
		else if (key == SDLK_s) {
			mGameObject->SetDir(GameObject::Dir::DOWN);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::down;
			mGameObject->SetPosition(newpos);
			SDL_Log("MOV_S");
		}
		else if (key == SDLK_a) {
			mGameObject->SetDir(GameObject::Dir::LEFT);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::left;
			mGameObject->SetPosition(newpos);
			SDL_Log("MOV_A");
		}
		else if (key == SDLK_d) {
			mGameObject->SetDir(GameObject::Dir::RIGHT);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::right;
			mGameObject->SetPosition(newpos);
			SDL_Log("MOV_D");
		}
		mGameObject->SetMovingState(false);
	}
	
}

void GameFrame::MoveComponent::ProcessInput2(const uint8_t* keystate)
{
	if (mGameObject->GetMovingState()) {
		//	return;
	}
	else {
		mGameObject->SetMovingState(true);
		if (keystate[SDL_SCANCODE_W]) {
			mGameObject->SetDir(GameObject::Dir::UP);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::up;
			mGameObject->SetPosition(newpos);
			if (mGameObject->GetComponent<CollisionComponent>()->CheckCollision())
				SDL_Log("pung!");
			//���⾯�棺��һ�ΰ�������4��
			SDL_Log("MOV_W");
		}
		else if (keystate[SDL_SCANCODE_S]) {
			mGameObject->SetDir(GameObject::Dir::DOWN);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::down;
			mGameObject->SetPosition(newpos);
			if (mGameObject->GetComponent<CollisionComponent>()->CheckCollision())
				SDL_Log("pung!");
			SDL_Log("MOV_S");
		}
		else if (keystate[SDL_SCANCODE_A]) {
			mGameObject->SetDir(GameObject::Dir::LEFT);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::left;
			mGameObject->SetPosition(newpos);
			if (mGameObject->GetComponent<CollisionComponent>()->CheckCollision())
				SDL_Log("pung!");
			SDL_Log("MOV_A");
		}
		else if (keystate[SDL_SCANCODE_D]) {
			mGameObject->SetDir(GameObject::Dir::RIGHT);
			Vector2 curpos = mGameObject->GetPosition();
			Vector2 newpos = curpos + Vector2::right;
			mGameObject->SetPosition(newpos);
			if (mGameObject->GetComponent<CollisionComponent>()->CheckCollision())
				SDL_Log("pung!");
			SDL_Log("MOV_D");
		}
		mGameObject->SetMovingState(false);
	}
}

void GameFrame::MoveComponent::update()
{
	/*if (mGameObject->GetDir() == GameObject::Dir::UP) {
		
	}
	else if(mGameObject->GetDir() == GameObject::Dir::DOWN)
	{
		
	}
	else if (mGameObject->GetDir() == GameObject::Dir::LEFT) {
		
	}
	else if (mGameObject->GetDir() == GameObject::Dir::RIGHT) {
		
	}*/
}
