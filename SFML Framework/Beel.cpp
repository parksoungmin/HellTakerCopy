#include "stdafx.h"
#include "Beel.h"

Beel::Beel(const std::string& name)
	: GameObject(name)
{
}

void Beel::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}


void Beel::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Beel::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Beel::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Beel::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	body.setTexture(TEXTURE_MGR.Get(texture));
	SetPosition({ 0.f,-100.f });
	SetOrigin(Origins::MC);
	active = false;
}
void Beel::Update(float dt)
{
}

void Beel::Reset()
{
}

void Beel::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
