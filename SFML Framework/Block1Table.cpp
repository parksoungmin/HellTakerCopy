#include "stdafx.h"
#include "Block1Table.h"
#include "rapidcsv.h"

DataBlock Block1Table::undefined;

Block1Table::Block1Table()
    : DataTable(Types::Block1)
{
}

Block1Table::~Block1Table()
{
}

bool Block1Table::Load()
{
    Release();

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);

        Block1::Types id = (Block1::Types)std::stoi(row[0]);
        if (tableMap.find(id) != tableMap.end())
            return false;

        tableMap[id].id = id;
        tableMap[id].textureId = row[1];
        tableMap[id].positionX = std::stoi(row[2]);
        tableMap[id].positionY = std::stoi(row[3]);
    }

    return true;
}

void Block1Table::Release()
{
    tableMap.clear();
}

const DataBlock& Block1Table::Get(Block1::Types id)
{
    auto find = tableMap.find(id);
    if (find == tableMap.end())
    {
        return undefined;
    }

    return find->second;
}