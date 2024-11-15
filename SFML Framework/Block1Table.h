#pragma once
#include "DataTable.h"
#include "Block1.h"

struct DataBlock
{
	Block1::Types id;
	std::string	textureId;
	float positionX;
	float positionY;
};


class Block1Table : public DataTable
{
public:
	static DataBlock undefined;

protected:
	std::unordered_map<Block1::Types, DataBlock> tableMap;
	std::string filePath = "tables/block_table.csv";
public:
	bool Load() override;
	void Release() override;


	const DataBlock& Get(Block1::Types id);
public:
	Block1Table();
	virtual ~Block1Table();
	Block1Table(const Block1Table& other) = delete;
	Block1Table& operator=(const Block1Table& other) = delete;
};
