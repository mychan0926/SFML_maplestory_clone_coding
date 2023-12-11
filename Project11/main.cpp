#include "System.h"
using namespace std;
using namespace sf;


float player_speed = 0;
float player_acc = 0.18;
float playertx_sizex = 1;
float playertx_sizey = 1;
bool jumped = 1;
int player_level = 1;
int player_EXP = 0;
int player_damage = 20;
int state = 0; //0은 서있기, 1은 걷기, 2는 점프
int jump_counting = 0;
int down_counting = 200;
int walk_animate = 0;
int attack_animate = 0;
int rope_animate = 0;
bool one_count = 0;
int player_rotate = 0;
int is_rope = 0;
int effect_clock = 60;
int player_skill = 0;
Texture playertx_wait;
Texture playertx_walk1;
Texture playertx_walk2;
Texture playertx_walk3;
Texture playertx_walk4;
Texture playertx_attack11;
Texture playertx_attack12;
Texture playertx_attack13;
Texture playertx_jump;
Texture guitx;
Texture maptx;
Texture guibacktx;
Texture playertx_rope1;
Texture playertx_rope2;
Texture monster_move1;
Texture monster_move2;
Texture monster_move3;
Texture monster_back;
Texture monster_damaged;
Texture monster_die1;
Texture monster_die2;
Texture monster_die3;
//==============================
Texture playertx_attack21;
Texture playertx_attack22;
Texture playertx_attack23;
Texture playertx_attack31;
Texture playertx_attack32;
Texture playertx_attack33;

//=============================




vector <Texture> effect_tx;

object player(500, 500, playertx_wait);
void d()
{
	player_EXP += 20;
}

void player_animate_change()
{
	if (state == 0)
	{
		player.setTexture(playertx_wait);
		walk_animate = 0;
		attack_animate = 0;
		rope_animate = 0;
	}
	else if (state == 1)
	{
		attack_animate = 0;
		rope_animate = 0;
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
		rope_animate = 0;
	}
	else if (state == 3)
	{
		walk_animate = 0;
		rope_animate = 0;
		attack_animate++;

		if (attack_animate > 80)
		{
			state = 0;
			attack_animate = 0;
		}
		if (attack_animate == 0)
		{
			player.setTexture(playertx_attack11);
		}
		if (attack_animate == 20)
		{
			player.setTexture(playertx_attack12);
		}
		if (attack_animate == 40)
		{
			player.setTexture(playertx_attack13);
		}
	
	}
	else if (state == 4)
	{
		walk_animate = 0;
		attack_animate = 0;


		if (rope_animate > 60)
		{
			rope_animate = 0;
		}
		if (rope_animate == 0)
		{
			player.setTexture(playertx_rope1);
		}
		if (rope_animate == 30)
		{
			player.setTexture(playertx_rope2);
		}
	}
}


