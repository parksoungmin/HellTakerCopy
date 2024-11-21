#pragma once

class AniNpc : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	sf::Vector2f velocity = { 0.f,0.f };

	std::unordered_map<std::string, AnimationClip*> animationMap;


public:
	AniNpc(const std::string& name = "");
	~AniNpc();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetGlobalBounds() const override;
	void Idle();
};
