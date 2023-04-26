#include	"InputSystem.h"
#include	<string>

bool GameFrame::InputSystem::Initialize()
{
	memset(mState.keyborad.mPrevState, 0, SDL_NUM_SCANCODES);//SDL_NUM_SCANCODES参数代表字节数
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
	mState.mouse.mPrevState = mState.mouse.mCurrState;
}

void GameFrame::InputSystem::update()
{
	SDL_GetKeyboardState(NULL);
	int x = 0, y = 0;
	mState.mouse.mCurrState = SDL_GetMouseState(&x, &y);
	mState.mouse.mMousePos.x = static_cast<float>(x);
	mState.mouse.mMousePos.y = static_cast<float>(y);
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
