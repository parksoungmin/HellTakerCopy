#include "stdafx.h"
#include "AniPlayerDie.h"
#include "AnimationClip.h"

AniPlayerDie::AniPlayerDie(const std::string& name)
	: GameObject(name)
{
}

AniPlayerDie::~AniPlayerDie()
{
}

void AniPlayerDie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayerDie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniPlayerDie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniPlayerDie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayerDie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayerDie::Init()
{
	sortingLayer = SortingLayers::Foreground;

	animator.SetTarget(&body);

	Idle();
	animator.Play(animationMap["Die"]);
}

void AniPlayerDie::Release()
{
}

void AniPlayerDie::Reset()
{
	animator.Play(animationMap["Die"]);
	SetPosition({ 0,0 });
	SetScale({ -1.f,1.f });
	SetOrigin(Origins::MC);
}

void AniPlayerDie::Update(float dt)
{
	animator.Update(dt);
}

void AniPlayerDie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect AniPlayerDie::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void AniPlayerDie::Idle()
{
	AnimationClip* die = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Death.csv");

	auto find = animationMap.find("Die");
	if (find == animationMap.end())
		animationMap.insert({ "Die", die });
}
