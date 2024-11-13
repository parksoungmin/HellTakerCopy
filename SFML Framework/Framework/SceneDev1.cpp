#include "stdafx.h"
#include "SceneDev1.h"
#include "AniPlayer2.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	AddGo(new AniPlayer2("Player"));

	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();
	
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());

	std::ifstream f("json/example.json");
	json data = json::parse(f);

	std::cout << data.at("pi").get<double>() << std::endl;
	std::cout << data.dump(10) << std::endl;
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
