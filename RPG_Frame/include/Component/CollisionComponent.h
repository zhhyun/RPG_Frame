#ifndef __CollisionComponent__
#define __CollisionComponent__

#include	"Component.h"
#include	<vector>
#include	"Math2.h"
#include	"MapObject.h"
#include	"PlayerObject.h"

//һ����ײ���ֻ����һ����ײ��״�������״��Ҫ��Ӷ����ײ���
//��ײ������������ÿ�������ض����еĹ�����Ϊ������Ӹ�������
//��ײ����ṩ��ײ��⺯������������ײ���������һ��ʹ�øú���
//ʹ����ײ��⣬Ϊ�˱���������Դ�������ģ�Ӧ���Ƕ�̬������ȥ������⣬��̬�����岻��Ҫ������⡣
//��ײ����������ص������ϣ���Ҫע�ᵽ����ռ���ȥ������ռ���һ���������ͷ�������ײ�����ݽṹ��


namespace GameFrame {
	using CallbackFunction = std::function<void()>;

	class Sence;

	//class Shape {
	//public:
	//	Shape(CollisionComponent* RigidBody);
	//	~Shape() {};
	//	CollisionComponent* GetRigid() { return mRigidBody; };
	//	virtual void updateFromObject();

	//protected:
	//	CollisionComponent* mRigidBody;
	//};


	//class RectShape : public Shape {
	//public:
	//	RectShape(CollisionComponent* RigidBody, float x, float y, int w, int h);
	//	~RectShape() {};

	//	Vector2 GetShapePos() { return shape_pos; };

	//	int GetWdith() { return wdith; };

	//	int GetHeight() { return height; };

	//	void updateFromObject() override;

	//private:
	//	Vector2 shape_pos;
	//	int wdith;
	//	int height;
	//};




	//class CircleShape : public Shape {
	//public:
	//	CircleShape(CollisionComponent* RigidBody, float x, float y, int r);//x��y��Բ��λ�ã�r�ǰ뾶
	//	~CircleShape() {};
	//	void updateFromObject() override;
	//private:
	//	Vector2 shape_pos;
	//	int r;
	//};

	

	class CollisionComponent : public Component {
	public:
		CollisionComponent(GameObject* gameobject);
		~CollisionComponent();

		//void CreateShape(Shape* shape);
		//void RemoveShape(Shape* body){};

		bool CheckCollision();

		void update() override;

		void SetCollisionArea(SDL_Rect area);

		void DefinecallbackOnCollision(CallbackFunction callback);
		SDL_Rect GetCollsionArea() { return CollisionArea; };
		Vector2 GetAreaPos();
		Vector2 GetCollisionPosA();

	private:
		bool								IsUpdateFromObject;
		SDL_Rect							CollisionArea;//deltaX��deltaY��w��h
		CallbackFunction					callbackOnCollision;
	};


}
#endif //__CollisionComponent__