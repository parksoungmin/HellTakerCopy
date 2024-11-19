#pragma once
#include "DataTable.h"

class Stage1MapTable : public DataTable
{
public:
	static int UndefinedTileType;

protected:
	std::unordered_map<int, std::vector<int>> table;
	std::string Stage1Map = "tables/tileMap_table.csv";

	int currentFileRowCnt = 0;
	int currentFileColumnCnt = 0;

public:
	Stage1MapTable() : DataTable(DataTable::Types::TileMap1) { };
	~Stage1MapTable() = default;

	bool Load() override;
	void Release() override;
	sf::Vector2i GetTileMapCount();
	std::unordered_map<int, std::vector<int>>& GetTileMapTable();

	const int& Get(int column, int row);
};

