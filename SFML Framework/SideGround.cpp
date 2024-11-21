#include "stdafx.h"
#include "SideGround.h"

SideGround::SideGround(const std::string& name)
	: GameObject(name)
	, textureId("graphics/BackGround/ChapterUI.png")
{

}

void SideGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetPosition(position);
}

void SideGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(texture, originPreset);
	}
}

void SideGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	texture.setOrigin(newOrigin);
}

void SideGround::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void SideGround::Release()
{
}

void SideGround::Reset()
{
	texture.setTexture(TEXTURE_MGR.Get(textureId));
	texture.setPosition({ 50.f,10.f });
	SetOrigin(Origins::MC);
}

void SideGround::Draw(sf::RenderWindow& window)
{
	window.draw(texture);
}
