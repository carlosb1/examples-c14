#include <iostream>
#include <string>
#include <memory>


struct Ball {
	std::string color;
	float ratio;
	Ball (std::string color_, float ratio_): color(color_), ratio(ratio_){};
};


Ball RedBall("red",1.0);
Ball BlueBall("blue",3.0);
Ball GreenBall("green",2.0);



class BallFlyWeight {
	private:
		std::shared_ptr<Ball> ball;
		int x;
		int y;
	public:
		BallFlyWeight(std::shared_ptr<Ball> & ball_, int x_, int  y_): ball(ball_), x(x_), y(y_) {}; 
		inline void who_i_am() {
			std::cout << "color="<<ball.get()->color<<"\n";
			std::cout << "x="<< x<<"y="<<y<<"\n";
		};
};


int main ()  {
	std::shared_ptr<Ball> redball = std::make_shared<Ball>(RedBall);
	std::shared_ptr<Ball> greenball = std::make_shared<Ball>(GreenBall);
	std::shared_ptr<Ball> blueball = std::make_shared<Ball>(BlueBall);

	
	BallFlyWeight red1(redball, 1,1);
	BallFlyWeight red2(redball, 1,3);
	BallFlyWeight red3(redball, 3,4);
	BallFlyWeight green1(greenball, 5,5);
	BallFlyWeight green2(greenball, 2,2);
	BallFlyWeight blue1(blueball, 2,2);

	red1.who_i_am();
	red2.who_i_am();
	red3.who_i_am();
	green1.who_i_am();
	green2.who_i_am();
	blue1.who_i_am();
}
