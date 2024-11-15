#pragma once

class Block1 : public GameObject
{
public:
	enum class Types
	{
		Block1,
		Block2,
		Block3,
		Block4,
	};
protected:

	sf::Sprite body;
	Types types = Types::Block1;
	std::string textureId;
	float positionX;
	float positionY;

public:
	Block1(const std::string& name = "");
	~Block1() = default;

	void SetType(Types type);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& s) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetPosition() { return { positionX, positionY };}

};
