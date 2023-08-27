#include	"CollisionComponent.h"

GameFrame::CollisionComponent::CollisionComponent(GameObject* gameobject):
	IsUpdateFromObject(true),
	Component(gameobject)
{
}

GameFrame::CollisionComponent::~CollisionComponent()
{
}

//GameFrame::CollisionComponent::~CollisionComponent()
//{
//	PhysWorld->RemoveRigid(this);
//}
//
//void GameFrame::CollisionComponent::CreateShape(Shape* shape)
//{
//	for (auto iter : mShapes) {
//		if (iter == shape) {
//			return ;
//		}
//	}
//	mShapes.emplace_back(shape);
//	return ;
//}



bool GameFrame::CollisionComponent::CheckCollision()
{
	auto map = dynamic_cast<PlayerObject*> (mOwner)->GetMapObject();
	if (map) {
		//获得碰撞区域的四个顶点，从左到右从上到下分别是ABCD
		Vector2 PosA = GetCollisionPosA(); 
		Vector2 PosB(PosA.x + CollisionArea.w, PosA.y);
		Vector2 PosC(PosA.x, PosA.y + CollisionArea.h);
		Vector2 PosD(PosB.x, PosC.y);

		std::vector<Tile> tileABCD;
		tileABCD.emplace_back(map->GetStandTileFromLayer(PosA));
		tileABCD.emplace_back(map->GetStandTileFromLayer(PosB));
		tileABCD.emplace_back(map->GetStandTileFromLayer(PosC));
		tileABCD.emplace_back(map->GetStandTileFromLayer(PosD));

		for (auto& tile : tileABCD) {
			for (const auto& iter : tile.mProperties) {
				if (iter.Name == "c") {
					return true;
				}
			}
		}
		return false;
	}
	return false;
}

void GameFrame::CollisionComponent::update()
{
	if (IsUpdateFromObject) {
		//mOwner->GetPosition();
	}
}
void GameFrame::CollisionComponent::SetCollisionArea(SDL_Rect area)
{
	CollisionArea = area;
}

void GameFrame::CollisionComponent::DefinecallbackOnCollision(CallbackFunction callback)
{
	callbackOnCollision = callback;
}

GameFrame::Vector2 GameFrame::CollisionComponent::GetAreaPos()
{
	Vector2 pos;
	Vector2 Objpos;
	auto map = dynamic_cast<PlayerObject*>(mOwner)->GetMapObject();

	if (map) {
		//调整位置
		Objpos.x = std::round(mOwner->GetPosition().x / map->GettileW()) * map->GettileW();
		Objpos.y = std::round(mOwner->GetPosition().y / map->GettileH()) * map->GettileH();

		pos.x = CollisionArea.x + Objpos.x;
		pos.y = CollisionArea.y + Objpos.y;
	}

	return pos;
}

GameFrame::Vector2 GameFrame::CollisionComponent::GetCollisionPosA()
{
	Vector2 PosA = mOwner->GetPosition();
	PosA.x += CollisionArea.x;
	PosA.y += CollisionArea.y;
	return PosA;
}

//GameFrame::Shape::Shape(CollisionComponent* RigidBody):
//	mRigidBody(RigidBody)
//{
//}

//void GameFrame::Shape::updateFromObject()
//{
//}
//
//GameFrame::RectShape::RectShape(CollisionComponent* RigidBody, float x, float y, int w, int h):
//	Shape(RigidBody),
//	shape_pos(x,y),
//	wdith(w),
//	height(h)
//{
//}
//
//void GameFrame::RectShape::updateFromObject()
//{
//	shape_pos = mRigidBody->GetGameObject()->GetPosition();
//}
