#include "stdafx.h"
#include "Stage1TileMap.h"


Stage1TileMap::Stage1TileMap(const std::string& name)
	: GameObject(name)
	, texture(nullptr)
	, spriteSheetId("graphics/background_sheet.png")
{
}

void Stage1TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void Stage1TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void Stage1TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	//cellSize = cellSize * scale;
	UpdateTransform();
}

void Stage1TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
		UpdateTransform();
	}
}

void Stage1TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void Stage1TileMap::SetTile(std::unordered_map<int, std::vector<int>>& tileType, sf::Vector2i count)
{
	SetScale({ 1.f,1.f });
	SetTileCount(count);
	SetLoadType(tileType);

	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(count.x * count.y * 4);

	texture = &TEXTURE_MGR.Get(spriteSheetId);

	//  타일 당 위치 값, 크기 정하기
	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { 100.f , 0.f }
		, { 100.f , 100.f }
		, { 0.f , 100.f }
	};

	// 텍스쳐 좌표 정하기
	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { 50.f, 0.f}
		, { 50.f, 50.f }
		, {0.f , 50.f }
	};

	for (int i = 0; i < (int)count.y; ++i)
	{
		for (int j = 0; j < (int)count.x; ++j)
		{
			// 사용할 텍스쳐 UV 구하기
			int texIndex = tileType[i][j];
			// 쿼드 좌표
			auto quadIndex = i * count.x + j;
			// 쿼드 위치 값 정하기
			sf::Vector2f quadPosition(j * 100.f, i * 100.f);

			if (texIndex == 0)
			{
				dontMoveTile.push_back({ quadPosition.x, quadPosition.y,100.f,100.f });
			}

			for (int k = 0; k < 4; ++k)
			{
				// 쿼드 생성 시 총 4개의 버텍스가 필요하기 때문에 * 4 및 버텍스 인덱스 구하기
				int vertexIndex = quadIndex * 4 + k;
				// 정점 위치 정하기
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				// 기본 UV 위치 지정
				vertexArray[vertexIndex].texCoords = textUv[k];
				// 텍스쳐에 따라 다른 타일 맵 설정
				vertexArray[vertexIndex].texCoords.y += texIndex * 50.f;
				//if (texIndex == 3)
				cell3Position.push_back(vertexArray);
				
			}
		}
	}
}


void Stage1TileMap::SetTileCount(sf::Vector2i tileCount)
{
	this->tileCount = tileCount;
}

void Stage1TileMap::SetLoadType(std::unordered_map<int, std::vector<int>>& tileMap)
{
	this->tileTypeMap = tileMap;
}

void Stage1TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;

	//SetInfo({ 6,6 }, { 100.f,100.f });
	SetOrigin(Origins::TL);
}

void Stage1TileMap::Release()
{
}

void Stage1TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);
	active = false;
	position = { -440.f,-400.f };
	SetScale(sf::Vector2f::one);
	UpdateTransform();
}

void Stage1TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

sf::FloatRect Stage1TileMap::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y);
}

sf::FloatRect Stage1TileMap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return transform.transformRect(bounds);
}

std::list<sf::FloatRect> Stage1TileMap::DontMoveBounds()
{
	std::list<sf::FloatRect> rtn;
	for (auto& a : dontMoveTile)
	{
		rtn.push_back(transform.transformRect(a));
	}
	return  rtn;
}

sf::FloatRect Stage1TileMap::GetCell3GetBounds()
{
	return sf::FloatRect();
}


void Stage1TileMap::Update(float dt)
{

}

void Stage1TileMap::Draw(sf::RenderWindow& window)
{
	renderState.texture = texture;
	renderState.transform = transform;
	
	window.draw(vertexArray, renderState);
}
