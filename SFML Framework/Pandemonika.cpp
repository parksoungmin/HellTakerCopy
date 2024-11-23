#include "stdafx.h"
#include "Pandemonika.h"

Pandemonika::Pandemonika(const std::string& name)
	: GameObject(name)
{
}

void Pandemonika::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Pandemonika::SetRotation(float angle)
{
	rotation = angle;
}

void Pandemonika::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Pandemonika::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(textId, originPreset);
		origin = Utils::SetOrigin(textId2, originPreset);
		origin = Utils::SetOrigin(choies1, originPreset);
		origin = Utils::SetOrigin(choies2, originPreset);
		origin = Utils::SetOrigin(textIdSuccess, originPreset);
	}
}

void Pandemonika::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	textId.setOrigin(origin);
	textId2.setOrigin(origin);
	choies1.setOrigin(origin);
	choies2.setOrigin(origin);
	textIdSuccess.setOrigin(origin);
}

void Pandemonika::SetString(std::wstring str)
{
	textId.setString(str);
}

bool Pandemonika::GetFail()
{
	return failbool;
}

bool Pandemonika::GetSuccessSelec()
{
	return SuccessSelec;
}


void Pandemonika::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetString(text1);
}

void Pandemonika::Release()
{
}

void Pandemonika::Reset()
{
	unsigned int textSize = 50;
	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");
	sf::Font& fontbd = FONT_MGR.Get("fonts/malgunbd.ttf");


	textId.setFont(font);
	textId.setCharacterSize(textSize);
	textId.setFillColor(sf::Color::White);

	SetString(text1);
	textId.setPosition(0.f, 360.f);
	textId.setScale({ 0.6f,0.6f });

	textId2.setScale({ 0.7f,0.7f });
	textId2.setFont(fontbd);
	textId2.setCharacterSize(textSize);
	textId2.setFillColor(sf::Color::Red);
	textId2.setString(text3);
	textId2.setPosition(0.f, 295.f);

	textIdSuccess.setScale({ 0.6f,0.6f });
	textIdSuccess.setFont(font);
	textIdSuccess.setCharacterSize(textSize);
	textIdSuccess.setFillColor(sf::Color::Transparent);
	SetOrigin(Origins::MC);

	textOn = false;
	textSelec = false;
	SuccessSelec = false;
	FailSelec = false;
	selec = false;
	failbool = false;
}

void Pandemonika::Update(float dt)
{
	if (!failbool &&FailSelec && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		textId.setString(fail);
		choies1.setColor(sf::Color::Transparent);
		choies2.setColor(sf::Color::Transparent);
		textIdSuccess.setFillColor(sf::Color::Transparent);
		SetOrigin(Origins::MC);
		failbool = true;
	}
	if (SuccessSelec && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		textId.setString(success);
		choies1.setColor(sf::Color::Transparent);
		choies2.setColor(sf::Color::Transparent);
		textIdSuccess.setFillColor(sf::Color::Transparent);
		SetOrigin(Origins::MC);
	}
	if (textSelec && InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies2.setScale({ 1.1f,1.1f });
		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies1.setScale({ 1.f,1.f });
		SuccessSelec = true;
		FailSelec = false;
		selec = true;
	}
	if (textSelec && InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies1.setScale({ 1.1f,1.1f });
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies2.setScale({ 1.f,1.f });
		FailSelec = true;
		SuccessSelec = false;
		selec = true;
	}
	if (!FailSelec &&!selec  && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		textId.setPosition(-5.f, 370.f);
		textId.setString(textFail);
		textIdSuccess.setString(textSuccess);
		textIdSuccess.setPosition(-5.f, 450.f);
		textIdSuccess.setFillColor(sf::Color::White);

		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies1.setPosition({ textId.getPosition() });
		choies1.setScale({ 1.1f,1.1f });
		choies2.setPosition({ textIdSuccess.getPosition() });
		choies2.setScale({ 1.f,1.f });
		SetOrigin(Origins::MC);

		choies1.setColor(sf::Color::White);
		choies2.setColor(sf::Color::White);

		textSelec = true;
		FailSelec = true;
	}
}

void Pandemonika::Draw(sf::RenderWindow& window)
{
	window.draw(textId);
	window.draw(textId2);
	window.draw(textIdFail);
	window.draw(textIdSuccess);
	window.draw(choies1);
	window.draw(choies2);
}
