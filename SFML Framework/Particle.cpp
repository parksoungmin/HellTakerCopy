#include "stdafx.h"
#include "Particle.h"

Particle::Particle(const std::string& name)
	: GameObject(name)
{
}

void Particle::SetType(Types type)
{
	auto& data = PARTICLE_TABLE->Get(type);

	types = data.id;
	textureId = data.textureId;
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);
}

void Particle::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Particle::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Particle::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Particle::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Particle::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 100;
}

void Particle::Release()
{
}

void Particle::Reset()
{
	SetOrigin(Origins::MC);
	SetPosition(position);
	SetScale({ 1.f,1.f });
	timer = 0;
}

void Particle::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		return;
	}
	velocity += gravity * dt;
	SetPosition(position + velocity * dt);
}

void Particle::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Particle::MonsterDie(sf::Vector2f v)
{
	velocity = v;
	timer = 0;
}
