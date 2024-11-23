#pragma once

#include "TextGo.h"
#include "SpriteGo.h"

class TitleText : public GameObject
{
protected:
	sf::Text textId;
	sf::Text textId2;
	sf::Text textIdExit;
	std::wstring text1 = L"����� �ֺ��� �ɿ����� �ѷ����� ���� �˾������ϴ�.\n              [ENTER ��ư] �� ���� ����ϱ�.";
	std::wstring text2 = L"ȯ���ϳ� �ΰ��̿�. �ʹ� ����� ���Գ�. \n        �ڳ��� ģ�� ���������ϼ�.";
	std::wstring text3 = L"�� ������ �ĸ�, �������� ��";
	std::wstring textNewGame = L"�� ����";
	std::wstring textExit = L"������";
	

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
