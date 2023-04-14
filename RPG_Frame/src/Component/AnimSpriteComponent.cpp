#include	"AnimSpriteComponent.h"
#include	"GameObject.h"
#include	"DEFINES.h"
GameFrame::AnimSpriteComponent::AnimSpriteComponent(GameObject* gameobject, int draworder):
	mCurrFrame(0),
	PlayingAnim(nullptr),
	IsPause(false),
	SpriteComponent(gameobject, draworder)
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
	PlayingAnim = mAnims.find(name)->second;
}

void GameFrame::AnimSpriteComponent::StopPlay()
{
	PlayingAnim = nullptr;
}

void GameFrame::AnimSpriteComponent::PausePlay()
{
	IsPause = !IsPause;
}

void GameFrame::AnimSpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (PlayingAnim == nullptr)
		return;
	//取出帧所在位置
	int textureW = PlayingAnim->textureW;
	int textureH = PlayingAnim->textureH;
	SDL_Rect imageRect{ PlayingAnim->AnimPosInTex.x + mCurrFrame * textureW,PlayingAnim->AnimPosInTex.y,textureW ,textureH };
	//帧渲染位置
	int x = mOwner->GetPosition().x;
	int y = mOwner->GetPosition().y;
	SDL_Rect dstRect{ x, y,textureW ,textureH };
	SDL_RenderCopy(renderer, PlayingAnim->mAnimTextures, &imageRect, &dstRect);
	if (!IsPause) {
		mCurrFrame++;
	}
	if (PlayingAnim->IsLoopPlay) {
		mCurrFrame = mCurrFrame % PlayingAnim->frame;
	}
	else if (mCurrFrame > PlayingAnim->frame) {
		return;
	}
}

