#ifndef __CollisionComponent__
#define __CollisionComponent__
#include	"Component.h"
#include	<vector>
#include	"Math2.h"

//һ����ײ���ֻ����һ����ײ��״�������״��Ҫ��Ӷ����ײ���
//��ײ������������ÿ�������ض����еĹ�����Ϊ������Ӹ�������
//��ײ����ṩ��ײ��⺯������������ײ���������һ��ʹ�øú���
//ʹ����ײ��⣬Ϊ�˱���������Դ�������ģ�Ӧ���Ƕ�̬������ȥ������⣬��̬�����岻��Ҫ������⡣
//��ײ����������ص������ϣ���Ҫע�ᵽ����ռ���ȥ������ռ���һ���������ͷ�������ײ�����ݽṹ��

namespace GameFrame {
	class GameObject;

	class Shape {
	public:
		Shape(CollisionComponent* RigidBody);
		~Shape() {};
		virtual void updateFromObject();

	protected:
		CollisionComponent* mRigidBody;
	};

	class RectShape :public Shape {
	public:
		RectShape(CollisionComponent* RigidBody, float x, float y, int w, int h);
		~RectShape() {};
		void updateFromObject() override;

	private:
		Vector2 shape_pos;
		int wdith;
		int height;
	};

	class CircleShape : public Shape {
	public:
		CircleShape(CollisionComponent* RigidBody, float x, float y, int r);//x��y��Բ��λ�ã�r�ǰ뾶
		~CircleShape() {};
		void updateFromObject() override;

	private:
		Vector2 shape_pos;
		int r;
	};



	class CollisionComponent : public Component {
	public:
		CollisionComponent(GameObject* gameobject);
		~CollisionComponent();
		
		void CreateShape(Shape* shape);
		int RemoveShape(Shape* body);

		void SetCollision(Vector2 vec, int h, int w);
		void SetCollision(Vector2 vec);

		int CheckCollision();
		void update()override;
		//void OnUpdateWorldTransform();
		void ResignInPhysSpace();

	private:
		//SDL_Rect							mCollision;
		std::vector<Shape*>					mShapes;
		PhysSpace*							PhysWorld;
		bool								IsUpdateFromObject;
	};
}
#endif __CollisionComponent__