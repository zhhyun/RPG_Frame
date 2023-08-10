#include	"PhysSpace.h"
#include	"Game.h"
//#include	"CollisionComponent.h"


GameFrame::PhysSpace::PhysSpace(Game* game):
	mGame(game)
{
}

void GameFrame::PhysSpace::AddRigid(CollisionComponent* rigid)
{
	if (Rigids.size() != 0) {
		for (auto rgd : Rigids) {
			if (rigid == rgd) {
				return;
			}
		}
	}
	Rigids.emplace_back(rigid);
}


void GameFrame::PhysSpace::RemoveRigid(CollisionComponent* rigid)
{
	auto iter = std::find(Rigids.begin(), Rigids.end(), rigid);
	if (iter != Rigids.end()) {
		std::iter_swap(iter, Rigids.end() - 1);
		//ÆÆ»µË³ÐòÉ¾³ý¶ÓÎ²
		Rigids.pop_back();
	}
}

void GameFrame::PhysSpace::ReleaseSpace()
{
	Rigids.clear();
}
