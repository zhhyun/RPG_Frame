#include	"NpcObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"BattleComponent.h"
#include	"CollisionComponent.h"
#include	"Game.h"

GameFrame::NpcObject::NpcObject(Game* game, Sence* map, const std::string& name):
	ActorObject(game, map, name)
{
	Vector2 pos{ 210,210 };
	SetPosition(pos);
	/*pos.x = pos.x - 5;
	pos.y = pos.y - 5;*/
	SpriteComponent* Npc = new SpriteComponent(this, 100);
	BattleComponent* Battle = new BattleComponent(this);

	CollisionComponent* collision = new CollisionComponent(this);
	/*auto shape = new RectShape(collision, pos.x, pos.y, PlayerH, PlayerW);
	collision->CreateShape(shape);*/

	std::string str = "Npc";
	Npc->LoadTexture(str);
	Vector2 TexWh = { Npc->GetTexture()->GetWidth() / 3,Npc->GetTexture()->GetHeight() / 4 };
	Npc->SetDrawTexWH(TexWh);
}

GameFrame::NpcObject::~NpcObject()
{
}

void GameFrame::NpcObject::update()
{
	//更新位置
	//获取摄像机坐标
	auto camera = GetGame()->GetCamera();
	ObjectPosion.x = ObjectPosion.x + camera->GetPreImageRect().x - camera->GetImageRect().x;
	ObjectPosion.y = ObjectPosion.y + camera->GetPreImageRect().y - camera->GetImageRect().y;
	//相对坐标->绝对坐标->相对坐标
	if (mState == GameObject::State::EActive) {
		for (auto component : mComponents) {
			component->update();
		}
	}
}
