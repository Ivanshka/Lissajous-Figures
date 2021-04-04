#include <SFML/Graphics.hpp>
#include <iostream> 

using namespace std;
using namespace sf;

#define PI 3.14159265

inline void changeWindowName(RenderWindow* win, float xFreq, float yFreq, float xAmplitude, float yAmplitude, int periodNumber) {
	win->setTitle("Lissajous Figures. Freq X = " + std::to_string(xFreq) + ", freq Y = " + std::to_string(yFreq) + ", xAmpl = " + std::to_string(xAmplitude) + ", yAmpl = " + std::to_string(yAmplitude) + ", period number = " + std::to_string(periodNumber));
}

int main()
{
	int width = 1280;
	int height = 720;

	RenderWindow window(sf::VideoMode(width, height), "Lissajous Figures");
	window.clear();
	Image texture_image;

	texture_image.loadFromFile("dot.png");
	Texture txtr;
	txtr.loadFromImage(texture_image);
	Sprite sprite;
	sprite.setTexture(txtr);

	Clock clock;


	float xAmplitude = 300;
	float yAmplitude = 300;

	float xFrequency = 20;
	float yFrequency = 60;
	float smallFrequencyStep = 0.01;

	int xCenter = width >> 1;
	int yCenter = height >> 1;

	float x;
	float y;

	float time;

	float xPeriod = 1 / xFrequency;
	float yPeriod = 1 / yFrequency;
	
	double maxPeriod = max(xPeriod, yPeriod);
	double minPeriod = min(xPeriod, yPeriod);

	int xTimeSum = 0;
	int yTimeSum = 0;
	int const controlInterval = 100000; // microseconds
	long periodNumber = 0; // номер полного колебания для отрисовки

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		xTimeSum += time;
		yTimeSum += time;

		clock.restart();

		// EVENTS
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::R)
					periodNumber = 0;
			}
		}

		// CONTROL
		// UP
		if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::LControl) && yTimeSum > controlInterval) {
			yAmplitude += 10;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::LControl) && yTimeSum > controlInterval) {
			yFrequency++;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::LShift) && yTimeSum > controlInterval) {
			yAmplitude++;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && yTimeSum > controlInterval) {
			yFrequency += smallFrequencyStep;
			yTimeSum = 0;
		}

		// DOWN
		if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::LControl) && yTimeSum > controlInterval) {
			yAmplitude -= 10;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::LControl) && yTimeSum > controlInterval) {
			yFrequency--;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::LShift) && yTimeSum > controlInterval) {
			yAmplitude--;
			yTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && yTimeSum > controlInterval) {
			yFrequency -= smallFrequencyStep;
			yTimeSum = 0;
		}
		
		// RIGHT
		if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::LControl) && xTimeSum > controlInterval) {
			xAmplitude += 10;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::LControl) && xTimeSum > controlInterval) {
			xFrequency++;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::LShift) && xTimeSum > controlInterval) {
			xAmplitude++;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && xTimeSum > controlInterval) {
			xFrequency += smallFrequencyStep;
			xTimeSum = 0;
		}

		// LEFT
		if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::LControl) && xTimeSum > controlInterval) {
			xAmplitude -= 10;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::LControl) && xTimeSum > controlInterval) {
			xFrequency--;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::LShift) && xTimeSum > controlInterval) {
			xAmplitude--;
			xTimeSum = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) && xTimeSum > controlInterval) {
			xFrequency -= smallFrequencyStep;
			xTimeSum = 0;
		}

		changeWindowName(&window, xFrequency, yFrequency, xAmplitude, yAmplitude, periodNumber);

		// PHYSICS & DRAWING
		window.clear();

		for (double time = maxPeriod * periodNumber; time < (periodNumber + 1L) * maxPeriod; time += 0.00005f)
		{
			x = xCenter + xAmplitude * cosf(xFrequency * 2 * PI * time);
			y = yCenter + yAmplitude * sinf(yFrequency * 2 * PI * time);
			sprite.setPosition(x, y);
			window.draw(sprite);
		}

		periodNumber++;

		periodNumber = periodNumber % 5000;

		window.display();
	}
	return 0;
}
