#include	"InputComponent.h"
#include	"MoveComponent.h"
#include	"GameObject.h"
#include	<SDL.h>

GameFrame::InputComponent::InputComponent(class GameObject* gameobject) :
	IsMain(false),
	RequestComp(NULL),
	Component(gameobject)
{
}

//����ʱ�ǵõ�Ӣ�����뷨
//void GameFrame::InputComponent::ProcessInput(const SDL_Keycode key)
//{
//	if (IsMain) {
//		//��ֵΪ1�����͸�������Ӧ�����
//		RequestComp->ProcessInput(key);	
//	}
//	else {
//		if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d) {
//			GetGameObject()->GetComponent<MoveComponent>()->ProcessInput(key);
//		}
//		//else if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_X]) {
//		//}
//		
//	}
//}

void GameFrame::InputComponent::ProcessInput(const uint8_t* keystate)
{
	if (IsMain) {
		//��ֵΪ1�����͸�������Ӧ�����
		RequestComp->ProcessInput(keystate);
	}
	else {
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_S]) {
			GetGameObject()->GetComponent<MoveComponent>()->ProcessInput(keystate);
		}
	}
}

void GameFrame::InputComponent::SetRequestCom(Component* component)
{
	RequestComp = component;
}

void GameFrame::InputComponent::SetIsMain(bool is)
{
	IsMain = is;
}

