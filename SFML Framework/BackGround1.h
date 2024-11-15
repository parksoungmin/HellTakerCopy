#pragma once

class BackGround1 : public GameObject
{
protected:
	std::string textureId;
	sf::Sprite texture;
public:
	BackGround1(const std::string& name = "");
	~BackGround1() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};


