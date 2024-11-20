#pragma once
#include "Scene.h"
#include "json.hpp"

class AniPlayer;
class Block1;
class AniMonster;
class TileMap;
class Stage1TileMap;
class AniMonsterHitEffect;

using json = nlohmann::json;


class SceneStage1 : public Scene
{
protected:
	AniPlayer* player;
	Stage1TileMap* tileMap;

	int count = 0;

	std::list<Block1*> block1List;
	ObjectPool<Block1> block1Pool;

	std::list<AniMonster*> monsterList;
	ObjectPool<AniMonster> MonsterPool;
	AniMonsterHitEffect* monsterHitEffect;

	std::list<sf::FloatRect> dontMoveTile;

	bool contact[4];
	bool kick[4];
	AniMonster* intersectMonster[4];
	Block1* intersectBlock[4];

public:
	std::vector < std::vector<int>> stageInfo;


	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void BlockSet();
	void MonsterSet();

	void ReturnMonster(AniMonster* item);
};

