#pragma once
class DataTable
{
public:
	enum class Types // 스트링 테이블에서 데이터를 가져올
					 // 리스트를 선언 OR 추가해준다.
	{
		Block1,
		Stage1,
		String,
		Item,
		Monster,
	};
	static const int TotalTypes = 1;

protected:
	Types type;

public:
	virtual bool Load() = 0;
	virtual void Release() = 0;

	virtual void Init();

public:
	DataTable(Types type);
	virtual ~DataTable() = default;
};

