#pragma once
class DeathBackGround : public GameObject
{
protected:
	std::string textureId;
	sf::Sprite texture;
public:
	DeathBackGround(const std::string& name = "");
	~DeathBackGround() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void SetActive(bool t);
};

