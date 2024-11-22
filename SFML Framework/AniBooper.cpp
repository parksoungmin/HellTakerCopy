#include "stdafx.h"
#include "AniBooper.h"
#include "AnimationClip.h"

AniBooper::AniBooper(const std::string& name)
	: GameObject(name)
{
}

AniBooper::~AniBooper()
{
}

void AniBooper::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniBooper::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniBooper::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniBooper::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniBooper::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniBooper::Init()
{
	sortingLayer = SortingLayers::Foreground;

	animator.SetTarget(&body);

	Idle();
	animator.Play(animationMap["Idle"]);
}

void AniBooper::Release()
{
}

void AniBooper::Reset()
{
	animator.Play(animationMap["Idle"]);
	SetPosition({ 0.f,500.f });
	SetScale({ 1.f,1.f });
	SetOrigin(Origins::MC);
}

void AniBooper::Update(float dt)
{
	animator.Update(dt);
}

void AniBooper::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect AniBooper::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void AniBooper::Idle()
{
	AnimationClip* idle = &ResourceMgr<AnimationClip>::Instance().Get("Animations/booper/Booper.csv");

	auto find = animationMap.find("Idle");
	if (find == animationMap.end())
		animationMap.insert({ "Idle", idle });
}
