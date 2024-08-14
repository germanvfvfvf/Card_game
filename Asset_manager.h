#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Asset
{
public:
	Sprite sprite;

	Asset() {}
	Asset(Texture& aset, int x, int y, int w, int h)
	{
		sprite.setTexture(aset);
		sprite.setTextureRect(IntRect(x, y, w, h));
	}
};

class AssetManager
{
public:


	std::map<int, Asset> assetList;
	int valueAssets = 0;
	int assetNumber = 0;

	void createManager(Texture& aset, int x, int y, int w, int h);
	void draw(RenderWindow& window);
	void set(int number);
	void setPos(float posX, float posY);
	void set_scale(int number, float x, float y);
	void rotate_asset(int number, float x);
};



