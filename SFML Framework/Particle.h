#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
public:
	enum class Types
	{
		Particle1,
		Particle2,
		Particle3,
		Particle4,
		Particle5,
		Particle6,
		Particle7,
	};
protected:
	sf::Vector2f gravity = { 0.f, 300.f };
	sf::Vector2f velocity;
	sf::Sprite body;
	Types types = Types::Particle1;
	std::string textureId;

	float duration = 3.f;
	float timer = 0.f;
public:
	Particle(const std::string& name = "");
	~Particle() = default;

	void SetType(Types type);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void MonsterDie(sf::Vector2f v);
};

