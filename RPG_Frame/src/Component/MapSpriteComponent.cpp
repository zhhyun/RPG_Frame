#include	"MapSpriteComponent.h"
#include	"MapObject.h"
#include	"Game.h"

GameFrame::MapSpriteComponent::MapSpriteComponent(GameObject* mapobject, int draworder, const char* fileName):
	SpriteComponent(mapobject, draworder)
{
	ReadMap(fileName);
}

GameFrame::MapSpriteComponent::~MapSpriteComponent()
{
}

void GameFrame::MapSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// 贴图即将被绘制的位置
	int textureW = 32;
	int textureH = 32;

	//扫描容器，将每一个元素在其位置打印出来
	for (auto iter : mElems) {
		mTexture = mTextures.find(iter->tex)->second;
		SDL_QueryTexture(mTexture, nullptr, nullptr, &textureW, &textureH);
		SDL_Rect imageRect{ 0,0,textureW,textureH };
		SDL_Rect dstRect{ iter->vec.x, iter->vec.y, textureW, textureH };

		SDL_RenderCopy(renderer, mTexture, &imageRect, &dstRect);
	}

}

void GameFrame::MapSpriteComponent::ReadMap(const char* fileName)
{
	std::ifstream readfile;
	readfile.open(fileName, std::ios_base::in);
	std::string str;
	while (std::getline(readfile, str)) {
		if (str == "<Texture>") {
			while (1) {
				readfile >> str; 
				if (str == "<Texture/>")
					break;
				LoadTexture(str);//如果<Texture>的下一行不是终止符，那默认下一行取到的是图片名称tile，所以COV符只能跟在图片名称后面，前面不能没有图片名称
				while (1) {
					
					Vector2 vec;
					readfile >> vec.x ;//处理数据，一行保存一个坐标
					if (vec.x == -9876) {
						break;
					}
					readfile >> vec.y;
					Elem* e = new Elem();
					e->tex = str;
					e->vec = vec;
					mElems.emplace_back(e);
				}
			}
		}
	}
	
}
