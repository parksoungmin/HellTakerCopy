#include "stdafx.h"
#include "AniMonster.h"
#include "AnimationClip.h"

AniMonster::AniMonster(const std::string& name)
	: GameObject(name)
{
}

AniMonster::~AniMonster()
{
}

void AniMonster::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniMonster::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniMonster::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniMonster::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniMonster::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);

}

sf::FloatRect AniMonster::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void AniMonster::Init()
{
	sortingLayer = SortingLayers::Foreground;

	animator.SetTarget(&body);

	Idle();
	HitMonster();

	animator.Play(animationMap["Idle"]);
}

void AniMonster::Release()
{
}

void AniMonster::Reset()
{
	animator.Play(animationMap["Idle"]);
	SetOrigin(Origins::MC);
	SetScale({ -1.f,1.f });
}

void AniMonster::Update(float dt)
{
	animator.Update(dt);
}

void AniMonster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniMonster::Idle()
{
	AnimationClip* idle = &ResourceMgr<AnimationClip>::Instance().Get("Animations/monster/Monster.csv");

	auto find = animationMap.find("Idle");
	if (find == animationMap.end())
		animationMap.insert({ "Idle", idle });
}

void AniMonster::HitMonster()
{
	AnimationClip* hitMonster = &ResourceMgr<AnimationClip>::Instance().Get("Animations/monster/MonsterHit.csv");

	auto find = animationMap.find("Hit");
	if (find == animationMap.end())
	{
		animationMap.insert({ "Hit",hitMonster });
	}
}

void AniMonster::HitingMonster(int dir)
{
	animator.PlayQueue("Animations/monster/Monster.csv");
	animator.Play(animationMap["Hit"], false);
	switch (dir)
	{
	case 0:
		SetPosition({ position.x-posX,position.y });
		if (scale.x > 0)
		{
			scale.x *= -1;
			SetScale(scale);
		}
		break;
	case 1:
		SetPosition({ position.x+posX,position.y });
		if (scale.x < 0)
		{
			scale.x *= -1;
			SetScale(scale);
		}
		break;
	case 2:
		SetPosition({ position.x,position.y-posY });
		break;
	case 3:
		SetPosition({ position.x,position.y+posY});
		break;
	}
}
void AniMonster::HitingMotion()
{
	animator.PlayQueue("Animations/monster/Monster.csv");
	animator.Play(animationMap["Hit"], false);
}

void AniMonster::DieMonster()
{
	SetActive(false);
}
