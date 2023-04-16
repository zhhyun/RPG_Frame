#ifndef __AnimSpriteComponent__
#define __AnimSpriteComponent__
#include	<unordered_map>
#include	"SpriteComponent.h"
#include	"Math2.h"

namespace GameFrame {
	class GameObject;

	typedef struct Anim {
		SDL_Texture* mAnimTextures;//֡����ͼ
		int frame;//֡��������ȷ������ͼ���и�ɼ�֡
		bool IsLoopPlay;//�Ƿ�ѭ������
		Vector2 AnimPosInTex;
		float mAnimFPS;//�����������ʣ�һ���ӷŶ���֡
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
		void StopPlay();//ֹͣ��ǰ���ŵĶ���
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