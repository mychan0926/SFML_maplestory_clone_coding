#include "System.h"
using namespace std;
using namespace sf;



	void object::setPosition(double input_x, double input_y)
	{
		x = input_x;
		y = input_y;
		apply();
	}
	void object::setVisiable(bool input_visiable)
	{
		visiable = input_visiable;
		apply();
	}
	void object::setObjectType(string input_objectType)
	{
		input_objectType = objectType;
		apply();
	}
	void object::setTexture(Texture input_texture)
	{

		texture = input_texture;

		apply();
	}
	void object::setScale(float input_scalex, float input_scaley)
	{

		scalex = input_scalex;
		scaley = input_scaley;

		apply();
	}
	void object::setCenter(float input_x, float input_y)
	{

		center_x = input_x;
		center_y = input_y;
		apply();
	}

	void object::apply()
	{
		objectSprite.setTexture(texture);
		objectSprite.setTextureRect({ 0,0, int(objectSprite.getTexture()->getSize().x), int(objectSprite.getTexture()->getSize().y) });
		objectSprite.setOrigin(center_x,center_y);
		objectSprite.setPosition(x,y);



		objectSprite.setScale(scalex,scaley);
	}



	pair<double, double> object:: getPosition()
	{
		return { x,y };
	}
	bool object::getVisiable()
	{
		return visiable;
	}
	string object::getObjectType()
	{
		return objectType;
	}
	Texture object::getTexture()
	{
		return texture;
	}
	Sprite object::getSprite()
	{
		return objectSprite;
	}



