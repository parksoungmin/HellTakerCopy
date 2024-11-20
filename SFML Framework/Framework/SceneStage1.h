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
	enum class Direction
	{
		NONE = -1,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	enum class Target
	{
		NONE,
		MONSTER,
		BLOCK,
		WALL,
	};


	sf::Vector2f directionVector[4] = { {-100.f,0.f},{100.f,0.f},{0.f,-100.f},{0.f,100.f} };

	AniPlayer* player;
	Stage1TileMap* tileMap;

	int count = 0;

	std::list<Block1*> block1List;
	ObjectPool<Block1> block1Pool;

	std::list<AniMonster*> monsterList;
	ObjectPool<AniMonster> MonsterPool;
	AniMonsterHitEffect* monsterHitEffect;

	std::list<sf::FloatRect> dontMoveTile;
	std::list<sf::FloatRect> blocksBound;

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

