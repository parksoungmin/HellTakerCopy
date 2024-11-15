#include "stdafx.h"
#include "MonsterTable.h"
#include "rapidcsv.h"

DataMonster MonsterTable::undefined;

MonsterTable::MonsterTable()
    : DataTable(Types::Monster)
{
}

MonsterTable::~MonsterTable()
{
}

bool MonsterTable::Load()
{
    Release();

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);

        int id = std::stoi(row[0]);
        if (tableMap.find(id) != tableMap.end())
            return false;

        tableMap[id].id = id;
        tableMap[id].textureId = row[1];
        tableMap[id].positionX = std::stoi(row[2]);
        tableMap[id].positionY = std::stoi(row[3]);
    }

    return true;
}

void MonsterTable::Release()
{
    tableMap.clear();
}

const DataMonster& MonsterTable::Get(int id)
{
    auto find = tableMap.find(id);
    if (find == tableMap.end())
    {
        return undefined;
    }

    return find->second;
}