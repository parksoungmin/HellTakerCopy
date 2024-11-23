#pragma once
#include "Scene.h"

class MainBackGround;
class MainMenuDialogue;
class AniBooper;
class Pandemonika;
class PandemoTexture;
class AniBadEnd;
class AniSuccess;

class Stage1ClearScene : public Scene
{
protected:
	MainBackGround* mainBack;
	MainMenuDialogue* mainMenuBG;
	AniBooper* booper;
	Pandemonika* pandemonika;
	PandemoTexture* pandemoTexture;
	AniBadEnd* aniBadEnd;
	AniSuccess* aniSuccess;

	bool turn = false;
	bool getSuccess = false;
	bool successOn = false;
	bool changeScene = false;
public:
	Stage1ClearScene();
	~Stage1ClearScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	bool GetSuccess() { return getSuccess; }

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

