#include "stdafx.h"
#include "AniBadEnd.h"
#include "AnimationClip.h"

AniBadEnd::AniBadEnd(const std::string& name)
	: GameObject(name)
{
}

AniBadEnd::~AniBadEnd()
{
}

void AniBadEnd::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniBadEnd::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniBadEnd::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniBadEnd::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniBadEnd::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniBadEnd::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 12;
	active = false;
	animator.SetTarget(&body);

	Idle();
	animator.Play(animationMap["Fail"]);
}

void AniBadEnd::Release()
{
}

void AniBadEnd::Reset()
{
	animator.Play(animationMap["Fail"]);
	SetPosition({ 0.f,0.f });
	SetScale({ 1.f,1.f });
	SetOrigin(Origins::MC);
}

void AniBadEnd::Update(float dt)
{
	animator.Update(dt);
}

void AniBadEnd::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniBadEnd::Idle()
{
	AnimationClip* fail = &ResourceMgr<AnimationClip>::Instance().Get("Animations/Fail/Fail.csv");

	auto find = animationMap.find("Fail");
	if (find == animationMap.end())
		animationMap.insert({ "Fail", fail });
}
