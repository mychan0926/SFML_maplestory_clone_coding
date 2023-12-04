#include "System.h"
using namespace std;
using namespace sf;

void keyPressup();
void keyPressdown();
void keyPressright();
void keyPressleft();
int main()
{

	RenderWindow window(VideoMode(1920, 1080), "HW Engine");
	window.setFramerateLimit(100);
	Text text;
	Font font;
	Vector2i mouse_pos;
	if (!font.loadFromFile("./text_file/arial.ttf"))
	{
		cout << "can't load font file.";
		return 0;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Blue);
	View camera(FloatRect(0, 0, 1280, 720));
	window.setView(camera);



	clock_t time = clock();
	Texture temp_texture;
	temp_texture.loadFromFile("./texture_asset/메이플 에셋/걷기/avatar_walk1(0)_default(0).png");


	object player(500,500, temp_texture);
	object player2(100, 105, temp_texture);
	temp_texture.loadFromFile("./texture_asset/map.png");


	object map(0, 0, temp_texture);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.setPosition(player.x, player.y - 3);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.setPosition(player.x, player.y + 3);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.setPosition(player.x - 3, player.y);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Right)) {

			player.setPosition(player.x + 3, player.y);

		}

		

		if (player.x- camera.getSize().x / 2 >0&& player.x + camera.getSize().x / 2 < 1980)
		{
			camera.setCenter(Vector2f(player.x, camera.getCenter().y));
		}

		if (player.y - camera.getSize().y / 2 > 0 && player.y + camera.getSize().y / 2 < 1230)
		{
			camera.setCenter(Vector2f(camera.getCenter().x,player.y ));
		}



		window.setView(camera);



		int posInView_x = camera.getCenter().x - camera.getSize().x / 2;
		int posInView_y = camera.getCenter().y - camera.getSize().y / 2;
		text.setPosition(posInView_x , posInView_y);
		text.setString(to_string(posInView_x));



		mouse_pos=Mouse::getPosition(window);



		// 이벤트 검사 및 처리
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}






		// 키보드 담당



		// 화면 그리기 담당
		window.clear();

		window.draw(map.getSprite());
		window.draw(text);
		window.draw(player2.getSprite());
		window.draw(player.getSprite());

		window.display();

	}

	return 0;

}
