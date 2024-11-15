#include "stdafx.h"
#include "SceneStage1.h"
#include "AniPlayer.h"
#include "BackGround1.h"
#include "Block1.h"
#include "rapidcsv.h"
#include "AniMonster.h"

SceneStage1::SceneStage1() : Scene(SceneIds::Dev1)
{
}

void SceneStage1::Init()
{
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());

	player = AddGo(new AniPlayer("player"));
	AddGo(new BackGround1);

	Scene::Init();
}

void SceneStage1::Enter()
{
	player->SetPosition({ 200.f, -220.f });
	BlockSet();
	Scene::Enter();
	MonsterSet();
}

void SceneStage1::Exit()
{
	for (auto& iter : block1List)
	{
		RemoveGo(iter);
		block1Pool.Return(iter);
	}
	block1List.clear();

	for (auto& iter : monsterList)
	{
		RemoveGo(iter);
		MonsterPool.Return(iter);
	}
	monsterList.clear();
	Scene::Exit();
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);
}

void SceneStage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneStage1::BlockSet()
{
	for (int i = 0; i < 4; ++i)
	{
		Block1* block = block1Pool.Take();
		block1List.push_back(block);



		Block1::Types blockType = (Block1::Types)count;
		block->SetType(blockType);
		count++;

		sf::Vector2f position = sf::Vector2f{ block->GetPosition() };
		block->SetPosition(position);

		AddGo(block);
	}
}

void SceneStage1::MonsterSet()
{
	for (int i = 0; i < 3; ++i)
	{
		AniMonster* monster = MonsterPool.Take();
		monsterList.push_back(monster);

		auto& data = MONSTER_TABLE->Get(i);
		monster->SetPosition({ data.positionX ,data.positionY });


		AddGo(monster);
	}
}
