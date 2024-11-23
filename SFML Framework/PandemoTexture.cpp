#include "stdafx.h"
#include "PandemoTexture.h"
#include "Pandemonika.h"
#include "Stage1ClearScene.h"


PandemoTexture::PandemoTexture(const std::string& name)
	: GameObject(name)
{
}

void PandemoTexture::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}


void PandemoTexture::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void PandemoTexture::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void PandemoTexture::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void PandemoTexture::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

}
void PandemoTexture::Update(float dt)
{
	if (getbool->GetSuccess() && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		body.setTexture(TEXTURE_MGR.Get(ChangeTexture));
		SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/hell/dialogue_success.wav"));
	}
}

void PandemoTexture::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texture));
	SetPosition({ 0.f,-50.f });
	SetOrigin(Origins::MC);
	getbool = dynamic_cast<Stage1ClearScene*>(SCENE_MGR.GetCurrentScene());
}

void PandemoTexture::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
