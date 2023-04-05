#include "InputComponent.h"
#include "MoveComponent.h"
#include	"GameObject.h"
#include	<SDL.h>

GameFrame::InputComponent::InputComponent(class GameObject* gameobject) :
	IsMain(false),
	RequestComp(NULL),
	Component(gameobject)
{
}

//����ʱ�ǵõ�Ӣ�����뷨
void GameFrame::InputComponent::ProcessInput(const uint8_t* keystate)
{
	if (IsMain) {
		//��ֵΪ1�����͸�������Ӧ�����
		RequestComp->ProcessInput(keystate);	
	}
	else {
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D]) {
			GetGameObject()->GetComponent<MoveComponent>()->ProcessInput(keystate);
		}
		else if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_X]) {
		}
		
	}
}

