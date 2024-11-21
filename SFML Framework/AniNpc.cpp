#include "stdafx.h"
#include "AniNpc.h"
#include "AnimationClip.h"

AniNpc::AniNpc(const std::string& name)
	: GameObject(name)
{
}

AniNpc::~AniNpc()
{
}

void AniNpc::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniNpc::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniNpc::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniNpc::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniNpc::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniNpc::Init()
{
	sortingLayer = SortingLayers::Foreground;

	animator.SetTarget(&body);

	Idle();
	animator.Play(animationMap["Idle"]);
}

void AniNpc::Release()
{
}

void AniNpc::Reset()
{
	animator.Play(animationMap["Idle"]);
	SetPosition({ 350.f,250.f });
	SetScale({ -1.f,1.f });
	SetOrigin(Origins::MC);
}

void AniNpc::Update(float dt)
{
	animator.Update(dt);
}

void AniNpc::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect AniNpc::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void AniNpc::Idle()
{
	AnimationClip* idle = &ResourceMgr<AnimationClip>::Instance().Get("Animations/npc/1StageNPC.csv");

	auto find = animationMap.find("Idle");
	if (find == animationMap.end())
		animationMap.insert({ "Idle", idle });
}
