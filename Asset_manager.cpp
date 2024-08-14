#include "Asset_manager.h"

void AssetManager::createManager(Texture& aset, int x, int y, int w, int h)
{
	assetList[++valueAssets] = Asset(aset, x, y, w, h);
}

void AssetManager::draw(RenderWindow& window)
{
	window.draw(assetList[assetNumber].sprite);
}

void AssetManager::set(int number)
{
	assetNumber = number;
}

void AssetManager::setPos(float posX, float posY)
{
	assetList[assetNumber].sprite.setPosition(posX, posY);
}

void AssetManager::set_scale(int number, float x, float y)
{
	assetNumber = number;
	assetList[assetNumber].sprite.setScale(x, y);
}

void AssetManager::rotate_asset(int number, float x)
{
	assetNumber = number;
	assetList[assetNumber].sprite.rotate(x);
}
