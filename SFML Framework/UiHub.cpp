#include "stdafx.h"
#include "UiHub.h"

UiHub::UiHub(const std::string& name)
	: GameObject(name)
{
}

void UiHub::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHub::SetRotation(float angle)
{
	rotation = angle;
}

void UiHub::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHub::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHub::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHub::SetLife(int life)
{
	textLife.setString(std::to_string(life));

	Utils::SetOrigin(textLife, Origins::MC);
}

void UiHub::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 8;
}

void UiHub::Release()
{
}

void UiHub::Reset()
{
	unsigned int textSize = 50;
	sf::Font& font = FONT_MGR.Get("fonts/himalaya.ttf");

	textLife.setFont(font);

	textLife.setCharacterSize(textSize);

	textLife.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLife, Origins::MC);;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeFloat();

	float BottomY = windowSize.y - 25.f;

	textLife.setPosition(-700.f, 210.f);
	textLife.setScale({ 2.2f,3.6f });
	SetLife(23);
}

void UiHub::Update(float dt)
{
}

void UiHub::Draw(sf::RenderWindow& window)
{
	window.draw(textLife);
}
