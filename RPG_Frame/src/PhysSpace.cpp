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
//		//�ƻ�˳��ɾ����β
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
//	//����λ�ã������ײ
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
//	//		//�����ȡ������������Լ�,������ײ
//	//		if (iter != this) {
//	//				int x1 = iter->mCollision.x;
//	//				int y1 = iter->mCollision.y;
//	//				int h1 = iter->mCollision.h;
//	//				int w1 = iter->mCollision.w;
//	//				//������ײԭ�����������ε�x���y��ͬʱ�ص�ʱ���������β���ײ��ֻҪ��һ������룬��û�з�����ײ
//	//				if (x0 > x1) {
//	//					//�ȼ��y����룬��������ײ�������λ��
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
//	//					//���x�����
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
//	// Ĭ��ʵ�֣�����״���Ͳ�ƥ��ʱ����øú���
//	return true;
//}
//
//// �ػ�����ģ�壬�����ض���״���͵���ײ����㷨
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
//	//������ײԭ�����������ε�x���y��ͬʱ�ص�ʱ���������β���ײ��ֻҪ��һ������룬��û�з�����ײ
//	if (x0 > x1) {
//		//�ȼ��y����룬��������ײ�������λ��
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
//		//���x�����
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
////	//������ײԭ�����������ε�x���y��ͬʱ�ص�ʱ���������β���ײ��ֻҪ��һ������룬��û�з�����ײ
////	if (x0 > x1) {
////		//�ȼ��y����룬��������ײ�������λ��
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
////		//���x�����
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
//					// ������ײ�¼��������ײ������
//					SDL_Log("???");
//					componentB->callbackOnCollision;
//				}
//			}
//		}
//	}
//}
