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
		if (notTile.contains({ playerpos.x - 100,playerpos.y }))
		{
			contact[0] = true;
		}
		if (notTile.contains({ playerpos.x + 100,playerpos.y }))
		{
			contact[1] = true;
		}
		if (notTile.contains({ playerpos.x,playerpos.y - 100 }))
		{
			contact[2] = true;
		}
		if (notTile.contains({ playerpos.x,playerpos.y + 100 }))
		{
			contact[3] = true;
		}
	}

	const auto& list = monsterList;

	for (auto monster : list)
	{
		sf::FloatRect monsterBounds = monster->GetGlobalBounds();
		if (monsterBounds.contains({ playerpos.x - 100,playerpos.y - 20 }))
		{
			contact[0] = true;
			kick[0] = true;
			intersectMonster[0] = monster;
		}
		if (monsterBounds.contains({ playerpos.x + 100,playerpos.y - 20 }))
		{
			contact[1] = true;
			kick[1] = true;
			intersectMonster[1] = monster;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y - 100 - 20 }))
		{
			contact[2] = true;
			kick[2] = true;
			intersectMonster[2] = monster;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y + 100 - 20 }))
		{
			contact[3] = true;
			kick[3] = true;
			intersectMonster[3] = monster;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) && !contact[0])
	{
		player->SetLeftMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right) && !contact[1])
	{
		player->SetRigthMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up) && !contact[2])
	{
		player->SetUpMove();
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down) && !contact[3])
	{
		player->SetDownMove();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left) && kick[0])
	{
		player->PlayingKick();
		bool wall = false;
		auto monsterPos = intersectMonster[0]->GetPosition();
		for (auto& notTile : dontMoveTile)
		{
			if (notTile.contains({ monsterPos.x - 100,monsterPos.y }))
			{
				wall = true;
			}
		}
		if (wall)
		{
			ReturnMonster(intersectMonster[0]);
		}
		else
		{
			player->SetScale({ 1.f,1.f });
			intersectMonster[0]->HitingMonster(0);
		}
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right) && kick[1])
	{
		player->PlayingKick();
		bool wall = false;
		auto monsterPos = intersectMonster[1]->GetPosition();
		for (auto& notTile : dontMoveTile)
		{
			if (notTile.contains({ monsterPos.x + 100, monsterPos.y }))
			{
				wall = true;
			}
		}
		if (wall)
		{
			ReturnMonster(intersectMonster[1]);
		}
		else
		{
			player->SetScale({ -1.f,1.f });
			intersectMonster[1]->HitingMonster(1);
		}
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up) && kick[2])
	{
		player->PlayingKick();
		bool wall = false;
		auto monsterPos = intersectMonster[2]->GetPosition();
		for (auto& notTile : dontMoveTile)
		{
			if (notTile.contains({ monsterPos.x,monsterPos.y - 100 }))
			{
				wall = true;
			}
		}
		if (wall)
		{
			ReturnMonster(intersectMonster[2]);
		}
		else
		{
			intersectMonster[2]->HitingMonster(2);
		}
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down) && kick[3])
	{
		player->PlayingKick();
		bool wall = false;
		auto monsterPos = intersectMonster[3]->GetPosition();
		for (auto& notTile : dontMoveTile)
		{
			if (notTile.contains({ monsterPos.x,monsterPos.y + 100 }))
			{
				wall = true;
			}
		}
		if (wall)
		{
			ReturnMonster(intersectMonster[3]);
		}

		else
		{
			intersectMonster[3]->HitingMonster(3);
		}
	}

}

void SceneStage1::LateUpdate(float dt)
{
	for (int i = 0; i < 4; ++i)
	{
		contact[i] = false;
		kick[i] = false;
	}
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

void SceneStage1::ReturnMonster(AniMonster* item)
{
	RemoveGo(item);
	MonsterPool.Return(item);
	monsterList.remove(item);
}