#include "BattleComponent.h"
#include "PlayerObject.h"
#include "NpcObject.h"
#include "InputComponent.h"
GameFrame::BattleComponent::BattleComponent(GameObject* gameobject):
	IsWaiting(false),
	Choose(0),
	Component(gameobject)
{
}

GameFrame::BattleComponent::~BattleComponent()
{
}

void GameFrame::BattleComponent::ProcessInput(const uint8_t* keystate)
{
	if (IsWaiting) {
		return;
	}
	else {
		if (keystate[SDL_SCANCODE_1]) {
			SetChoose(1);
		}
		else if(keystate[SDL_SCANCODE_2]) {
			SetChoose(2);
		}
		else if (keystate[SDL_SCANCODE_3]) {
			SetChoose(3);
		}
		else if (keystate[SDL_SCANCODE_4]) {
			SetChoose(4);
		}
	}
	
}

void GameFrame::BattleComponent::combat(PlayerObject* a, NpcObject* b)
{
	BattleComponent* a_com = a->GetComponent<BattleComponent>();
	BattleComponent* b_com = b->GetComponent<BattleComponent>();
	BattleInint(b);
	while (a->GetHp() != 0 && b->GetHp() != 0) {
		a_com->PlayerDecision();
		SetWaiting(true);
		b_com->NpcDecision();
		SetWaiting(false);
	}
	BattleFin(b);
}

void GameFrame::BattleComponent::PlayerDecision()
{
	if (GetChoose() == 0) {
		PlayerDecision();
	}
	else {
		switch (GetChoose())
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;

			SetChoose(0);
		}
	}
	
}

void GameFrame::BattleComponent::NpcDecision()
{
}

int GameFrame::BattleComponent::BattleInint(NpcObject* b)
{
	if (mGameObject->GetBattleState() == 1) {
		return 0;
	}
	else {
		mGameObject->SetBattleSate(true);
		b->SetBattleSate(true);
		InputComponent* temp = mGameObject->GetComponent<InputComponent>();
		temp->SetRequestCom(this);
		temp->SetIsMain(true);
	}
	return 0;
}

void GameFrame::BattleComponent::BattleFin(NpcObject* b)
{
	mGameObject->SetBattleSate(false);
	b->SetBattleSate(false);
	InputComponent* temp = mGameObject->GetComponent<InputComponent>();
	temp->SetRequestCom(nullptr);
	temp->SetIsMain(false);
}

void GameFrame::BattleComponent::SetWaiting(bool set)
{
	IsWaiting = set;
}

bool GameFrame::BattleComponent::GetWaiting()
{
	return IsWaiting;
}

void GameFrame::BattleComponent::SetChoose(int choose)
{
	Choose = choose;
}

int GameFrame::BattleComponent::GetChoose()
{
	return Choose;
}
