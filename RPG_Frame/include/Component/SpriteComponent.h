#ifndef __SpriteComponent__
#define __SpriteComponent__
#include	"Component.h"
#include	<string>
#include	"Math2.h"
//һ���������ֻ��Ⱦһ��ͼƬ
namespace GameFrame {
	class GameObject;
	class Texture;
	class SpriteComponent : public Component {
	public:
		SpriteComponent(GameObject *gameobject, int draworder);
		~SpriteComponent(); 
		virtual void Draw(SDL_Renderer* renderer);
		void LoadTexture(std::string& fileName);//����ͼװ�ص�������
		Texture* GetTexture(){ return mTexture; };
		void SetImageDst(Vector2 Dst) { imageDst = Dst; };
		void SetDrawTexWH(Vector2 WH) { DrawTexWH = WH; };

	protected:
		Texture* mTexture;
		int mDrawOrder;
		//ע�⣬���������ͼƬ��Դ�Ǽ��ɵģ���Ҫ����Ҫ�ó������λ�úʹ�С��Ĭ����ͼƬ�����С.
		Vector2 DrawTexWH;
		Vector2 imageDst;
	};
}
#endif __SpriteComponent__