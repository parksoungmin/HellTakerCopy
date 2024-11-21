#include "stdafx.h"
#include "BackGround1.h"

BackGround1::BackGround1(const std::string& name)
	: GameObject(name)
	,textureId("graphics/BackGround/ChapterBG_001.png")
{

}

void BackGround1::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetPosition(position);
}

void BackGround1::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(texture, originPreset);
	}
}

void BackGround1::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	texture.setOrigin(newOrigin);
}

void BackGround1::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void BackGround1::Release()
{
}

void BackGround1::Reset()
{
	texture.setTexture(TEXTURE_MGR.Get(textureId));
	texture.setPosition({ 50.f,10.f });
	SetOrigin(Origins::MC);
}

void BackGround1::Draw(sf::RenderWindow& window)
{
	window.draw(texture);
}

