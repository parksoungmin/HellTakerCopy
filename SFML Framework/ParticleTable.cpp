#include "stdafx.h"
#include "ParticleTable.h"
#include "rapidcsv.h"

DataParticle ParticleTable::undefined;

ParticleTable::ParticleTable()
    : DataTable(Types::Particle)
{
}

ParticleTable::~ParticleTable()
{
}

bool ParticleTable::Load()
{
    Release();

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);

        Particle::Types id = (Particle::Types)std::stoi(row[0]);
        if (tableMap.find(id) != tableMap.end())
            return false;

        tableMap[id].id = id;
        tableMap[id].textureId = row[1];
    }
    return true;
}

void ParticleTable::Release()
{
    tableMap.clear();
}

const DataParticle& ParticleTable::Get(Particle::Types id)
{
    auto find = tableMap.find(id);
    if (find == tableMap.end())
    {
        return undefined;
    }

    return find->second;
}