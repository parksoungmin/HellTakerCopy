#include "stdafx.h"
#include "TitleText.h"

TitleText::TitleText(const std::string& name)
	: GameObject(name)
{
}

void TitleText::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TitleText::SetRotation(float angle)
{
	rotation = angle;
}

void TitleText::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TitleText::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(textId, originPreset);
		origin = Utils::SetOrigin(textId2, originPreset);
	}
}

void TitleText::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	textId.setOrigin(origin);
	textId2.setOrigin(origin);
}

void TitleText::SetTexture(std::wstring str)
{
	textId.setString(str);
}

void TitleText::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetTexture(text1);
}

void TitleText::Release()
{
}

void TitleText::Reset()
{
	unsigned int textSize = 50;
	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");
	sf::Font& fontbd = FONT_MGR.Get("fonts/malgunbd.ttf");

	textId.setFont(font);
	textId.setCharacterSize(textSize);
	textId.setFillColor(sf::Color::White);
	Utils::SetOrigin(textId, Origins::MC);;

	SetTexture(text1);
	textId.setPosition(0.f, 360.f);
	textId.setScale({ 0.6f,0.6f });

	textId2.setScale({ 0.7f,0.7f });
	textId2.setFont(fontbd);
	textId2.setCharacterSize(textSize);
	SetOrigin(Origins::MC);
}

void TitleText::Update(float dt)
{
	if(InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetTexture(text2);
		textId.setPosition(10.f, 400.f);


		textId2.setScale({ 1.f,1.f });
		textId2.setFillColor(sf::Color::Red);
		textId2.setString(text3);
		textId2.setPosition(0.f, 295.f);
		SetOrigin(Origins::MC);
	}
}

void TitleText::Draw(sf::RenderWindow& window)
{
	window.draw(textId);
	window.draw(textId2);
}
