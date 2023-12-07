#include "System.h"
using namespace std;
using namespace sf;

void keyPressup();
void keyPressdown();
void keyPressright();
void keyPressleft();

float player_speed = 0;
float player_acc = 0.15;
float playertx_sizex = 1;
float playertx_sizey = 1;
bool jumped = 1;
int state = 0; //0은 서있기, 1은 걷기, 2는 점프
int jump_counting = 0;
int down_counting = 200;
int walk_animate = 0;
int attack_animate = 0;
bool one_count = 0;
int rotate = 1;

Texture playertx_wait;
Texture playertx_walk1;
Texture playertx_walk2;
Texture playertx_walk3;
Texture playertx_walk4;
Texture playertx_attack1;
Texture playertx_attack2;
Texture playertx_attack3;
Texture playertx_jump;
Texture guitx;
Texture maptx;
Texture guibacktx;

object player(500, 500, playertx_wait);

void player_animate_change()
{
	if (state == 0)
	{
		player.setTexture(playertx_wait );
		walk_animate = 0;
		attack_animate = 0;
	}
	else if (state == 1)
	{
		attack_animate = 0;
		walk_animate++;
		if (walk_animate > 60)
		{

			walk_animate = 0;
		}
		if (walk_animate == 0)
		{
			player.setTexture(playertx_walk1);
		}
		if (walk_animate == 15)
		{
			player.setTexture(playertx_walk2);
		}
		if (walk_animate == 30)
		{
			player.setTexture(playertx_walk3);
		}
		if (walk_animate == 45)
		{
			player.setTexture(playertx_walk4);
		}

	
	}
	else if (state == 2)
	{
		player.setTexture(playertx_jump);
		walk_animate = 0;
		attack_animate = 0;
	}
	else if (state == 3)
	{
		walk_animate = 0;
		attack_animate++;
		if (attack_animate > 60)
		{
			state = 0;
			attack_animate = 0;
		}
		if (attack_animate == 0)
		{
			player.setTexture(playertx_attack1);
		}
		if (attack_animate == 20)
		{
			player.setTexture(playertx_attack2);
		}
		if (attack_animate == 40)
		{
			player.setTexture(playertx_attack3);
		}
	
	}
}


