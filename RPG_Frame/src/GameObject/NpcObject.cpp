#include	"NpcObject.h"
#include	"SpriteComponent.h"
#include	"MoveComponent.h"
#include	"InputComponent.h"
#include	"Game.h"

GameFrame::NpcObject::NpcObject(Game* game):
	Hp(100),
	ACK(10),
	DEF(10),
	Speed(1),
	GameObject(game)
{
	Vector2 pos{ 210,210 };
	SetPosition(pos);
	SpriteComponent* Npc = new SpriteComponent(this, 100);
	AddSpriteComponent(Npc);
	SDL_Texture* tex = GetGame()->GetTexture("Npc");
	Npc->SetTexture(tex);
}

GameFrame::NpcObject::~NpcObject()
{
}
