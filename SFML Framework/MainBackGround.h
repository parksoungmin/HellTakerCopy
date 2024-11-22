#pragma once

class MainBackGround : public GameObject
{
protected:
	sf::Sprite body;
	std::string texture = "graphics/MainBackGround.png";
public:
	 MainBackGround(const std::string& name = "");
	~ MainBackGround() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};