int main()
{
	RenderWindow window(VideoMode(800, 600), "HW Engine");
	window.setFramerateLimit(100);
	Text text;
	Font font;
	player.setCenter(player.getSprite().getLocalBounds().width / 2+132, player.getSprite().getLocalBounds().height / 2+155);
	srand(time(NULL));
	Vector2i mouse_pos;
	if (!font.loadFromFile("./text_file/gulim.ttc"))
	{
		cout << "can't load font file.";
		return 0;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
	View camera(FloatRect(0, 0, 800, 600));
	window.setView(camera);

	Sound s;
	Sound s1;
	Sound s2;
	Sound s3;

	SoundBuffer Sattack;
	SoundBuffer Snormalattack;
	SoundBuffer Slevel;
	SoundBuffer Sjump;

	playertx_wait.loadFromFile("./texture_asset/메이플 에셋/서기/avatar_stand1(0)_default(0).png");
	playertx_walk1.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(0)_default(0).png");
	playertx_walk2.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(1)_default(0).png");
	playertx_walk3.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(2)_default(0).png");
	playertx_walk4.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(3)_default(0).png");
	playertx_jump.loadFromFile("./texture_asset/메이플 에셋/점프/avatar_jump(0)_default(0).png");
	playertx_attack11.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_stand1(2)_default(0).png");
	playertx_attack12.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_swingO1(1)_default(0).png");
	playertx_attack13.loadFromFile("./texture_asset/메이플 에셋/공격1/avatar_swingO1(2)_default(0).png");
	playertx_rope1.loadFromFile("./texture_asset/메이플 에셋/로프/avatar_rope(0)_default(0).png");
	playertx_rope2.loadFromFile("./texture_asset/메이플 에셋/로프/avatar_rope(1)_default(0).png");


	monster_move1.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/0.png");
	monster_move2.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/1.png");
	monster_move3.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/2.png");
	monster_back.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/3.png");
	monster_die1.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/10.png");
	monster_die2.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/11.png");
	monster_die3.loadFromFile("./texture_asset/메이플 에셋/몬스터/주황버섯/12.png");
	maptx.loadFromFile("./texture_asset/map.png");
	guitx.loadFromFile("./texture_asset/level.png");
	guibacktx.loadFromFile("./texture_asset/_outlink.png");

	Sattack.loadFromFile("./texture_asset/메이플 에셋/이펙트/Use.wav");
	Snormalattack.loadFromFile("./texture_asset/메이플 에셋/이펙트/Attack.wav");
	Sjump.loadFromFile("./texture_asset/메이플 에셋/이펙트/Jump.wav");
	Slevel.loadFromFile("./texture_asset/메이플 에셋/이펙트/LevelUp.wav");
	s.setBuffer(Sattack);
	s1.setBuffer(Snormalattack);
	s2.setBuffer(Sjump);
	s3.setBuffer(Slevel);
	Music M;
	M.openFromFile("./texture_asset/메이플 에셋/이펙트/FloralLife.wav");


	for (int i = 0; i < 11; i++)
	{
		Texture T;
		T.loadFromFile("./texture_asset/메이플 에셋/이펙트/"+ to_string(i*60)+'_'+to_string((i+1)*60)+".png");
		effect_tx.push_back(T);


	}
	



	object map(0, 0, maptx);
	object GUI(500, 500, guitx);
	object GUI_background(500, 500, guibacktx);
	object effect(-1000, -1000, effect_tx[0]);

	vector <RectangleShape> road;
	vector <vector<float>> road_pos;
	road_pos = { {2000, 100,0, 1035}, {500, 10,330, 790},{310, 10,875, 790},{400, 10,1240, 790},{400, 10,520, 612},{130, 10,970, 612},{310, 10,1150, 612} ,{310, 10,700, 432} ,{220, 10,1060, 432},{310, 10,880, 252} };
	//sizex, sizey, x, y
	vector <RectangleShape> ladder;
	vector <vector<float>> ladder_pos;
	ladder_pos = { {45,180,710,790}, {45,180,1310,790}, {45,120,600,612}, {45,120,1190,612} , {45,120,925, 432} , {45,120,1075, 252} };

	vector <monster> monster_vector;
	vector <vector<float>> 	monster_pos;
	monster_pos = {{500, 10,330, 790},{500, 10,330, 790},{500, 10,330, 790},{310, 10,875, 790},{310, 10,875, 790},{310, 10,875, 790},{400, 10,1240, 790},{400, 10,1240, 790},{400, 10,520, 612},{400, 10,520, 612},{400, 10,520, 612},{130, 10,970, 612},{130, 10,970, 612},{310, 10,1150, 612} ,{310, 10,700, 432} ,{220, 10,1060, 432},{310, 10,880, 252} };

	RectangleShape crash;
	RectangleShape rope_crash;
	RectangleShape attach;
	RectangleShape exp_backbar;
	RectangleShape exp_bar;

	crash.setSize(Vector2f(7, 5));
	rope_crash.setSize(Vector2f(7, 5));
	attach.setSize(Vector2f(100, 50));
	exp_backbar.setSize(Vector2f(300, 15));


	crash.setFillColor(sf::Color(255, 255, 255, 0));
	rope_crash.setFillColor(sf::Color(255, 255, 255, 0));
	attach.setFillColor(sf::Color(255, 0, 255, 0));
	exp_backbar.setFillColor(sf::Color::Black);
	exp_bar.setFillColor(sf::Color::Green);

	//땅 생성
	for (int i = 0; i < road_pos.size(); i++)
	{
		RectangleShape T_road;
		T_road.setSize(Vector2f(road_pos[i][0], road_pos[i][1]));
		T_road.setPosition(Vector2f(road_pos[i][2], road_pos[i][3]));
		T_road.setFillColor(sf::Color(255, 255, 255, 0));
		road.push_back(T_road);

	}
	//로프 생성
	for (int i = 0; i < ladder_pos.size(); i++)
	{
		RectangleShape T_ladder;
		T_ladder.setSize(Vector2f(ladder_pos[i][0]-10, ladder_pos[i][1]));
		T_ladder.setPosition(Vector2f(ladder_pos[i][2]+5, ladder_pos[i][3]+1));
		T_ladder.setFillColor(sf::Color(0, 0, 255, 0));
		ladder.push_back(T_ladder);

	}


	//몬스터 생성
	for (int i = 0; i < monster_pos.size(); i++)
	{
		monster T_monster((monster_pos[i][2]), (monster_pos[i][3]-60),monster_move1);
		T_monster.setStartx(monster_pos[i][2]);
		T_monster.setEndx(monster_pos[i][2]+ monster_pos[i][0]-50);
		T_monster.targetx = monster_pos[i][2];
		T_monster.setHp(100);
		T_monster.setDamage(10);
		T_monster.playero=&attach;
		T_monster.monster_texture.push_back(monster_move1);
		T_monster.monster_texture.push_back(monster_move2);
		T_monster.monster_texture.push_back(monster_move3);
		T_monster.monster_texture.push_back(monster_back);
		T_monster.monster_texture.push_back(monster_damaged);
		T_monster.monster_texture.push_back(monster_die1);
		T_monster.monster_texture.push_back(monster_die2);
		T_monster.monster_texture.push_back(monster_die3);
		T_monster.setCenter(T_monster.getSprite().getLocalBounds().width / 2, T_monster.getSprite().getLocalBounds().height / 230);
		monster_vector.push_back(T_monster);
		monster_vector[i].setTexture(monster_move1);
		monster_vector[i].schedule();
		monster_vector[i].killed = d;
	}

	bool is_road = 0;
	M.play();

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
					if (!jumped && state != 3&&state!=4) //점프,공격,줄타기 중이 아니면
					{
						player_speed -= 2;
						jumped = 1;
						down_counting = 0;
						s2.play();
					}
				}
				else//19 24
				{
					if (!jumped && state != 3 && state != 4) //점프,공격,줄타기 중이 아니면
					{
						player_speed -= 2;
						jumped = 1;
						jump_counting = 0;
						s2.play();
					}

				}

			}
			else
			{
				if (!jumped && state != 3 && state != 4)
				{
					player_speed -= 4;
					jumped = 1;
					jump_counting = 0;
					s2.play();
				}
			}

		}

		is_rope = 0;
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (state != 2&&state!=3 && state != 4)
			{
				state = 3;
				player_skill = 0;
				s1.play();
			}


		}
		if (Keyboard::isKeyPressed(Keyboard::F)) {
			if (state != 2 && state != 3 && state != 4)
			{
				state = 3;
				effect_clock = 0;
				player_skill = 1;
				s.play();
			}


		}

		if (effect_clock == 0)
		{
			if (player_rotate == 1)
			{
				effect.setScale(1, 1);
				effect.setPosition(player.x - 420, player.y - 140);
			}
			else
			{
				effect.setScale(-1, 1);
				effect.setPosition(player.x + 420, player.y - 140);
			}
		
			effect.setTexture(effect_tx[0]);
		}
		if (effect_clock %(60/ effect_tx.size())==0)
		{
			effect.setTexture(effect_tx[effect_clock / (60 / effect_tx.size())]);

		}
		if (effect_clock == 60)
		{
			effect.setPosition(-500, -500);
		}
		else
		{
			effect_clock++;
		}


		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			//로프 충돌 처리
			if(jumped)
			{

				for (int i = 0; i < ladder.size(); i++)
				{
					if (crash.getGlobalBounds().intersects(ladder[i].getGlobalBounds()))
					{
						player.setPosition(ladder[i].getPosition().x + ladder[i].getSize().x / 2 - 3, player.y);
						jump_counting = 200;
						player_speed = 0;
						down_counting = 200;
						state = 4;
						is_rope = 1;
						jumped = 1;
					}
				}
				if (is_rope)
				{
					player_rotate = -1;
					player.setScale(-1.f, 1.f);
					player_animate_change();
					rope_animate++;
					player.setPosition(player.x , player.y - 1.5);
				}
				else
				{
					state = 0;
				}

			}



		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))

		{
			//로프 충돌 처리
			if (jumped)
			{
				
				for (int i = 0; i < ladder.size(); i++)
				{
					if (crash.getGlobalBounds().intersects(ladder[i].getGlobalBounds()))
					{
						player.setPosition(ladder[i].getPosition().x+ ladder[i].getSize().x/2-3, player.y);
						jump_counting = 200;
						player_speed = 0;
						down_counting = 200;
						state = 4;
						is_rope = 1;
					}
				}
				if (is_rope)
				{
					player_rotate = -1;
					player.setScale(-1.f, 1.f);
					player_animate_change();
					rope_animate++;
					player.setPosition(player.x, player.y + 1.5);
				}
				else
				{
					state = 0;
				}
			}
			else
			{
				for (int i = 0; i < ladder.size(); i++)
				{
					if (rope_crash.getGlobalBounds().intersects(ladder[i].getGlobalBounds()))
					{
						player.setPosition(ladder[i].getPosition().x + ladder[i].getSize().x / 2 - 3, player.y);
						jump_counting = 200;
						player_speed = 0;
						down_counting = 200;
						state = 4;
						is_rope = 1;
						jumped = 1;
					}
				}
				if (is_rope)
				{
					player_rotate = -1;
					player.setScale(-1.f, 1.f);
					player_animate_change();
					rope_animate++;
					player.setPosition(player.x, player.y + 1.5);
				}
				else
				{
					state = 0;
				}

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

		is_road = 0;


		//땅 충돌 처리
		{

			if (crash.getGlobalBounds().intersects(road[0].getGlobalBounds()))
			{

				is_road = 1;
				jumped = 0;
				jump_counting = 200;
				player_speed = 0;
				down_counting = 200;
			}

			for (int i = 1; i < road.size(); i++)
			{
				if (crash.getGlobalBounds().intersects(road[i].getGlobalBounds()))
				{

					if (down_counting > 50&&state!=4)
					{
						is_road = 1;
						jumped = 0;
						jump_counting = 200;
						player_speed = 0;
						down_counting = 200;
					}
				}
			}

		}




		//점프 물리 엔진

		if (!is_road)
		{
			one_count = 1;

			if (jump_counting > 10&&state != 4)
			{
				state = 2;
				player_speed += player_acc;
			}
		}
		else
		{

			if (one_count == 1)
			{
				one_count = 0;
				player_animate_change();
				state = 0;
			}
			player_speed = 0;

		}








		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (state != 3 && state != 4)
			{

				player_rotate = 1;
				if (player.x>0)
				{
					player.setPosition(player.x - 1.5, player.y);
				}

				if (state != 2)
				{
					state = 1;
				}
			}
			else if (state == 4&& !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (Keyboard::isKeyPressed(Keyboard::Space)) {


					state = 2;
					player_speed -= 3;


				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (state != 3 && state != 4)
			{

				player_rotate = -1;
				if (player.x < map.getSprite().getLocalBounds().width)
				{
					player.setPosition(player.x + 1.5, player.y);
				}

				if (state != 2)
				{
					state = 1;
				}
			}
			else if (state == 4 && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (Keyboard::isKeyPressed(Keyboard::Space)) {

					state = 2;
					player_speed -= 3;

				}
			}
		}
		else
		{
			if (state != 2 && state != 3 && state != 4)
			{
				state = 0;
			}
		}


		if (player_rotate == 1)
		{
			player.setScale(1.f, 1.f);
		}
		else if(player_rotate == -1)
		{
			player.setScale(-1.f, 1.f);
		}


		

		player_animate_change();
		exp_bar.setSize(Vector2f(((float)(player_EXP) /(player_level * 40 + 100))*300, 15));


		if (player_EXP >= player_level * 40 + 100)
		{
			player_EXP -= player_level * 40 + 100;
			player_level++;
			s3.play();
		}

		//카메라 설정
		{
			float camera_tx = camera.getCenter().x + (player.x - camera.getCenter().x) / 60;
			float camera_ty = camera.getCenter().y + (player.y - camera.getCenter().y) / 60;


			if (camera_tx - camera.getSize().x / 2 > 0 && camera_tx + camera.getSize().x / 2 < 1980)
			{
				camera.setCenter(Vector2f(camera.getCenter().x + (player.x - camera.getCenter().x) / 60, camera.getCenter().y));
			}

			if (camera_ty - camera.getSize().y / 2 > 0 && camera_ty + camera.getSize().y / 2 < 1230)
			{
				camera.setCenter(Vector2f(camera.getCenter().x, camera.getCenter().y + (player.y - camera.getCenter().y) / 60));
			}




			float posInView_x = camera.getCenter().x - camera.getSize().x / 2;
			float posInView_y = camera.getCenter().y - camera.getSize().y / 2;

			text.setPosition(posInView_x+45, posInView_y+570);
			text.setString(to_string(player_level));
			GUI_background.setPosition(posInView_x, posInView_y + 530);
			GUI.setPosition(posInView_x, posInView_y + 530);
			crash.setPosition(Vector2f(player.x, player.y + 10 + player_speed));
			rope_crash.setPosition(Vector2f(player.x, player.y + 20));
			exp_backbar.setPosition(Vector2f(posInView_x +220, posInView_y + 575));
			exp_bar.setPosition(Vector2f(posInView_x + 220, posInView_y + 575));


		}



		//카메라 설정
		{
			if (state == 3)
			{
				if (effect_clock != 60)
				{
					attach.setSize(Vector2f(400, 100));
					if (player_rotate == 1)
					{

						attach.setPosition(Vector2f(player.x - 400, player.y - 100));

					}
					else if (player_rotate == -1)
					{
						attach.setPosition(Vector2f(player.x, player.y - 100));
					}

				}
				else
				{
					attach.setSize(Vector2f(100, 50));
					if (player_rotate == 1)
					{

						attach.setPosition(Vector2f(player.x - 100, player.y - 50));

					}
					else if (player_rotate == -1)
					{
						attach.setPosition(Vector2f(player.x, player.y - 50));
					}

				}

			}
			else
			{
				attach.setPosition(Vector2f(-500, -500));
			}



			mouse_pos = Mouse::getPosition(window);



			window.setView(camera);

		}
		// 화면 그리기 담당
		{
			window.clear();

			window.draw(map.getSprite());
	

			for (int i = 0; i < road.size(); i++)
			{
				window.draw(road[i]);
			}
			for (int i = 0; i < ladder.size(); i++)
			{
				window.draw(ladder[i]);
			}

			for (int i = 0; i < monster_vector.size(); i++)
			{

				monster_vector[i].schedule();
				monster_vector[i].player_x = player.x;
				monster_vector[i].player_y = player.y;
				monster_vector[i].player_damage = player_level*5+20;
				monster_vector[i].player_skill = player_skill;
				window.draw(monster_vector[i].getSprite());

			}

			window.draw(player.getSprite());
			window.draw(attach);
			window.draw(crash);
			window.draw(effect.getSprite());
			window.draw(rope_crash);
			window.draw(GUI_background.getSprite());
			window.draw(GUI.getSprite());
			window.draw(exp_backbar);
			window.draw(exp_bar);
			window.draw(text);
			window.display();

		}
	}

	return 0;

}
