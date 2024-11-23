#pragma once

#include "TextGo.h"
#include "SpriteGo.h"

class TitleText : public GameObject
{
protected:
	sf::Text textId;
	sf::Text textId2;
	sf::Text textIdExit;
	std::wstring text1 = L"당신은 주변이 심연으로 둘러쌓인 것을 알아차립니다.\n              [ENTER 버튼] 을 눌러 계속하기.";
	std::wstring text2 = L"환영하네 인간이여. 너무 놀라지 말게나. \n        자네의 친구 베엘제붑일세.";
	std::wstring text3 = L"· 위대한 파리, 베엘제붑 ·";
	std::wstring textNewGame = L"새 게임";
	std::wstring textExit = L"나가기";
	

	sf::Sprite choies1;
	sf::Sprite choies2;

	bool textOn = false;
	bool textSelec = false;
	bool NewGameSelec = false;
	bool ExitSelec = false;
	bool selec = false;
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetString(std::wstring str);

	bool GetNewGameSclec();
	bool GetExitSelec();

public:

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	TitleText(const std::string& name = "");
	~TitleText() = default;
};
