#include "stdafx.h"
#include "ChangeSceneAni.h"

ChangeSceneAni::ChangeSceneAni(const std::string& name)
	: GameObject(name)
{
}

ChangeSceneAni::~ChangeSceneAni()
{
}

void ChangeSceneAni::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void ChangeSceneAni::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void ChangeSceneAni::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void ChangeSceneAni::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void ChangeSceneAni::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void ChangeSceneAni::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 11;

	animator.SetTarget(&body);
	active = false;
	SetChange();
}

void ChangeSceneAni::Release()
{
}

void ChangeSceneAni::Reset()
{
	animator.Play(animationMap["Change"]);
	SetOrigin(Origins::MC);
}

void ChangeSceneAni::Update(float dt)
{
	animator.Update(dt);
}

void ChangeSceneAni::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect ChangeSceneAni::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void ChangeSceneAni::SetChange()
{
	AnimationClip* change = &ResourceMgr<AnimationClip>::Instance().Get("Animations/changeScene/changeScene.csv");

	auto find = animationMap.find("Change");
	if (find == animationMap.end())
		animationMap.insert({ "Change", change });
}

void ChangeSceneAni::OnChange()
{
	active = true;
	Reset();
}
