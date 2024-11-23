#include "stdafx.h"
#include "AniSuccess.h"
#include "AnimationClip.h"

AniSuccess::AniSuccess(const std::string& name)
	: GameObject(name)
{
}

AniSuccess::~AniSuccess()
{
}

void AniSuccess::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniSuccess::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniSuccess::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniSuccess::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniSuccess::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniSuccess::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 12;
	active = false;
	animator.SetTarget(&body);
	Idle();
	animator.Play(animationMap["Success"]);
}

void AniSuccess::Release()
{
}

void AniSuccess::Reset()
{
	animator.Play(animationMap["Success"]);
	SetPosition({ 0.f,430.f });
	SetScale({ 1.f,1.f });
	SetOrigin(Origins::MC);
}

void AniSuccess::Update(float dt)
{
	animator.Update(dt);
}

void AniSuccess::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniSuccess::Idle()
{
	AnimationClip* success = &ResourceMgr<AnimationClip>::Instance().Get("Animations/Success/Success.csv");

	auto find = animationMap.find("Success");
	if (find == animationMap.end())
		animationMap.insert({ "Success", success });
}
