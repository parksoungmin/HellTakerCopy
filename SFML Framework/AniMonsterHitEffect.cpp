#include "stdafx.h"
#include "AniMonsterHitEffect.h"


AniMonsterHitEffect::AniMonsterHitEffect(const std::string& name)
	: GameObject(name)
{
}

AniMonsterHitEffect::~AniMonsterHitEffect()
{
}

void AniMonsterHitEffect::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniMonsterHitEffect::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniMonsterHitEffect::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniMonsterHitEffect::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniMonsterHitEffect::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);

}

sf::FloatRect AniMonsterHitEffect::GetGlobalBounds() const
{
	return  body.getGlobalBounds();
}

void AniMonsterHitEffect::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 10;
	HitEffect();
	animator.SetTarget(&body);
	SetActive(false);
}

void AniMonsterHitEffect::Release()
{
}

void AniMonsterHitEffect::Reset()
{
	animator.Play(animationMap["Hit"]);
	SetOrigin(Origins::MC);
	SetScale({ -1.f,1.f });
}

void AniMonsterHitEffect::Update(float dt)
{
	animator.Update(dt);

	if (!animator.IsPlaying())
		active = false;
}

void AniMonsterHitEffect::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniMonsterHitEffect::PlayAnimation(const std::string& id)
{
	active = true;
	animator.Play(animationMap[id]);
}

void AniMonsterHitEffect::HitEffect()
{
	AnimationClip* Hit = &ResourceMgr<AnimationClip>::Instance().Get("Animations/monster/Effect/MonsterHit.csv");

	auto find = animationMap.find("Hit");
	if (find == animationMap.end())
		animationMap.insert({ "Hit", Hit });
}

