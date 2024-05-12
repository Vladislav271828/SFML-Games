#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int PinkPong() {

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Pink Pong");
	window.setFramerateLimit(144);
	int r = 30;
	sf::CircleShape circle(r);

	float recHeight = 200.0f;
	float recWidth = 20.0f;
	sf::RectangleShape rec(sf::Vector2f(recWidth, recHeight));
	

	circle.setFillColor(sf::Color(255, 179, 242));
	circle.setPosition(610.0f, 300.0f);

	rec.setFillColor(sf::Color(255, 179, 242));

	sf::RectangleShape rec2(rec);

	rec.setPosition(30.0f, 300.0f);
	rec2.setPosition(1230.0f, 300.0f);


	float circleMoveSpeed = 0.0f;
	float recMoveSpeed = 2.0f;

	int mirroredx = 1;
	int mirroredy = 1;

	float move = 0;
	float move2 = 0;


	sf::Font myFont;
	sf::Event event;
	int score = 0;
	int score2 = 0;

	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("Roboto-Regular.ttf")) {
		return 11;
	}
	text.setFont(font);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 179, 242));
	text.setPosition(607.0f, 20.0f);
	text.setString("0 : 0");

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			

			if (event.type == sf::Event::KeyPressed) {
				//cout << "Key pressed with code = " << event.key.code << endl;

				if (event.key.code == sf::Keyboard::Escape) {
					circleMoveSpeed = 4.0f;
				}

				if (event.key.code == sf::Keyboard::Space) {
					circleMoveSpeed = 4.0f;
				}

				if (event.key.code == sf::Keyboard::X) {
					mirroredx *= -1;
				}

				if (event.key.code == sf::Keyboard::Y) {
					mirroredy *= -1;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				move = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				move = 1;
			}
			else {
				move = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				move2 = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				move2 = 1;
			}
			else {
				move2 = 0;
			}
		}
		if (circle.getPosition().y >= 720 - 2 * r || circle.getPosition().y <= 0) {
			mirroredy *= -1;
		}
		if (circle.getPosition().x >= 1280) {
			score++;
			circle.setPosition(600.0f, 300.0f);
			circleMoveSpeed = 0.0f;
			mirroredx *= -1;
			text.setString(std::to_string(score) + " : " + std::to_string(score2));
		}
		if (circle.getPosition().x <= 0 - 2 * r) {
			score2++;
			circle.setPosition(600.0f, 300.0f);
			circleMoveSpeed = 0.0f;
			mirroredx *= -1;
			text.setString(std::to_string(score) + " : " + std::to_string(score2));
		}

		if (circle.getGlobalBounds().intersects(rec.getGlobalBounds())) {
			sf::FloatRect intersection;
			if (circle.getGlobalBounds().intersects(rec.getGlobalBounds(), intersection)) {

				if (intersection.height > intersection.width) {

					mirroredx *= -1;
				}
				else {
					mirroredy *= -1;

				}
				circle.setPosition(circle.getPosition().x + circleMoveSpeed * mirroredx, circle.getPosition().y + circleMoveSpeed * mirroredy);
			}
		}

		if (circle.getGlobalBounds().intersects(rec2.getGlobalBounds())) {
			sf::FloatRect intersection;
			if (circle.getGlobalBounds().intersects(rec2.getGlobalBounds(), intersection)) {

				if (intersection.height > intersection.width) {

					mirroredx *= -1;
				}
				else {

					mirroredy *= -1;
				}
			}
			circle.setPosition(circle.getPosition().x + circleMoveSpeed * mirroredx, circle.getPosition().y + circleMoveSpeed * mirroredy);
		}

		if ((rec.getPosition().y >=  720 - recHeight && move == 1) || (rec.getPosition().y <= 0 && move == -1)) {
			move = 0;
		}

		if ((rec2.getPosition().y >= 720 - recHeight && move2 == 1) || (rec2.getPosition().y <= 0 && move2 == -1)) {
			move2 = 0;
		}

		
		
		circle.setPosition(circle.getPosition().x + circleMoveSpeed * mirroredx, circle.getPosition().y + circleMoveSpeed * mirroredy);
		rec.setPosition(rec.getPosition().x, rec.getPosition().y + recMoveSpeed * move);
		rec2.setPosition(rec2.getPosition().x, rec2.getPosition().y + recMoveSpeed * move2);
		window.clear();
		
		window.draw(circle);
		window.draw(rec);
		window.draw(rec2);
		window.draw(text);
		window.display();
	}
	return 0;
}