#pragma once

class MainMenuDialogue : public GameObject
{
protected:
	sf::Sprite body;
	sf::Sprite body2;
	std::string textureId = "graphics/MainMenuDialogue_001.png";

	float speed = 100.f;
public:
	MainMenuDialogue(const std::string& name = "");
	~MainMenuDialogue() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};


