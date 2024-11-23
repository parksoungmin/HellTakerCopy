#include "stdafx.h"
#include "Stage1ClearScene.h"
#include "MainBackGround.h"
#include "MainMenuDialogue.h"
#include "AniBooper.h"
#include "Pandemonika.h"
#include "PandemoTexture.h"
#include "AniBadEnd.h"
#include "AniSuccess.h"

Stage1ClearScene::Stage1ClearScene() : Scene(SceneIds::Stage1Clear)
{

}

void Stage1ClearScene::Init()
{
	cameraView.setCenter(0.f, 0.f);
	cameraView.setSize(FRAMEWORK.GetWindowSizeFloat());
	mainBack = AddGo(new MainBackGround("mainBack"));
	mainMenuBG = AddGo(new MainMenuDialogue("mainMenuBG"));
	booper = AddGo(new AniBooper("booper"));
	pandemonika = AddGo(new Pandemonika("pandemonika"));
	pandemoTexture = AddGo(new PandemoTexture("pandemoTexture"));
	aniBadEnd = AddGo(new AniBadEnd("aniBadEnd"));
	aniSuccess = AddGo(new AniSuccess("aniSuccess"));
	Scene::Init();
}

void Stage1ClearScene::Enter()
{
	turn = false;
	getSuccess = false;
	restart = false;
	Scene::Enter();
	getSuccess = pandemonika->GetSuccessSelec();
}

void Stage1ClearScene::Exit()
{
	Scene::Exit();
	aniBadEnd->SetActive(false);
}

void Stage1ClearScene::Update(float dt)
{
	if (turn && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::Dev1);
	}
	if (pandemonika->GetSuccessSelec() && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		getSuccess = true;
	}
	if (restart && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	if (getSuccess&& InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		aniSuccess->SetActive(true);
		restart = true;
	}
	if (pandemonika->GetFail() && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/hell/bad_end_screen.wav"));

		aniBadEnd->SetActive(true);
		mainBack->SetSortingOrder(11);
		turn = true;
	}
	Scene::Update(dt);
}
void Stage1ClearScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
