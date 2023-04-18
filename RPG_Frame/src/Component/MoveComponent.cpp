#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"CollisionComponent.h"
#include	"Math2.h"
#include	"GameObject.h"
#include	"AnimSpriteComponent.h"
#include	"InputSystem.h"

GameFrame::MoveComponent::MoveComponent(GameObject* gameobject) :
	movdir(0, 0),
	mMovState(MovState::Idle),
	Speed(5.0),
	Component(gameobject)
{
}

void GameFrame::MoveComponent::ProcessInput(const InputSystem* keystate)
{
	//根据按钮状态，人物移动也分四种情况：静止、开始移动，保持移动、停止移动
	ButtomState W = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_W);
	ButtomState A = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_A);
	ButtomState S = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_S);
	ButtomState D = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_D);
	//不在运动的状态
	if ((W == ButtomState::ENone) &&
		(S == ButtomState::ENone) &&
		(A == ButtomState::ENone) &&
		(D == ButtomState::ENone)) {
		if (mMovState != MovState::Idle) {
			mMovState = MovState::Idle;
		}
		return;
	}

	//先只管把运动状态加入或删除响应队列，然后再判断正在响应的按键，并赋予状态；
	//在运动或运动上下沿阶段
	//如果按下按键则加入响应队列,按键优先响应顺序WASD
	if (W == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_W , W };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//检测重复输入
			bool tag = false;
			for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
				if (iter->key == kqs.key) {
					iter->keystate = W;
					tag = true;
					break;
				}

			}
			if (!tag) {
				mReqKeys.insert(mReqKeys.begin(), 1, kqs);
			}
		}
		if (mReqKeys.size() > 2) {
			mReqKeys.pop_back();//先进先出
		}
	}
	if (A == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_A , A };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//检测重复输入
			bool tag = false;
			for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
				if (iter->key == kqs.key) {
					iter->keystate = A;
					tag = true;
					break;
				}
			}
			if (!tag) {
				mReqKeys.insert(mReqKeys.begin(), 1, kqs);
			}
		}
		if (mReqKeys.size() > 2) {
			mReqKeys.pop_back();
		}
	}
	if (S == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_S , S };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//检测重复输入
			bool tag = false;
			for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
				if (iter->key == kqs.key) {
					iter->keystate = S;
					tag = true;
					break;
				}
			}
			if (!tag) {
				mReqKeys.insert(mReqKeys.begin(), 1, kqs);
			}
		}
		if (mReqKeys.size() > 2) {
			mReqKeys.pop_back();
		}
	}
	if (D == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_D , D };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//检测重复输入
			bool tag = false;
			for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
				if (iter->key == kqs.key) {
					iter->keystate = D;
					tag = true;
					break;
				}
			}
			if (!tag) {
				mReqKeys.insert(mReqKeys.begin(), 1, kqs);
			}
		}
		if (mReqKeys.size() > 2) {
			mReqKeys.pop_back();
		}
	}

	//如果按住or松开按键，则更新响应按键容器的按键状态
	if (W == ButtomState::EHeld || W == ButtomState::EReleased) {
		for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
			if (iter->key == SDL_SCANCODE_W)
				iter->keystate = W;
		}
	}
	if (A == ButtomState::EHeld || A == ButtomState::EReleased) {
		for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
			if (iter->key == SDL_SCANCODE_A)
				iter->keystate = A;
		}
	}
	if (S == ButtomState::EHeld || S == ButtomState::EReleased) {
		for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
			if (iter->key == SDL_SCANCODE_S)
				iter->keystate = S;
		}
	}
	if (D == ButtomState::EHeld || D == ButtomState::EReleased) {
		for (auto iter = mReqKeys.begin(); iter != mReqKeys.end(); iter++) {
			if (iter->key == SDL_SCANCODE_D)
				iter->keystate = D;
		}
	}

	//判定人物当前运动状态并更新到类成员中
	if (mReqKeys.size() == 1) //如果当前只按下一个按键
	{
		auto iter = mReqKeys.begin();
		if (iter->keystate == ButtomState::EPressed) {
			mMovState = MovState::MovStart;
			switch (iter->key) {
			case SDL_SCANCODE_W:
				mOwner->SetDir(GameObject::Dir::UP);
				movdir = Vector2::up;
				break;
			case SDL_SCANCODE_A:
				mOwner->SetDir(GameObject::Dir::LEFT);
				movdir = Vector2::left;
				break;
			case SDL_SCANCODE_S:
				mOwner->SetDir(GameObject::Dir::DOWN);
				movdir = Vector2::down;
				break;
			case SDL_SCANCODE_D:
				mOwner->SetDir(GameObject::Dir::RIGHT);
				movdir = Vector2::right;
				break;
			}
		}
		else if (iter->keystate == ButtomState::EHeld) {
			if (mMovState != MovState::MovHeld)
				mMovState = MovState::MovHeld;
		}
		else if (iter->keystate == ButtomState::EReleased) {
			mMovState = MovState::MovStop;
			movdir = Vector2::ZERO;
		}
	}

	else if (mReqKeys.size() == 2) //如果当前存在两个按键状态//按键松下也算是状态，不过在执行完对应的事件后要把该按键信息从容器中删除
	{
		/*响应规则：
		* 1 只响应容器顶端的键码
		* 2 优先响应按下状态的键码
		（由于按下按键时，键码会自动添加到容器顶端，所以只响应容器首键码就能保证规则实现）
		*/
		auto first = mReqKeys.begin();
		auto last = mReqKeys.end() - 1;
		if (first->keystate == ButtomState::EPressed) {
			mMovState = MovState::MovStart;
			switch (first->key) {
			case SDL_SCANCODE_W:
				mOwner->SetDir(GameObject::Dir::UP);
				movdir = Vector2::up;
				break;
			case SDL_SCANCODE_A:
				mOwner->SetDir(GameObject::Dir::LEFT);
				movdir = Vector2::left;
				break;
			case SDL_SCANCODE_S:
				mOwner->SetDir(GameObject::Dir::DOWN);
				movdir = Vector2::down;
				break;
			case SDL_SCANCODE_D:
				mOwner->SetDir(GameObject::Dir::RIGHT);
				movdir = Vector2::right;
				break;
			}
		}
		else if (first->keystate == ButtomState::EReleased && last->keystate == ButtomState::EHeld) {
			//后按下的按键先释放，则释放掉first，响应last,移动状态更新为last的状态，并切换动画
			mMovState = MovState::MovHeld;
			switch (last->key) {
			case SDL_SCANCODE_W:
				mOwner->SetDir(GameObject::Dir::UP);
				movdir = Vector2::up;
				break;
			case SDL_SCANCODE_A:
				mOwner->SetDir(GameObject::Dir::LEFT);
				movdir = Vector2::left;
				break;
			case SDL_SCANCODE_S:
				mOwner->SetDir(GameObject::Dir::DOWN);
				movdir = Vector2::down;
				break;
			case SDL_SCANCODE_D:
				mOwner->SetDir(GameObject::Dir::RIGHT);
				movdir = Vector2::right;
				break;
			}

			if (movdir == Vector2::up) {
				mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("UpForward");
			}
			else if (movdir == Vector2::down) {
				mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("DownForward");
			}
			else if (movdir == Vector2::left) {
				mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("LeftForward");
			}
			else if (movdir == Vector2::right) {
				mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("RightForward");
			}

			mReqKeys.erase(first);

		}
		else if (first->keystate == ButtomState::EHeld && last->keystate == ButtomState::EReleased) {
			//先按下的键先释放，状态不变
			mReqKeys.erase(last);
		}
		else if (first->keystate == ButtomState::EHeld && last->keystate == ButtomState::EHeld) {
			//两个按键都是按住的状态，按原则响应后按下的
			if (mMovState == MovState::MovStart)
				mMovState = MovState::MovHeld;
			switch (first->key) {
			case SDL_SCANCODE_W:
				mOwner->SetDir(GameObject::Dir::UP);
				movdir = Vector2::up;
				break;
			case SDL_SCANCODE_A:
				mOwner->SetDir(GameObject::Dir::LEFT);
				movdir = Vector2::left;
				break;
			case SDL_SCANCODE_S:
				mOwner->SetDir(GameObject::Dir::DOWN);
				movdir = Vector2::down;
				break;
			case SDL_SCANCODE_D:
				mOwner->SetDir(GameObject::Dir::RIGHT);
				movdir = Vector2::right;
				break;
			}
		}
	}
}


