#include "stdafx.h"
#include "AniPlayerDie.h"
#include "AnimationClip.h"
#include "Scene.h"
#include "SceneStage1.h"

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
	sortingOrder = 10;

	animator.SetTarget(&body);
	active = false;
	stage1 = dynamic_cast<SceneStage1*>(SCENE_MGR.GetCurrentScene());
	SetDie();
	SetChange();
}

void AniPlayerDie::Release()
{
}

void AniPlayerDie::Reset()
{
	animator.Play(animationMap["Die"]);
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

void AniPlayerDie::SetDie()
{
	AnimationClip* die = &ResourceMgr<AnimationClip>::Instance().Get("Animations/hero/Death.csv");

	auto find = animationMap.find("Die");
	if (find == animationMap.end())
		animationMap.insert({ "Die", die });
}

void AniPlayerDie::OnDie()
{
	stage1->SetLife();
	active=true;
	animator.Play(animationMap["Die"]);
	SetOrigin(Origins::MC);
	animator.ClearEvent("Death", 15);
	animator.AddEvent("Death", 15, std::bind(&AniPlayerDie::ChangeScene, this));
}

void AniPlayerDie::SetChange()
{
	AnimationClip* change = &ResourceMgr<AnimationClip>::Instance().Get("Animations/changeScene/changeScene.csv");

	auto find = animationMap.find("Change");
	if (find == animationMap.end())
		animationMap.insert({ "Change", change });

	animator.ClearEvent("Death", 15);
}

void AniPlayerDie::ChangeScene()
{
	/*SceneMgr::Instance().ChangeScene(SceneIds::Dev2);*/
	active = true;
	animator.Play(animationMap["Change"]);
	body.setPosition({ -550.f,20.f });
	animator.ClearEvent("Death", 1);
	animator.AddEvent("Change", 27, std::bind(&AniPlayerDie::Restart, this));
	animator.ClearEvent("Change", 30);
}

void AniPlayerDie::SceneSet()
{
}

void AniPlayerDie::Restart()
{
	SceneMgr::Instance().ChangeScene(SceneIds::Dev1);
	active = false;
	animator.ClearEvent("Change", 1);
}
