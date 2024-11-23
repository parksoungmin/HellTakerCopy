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
	std::wstring text1 = L"���� �� ���� ������ �ǵ����ī�Դϴ�.\n             ������ ���͵帱���?";
	std::wstring text3 = L"�� ��ģ �Ǹ�, �ǵ����ī ��";
	std::wstring textFail = L"�츮 ���� �ѹ� ���� �˰� �ɰž�.";
	std::wstring textSuccess = L"������'�� ��'�� ������� �� ���ε�?";
	std::wstring fail = L"   ������ ��Ƽ� ���� ������ �Ѱž�? ���� ���ϼŶ�.";
	std::wstring success = L" �׷��ָ� ���ڳ׿�. ���� Ŀ�� ������ �ʹ� ���ð� ������. \n                    ���� �������� �ƴϳ׿�.";
	 

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
