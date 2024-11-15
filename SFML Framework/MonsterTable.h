#pragma once
#include "DataTable.h"
#include "Block1.h"

struct DataMonster
{
	int id;
	std::string	textureId;
	float positionX;
	float positionY;
};


class MonsterTable : public DataTable
{
public:
	static DataMonster undefined;

protected:
	std::unordered_map<int, DataMonster> tableMap;
	std::string filePath = "tables/monster_table.csv";
public:
	bool Load() override;
	void Release() override;


	const DataMonster& Get(int id);
public:
	MonsterTable();
	virtual ~MonsterTable();
	MonsterTable(const MonsterTable& other) = delete;
	MonsterTable& operator=(const MonsterTable& other) = delete;
};
