#include "stdafx.h"
#include "SceneDev2.h"
#include "AniPlayer.h"
#include <codecvt>


SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	AddGo(new AniPlayer("ANI TEST"));
	Scene::Init();

}

void SceneDev2::Enter()
{
	Scene::Enter();
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
