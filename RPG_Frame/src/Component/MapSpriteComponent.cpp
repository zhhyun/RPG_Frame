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
	// ��ͼ���������Ƶ�λ��
	int textureW = 32;
	int textureH = 32;

	//ɨ����������ÿһ��Ԫ������λ�ô�ӡ����
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
				LoadTexture(str);//���<Texture>����һ�в�����ֹ������Ĭ����һ��ȡ������ͼƬ����tile������COV��ֻ�ܸ���ͼƬ���ƺ��棬ǰ�治��û��ͼƬ����
				while (1) {
					
					Vector2 vec;
					readfile >> vec.x ;//�������ݣ�һ�б���һ������
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
