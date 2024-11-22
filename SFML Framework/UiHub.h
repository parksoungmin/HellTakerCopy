#pragma once

#include "TextGo.h"
#include "SpriteGo.h"

class UiHub : public GameObject
{
protected:
	sf::Text textLife;


public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetLife(int life);

public:
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	UiHub(const std::string& name = "");
	~UiHub() = default;
};
