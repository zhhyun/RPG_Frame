#include "BattleComponent.h"
#include "PlayerObject.h"
#include "NpcObject.h"
#include "InputComponent.h"
GameFrame::BattleComponent::BattleComponent(ActorObject* gameobject):
	IsWaiting(false),
	InputBuf(0),
	Enemies(nullptr),
	Player(gameobject),
	Component(gameobject)
{
}

GameFrame::BattleComponent::~BattleComponent()
{
}

void GameFrame::BattleComponent::ProcessInput(const SDL_Keycode key)
{
	
	if (IsWaiting) {
		SDL_Log("is waiting");
		return;
	}
	if (InputBuf != 0) {
		SDL_Log("buf is full!");
		return;
	}
	else {
		switch (key) {
		case SDLK_1:
			SetBuf(1);
			break;
		case SDLK_2:
			SetBuf(2);
			break;
		case SDLK_3:
			SetBuf(3);
			break;
		case SDLK_4:
			SetBuf(4);
			break;
		}
	}
	
}

void GameFrame::BattleComponent::ProcessInput2(const uint8_t* keystate)
{
	if (IsWaiting) {
		SDL_Log("is waiting");
		return;
	}
	if (InputBuf != 0) {
		SDL_Log("buf is full!");
		return;
	}
	else {
		if(keystate[SDL_SCANCODE_1])
			SetBuf(1);
		else if(keystate[SDL_SCANCODE_2])
			SetBuf(2);
		else if(keystate[SDL_SCANCODE_3])
			SetBuf(3);
		else if(keystate[SDL_SCANCODE_4])
			SetBuf(4);
		}
}

void GameFrame::BattleComponent::combat(ActorObject* a, ActorObject* b)
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
	if (InputBuf == 0) {
		return;
	}
	else {
		SDL_Log("");
		SDL_Log("Player Action:");
		switch (InputBuf)
		{
		case 1:
			SDL_Log("Player ATTACK");
			Attack();
			SDL_Log("npc hp:%d", Enemies->GetHp());
			break;
		case 2:
			SDL_Log("DEF");
			break;
		case 3:
			SDL_Log("treat");
			break;
		case 4:
			SDL_Log("esc");
			break;

		}
		ResetBuf();
		IsWaiting = true;
	}
	
}

void GameFrame::BattleComponent::NpcDecision()
{
	SDL_Log("NPC Action:");
	SDL_Log("Npc ATTACK");
	Enemies->GetComponent<BattleComponent>()->Attack(); 
	SDL_Log("player hp:%d", Player->GetHp());
	IsWaiting = false;
	SDL_Log("NPC Action Finish!");
}

int GameFrame::BattleComponent::BattleInint(ActorObject* b)
{
	//如果已经在战斗，则返回错误
	if (Player->GetBattleState() == 1) {
		return 0;
	}
	else {
		Enemies = b;
		b->GetComponent<BattleComponent>()->SetEnemy(Player);
		//dynamic_cast<PlayerObject *>(mGameObject)->SetBattleSate(true);
		Player->SetBattleSate(true);
		Enemies->SetBattleSate(true);
		InputComponent* temp = Player->GetComponent<InputComponent>();

		//组件响应调整
		temp->SetRequestCom(this);
		temp->SetIsMain(true);
	}
	return 0;
}

void GameFrame::BattleComponent::BattleFin(ActorObject* b)
{
	Player->SetBattleSate(false);
	b->SetBattleSate(false);
	InputComponent* temp = Player->GetComponent<InputComponent>();
	temp->SetRequestCom(nullptr);
	temp->SetIsMain(false);
	SDL_Log("battle end");
}

void GameFrame::BattleComponent::SetWaiting(bool set)
{
	IsWaiting = set;
}

bool GameFrame::BattleComponent::GetWaiting()
{
	return IsWaiting;
}

void GameFrame::BattleComponent::ResetBuf()
{
	InputBuf = 0;
}

void GameFrame::BattleComponent::SetBuf(int input)
{
	InputBuf = input;
}

int GameFrame::BattleComponent::GetBuf()
{
	return InputBuf;
}

void GameFrame::BattleComponent::SetEnemy(ActorObject* b)
{
	Enemies = b;
}

bool GameFrame::BattleComponent::IsActive()
{
	if (Player->GetHp() <= 0) {
		return false;
	}
	else
		return true;
}

void GameFrame::BattleComponent::Attack()
{
	int ack = Player->GetACK();
	int en_def = Enemies->GetDEF();
	int damage = ack - en_def;
	if (damage <= 0)
		damage = 1;
	SDL_Log("hp-%d", damage);
	Enemies->AddHp(-damage);
}

void GameFrame::BattleComponent::update()
{
	if (Player->GetBattleState() == 0) {
		return;
	}
	//如果现在不是自己的回合，则调用敌人的决定函数
	//如果现在是自己的回合，则查看缓冲区看玩家有没有做出选择
	if (IsWaiting) {
		NpcDecision();
	}
	else {
		PlayerDecision();
	}
	if (!(Enemies->GetComponent<BattleComponent>()->IsActive())) {
		Enemies->SetState(GameObject::State::EDead);
		SDL_Log("enemy has died!");
		BattleFin(Enemies);
		return;
	}
	if (!IsActive()) {
		Player->SetState(GameObject::State::EDead);
		SDL_Log("you died");
		BattleFin(Enemies);
	}

}