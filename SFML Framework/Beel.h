#pragma once

class Beel : public GameObject
{
protected:
	sf::Sprite body;
	std::string texture = "graphics/BackGround/Beel_Fly.png";
public:
	Beel(const std::string& name = "");
	~Beel() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Update(float dt);
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};
