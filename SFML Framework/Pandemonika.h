#pragma once

#include "TextGo.h"
#include "SpriteGo.h"

class Pandemonika : public GameObject
{
protected:
	sf::Text textId;
	sf::Text textId2;
	sf::Text textIdSuccess;
	sf::Text textIdFail;
	std::wstring text1 = L"지옥 고객 서비스 센터의 판데모니카입니다.\n             무엇을 도와드릴까요?";
	std::wstring text3 = L"· 지친 악마, 판데모니카 ·";
	std::wstring textFail = L"우리 집에 한번 오면 알게 될거야.";
	std::wstring textSuccess = L"오히려'그 쪽'을 도와줘야 할 판인데?";
	std::wstring fail = L"   지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.";
	std::wstring success = L" 그래주면 좋겠네요. 지금 커피 한잔이 너무 마시고 싶은데. \n                    지금 제정신이 아니네요.";
	 

	sf::Sprite choies1;
	sf::Sprite choies2;

	bool textOn = false;
	bool textSelec = false;
	bool SuccessSelec = false;
	bool FailSelec = false;
	bool selec = false;
	bool failbool = false;
	bool fix = false;
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetString(std::wstring str);

	bool GetFail();
	bool GetSuccessSelec();

public:

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	Pandemonika(const std::string& name = "");
	~Pandemonika() = default;
};
