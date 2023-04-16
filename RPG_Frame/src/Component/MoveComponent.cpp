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
	Speed(5),
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
//			//���⾯�棺��һ�ΰ�������4��
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
		/*if (keystate[SDL_SCANCODE_W]) {
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
		}*/
}

void GameFrame::MoveComponent::ProcessInput(const InputSystem* keystate)
{
	//���ݰ�ť״̬�������ƶ�Ҳ�������������ֹ����ʼ�ƶ��������ƶ���ֹͣ�ƶ�
	ButtomState W = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_W);
	ButtomState A = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_A);
	ButtomState S = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_S);
	ButtomState D = keystate->GetState().keyborad.GetKeyState(SDL_SCANCODE_D);
	SDL_Log("%d", W);
	//�����˶���״̬
	if ((W == ButtomState::ENone) &&
		(S == ButtomState::ENone) &&
		(A == ButtomState::ENone) &&
		(D == ButtomState::ENone)) {
		if (mMovState != MovState::Idle) {
			mMovState = MovState::Idle;
		}
		return;
	}

	//��ֻ�ܰ��˶�״̬�����ɾ����Ӧ���У�Ȼ�����ж�������Ӧ�İ�����������״̬��
	//���˶����˶������ؽ׶�
	//������°����������Ӧ����,����������Ӧ˳��WASD
	if (W == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_W , W };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//����ظ�����
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
			mReqKeys.pop_back();//�Ƚ��ȳ�
		}
	}
	if (A == ButtomState::EPressed) {
		KeyQueSate kqs = { SDL_SCANCODE_A , A };
		if (mReqKeys.size() == 0) {
			mReqKeys.insert(mReqKeys.begin(), 1, kqs);
		}
		else {
			//����ظ�����
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
			//����ظ�����
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
			//����ظ�����
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

	//�����סor�ɿ��������������Ӧ���������İ���״̬
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

	//�ж����ﵱǰ�˶�״̬�����µ����Ա��
	if (mReqKeys.size() == 1) //�����ǰֻ����һ������
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

	else if (mReqKeys.size() == 2) //�����ǰ������������״̬//��������Ҳ����״̬��������ִ�����Ӧ���¼���Ҫ�Ѹð�����Ϣ��������ɾ��
	{
		/*��Ӧ����
		* 1 ֻ��Ӧ�������˵ļ���
		* 2 ������Ӧ����״̬�ļ���
		�����ڰ��°���ʱ��������Զ���ӵ��������ˣ�����ֻ��Ӧ�����׼�����ܱ�֤����ʵ�֣�
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
			//���µİ������ͷţ����ͷŵ�first����Ӧlast,�ƶ�״̬����Ϊlast��״̬�����л�����
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
			//�Ȱ��µļ����ͷţ�״̬����
			mReqKeys.erase(last);
		}
		else if (first->keystate == ButtomState::EHeld && last->keystate == ButtomState::EHeld) {
			//�����������ǰ�ס��״̬����ԭ����Ӧ���µ�
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

