#include "stdafx.h"
#include "Block1.h"

Block1::Block1(const std::string& name)
	:GameObject(name)
{
}

void Block1::SetType(Types type)
{
	auto& data = BLOCK_TABLE->Get(type);

	types = data.id;
	textureId = data.textureId;
	positionX = data.positionX;
	positionY = data.positionY;

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);


}

void Block1::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Block1::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Block1::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Block1::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Block1::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Block1::Release()
{
}

void Block1::Reset()
{
	SetOrigin(Origins::MC);
	SetPosition({ positionX, positionY });
	SetScale({1.f,1.f});
}

void Block1::Update(float dt)
{
}

void Block1::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
