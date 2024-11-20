#pragma once
#include "GameObject.h"
class Stage1TileMap : public GameObject
{
protected:
	sf::VertexArray vertexArray;
	sf::RenderStates renderState;
	std::string spriteSheetId;

	sf::Texture* texture;
	sf::Transform transform;

	sf::Vector2u cellCount;
	sf::Vector2f cellSize= { 100.f,100.f };

	std::list<sf::FloatRect> dontMoveTile;

	std::list<sf::VertexArray> cell3Position;

	std::unordered_map<int, std::vector<int>> tileTypeMap;

	sf::Vector2f direction;

public:

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetInfo(const sf::Vector2u& count, const sf::Vector2f& size);
	void SetTile(std::unordered_map<int, std::vector<int>>& tileType, sf::Vector2i count);
	void UpdateTransform();

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
	std::list<sf::FloatRect> DontMoveBounds();

	const sf::Vector2f& GetCellSize() const { return cellSize; }
	sf::FloatRect GetCell3GetBounds();
public:

	void SetTileCount(sf::Vector2i tileCount);
	sf::Vector2f GetTileSize() { return cellSize; }

	void SetLoadType(std::unordered_map<int, std::vector<int>>& tileMap);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
public:
	Stage1TileMap(const std::string& name = "");
	~Stage1TileMap() = default;
};

