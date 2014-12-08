
#ifndef ASSET_H
#define ASSET_H

class AssetManager;

class Asset
{
	friend class AssetManager;
public:
	virtual ~Asset() { };
private:
	size_t m_UseCount;
	size_t m_Type;
};

#endif // Include guard
