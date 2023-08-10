#ifndef __CollisionComponent__
#define __CollisionComponent__
#include	"Component.h"
#include	<vector>
#include	"Math2.h"

//一个碰撞组件只负责一个碰撞形状，多个形状需要添加多个碰撞组件
//碰撞组件最基本的且每个被挂载对象都有的功能是为物体添加刚体属性
//碰撞组件提供碰撞检测函数，但是有碰撞组件不代表一定使用该函数
//使用碰撞检测，为了避免计算机资源过度消耗，应该是动态的物体去主动检测，静态的物体不需要调动检测。
//碰撞组件不仅挂载到物体上，还要注册到物理空间中去，物理空间是一个管理刚体和方便检测碰撞的数据结构。

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
		CircleShape(CollisionComponent* RigidBody, float x, float y, int r);//x、y是圆心位置，r是半径
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