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
	//text.setFont(font);
	//text.setString();
	//text.setCharacterSize(20);
	//text.setFillColor(Color::Blue);
	//text.setPosition(0, 0);
	clock_t time = clock();
	Texture temp_texture;
	temp_texture.loadFromFile("./texture_asset/mario.png");
	object player(100,100, temp_texture);
	View camera(sf::FloatRect(0, 0, 1280, 720));
	window.setView(camera);
	while (window.isOpen())
	{
		
		// 이벤트 검사 및 처리
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}









		time = clock();
		time = time / CLOCKS_PER_SEC;
		text.setString(to_string(time) + " sec");


		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.setPosition(player.x, player.y-1);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.setPosition(player.x, player.y +1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.setPosition(player.x-1, player.y);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.setPosition(player.x+1, player.y);
		}

		// 화면을 지운다. 
		window.clear();
		window.draw(player.getSprite());
		window.display();
		camera.setCenter(player.x,100);
		window.setView(camera);
	}

	return 0;

}
