#include "stdafx.h"
#include "MainMenuDialogue.h"

MainMenuDialogue::MainMenuDialogue(const std::string& name)
	: GameObject(name)
{
}

void MainMenuDialogue::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void MainMenuDialogue::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void MainMenuDialogue::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void MainMenuDialogue::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void MainMenuDialogue::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

}

void MainMenuDialogue::Release()
{
}

void MainMenuDialogue::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetScale({ 1.f,1.f });
	SetPosition({ 1016,-20.f });
	SetOrigin(Origins::MC);
}

void MainMenuDialogue::Update(float dt)
{
	position.x = position.x - (speed * dt);
	SetPosition(position);
	if (position.x <= -1064)
	{
		position = { 1920.f/2.f,-120.f };
	}
}

void MainMenuDialogue::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
