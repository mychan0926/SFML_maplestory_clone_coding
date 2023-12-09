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
		if (x != input_gox&& texture_clock == 80)
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
		else if (x == input_gox)
		{
			move_counting = 1;
			setTexture(monster_texture[0]);
		}
		
	}
	void monster::die()
	{
		if (live_clock == 179)
		{
			setTexture(monster_texture[0]);
			T_clock = 100;
			R_clock = 100;
			damage_clock = 0;
			texture_clock = 80;
			death_clock = 0;
			damage_trigger = 0;
			live_clock = 0;
			hp = 100;
		}
		else
		{
			live_clock++;
		}

		if (live_clock == 40)
		{
			setTexture(monster_texture[0]);
			x = startx + rand() % (endx - startx);
		}
		if (live_clock > 50&& live_clock <= 178)
		{
			getSprite().setColor(sf::Color(255, 255, 255, (live_clock - 50) * 2));
		}


		if (live_clock==20)
		{
			setPosition(-1000,y);
		}


	

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
			if (death_clock == 60)
			{
				die();
			}
			else if (death_clock == 0)
			{
				setTexture(monster_texture[5]);
			}
			else if (death_clock == 20)
			{
				setTexture(monster_texture[6]);
			}
			else if (death_clock == 40)
			{
				setTexture(monster_texture[7]);
			}

			if(death_clock!=60)
			{
				death_clock++;
			}
			

		}
		else
		{
			if (texture_clock != 80)
			{
				
	
				if (texture_clock == 0)
				{
					setTexture(monster_texture[3]);

					
				}
				if (texture_clock > 0 && texture_clock < 30)
				{
					if (player_x < x)
					{
						if (x < endx)
						{

							setPosition(x + 1, y);
						}
					}
					else
					{
						if (x >startx)
						{

							setPosition(x - 1, y);
						}
					}
				}
				if (texture_clock == 49)
				{
					setTexture(monster_texture[0]);
					targetx = startx + rand() % (endx - startx);
					T_clock = 150;
					move_counting = 0;
				}

				texture_clock++;


			}

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

			if (damage_clock == 2)
			{
				damage_clock = 0;
				if (is_crash(playero)&& texture_clock == 80)
				{
					is_damaged(50);
				}
			}
			else
			{
				damage_clock++;

			}
		}
	
	}

    void monster::is_damaged(int input_damage)

	{
		texture_clock = 0;
		damage_trigger = 1;
		hp -= input_damage;
	}

	bool monster::is_crash(RectangleShape *T)
	{

		return this->getSprite().getGlobalBounds().intersects(T->getGlobalBounds());
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



