#include "stdafx.h"
#include "SceneTitle.h"
#include "AniPlayer.h"
#include "MainMenuDialogue.h"
#include "TitleText.h"
#include "AniBooper.h"
#include "Beel.h"
#include "MainBackGround.h"

SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{

}
void SceneTitle::Init()
{
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());
	mainMenuBG = AddGo(new MainMenuDialogue("mainMenuBG"));
	titleText = AddGo(new TitleText("titleText"));
	booper = AddGo(new AniBooper("booper"));
	mainBack = AddGo(new MainBackGround("mainBack"));
	beel = AddGo(new Beel("beel"));
	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	if(InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		beel->SetActive(true);
	}
	if (titleText->GetExitSelec()&& InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		FRAMEWORK.GetRenderWindow().close();
	}
	if (titleText->GetNewGameSclec()&& InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::Dev1);
	}
	Scene::Update(dt);
	
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
