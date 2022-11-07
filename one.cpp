#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)
using namespace std;

int WIDTH = 1920, HEIGHT = 1080;
float DELTA = 3;

RenderWindow Field(VideoMode(1920, 1080), "Field", Style::Default); 

CircleShape ball(10.f); 

Clock CLOCK;

Color GetRainbow(int x){
	x %= 1530; //ограничиваем
	
	int layer = x/255; // узнаём какой сектор
	
	x %= 255; // делаем до цветового диапазона
	
	switch(layer){
		case 0:{
			return Color(255, x, 0);
		}
		case 1:{
			return Color(255 - x, 255, 0);
		}
		case 2:{
			return Color(0, 255, x);
		}
		case 3:{
			return Color(0, 255 - x, 255);
		}
		case 4:{
			return Color(x, 0, 255);
		}
		case 5:{
			return Color(255, 0, 255-x);
		}
	}
	
}

class Ball{
	public:
		Vector2f cordf;
		Vector2i cordi; 
		Vector2f speed;
		Ball();
		void run();
		void update();
		void g(int a);
};

Ball::Ball(){
	cordf = Vector2f(WIDTH/2, HEIGHT/2);
	cordi = Vector2i(0, 0);
}

void Ball::g(int a){
	float alpha = a%628318531;
	alpha /= 100000000;
	speed = Vector2f(DELTA * cos(alpha), -DELTA * sin(alpha));
}

void Ball::update(){
	if(cordf.x <= 0 or cordf.x >= WIDTH - ball.getRadius()){
		if(cordf.x <= 0)
			cordf.x = 1;
		else
			cordf.x = WIDTH - ball.getRadius() - 1;
		
		speed.x = -speed.x;
	}
		
	if(cordf.y <= 0 or cordf.y >= HEIGHT - ball.getRadius()){
		if(cordf.y <= 0)
			cordf.y = 1;
		else
			cordf.y = HEIGHT - ball.getRadius() - 1;
		speed.y = - speed.y;
	}
		

	cordf.x += speed.x;
	cordf.y -= speed.y;
}

void Ball::run(){
	ball.setPosition(cordf.x, cordf.y);
	ball.setFillColor(GetRainbow(CLOCK.getElapsedTime().asMilliseconds()/10));
	Field.draw(ball);
}

int main()
{	
	Field.setFramerateLimit(120);
	
	random_device rd;
	mt19937 gen(rd());
		
	Ball ballfield[10000];
	for(int i=0; i<10000; i++)
		ballfield[i].g(gen());
	
	RectangleShape fon(Vector2f(WIDTH, HEIGHT));  
    fon.setFillColor(Color(0, 0, 0, 20));  
	
	while (Field.isOpen())  
	{
		Event event; 
		while (Field.pollEvent(event))  
		{
			if (event.type == Event::Closed)  
				Field.close();  
		}
		
		for(int i=0; i<10000; i++){
			ballfield[i].update();
			ballfield[i].run();
		}
		Field.draw(fon);
		Field.display(); 
	}
	return 0;
}