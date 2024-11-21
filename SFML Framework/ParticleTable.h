#pragma once
#include "DataTable.h"
#include "Particle.h"

struct DataParticle
{
	Particle::Types id;
	std::string	textureId;
};


class ParticleTable : public DataTable
{
public:
	static DataParticle undefined;

protected:
	std::unordered_map<Particle::Types, DataParticle> tableMap;
	std::string filePath = "tables/Particle_table.csv";
public:
	bool Load() override;
	void Release() override;


	const DataParticle& Get(Particle::Types id);
public:
	ParticleTable();
	virtual ~ParticleTable();
	ParticleTable(const ParticleTable& other) = delete;
	ParticleTable& operator=(const ParticleTable& other) = delete;
};