void GameFrame::MoveComponent::update()
{
	if (mMovState == MovState::Idle) {
		return;
	}
	else if (mMovState == MovState::MovStart) {
		if (movdir == Vector2::up) {
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("UpForward");
		}
		else if (movdir == Vector2::down) {
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("DownForward");
		}
		else if (movdir == Vector2::left) {
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("LeftForward");
		}
		else if (movdir == Vector2::right) {
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("RightForward");
		}
		
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + movdir * Speed;
		mOwner->SetPosition(newpos);
		CollisionComponent* coll = mOwner->GetComponent<CollisionComponent>();
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		coll->OnUpdateWorldTransform();
	}
	else if (mMovState == MovState::MovHeld) {
		Vector2 curpos = mOwner->GetPosition();
		Vector2 newpos = curpos + movdir * Speed;
		mOwner->SetPosition(newpos);
		CollisionComponent* coll = mOwner->GetComponent<CollisionComponent>();
		if (coll->CheckCollision()) {
			mOwner->SetPosition(curpos);
			return;
		}
		coll->OnUpdateWorldTransform();
	}
	else if (mMovState == MovState::MovStop) {
		mOwner->GetComponent<AnimSpriteComponent>()->StopPlay();
		switch(mOwner->GetDir()) {
		case GameObject::Dir::UP:
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("UpIdle");
			break;
		case GameObject::Dir::DOWN:
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("DownIdle");
			break;
		case GameObject::Dir::LEFT:
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("LeftIdle");
			break;
		case GameObject::Dir::RIGHT:
			mOwner->GetComponent<AnimSpriteComponent>()->PlayAnimation("RightIdle");
			break;
		}
	}
}