#include	"CollisionComponent.h"
#include	"GameObject.h"
#include	"MapObject.h"

GameFrame::CollisionComponent::CollisionComponent(GameObject* gameobject):
	Component(gameobject)
{
	//Ĭ����ײ�����ǰ󶨶���Ĵ�С
	SetCollision(mGameObject->GetPosition(), 64, 64);
}

GameFrame::CollisionComponent::~CollisionComponent()
{
}

void GameFrame::CollisionComponent::SetCollision(Vector2 vec, int h, int w)
{
	SDL_Rect* tmp = new SDL_Rect{ vec.x,vec.y,w,h };
	mCollision = tmp;
	//delete tmp;
}

int GameFrame::CollisionComponent::CheckCollision()
{ 
	MapObject* map = dynamic_cast<ActorObject*>(mGameObject)->mMap;
	int x0 = mGameObject->GetPosition().x;
	int y0 = mGameObject->GetPosition().y;
	int h0 = mCollision->h;
	int w0 = mCollision->w;

	for (auto iter : map->mMapObjects) {
		//�����ȡ����ײ���
		if (iter->GetComponent<CollisionComponent>()) {
			CollisionComponent* cc = iter->GetComponent<CollisionComponent>();
			//�����ȡ������������Լ�,������ײ
			if (cc != this) {
				int x1 = cc->mCollision->x;
				int y1 = cc->mCollision->y;
				int h1 = cc->mCollision->h;
				int w1 = cc->mCollision->w;
				//������ײԭ�����������ε�x���y��ͬʱ�ص�ʱ���������β���ײ��ֻҪ��һ������룬��û�з�����ײ
				if (x0 > x1) {
					//�ȼ��y����룬��������ײ�������λ��
					if ((x0 + w0 - x1) >= (w0 + w1)) {
						return 0;
					}
				}
				else{
					if ((x1 + w1 - x0) >= (w0 + w1)) {
						return 0;
					}
				}
				if (y0 > y1) {
					//���x�����
					if ((y0 + y0 - y1) >= (h0 + h1)) {
						return 0;
					}
				}
				else {
					if ((y1 + h1 - y0) >= (h0 + h1)) {
						return 0;
					}
				}
				return 1;
			}
		}
		
	}
}

void GameFrame::CollisionComponent::update()
{
	//������ײ����λ��
	SetCollision(mGameObject->GetPosition(), 64, 64);
}
