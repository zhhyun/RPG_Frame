#include	"CollisionComponent.h"
#include	"GameObject.h"
#include	"MapObject.h"
#include	"PhysSpace.h"
#include	"Game.h"

GameFrame::CollisionComponent::CollisionComponent(GameObject* gameobject):
	IsUpdateFromObject(true),
	Component(gameobject)
{//默认碰撞区间是绑定对象的大小
	SetCollision(mOwner->GetPosition(), 64, 64);
	PhysWorld = mOwner->GetGame()->GetPhysSpace();
	ResignInPhysSpace();
}

GameFrame::CollisionComponent::~CollisionComponent()
{
	PhysWorld->RemoveRigid(this);
}

void GameFrame::CollisionComponent::CreateShape(Shape* shape)
{
	for (auto iter : mShapes) {
		if (iter == shape) {
			return ;
		}
	}
	mShapes.emplace_back(shape);
	return ;
}

void GameFrame::CollisionComponent::SetCollision(Vector2 vec, int h , int w )
{
	mCollision.x = vec.x;
	mCollision.y = vec.y;
	mCollision.w = w;
	mCollision.h = h;
}

void GameFrame::CollisionComponent::SetCollision(Vector2 vec)
{
	mCollision.x = vec.x;
	mCollision.y = vec.y;
}

int GameFrame::CollisionComponent::CheckCollision()
{ 
	//int x0 = mOwner->GetPosition().x;
	//int y0 = mOwner->GetPosition().y;
	//int h0 = mCollision.h;
	//int w0 = mCollision.w;

	//if (PhysWorld == NULL) {
	//	return 0;
	//}
	//	
	//for (auto iter : PhysWorld->Rigids) {
	//	//如果获取到的组件不是自己,则检测碰撞
	//	if (iter != this) {
	//			int x1 = iter->mCollision.x;
	//			int y1 = iter->mCollision.y;
	//			int h1 = iter->mCollision.h;
	//			int w1 = iter->mCollision.w;
	//			//矩形碰撞原理：当两个矩形的x轴和y轴同时重叠时，两个矩形才碰撞；只要有一个轴分离，就没有发生碰撞
	//			if (x0 > x1) {
	//				//先检查y轴分离，看两个碰撞区域相对位置
	//				if ((x0 + w0 - x1) >= (w0 + w1)) {
	//					return 0;
	//				}
	//			}
	//			else{
	//				if ((x1 + w1 - x0) >= (w0 + w1)) {
	//					return 0;
	//				}
	//			}
	//			if (y0 > y1) {
	//				//检查x轴分离
	//				if ((y0 + h0 - y1) >= (h0 + h1)) {
	//					return 0;
	//				}
	//			}
	//			else {
	//				if ((y1 + h1 - y0) >= (h0 + h1)) {
	//					return 0;
	//				}
	//			}
	//			return 1;
	//		}
	//	}	
}

void GameFrame::CollisionComponent::update()
{
	if (IsUpdateFromObject) {
		for (auto iter : mShapes) {
			iter->updateFromObject();
		}
	}
}

//void GameFrame::CollisionComponent::OnUpdateWorldTransform()
//{
//	if (IsUpdateFromObject) {
//		SetCollision(mOwner->GetPosition());
//	}
//}

void GameFrame::CollisionComponent::ResignInPhysSpace()
{
	PhysWorld->AddRigid(this);
}

GameFrame::Shape::Shape(CollisionComponent* RigidBody):
	mRigidBody(RigidBody)
{
}

void GameFrame::Shape::updateFromObject()
{
}

GameFrame::RectShape::RectShape(CollisionComponent* RigidBody, float x, float y, int w, int h):
	Shape(RigidBody)
{
	shape_pos.x = x;
	shape_pos.y = y;
	wdith = w;
	height = h;
}

void GameFrame::RectShape::updateFromObject()
{
	shape_pos = mRigidBody->GetGameObject()->GetPosition();
}
