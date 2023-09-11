#ifndef __Control__
#define __Control__
#include "Math2.h"

namespace GameFrame {
	class GameObject;

	class Control {
	public:
		Control(GameObject* gameobject, Vector2 pos);
	 	virtual void update();

	protected:
		Vector2 ObjectPosion;
		GameObject* BindObject;//控件绑定对象
	};
}

#endif // __Control__
