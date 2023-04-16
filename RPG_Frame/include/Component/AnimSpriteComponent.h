#ifndef __AnimSpriteComponent__
#define __AnimSpriteComponent__
#include	<unordered_map>
#include	"SpriteComponent.h"
#include	"Math2.h"

namespace GameFrame {
	class GameObject;

	typedef struct Anim {
		SDL_Texture* mAnimTextures;//帧集成图
		int frame;//帧数，用于确定集成图被切割成几帧
		bool IsLoopPlay;//是否循环播放
		Vector2 AnimPosInTex;
		float mAnimFPS;//动画播放速率，一秒钟放多少帧
		int textureW;
		int textureH;
		Anim(SDL_Texture* tex,int frame,bool isplay,Vector2 pos,int fps, int w, int h):
			mAnimTextures(tex),
			frame(frame),
			IsLoopPlay(isplay),
			AnimPosInTex(pos),
			mAnimFPS(fps),
			textureW(w),
			textureH(h)
		{}
	}Anim;
	class AnimSpriteComponent : public SpriteComponent {
	public:
		AnimSpriteComponent(GameObject* gameobject, int draworder);
		~AnimSpriteComponent();
		void AddAnimation(Anim* anim, const std::string& name);
		void PlayAnimation(const std::string& name);
		void StopPlay();//停止当前播放的动画
		void PausePlay();
		void Draw(SDL_Renderer* renderer) override;

		void SetCurrFrame(int cf);
		int GetCurrFrame();
		void SetFPS(int fps);
		int GetFPS();

	private:
		std::unordered_map<std::string, Anim*>	mAnims;
		Anim* PlayingAnim;
		int mCurrFrame;
		bool IsPause;
	};
}
#endif __AnimSpriteComponent__ 