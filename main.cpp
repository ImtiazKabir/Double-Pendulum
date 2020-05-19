#include <SFML/Graphics.hpp>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500
#define g 1.f
#define L1 70.f
#define L2 150.f
#define m1 40.f
#define m2 30.f
#define theta1i M_PI_2 / 3
#define theta2i M_PI
#define omega1i 0.f
#define omega2i 0.f
#define step 0.0250f
#define thick 2.f
#define r_scale 0.25f
#define r1 r_scale * m1
#define r2 r_scale * m2
#define rod1_col sf::Color(0, 0, 0)
#define rod2_col sf::Color(0, 0, 0)
#define bob1_col sf::Color(0, 0, 0)
#define bob2_col sf::Color(0, 0, 0)
#define origin1 sf::Vector2f(WIDTH/2.f, HEIGHT/4.f)

int main() {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double Pendulam");

	// inititate variables
	float theta1 = theta1i;
	float theta2 = theta2i;
	float omega1 = omega1i;
	float omega2 = omega2i;

	// prepare the background
	sf::RectangleShape background(sf::Vector2f(WIDTH, HEIGHT));
	background.setFillColor(sf::Color(255, 255, 255));
	background.setPosition(0, 0);

	// prepare the rods
	sf::RectangleShape rod1(sf::Vector2f(L1, thick));
	rod1.setFillColor(rod1_col);
	rod1.setPosition(origin1);

	sf::RectangleShape rod2(sf::Vector2f(L2, thick));
	rod2.setFillColor(rod2_col);

	// prepare the bobs
	sf::CircleShape bob1(r1);
	bob1.setFillColor(bob1_col);

	sf::CircleShape bob2(r2);
	bob2.setFillColor(bob2_col);


	// for rotation
	float ptheta1 = -M_PI_2;
	float ptheta2 = -M_PI_2;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear();

		// update everything

		float alpha1 = -g * (2*m1 + m2) * sin(theta1);
		alpha1 += -m2 * g * sin(theta1 - 2 * theta2);
		alpha1 += -2 * sin(theta1 - theta2) * m2 * (omega2*omega2*L2+ omega1*omega1*L1 * cos(theta1 - theta2));
		alpha1 /= L1 * (2*m1 + m2 - m2 * cos(2*theta1 - 2*theta2));
		
		float alpha2 = omega1*omega1 * L1 * (m1+m2);
		alpha2 += g * (m1 + m2) * cos(theta1);
		alpha2 += omega2*omega2 * L2 * m2 * cos(theta1 - theta2);
		alpha2 *= 2 * sin(theta1 - theta2) / L2 / (2*m1 + m2 - m2 * cos(2*theta1 - 2 * theta2));

		omega1 += alpha1 * step;
		omega2 += alpha2 * step;

		theta1 += omega1 * step;
		theta2 += omega2 * step;

		sf::Vector2f origin2(origin1.x - L1 * sin(theta1), origin1.y + L1 * cos(theta1));
		sf::Vector2f end(origin2.x - L2 * sin(theta2), origin2.y + L2 * cos(theta2));
		

		// draw everything
		window.draw(background);

		rod1.rotate((theta1 - ptheta1) * 180 * M_1_PI);
		ptheta1 = theta1;
		window.draw(rod1);

		rod2.setPosition(origin2);
		rod2.rotate((theta2 - ptheta2) * 180 * M_1_PI);
		ptheta2 = theta2;
		window.draw(rod2);
		
		bob1.setPosition(origin2.x - r1, origin2.y - r2);
		window.draw(bob1);

		bob2.setPosition(end.x - r2, end.y - r2);
		window.draw(bob2);

		window.display();
	}

	return EXIT_SUCCESS;
}



