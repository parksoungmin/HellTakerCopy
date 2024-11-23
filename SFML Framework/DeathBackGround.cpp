#include "stdafx.h"
#include "DeathBackGround.h"

DeathBackGround::DeathBackGround(const std::string& name)
	: GameObject(name)
	, textureId("Resources/Character/Hero/Hero_Death/Death_BackGround.png")
{

}

void DeathBackGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetPosition(position);
}

void DeathBackGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(texture, originPreset);
	}
}

void DeathBackGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	texture.setOrigin(newOrigin);
}

void DeathBackGround::Init()
{	
	active = false;
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 9;
}

void DeathBackGround::Release()
{
}

void DeathBackGround::Reset()
{
	texture.setTexture(TEXTURE_MGR.Get(textureId));
	texture.setPosition({ 50.f,10.f });
	SetOrigin(Origins::MC);
}

void DeathBackGround::Draw(sf::RenderWindow& window)
{
	window.draw(texture);
}

void DeathBackGround::SetActive(bool t)
{
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/hell/transition_off.wav"));

	active = t;
}

