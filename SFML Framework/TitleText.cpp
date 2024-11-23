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
		origin = Utils::SetOrigin(choies1, originPreset);
		origin = Utils::SetOrigin(choies2, originPreset);
		origin = Utils::SetOrigin(textIdExit, originPreset);
	}
}

void TitleText::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	textId.setOrigin(origin);
	textId2.setOrigin(origin);
	choies1.setOrigin(origin);
	choies2.setOrigin(origin);
	textIdExit.setOrigin(origin);
}

void TitleText::SetString(std::wstring str)
{
	textId.setString(str);
}

bool TitleText::GetNewGameSclec()
{
	return NewGameSelec;
}

bool TitleText::GetExitSelec()
{
	return ExitSelec;
}

void TitleText::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetString(text1);
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

	SetString(text1);
	textId.setPosition(0.f, 360.f);
	textId.setScale({ 0.6f,0.6f });

	textId2.setScale({ 0.7f,0.7f });
	textId2.setFont(fontbd);
	textId2.setCharacterSize(textSize);
	textId2.setFillColor(sf::Color::Red);

	textIdExit.setScale({ 0.6f,0.6f });
	textIdExit.setFont(font);
	textIdExit.setCharacterSize(textSize);
	textIdExit.setFillColor(sf::Color::White);

	SetOrigin(Origins::MC);
}

void TitleText::Update(float dt)
{
	if (textSelec && InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies2.setScale({ 1.1f,1.1f });
		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies1.setScale({ 1.f,1.f });
		ExitSelec = true;
		NewGameSelec = false;
		selec = true;
	}
	if (textSelec && InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies1.setScale({ 1.1f,1.1f });
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies2.setScale({ 1.f,1.f });
		NewGameSelec = true;
		ExitSelec = false;
		selec = true;

	}
	if (!selec && textOn && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		textId.setString(textNewGame);
		textId.setPosition(-5.f, 370.f);
		textIdExit.setString(textExit);
		textIdExit.setPosition(-5.f, 450.f);
		choies1.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Selected.png"));
		choies2.setTexture(TEXTURE_MGR.Get("graphics/MenuBar_Unselected.png"));
		choies1.setPosition({ textId.getPosition() });
		choies1.setScale({ 1.1f,1.1f });
		choies2.setPosition({ textIdExit.getPosition() });
		choies2.setScale({ 1.f,1.f });
		SetOrigin(Origins::MC);
		textSelec = true;	
		NewGameSelec = true;
	}
	else if(!selec&&InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		textOn = true; 
		SetString(text2);
		textId.setPosition(10.f, 400.f);

		textId2.setString(text3);
		textId2.setPosition(0.f, 295.f);
		SetOrigin(Origins::MC);
	}

}

void TitleText::Draw(sf::RenderWindow& window)
{
	window.draw(textId);
	window.draw(textId2);
	window.draw(textIdExit);
	window.draw(choies1);
	window.draw(choies2);
}
