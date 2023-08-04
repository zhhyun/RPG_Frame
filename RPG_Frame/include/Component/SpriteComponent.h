#ifndef __SpriteComponent__
#define __SpriteComponent__
#include	"Component.h"
#include	<string>
#include	"Math2.h"
//一个精灵组件只渲染一张图片
namespace GameFrame {
	class GameObject;
	class Texture;
	class SpriteComponent : public Component {
	public:
		SpriteComponent(GameObject *gameobject, int draworder);
		~SpriteComponent(); 
		virtual void Draw(SDL_Renderer* renderer);
		void LoadTexture(std::string& fileName);//将贴图装载到容器中
		Texture* GetTexture(){ return mTexture; };
		void SetImageDst(Vector2 Dst) { imageDst = Dst; };
		void SetDrawTexWH(Vector2 WH) { DrawTexWH = WH; };

	protected:
		Texture* mTexture;
		int mDrawOrder;
		//注意，往往导入的图片资源是集成的，需要给定要裁出的零件位置和大小。默认是图片本身大小.
		Vector2 DrawTexWH;
		Vector2 imageDst;
	};
}
#endif __SpriteComponent__