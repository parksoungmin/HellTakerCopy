#include "stdafx.h"
#include "DataTableManger.h"
#include "ItemTable.h"
#include "Block1Table.h"
#include "Stage1MapTable.h"

DataTableManger::~DataTableManger()
{
	Release();
}

void DataTableManger::Init()
{
	Release();

	tableMap.insert({ DataTable::Types::String, new StringTable() });
	tableMap.insert({ DataTable::Types::Item, new ItemTable() });
	tableMap.insert({ DataTable::Types::Block1, new Block1Table() });
	tableMap.insert({ DataTable::Types::Monster, new MonsterTable() });
	tableMap.insert({ DataTable::Types::Stage1Map, new Stage1MapTable() });
	tableMap.insert({ DataTable::Types::Particle, new ParticleTable() });

	for (auto table : tableMap)
	{
		table.second->Load();
	}
}

void DataTableManger::Release()
{
	for (auto table : tableMap)
	{
		table.second->Release();
		delete table.second;
	}

	tableMap.clear();
}
