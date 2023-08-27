//#include	"PhysSpace.h"
//#include	"CollisionComponent.h"
//
//GameFrame::PhysSpace::PhysSpace(Game* game):
//	mGame(game)
//{
//}
//
//void GameFrame::PhysSpace::RegisterCollisionComponent(CollisionComponent* rigid)
//{
//	if (Rigids.size() != 0) {
//		for (auto rgd : Rigids) {
//			if (rigid == rgd) {
//				return;
//			}
//		}
//	}
//	Rigids.emplace_back(rigid);
//}
//
//void GameFrame::PhysSpace::RemoveRigid(CollisionComponent* rigid)
//{
//	auto iter = std::find(Rigids.begin(), Rigids.end(), rigid);
//	if (iter != Rigids.end()) {
//		std::iter_swap(iter, Rigids.end() - 1);
//		//破坏顺序删除队尾
//		Rigids.pop_back();
//	}
//}
//
//void GameFrame::PhysSpace::ReleaseSpace()
//{
//	Rigids.clear();
//}
//
//void GameFrame::PhysSpace::Update()
//{
//	//更新位置，检查碰撞
//	for (size_t i = 0; i < Rigids.size(); ++i) {
//		CollisionComponent* componentA = Rigids[i];
//		for (size_t j = i + 1; j < Rigids.size(); ++j) {
//			CollisionComponent* componentB = Rigids[j];
//			CheckCollisionsBetweenComponents(componentA, componentB);
//		}
//	}
//	
//}
//
//
////int GameFrame::PhysSpace::CheckCollisionBetweenShapes(Shape* shapeA, Shape* shapeB)
////{
//	//int x0 = mOwner->GetPosition().x;
//	//	int y0 = mOwner->GetPosition().y;
//	//	int h0 = mCollision.h;
//	//	int w0 = mCollision.w;
//	//
//	//	if (PhysWorld == NULL) {
//	//		return 0;
//	//	}
//	//		
//	//	for (auto iter : PhysWorld->Rigids) {
//	//		//如果获取到的组件不是自己,则检测碰撞
//	//		if (iter != this) {
//	//				int x1 = iter->mCollision.x;
//	//				int y1 = iter->mCollision.y;
//	//				int h1 = iter->mCollision.h;
//	//				int w1 = iter->mCollision.w;
//	//				//矩形碰撞原理：当两个矩形的x轴和y轴同时重叠时，两个矩形才碰撞；只要有一个轴分离，就没有发生碰撞
//	//				if (x0 > x1) {
//	//					//先检查y轴分离，看两个碰撞区域相对位置
//	//					if ((x0 + w0 - x1) >= (w0 + w1)) {
//	//						return 0;
//	//					}
//	//				}
//	//				else{
//	//					if ((x1 + w1 - x0) >= (w0 + w1)) {
//	//						return 0;
//	//					}
//	//				}
//	//				if (y0 > y1) {
//	//					//检查x轴分离
//	//					if ((y0 + h0 - y1) >= (h0 + h1)) {
//	//						return 0;
//	//					}
//	//				}
//	//				else {
//	//					if ((y1 + h1 - y0) >= (h0 + h1)) {
//	//						return 0;
//	//					}
//	//				}
//	//				return 1;
//	//			}
//	//		}
////}
//
//template <typename ShapeTypeA, typename ShapeTypeB> bool CheckCollisionBetweenShapes(ShapeTypeA& shapeA, ShapeTypeB& shapeB) {
//	// 默认实现，当形状类型不匹配时会调用该函数
//	return true;
//}
//
//// 特化函数模板，处理特定形状类型的碰撞检测算法
//template <> bool CheckCollisionBetweenShapes<GameFrame::RectShape, GameFrame::RectShape>(GameFrame::RectShape& shapeA, GameFrame::RectShape& shapeB) {
//	auto coll = shapeA.GetRigid();
//	
//	int x0 = coll->GetGameObject()->GetPosition().x;
//	int y0 = coll->GetGameObject()->GetPosition().y;
//	int h0 = shapeA.GetHeight();
//	int w0 = shapeA.GetWdith();
//
//	int x1 = shapeB.GetShapePos().x;
//	int y1 = shapeB.GetShapePos().y;
//	int h1 = shapeB.GetHeight();
//	int w1 = shapeB.GetWdith();
//
//	//矩形碰撞原理：当两个矩形的x轴和y轴同时重叠时，两个矩形才碰撞；只要有一个轴分离，就没有发生碰撞
//	if (x0 > x1) {
//		//先检查y轴分离，看两个碰撞区域相对位置
//		if ((x0 + w0 - x1) >= (w0 + w1)) {
//			return 0;
//		}
//	}
//	else {
//		if ((x1 + w1 - x0) >= (w0 + w1)) {
//			return 0;
//		}
//	}
//	if (y0 > y1) {
//		//检查x轴分离
//		if ((y0 + h0 - y1) >= (h0 + h1)) {
//			return 0;
//		}
//	}
//	else {
//		if ((y1 + h1 - y0) >= (h0 + h1)) {
//			return 0;
//		}
//	}
//	return 1;
//
//}
//
//
////int GameFrame::PhysSpace::CheckCollisionBetweenShapes(RectShape* shapeA, RectShape* shapeB)
////{
////	auto coll = shapeA->GetRigid();
////
////	int x0 = coll->mOwner->GetPosition().x;
////	int y0 = coll->mOwner->GetPosition().y;
////	int h0 = shapeA->GetHeight();
////	int w0 = shapeA->GetWdith();
////
////	int x1 = shapeB->GetShapePos().x;
////	int y1 = shapeB->GetShapePos().y;
////	int h1 = shapeB->GetHeight();
////	int w1 = shapeB->GetWdith();
////	
////	//矩形碰撞原理：当两个矩形的x轴和y轴同时重叠时，两个矩形才碰撞；只要有一个轴分离，就没有发生碰撞
////	if (x0 > x1) {
////		//先检查y轴分离，看两个碰撞区域相对位置
////		if ((x0 + w0 - x1) >= (w0 + w1)) {
////			return 0;
////		}
////	}
////	else {
////		if ((x1 + w1 - x0) >= (w0 + w1)) {
////			return 0;
////		}
////	}
////	if (y0 > y1) {
////		//检查x轴分离
////		if ((y0 + h0 - y1) >= (h0 + h1)) {
////			return 0;
////		}
////	}
////	else {
////		if ((y1 + h1 - y0) >= (h0 + h1)) {
////			return 0;
////		}
////	}
////	return 1;
////
////}
//
//
//void GameFrame::PhysSpace::CheckCollisionsBetweenComponents(CollisionComponent* componentA, CollisionComponent* componentB)
//{
//	{
//		for (auto shapeA : componentA->mShapes) {
//			for (auto& shapeB : componentB->mShapes) {
//				if ( CheckCollisionBetweenShapes(shapeA, shapeB) ) {
//					// 发布碰撞事件或调用碰撞处理函数
//					SDL_Log("???");
//					componentB->callbackOnCollision;
//				}
//			}
//		}
//	}
//}
