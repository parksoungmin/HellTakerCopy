#pragma once
#include "Scene.h"
#include "json.hpp"

class AniPlayer;
class Block1;
class AniMonster;
class TileMap;
class Stage1TileMap;

using json = nlohmann::json;


class SceneStage1 : public Scene
{
protected:
	AniPlayer* player;
	//TileMap* tilemap;
	Stage1TileMap* tileMap;

	int count = 0;

	std::list<Block1*> block1List;
	ObjectPool<Block1> block1Pool;

	std::list<AniMonster*> monsterList;
	ObjectPool<AniMonster> MonsterPool;

	std::list<sf::FloatRect> dontMoveTile;

	bool leftContact = false;
	bool rightContact = false;
	bool upContact = false;
	bool downContact = false;
public:
	std::vector < std::vector<int>> stageInfo;


	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void BlockSet();
	void MonsterSet();
};

