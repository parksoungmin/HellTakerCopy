#pragma once

class SideGround : public GameObject
{
protected:
	std::string textureId;
	sf::Sprite texture;
public:
	SideGround(const std::string& name = "");
	~SideGround() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};