int main()
{
	RenderWindow window(VideoMode(800, 600), "HW Engine");
	window.setFramerateLimit(100);
	Text text;
	Font font;
	player.setCenter(player.getSprite().getLocalBounds().width / 2+70, player.getSprite().getLocalBounds().height / 2+90);

	Vector2i mouse_pos;
	if (!font.loadFromFile("./text_file/arial.ttf"))
	{
		cout << "can't load font file.";
		return 0;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Blue);
	View camera(FloatRect(0, 0, 800, 600));
	window.setView(camera);





	playertx_wait.loadFromFile("./texture_asset/메이플 에셋/서기/avatar_stand1(0)_default(0).png");
	playertx_walk1.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(0)_default(0).png");
	playertx_walk2.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(1)_default(0).png");
	playertx_walk3.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(2)_default(0).png");
	playertx_walk4.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(3)_default(0).png");
	playertx_jump.loadFromFile("./texture_asset/메이플 에셋/점프/avatar_jump(0)_default(0).png");
	playertx_attack1.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_stand1(2)_default(0).png");
	playertx_attack2.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_swingO1(1)_default(0).png");
	playertx_attack3.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_swingO1(2)_default(0).png");



	maptx.loadFromFile("./texture_asset/map.png");
	guitx.loadFromFile("./texture_asset/level.png");
	guibacktx.loadFromFile("./texture_asset/_outlink.png");






	object map(0, 0, maptx);
	object GUI(500, 500, guitx);
	object GUI_background(500, 500, guibacktx);
	vector <RectangleShape> road;


	RectangleShape crash;
	crash.setSize(Vector2f(15, 5));

	crash.setFillColor(sf::Color(255, 255, 255, 0));

	vector <vector<float>> road_pos;
	road_pos = { {2000, 100,0, 1035}, {500, 10,330, 790},{310, 10,875, 790},{400, 10,1240, 790} };


	for (int i = 0; i < road_pos.size(); i++)
	{
		RectangleShape T_road;
		T_road.setSize(Vector2f(road_pos[i][0], road_pos[i][1]));
		T_road.setPosition(Vector2f(road_pos[i][2], road_pos[i][3]));
		T_road.setFillColor(sf::Color(255, 255, 255, 0));
		road.push_back(T_road);

	}



	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Space)) {

			if (Keyboard::isKeyPressed(Keyboard::Down)) { //키를 누르고, 아래바닥이 아니면

				if (!crash.getGlobalBounds().intersects(road[0].getGlobalBounds()))
				{
					if (!jumped && state != 3) //점프중이 아니면
					{
						player_speed -= 2;
						jumped = 1;
						down_counting = 0;
					}
				}
				else//19 24
				{
					if (!jumped&&state!=3) //점프중이 아니면
					{
						player_speed -= 2;
						jumped = 1;
						jump_counting = 0;


					}

				}

			}
			else
			{
				if (!jumped)
				{
					player_speed -= 4;
					jumped = 1;
					jump_counting = 0;
				}
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (state != 2&&state!=3)
			{
				state = 3;
			}
		}


		jump_counting++;
		down_counting++;
		if (jump_counting > 300)
		{
			jump_counting = 300;
		}
		if (down_counting > 300)
		{
			down_counting = 300;
		}
		player.setPosition(player.x, player.y + player_speed);

		//땅 충돌 처리
		{

			if (crash.getGlobalBounds().intersects(road[0].getGlobalBounds()))
			{


				jumped = 0;
				jump_counting = 200;
				player_speed = 0;
				down_counting = 200;
			}

			for (int i = 1; i < road.size(); i++)
			{
				if (crash.getGlobalBounds().intersects(road[i].getGlobalBounds()))
				{

					if (down_counting > 50)
					{

						jumped = 0;
						jump_counting = 200;
						player_speed = 0;
						down_counting = 200;
					}
				}
			}

		}


		if (jumped)
		{
			one_count = 1;
			state = 2;
			if (jump_counting > 10)
			{
				player_speed += player_acc;
			}
		}
		else
		{

			if (one_count == 1)
			{
				one_count = 0;
				state = 0;
			}
			player_speed = 0;

		}



		if (Keyboard::isKeyPressed(Keyboard::Up)) {

		}


		else if (Keyboard::isKeyPressed(Keyboard::Down)) {

		}




		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (state != 3)
			{


				player.setScale(1.f, 1.f);
				player.setPosition(player.x - 2, player.y);

				if (state != 2)
				{
					state = 1;
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (state != 3)
			{

				player.setScale(-1.f, 1.f);
				player.setPosition(player.x + 2, player.y);

				if (state != 2)
				{
					state = 1;
				}
			}
		}
		else
		{
			if (state != 2&&state!=3)
			{
				state = 0;
			}
		}




	

		player_animate_change();
	

		//카메라 설정
		{
		if (player.x- camera.getSize().x / 2 >0&& player.x + camera.getSize().x / 2 < 1980)
		{
			camera.setCenter(Vector2f(player.x, camera.getCenter().y));
		}

		if (player.y - camera.getSize().y / 2 > 0 && player.y + camera.getSize().y / 2 < 1230)
		{
			camera.setCenter(Vector2f(camera.getCenter().x,player.y ));
		}




			float posInView_x = camera.getCenter().x - camera.getSize().x / 2;
			float posInView_y = camera.getCenter().y - camera.getSize().y / 2;

			text.setPosition(posInView_x, posInView_y);
			text.setString(to_string(player.x) + ' ' + to_string(player.y) + ' ' + to_string(!crash.getGlobalBounds().intersects(road[0].getGlobalBounds())));
			GUI_background.setPosition(posInView_x, posInView_y + 530);
			GUI.setPosition(posInView_x, posInView_y + 530);
			crash.setPosition(Vector2f(player.x - 14, player.y + 10 + player_speed));



			mouse_pos = Mouse::getPosition(window);



			window.setView(camera);

		}
		// 화면 그리기 담당
		{
			window.clear();

			window.draw(map.getSprite());
			window.draw(text);

			for (int i = 0; i < road.size(); i++)
			{
				window.draw(road[i]);
			}

			window.draw(player.getSprite());
			window.draw(crash);
			window.draw(GUI_background.getSprite());
			window.draw(GUI.getSprite());
			window.display();

		}
	}

	return 0;

}
