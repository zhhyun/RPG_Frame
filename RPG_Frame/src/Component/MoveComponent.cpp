#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"CollisionComponent.h"
#include	"Math2.h"
#include	"GameObject.h"
#include	"AnimSpriteComponent.h"

GameFrame::MoveComponent::MoveComponent(GameObject* gameobject) :
	IsMoving(false),
	movdir(MovDir::idle),
	Component(gameobject)
{
}

//void GameFrame::MoveComponent::ProcessInput(const SDL_Keycode key)
//{
//	if (mGameObject->GetMovingState() ){
//	//	return;
//	}
//	else {
//		mGameObject->SetMovingState(true);
//		if (key == SDLK_w) {
//			mGameObject->SetDir(GameObject::Dir::UP);
//			Vector2 curpos = mGameObject->GetPosition();
//			Vector2 newpos = curpos + Vector2::up;
//			mGameObject->SetPosition(newpos);
//			//问题警告：按一次按键运行4次
//			SDL_Log("MOV_W");
//		}
//		else if (key == SDLK_s) {
//			mGameObject->SetDir(GameObject::Dir::DOWN);
//			Vector2 curpos = mGameObject->GetPosition();
//			Vector2 newpos = curpos + Vector2::down;
//			mGameObject->SetPosition(newpos);
//			SDL_Log("MOV_S");
//		}
//		else if (key == SDLK_a) {
//			mGameObject->SetDir(GameObject::Dir::LEFT);
//			Vector2 curpos = mGameObject->GetPosition();
//			Vector2 newpos = curpos + Vector2::left;
//			mGameObject->SetPosition(newpos);
//			SDL_Log("MOV_A");
//		}
//		else if (key == SDLK_d) {
//			mGameObject->SetDir(GameObject::Dir::RIGHT);
//			Vector2 curpos = mGameObject->GetPosition();
//			Vector2 newpos = curpos + Vector2::right;
//			mGameObject->SetPosition(newpos);
//			SDL_Log("MOV_D");
//		}
//		mGameObject->SetMovingState(false);
//	}
//	
//}

void GameFrame::MoveComponent::ProcessInput(const uint8_t* keystate)
{
		IsMoving = true;
		if (keystate[SDL_SCANCODE_W]) {
			mOwner->SetDir(GameObject::Dir::UP);
			movdir = MovDir::toUp;
		}
		else if (keystate[SDL_SCANCODE_S]) {
			mOwner->SetDir(GameObject::Dir::DOWN);
			movdir = MovDir::toDown;
		}
		else if (keystate[SDL_SCANCODE_A]) {
			mOwner->SetDir(GameObject::Dir::LEFT);
			movdir = MovDir::toLeft;
		}
		else if (keystate[SDL_SCANCODE_D]) {
			mOwner->SetDir(GameObject::Dir::RIGHT);
			movdir = MovDir::toRight;
		}
}

void GameFrame::MoveComponent::update()
{
	if (!IsMoving)
		return;
	GameObject::Dir dir = mOwner->GetDir();
	CollisionComponent* coll = mOwner->GetComponent<CollisionComponent>();
	if (movdir == MovDir::toUp) {
		mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("UpForward");
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + Vector2::up;
		mOwner->SetPosition(newpos);
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		//问题警告：按一次按键运行4次
		movdir = MovDir::idle;
		SDL_Log("MOV_W");
	}
	else if(movdir == MovDir::toDown){
		mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("DownForward");
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + Vector2::down;
		mOwner->SetPosition(newpos);
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		movdir = MovDir::idle;
		SDL_Log("MOV_D");
	}
	else if (movdir == MovDir::toLeft) {
		mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("LeftForward");
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + Vector2::left;
		mOwner->SetPosition(newpos);
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		movdir = MovDir::idle;
		
		SDL_Log("MOV_A");
	}
	else if (movdir == MovDir::toRight) {
		mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("RightForward");
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + Vector2::right;
		mOwner->SetPosition(newpos);
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		movdir = MovDir::idle;
		SDL_Log("MOV_D");
	}
	coll->OnUpdateWorldTransform();
	IsMoving = false;
}

