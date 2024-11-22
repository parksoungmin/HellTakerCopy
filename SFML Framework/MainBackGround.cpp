#include "stdafx.h"
#include "MainBackGround.h"

MainBackGround::MainBackGround(const std::string& name)
	: GameObject(name)
{
}

void MainBackGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void MainBackGround::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void MainBackGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void MainBackGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void MainBackGround::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -10;
	body.setTexture(TEXTURE_MGR.Get(texture), true);
	SetPosition({ 0.f,0.f });
	SetOrigin(Origins::MC);
}

void MainBackGround::Reset()
{

}
void MainBackGround::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
