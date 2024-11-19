#include "stdafx.h"
#include "SceneStage1.h"
#include "AniPlayer.h"
#include "BackGround1.h"
#include "Block1.h"
#include "rapidcsv.h"
#include "AniMonster.h"
#include "Stage1TileMap.h"

SceneStage1::SceneStage1() : Scene(SceneIds::Dev1)
{
}

void SceneStage1::Init()
{
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());

	player = AddGo(new AniPlayer("player"));
	AddGo(new BackGround1);
	tileMap = AddGo(new Stage1TileMap("tilemap"));

	tileMap->SetTile(STAGE1_TABLE->GetTileMapTable(), STAGE1_TABLE->GetTileMapCount());


	Scene::Init();
}

void SceneStage1::Enter()
{
	player->SetPosition({ 200.f, -220.f });
	BlockSet();
	Scene::Enter();
	MonsterSet();
	dontMoveTile = tileMap->DontMoveBounds();

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
	sf::Vector2f playerpos = player->GetPosition();
	for (auto& notTile : dontMoveTile)
	{
		if (notTile.contains({ playerpos.x-100,playerpos.y}))
		{
			leftContact = true;
		}
		if (notTile.contains({ playerpos.x + 100,playerpos.y }))
		{
			rightContact = true;
		}
		if (notTile.contains({ playerpos.x,playerpos.y - 100}))
		{
			upContact = true;
		}
		if (notTile.contains({ playerpos.x,playerpos.y + 100}))
		{
			downContact = true;
		}
	}

	const auto& list = monsterList;
	
	for (auto& monster : list)
	{
		sf::FloatRect monsterBounds = monster->GetGlobalBounds();
		if (monsterBounds.contains({ playerpos.x - 100,playerpos.y - 20 }))
		{
			leftContact = true;
		}
		if (monsterBounds.contains({ playerpos.x + 100,playerpos.y-20}))
		{
			rightContact = true;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y - 100 - 20 }))
		{
			upContact = true;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y + 100 - 20 }))
		{
			downContact = true;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) && !leftContact)
	{
		player->SetLeftMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right) && !rightContact)
	{
		player->SetRigthMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up) && !upContact)
	{
		player->SetUpMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down) && !downContact)
	{
		player->SetDownMove();
	}
	leftContact = false;
	rightContact = false;
	upContact = false;
	downContact = false;
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
