#include	"InputSystem.h"
#include	<string>

bool GameFrame::InputSystem::Initialize()
{
	memset(mState.keyborad.mPrevState, 0, SDL_NUM_SCANCODES);//SDL_NUM_SCANCODES���������ֽ���
	mState.keyborad.mCurrState = SDL_GetKeyboardState(NULL);
	return true;
}

void GameFrame::InputSystem::ShutDown()
{
}

void GameFrame::InputSystem::PrepareUpdate()
{
	memcpy(mState.keyborad.mPrevState, 
		mState.keyborad.mCurrState,
		SDL_NUM_SCANCODES);
}

void GameFrame::InputSystem::update()
{
	SDL_GetKeyboardState(NULL);
}

bool GameFrame::KeyboradState::GetKeyValue(SDL_Scancode keycode) const
{
	return mCurrState[keycode];
}

GameFrame::ButtomState GameFrame::KeyboradState::GetKeyState(SDL_Scancode keycode) const
{
	if (mCurrState[keycode]) {
		if (mPrevState[keycode])
			return ButtomState::EHeld;
		else
			return ButtomState::EPressed;
	}
	else {
		if (mPrevState[keycode])
			return ButtomState::EReleased;
		else
			return ButtomState::ENone;
	}
}
