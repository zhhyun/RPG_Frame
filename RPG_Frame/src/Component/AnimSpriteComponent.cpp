#include	"AnimSpriteComponent.h"
#include	"GameObject.h"
#include	"Game.h"
#include	"DEFINES.h"
GameFrame::AnimSpriteComponent::AnimSpriteComponent(GameObject* gameobject, int draworder):
	mCurrFrame(0),
	PlayingAnim(nullptr),
	PlayingAnimName("��"),
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
	//ȡ��֡����λ��

	Uint32 deltaTime = SDL_GetTicks() - mOwner->GetGame()->GetAnimTicks();
	//FPS����Ϊ-1�����Ǿ�̬ͼƬ������Ҫ���Ŷ���
	if (PlayingAnim->mAnimFPS != -1 || IsPause || IsOver) {
		float fm = (1 / PlayingAnim->mAnimFPS) * 1000.0f;
		//AnimTicks��¼������һ�λ��Ƶ�ʱ�䣬���λ��ƺ���һ�λ��Ƶ�ʱ�����1/AnimFPSʱ���ٻ���һ��
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
	//֡��Ⱦλ��
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

