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

	void monster::setHp(int input_hp)
	{
		hp = input_hp;
	}

	void monster::setDamage(int input_damage)
	{
		damage = input_damage;
	}

	void monster::setStartx(int input_startx)
	{
		startx = input_startx;
	}

	void monster::setEndx(int input_endx)
	{
		endx = input_endx;
	}

	int monster::getHp()
	{
		return hp;
	}

	int monster::getDamage()
	{
		return damage;
	}

	int monster::getStartx()
	{
		return startx;
	}

	int monster::getEndx()
	{
		return endx;
	}

	void monster::move(int input_gox)
	{
		if (x != input_gox)
		{
			if (x < input_gox)
			{
				setPosition(x + 1, y);
				setScale(-1,1);
			}
			else
			{
				setPosition(x - 1, y);
				setScale(1, 1);
			}
			move_animate();
		}
		else
		{
			move_counting = 1;
			setTexture(monster_texture[0]);
		}
		
	}
	void monster::die()
	{

	}
	void monster::move_animate()
	{
		if (A_clock == 90)
		{
			A_clock = 0;
		}
		if (A_clock == 0)
		{
			setTexture(monster_texture[0]);
		}
		if (A_clock == 30)
		{
			setTexture(monster_texture[1]);
		}
		if (A_clock == 60)
		{
			setTexture(monster_texture[2]);
		}

		A_clock++;
	}

	void monster::schedule()
	{
		if (hp <= 0)
		{
			die();
		}
		else
		{
			if (T_clock == 200)
			{
				move(targetx);
				if (move_counting)
				{
					targetx = startx + rand() % (endx - startx);
					T_clock = 1;
					move_counting = 0;
				}

			}
			else
			{
				T_clock++;
			}

		}
	
	}

    void monster::is_damaged(int input_damage)

	{
		hp -= input_damage;
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



