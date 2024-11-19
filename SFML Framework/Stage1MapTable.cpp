#include "stdafx.h"
#include "Stage1MapTable.h"
#include "rapidcsv.h"

int Stage1MapTable::UndefinedTileType = -99;

bool Stage1MapTable::Load() // csv 직접 파싱하지 않고 라이브러리 사용
{
	Release();

	rapidcsv::Document doc;

	doc.Load(Stage1Map, rapidcsv::LabelParams(0, -1));

	currentFileRowCnt = doc.GetRowCount();

	for (int i = 0; i < currentFileRowCnt; i++)
	{
		std::vector<int> row = doc.GetRow<int>(i);
		// GetRow 반환형 const 붙어서 &일 경우 const로 받아야함 (& 없으면 복사생성임에 무관)

		auto find = table.find(row[0]);
		if (find != table.end())
		{
			std::cout << "already exists" << std::endl;
			return false;
		}

		row.erase(row.begin());
		table[i] = row;
	}
	currentFileColumnCnt = table[0].size();
	return true;
}

void Stage1MapTable::Release()
{
	table.clear();
}

sf::Vector2i Stage1MapTable::GetTileMapCount()
{
	return sf::Vector2i({ currentFileColumnCnt, currentFileRowCnt });
}

std::unordered_map<int, std::vector<int>>& Stage1MapTable::GetTileMapTable()
{
	return this->table;
}

const int& Stage1MapTable::Get(int column, int row)
{
	if (table.find(row) == table.end())
	{
		return UndefinedTileType; // String table에 없는 아이디 리턴 요청한 것
	}
	if (std::find(table[row].begin(), table[row].end(), table[row][column]) == table[row].end())
		return UndefinedTileType;
	return table[row][column];

}