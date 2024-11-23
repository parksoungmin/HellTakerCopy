#pragma once

class Stage1ClearScene;

class PandemoTexture : public GameObject
{
protected:
	sf::Sprite body;
	std::string texture = "Resources/Character/1StageNPC/1stageScene/Pand_Idle.png";
	std::string ChangeTexture = "Resources/Character/1StageNPC/1stageScene/Pand_Flust.png";

	Stage1ClearScene* getbool;
public:
	PandemoTexture(const std::string& name = "");
	~PandemoTexture() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Update(float dt);
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};
