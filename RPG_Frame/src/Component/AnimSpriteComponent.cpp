#include	"AnimSpriteComponent.h"
#include	"GameObject.h"
#include	"Game.h"
#include	"DEFINES.h"
GameFrame::AnimSpriteComponent::AnimSpriteComponent(GameObject* gameobject, int draworder):
	mCurrFrame(0),
	PlayingAnim(nullptr),
	PlayingAnimName("空"),
	IsPause(false),
	IsOver(false),
	Component(gameobject)
{
}

GameFrame::AnimSpriteComponent::~AnimSpriteComponent()
{
}

void GameFrame::AnimSpriteComponent::AddAnimation(Anim* anim, const std::string& name)
{
	mAnims.emplace(name, anim);
}

void GameFrame::AnimSpriteComponent::PlayAnimation(const std::string& name)
{
	IsOver = false;
	IsPause = false;
	mCurrFrame = 0;
	PlayingAnim = mAnims.find(name)->second;
	PlayingAnimName = name;
}

void GameFrame::AnimSpriteComponent::StopPlay()
{
	mCurrFrame = 0;
	IsOver = true;
}

void GameFrame::AnimSpriteComponent::PausePlay()
{
	IsPause = !IsPause;
}

void GameFrame::AnimSpriteComponent::Draw(SDL_Renderer* renderer)
{ 
	if (PlayingAnim == 0)
		return;
	//取出帧所在位置

	Uint32 deltaTime = SDL_GetTicks() - mOwner->GetGame()->GetAnimTicks();
	//FPS设置为-1代表是静态图片，不需要播放动画
	if (PlayingAnim->mAnimFPS != -1 || IsPause || IsOver) {
		float fm = (1 / PlayingAnim->mAnimFPS) * 1000.0f;
		//AnimTicks记录的是上一次绘制的时间，本次绘制和上一次绘制的时间大于1/AnimFPS时才再绘制一次
		if (deltaTime >= fm && (!IsPause)) {
			mCurrFrame++;

			if (PlayingAnim->IsLoopPlay) {
				mCurrFrame = mCurrFrame % PlayingAnim->frame;
			}
			else if (mCurrFrame == PlayingAnim->frame) {
				IsOver = true;
				mCurrFrame--;
			}
			mOwner->GetGame()->SetAnimTicks(SDL_GetTicks());
		}
	}
	
	int textureW = PlayingAnim->textureW;
	int textureH = PlayingAnim->textureH;
	SDL_Rect imageRect{ PlayingAnim->AnimPosInTex.x + mCurrFrame * textureW,PlayingAnim->AnimPosInTex.y,textureW ,textureH };
	//帧渲染位置
	int x = mOwner->GetPosition().x;
	int y = mOwner->GetPosition().y;
	SDL_Rect dstRect{ x, y,textureW ,textureH };
	SDL_RenderCopy(renderer, PlayingAnim->mAnimTextures, &imageRect, &dstRect);	
}

void GameFrame::AnimSpriteComponent::SetFPS(int fps)
{
	if (PlayingAnim) {
		PlayingAnim->mAnimFPS = fps;
	}
}

int GameFrame::AnimSpriteComponent::GetFPS()
{
	if (PlayingAnim) {
		return PlayingAnim->mAnimFPS;
	}
}

