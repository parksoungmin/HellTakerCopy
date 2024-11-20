#include "stdafx.h"
#include "SceneStage1.h"
#include "AniPlayer.h"
#include "BackGround1.h"
#include "Block1.h"
#include "rapidcsv.h"
#include "AniMonster.h"
#include "Stage1TileMap.h"
#include "AniMonsterHitEffect.h"

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
	monsterHitEffect = AddGo(new AniMonsterHitEffect("monsterHit"));
	tileMap->SetTile(STAGE1_TABLE->GetTileMapTable(), STAGE1_TABLE->GetTileMapCount());

	Scene::Init();
}

void SceneStage1::Enter()
{
	player->SetPosition({ 250.f, -250.f });
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

	for (int i = 0; i < 4; ++i)
	{
		intersectMonster[i] = nullptr;
		intersectBlock[i] = nullptr;
	}
	for (auto monster : list)
	{
		sf::FloatRect monsterBounds = monster->GetGlobalBounds();
		if (monsterBounds.contains({ playerpos.x - 100,playerpos.y }))
		{
			contact[0] = true;
			kick[0] = true;
			intersectMonster[0] = monster;
		}
		if (monsterBounds.contains({ playerpos.x + 100,playerpos.y  }))
		{
			contact[1] = true;
			kick[1] = true;
			intersectMonster[1] = monster;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y - 100 }))
		{
			contact[2] = true;
			kick[2] = true;
			intersectMonster[2] = monster;
		}
		if (monsterBounds.contains({ playerpos.x,playerpos.y + 100 }))
		{
			contact[3] = true;
			kick[3] = true;
			intersectMonster[3] = monster;
		}
	}
	const auto& blocklist = block1List;
	for (auto block : blocklist)
	{
		sf::FloatRect blockBounds = block->GetGlobalBounds();
		if (blockBounds.contains({ playerpos.x - 100,playerpos.y }))
		{
			contact[0] = true;
			kick[0] = true;
			intersectBlock[0] = block;
		}
		if (blockBounds.contains({ playerpos.x + 100,playerpos.y  }))
		{
			contact[1] = true;
			kick[1] = true;
			intersectBlock[1] = block;
		}
		if (blockBounds.contains({ playerpos.x,playerpos.y - 100  }))
		{
			contact[2] = true;
			kick[2] = true;
			intersectBlock[2] = block;
		}
		if (blockBounds.contains({ playerpos.x,playerpos.y + 100  }))
		{
			contact[3] = true;
			kick[3] = true;
			intersectBlock[3] = block;
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
		player->SetScale({ 1.f,1.f });
		bool wallcrash = false;
		bool blockWall = false;
		bool MonsterCrash = false;
		if (intersectMonster[0] != nullptr)
		{
			auto monsterPos = intersectMonster[0]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ monsterPos.x - 100,monsterPos.y }))
				{
					wallcrash = true;
				}
			}
			for (auto Monsters : monsterList)
			{
				if (intersectMonster[0] != Monsters && Monsters->GetGlobalBounds().contains({ monsterPos.x - 100,monsterPos.y }))
				{
					MonsterCrash = true;
				}
				if (intersectBlock[0] != nullptr)
				{
					auto blockPos = intersectBlock[0]->GetPosition();
					if (Monsters->GetGlobalBounds().contains({ blockPos.x - 100, blockPos.y  }))
					{
						MonsterCrash = true;
					}
				}
			}
			if (MonsterCrash)
			{
				intersectMonster[0]->HitingMotion();
			}
			else if (wallcrash)
			{
				ReturnMonster(intersectMonster[0]);
			}
			else
			{
				intersectMonster[0]->HitingMonster(0);
			}
		}
		if (intersectBlock[0] != nullptr)
		{
			auto blockPos = intersectBlock[0]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ blockPos.x - 100,blockPos.y }))
				{
					blockWall = true;
				}
			}
			if (!blockWall)
			{
				intersectBlock[0]->HitingBlock1(0);
			}
		}
		monsterHitEffect->SetPosition({ playerpos.x - 50, playerpos.y });
		monsterHitEffect->SetActive(true);
		monsterHitEffect->PlayAnimation("Hit");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right) && kick[1])
	{
		player->PlayingKick();
		player->SetScale({ -1.f,1.f });
		bool wallcrash = false;
		bool blockWall = false;
		bool MonsterCrash = false;
		if (intersectMonster[1] != nullptr)
		{
			auto monsterPos = intersectMonster[1]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ monsterPos.x + 100, monsterPos.y }))
				{
					wallcrash = true;
				}
			}
			for (auto& Monsters : monsterList)
			{
				if (intersectMonster[1] != Monsters && Monsters->GetGlobalBounds().contains({ monsterPos.x + 100,monsterPos.y  }))
				{
					MonsterCrash = true;
				}
				if (intersectBlock[1] != nullptr)
				{
					auto blockPos = intersectBlock[1]->GetPosition();
					if (Monsters->GetGlobalBounds().contains({ blockPos.x + 100, blockPos.y  }))
					{
						MonsterCrash = true;
					}
				}
			}
			if (MonsterCrash)
			{
				intersectMonster[1]->HitingMotion();
			}
			else if (wallcrash)
			{
				ReturnMonster(intersectMonster[1]);
			}
			else
			{
				intersectMonster[1]->HitingMonster(1);
			}
		}
		if (intersectBlock[1] != nullptr)
		{
			auto blockPos = intersectBlock[1]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ blockPos.x + 100,blockPos.y }))
				{
					blockWall = true;
				}
			}
			if (!blockWall)
			{
				intersectBlock[1]->HitingBlock1(1);
			}
		}
		monsterHitEffect->SetPosition({ playerpos.x + 50, playerpos.y });
		monsterHitEffect->SetActive(true);
		monsterHitEffect->PlayAnimation("Hit");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up) && kick[2])
	{
		player->PlayingKick();
		bool wallcrash = false;
		bool blockWall = false;
		bool MonsterCrash = false;
		if (intersectMonster[2] != nullptr)
		{
			auto monsterPos = intersectMonster[2]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ monsterPos.x,monsterPos.y - 100 }))
				{
					wallcrash = true;
				}
			}
			for (auto& Monsters : monsterList)
			{
				if (intersectMonster[2] != Monsters && Monsters->GetGlobalBounds().contains({ monsterPos.x ,monsterPos.y - 100 }))
				{
					MonsterCrash = true;
				}
				if (intersectBlock[2] != nullptr)
				{
					auto blockPos = intersectBlock[2]->GetPosition();
					if (Monsters->GetGlobalBounds().contains({ blockPos.x , blockPos.y - 100 }))
					{
						MonsterCrash = true;
					}
				}
			}
			if (MonsterCrash)
			{
				intersectMonster[2]->HitingMotion();
			}
			else if (wallcrash)
			{
				ReturnMonster(intersectMonster[2]);
			}
			else
			{
				intersectMonster[2]->HitingMonster(2);
			}
		}
		if (intersectBlock[2] != nullptr)
		{
			auto blockPos = intersectBlock[2]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ blockPos.x,blockPos.y - 100 }))
				{
					blockWall = true;
				}
			}
			if (!blockWall)
			{
				intersectBlock[2]->HitingBlock1(2);
			}
		}
		monsterHitEffect->SetPosition({ playerpos.x, playerpos.y - 50 });
		monsterHitEffect->SetActive(true);
		monsterHitEffect->PlayAnimation("Hit");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down) && kick[3])
	{
		player->PlayingKick();
		bool wallcrash = false;
		bool blockWall = false;
		bool MonsterCrash = false;
		for (auto& monster : monsterList)
		{
		}
		if (intersectMonster[3] != nullptr)
		{
			auto monsterPos = intersectMonster[3]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ monsterPos.x,monsterPos.y + 100 }))
				{
					wallcrash = true;
				}
			}
			for (auto& Monsters : monsterList)
			{
				if (intersectMonster[3] != Monsters && Monsters->GetGlobalBounds().contains({ monsterPos.x ,monsterPos.y + 100 }))
				{
					MonsterCrash = true;
				}
				if (intersectBlock[3] != nullptr)
				{
					auto blockPos = intersectBlock[3]->GetPosition();
					if (Monsters->GetGlobalBounds().contains({ blockPos.x , blockPos.y + 100 }))
					{
						MonsterCrash = true;
					}
				}
			}
			if (MonsterCrash)
			{
				intersectMonster[3]->HitingMotion();
			}
			else if (wallcrash)
			{
				ReturnMonster(intersectMonster[3]);
			}
			else
			{
				intersectMonster[3]->HitingMonster(3);
			}
		}
		if (intersectBlock[3] != nullptr)
		{
			auto blockPos = intersectBlock[3]->GetPosition();
			for (auto& notTile : dontMoveTile)
			{
				if (notTile.contains({ blockPos.x ,blockPos.y + 100 }))
				{
					blockWall = true;
				}
			}
			if (!blockWall)
			{
				intersectBlock[3]->HitingBlock1(3);
			}
		}
		monsterHitEffect->SetPosition({ playerpos.x, playerpos.y + 50 });
		monsterHitEffect->SetActive(true);
		monsterHitEffect->PlayAnimation("Hit");
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