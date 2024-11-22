#pragma once
#include "Scene.h"

class AniBooper;
class MainMenuDialogue;
class TitleText;
class Beel;
class MainBackGround;

class SceneTitle : public Scene
{
protected:
	Beel* beel;
	MainBackGround* mainBack;
	AniBooper* booper;
	TitleText* titleText;
	MainMenuDialogue* mainMenuBG;
public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

