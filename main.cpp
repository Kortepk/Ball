#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)
using namespace std;

int WIDTH = 1920, HEIGHT = 1080;
float DELTA = 3;

class Ball{
	public:
		Vector2f cordf;
		Vector2i cordi; 
		Vector2f speed;
		Ball();
		void run();
		void update();
		void g(float a);
		RenderWindow ball; 
};

Ball::Ball(){
	cordf = Vector2f(WIDTH/2, HEIGHT/2);
	cordi = Vector2i(0, 0);
	
	ball.create(VideoMode(130, 105), "Ball", Style::Titlebar);
}

void Ball::g(float a){
	float alpha = a;
	alpha /= 1000;
	speed = Vector2f(DELTA * cos(alpha), -DELTA * sin(alpha));
}

void Ball::update(){
	if(cordf.x <= 0 or cordf.x >= 1790){
		if(cordf.x <= 0)
			cordf.x = 1;
		else
			cordf.x = 1789;
		
		speed.x = -speed.x;
	}
		
	if(cordf.y <= 0 or cordf.y >= 950){
		if(cordf.y <= 0)
			cordf.y = 1;
		else
			cordf.y = 949;
		speed.y = - speed.y;
	}
		
		//cout<<speed.x<<" "<<speed.y<<"\n";
	ball.clear(Color::White); 
	cordf.x += speed.x;
	cordf.y -= speed.y;
}

void Ball::run(){
	ball.setPosition(Vector2i(cordf.x, cordf.y));
	ball.display(); 
}

int main()
{	
	random_device rd;
	mt19937 gen(rd());

	RenderWindow ball(VideoMode(130, 105), "Ball", Style::Titlebar); 
		
	//ball.setFramerateLimit(120);
	Vector2f cordf = Vector2f(WIDTH/2, HEIGHT/2);
		
	Vector2i cordi = Vector2i(0, 0);
	//cout<<rand()%6283<<"\n";
	float alpha = gen();
	alpha = gen()%6283;
	alpha /= 1000;
	Vector2f speed = Vector2f(DELTA * cos(alpha), -DELTA * sin(alpha));
	
	//ball.setPosition(Vector2i(1920/2, 1080/2));
	Ball ballfield[5];
	for(int i=0; i<5; i++)
		ballfield[i].g(gen());
	
	while (ball.isOpen())  
	{
		Event event; 
		while (ball.pollEvent(event))  
		{
			if (event.type == Event::Closed)  
				ball.close();  
		}
				
		if(cordf.x <= 0 or cordf.x >= 1790){
			if(cordf.x <= 0)
				cordf.x = 1;
			else
				cordf.x = 1789;
				
			speed.x = -speed.x;
		}
		
		if(cordf.y <= 0 or cordf.y >= 950){
			if(cordf.y <= 0)
				cordf.y = 1;
			else
				cordf.y = 949;
			speed.y = - speed.y;
		}
		
		//cout<<speed.x<<" "<<speed.y<<"\n";
		ball.clear(Color::White); 
		cordf.x += speed.x;
		cordf.y -= speed.y;
		
		//cordi.x = cordf.x;
		//cordi.y = cordf.x;
		
		for(int i=0; i<5; i++){
			ballfield[i].update();
			ballfield[i].run();
		}
		
		ball.setPosition(Vector2i(cordf.x, cordf.y));
		ball.display(); 
	}
	return 0;
}