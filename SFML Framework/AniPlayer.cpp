#include "stdafx.h"
#include "AniPlayer.h"
#include "AnimationClip.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

AniPlayer::~AniPlayer()
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer::Init()
{
	sortingLayer = SortingLayers::Foreground;

	animator.SetTarget(&body);

	Idle();
	Moving();

	animator.Play(animationMap["Idle"]);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play(animationMap["Idle"]);
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		if(GetPosition().x - 50 > -350.f)
		{
		animator.PlayQueue("Animations/hero/idle.csv");
		animator.Play(animationMap["Move"], false);
		SetScale({ 1.f, 1.f });
		auto move = GetPosition();
		move.x = GetPosition().x - posX;
		SetPosition(move);

		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		if (GetPosition().x + 50 < 250.f)
		{
			animator.PlayQueue("Animations/hero/idle.csv");
			animator.Play(animationMap["Move"], false);
			SetScale({ -1.f, 1.f });
			auto move = GetPosition();
			move.x = GetPosition().x + posX;
			SetPosition(move);
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		if (GetPosition().y - 50 > -250.f)
		{
			animator.PlayQueue("Animations/hero/idle.csv");
			animator.Play(animationMap["Move"], false);
			auto move = GetPosition();
			move.y = GetPosition().y - posY;
			SetPosition(move);
			
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		if (GetPosition().y + 50 < 250.f)
		{
			animator.PlayQueue("Animations/hero/idle.csv");
			animator.Play(animationMap["Move"], false);
			auto move = GetPosition();
			move.y = GetPosition().y + posY;
			SetPosition(move);
		}
	}

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniPlayer::Idle()
{
	AnimationClip* idle = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/idle.csv");

	auto find = animationMap.find("Idle");
	if (find == animationMap.end())
		animationMap.insert({ "Idle", idle });
}

void AniPlayer::Moving()
{
	AnimationClip* move = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Move.csv");

	auto find = animationMap.find("Move");
	if (find == animationMap.end())
		animationMap.insert({ "Move", move });
}

void AniPlayer::Kick()
{
	AnimationClip* kick = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Kick.csv");

	auto find = animationMap.find("Kick");
	if (find == animationMap.end())
		animationMap.insert({ "Kick", kick });
}

void AniPlayer::Death()
{
	AnimationClip* death = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Death.csv");

	auto find = animationMap.find("Death");
	if (find == animationMap.end())
		animationMap.insert({ "Death", death });
}

void AniPlayer::Victory()
{
	AnimationClip* victory = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Victory.csv");

	auto find = animationMap.find("Victory");
	if (find == animationMap.end())
		animationMap.insert({ "Victory", victory });
}
