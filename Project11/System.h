#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include <map>


using namespace std;
using namespace sf;

class object
{
private:
	static int objectCount;
	string objectType;
	bool visiable = 1;
	Texture texture;
	Sprite objectSprite;
	float scalex = 1;
	float scaley = 1;
	float center_x=0;
	float center_y=0;


public:
	double x, y;
	object(double input_x, double input_y, Texture input_texture) : x(input_x), y(input_y), texture(input_texture) { apply(); }
	
	void setPosition(double input_x, double input_y);
	void setVisiable(bool input_visiable);
	void setObjectType(string input_objectType);
	void setTexture(Texture input_texture);
	void setScale(float input_scalex, float input_scaley);
	void setCenter(float input_x, float input_y);
	void apply();

	pair <float, float> getScale();
	pair<double, double> getPosition();
	bool getVisiable();
	string getObjectType();
	Texture getTexture();
	Sprite getSprite();

};

