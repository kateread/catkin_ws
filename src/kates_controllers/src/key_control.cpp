#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <iostream>
#include <termios.h>
#include <string>
#include <map>


using namespace std;


class KeyControl {
public:
	KeyControl();
	//teleop_twist();

private:
	void printMsg();
	char getKey();

	double speed, turn;

	ros::NodeHandle nh_;

	ros::Publisher vel_pub_;

	std::map<char, std::vector<int> > moveBindings 
	{
		{'i', { 1, 0, 0, 0 }},
		{'o', { 1, 0, 0, -1 }},
		{'j', { 0, 0, 0, 1 }},
		{'l', { 0, 0, 0, -1 }},
		{'u', { 1, 0, 0, 1 }},
		{',', { 1, 0, 0, 0 }},
		{'.', { -1, 0, 0, 1 }},
		{'m', { -1, 0, 0, -1 }}
	};

	std::map<char, std::vector<double> > speedBindings {
		{'q', { 1.1, 1.1 }},
		{'z', { 0.9, 0.9 }},
		{'w', { 1.1, 1.0 }},
		{'x', { 0.9, 1.0 }},
		{'e', { 1.0, 1.1 }},
		{'c', { 1.0, 0.9 }}
	};
};


KeyControl::KeyControl()
{
	char key;
	int x = 0;
	int y = 0;
	int z = 0;
	int th = 0;
	int status = 0;

	nh_.param("speed", speed, 0.5);
	nh_.param("turn", turn, 1.0);

	vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

	geometry_msgs::Twist twist;


	KeyControl::printMsg();

	// cout << "speed: " << speed << endl;
	// cout << "turn: " << turn << endl;

	while (nh_.ok())
	{
		key = KeyControl::getKey();
		// cout << "got key: " << key << endl;
		if ( moveBindings.count( key ) > 0 ) {
			x = moveBindings[key][0];
			y = moveBindings[key][1];
			z = moveBindings[key][2];
			th = moveBindings[key][3];
			// cout << "x: " << x << endl;
			// cout << "y: " << y << endl;
			// cout << "z: " << z << endl;
			// cout << "th: " << th << endl;
		} else if ( speedBindings.count( key ) > 0) {
			speed = speed * speedBindings[key][0];
			turn = turn * speedBindings[key][1];
			cout << "speed: " << speed << ", turn: " << turn << endl;
			if ( status == 7 ){
				KeyControl::printMsg();
				status = 0;
			} else {
				status += 1;
			}
		} else {
			// cout << key << " is not a valid key\n";
			x = 0;
			y = 0;
			z = 0;
			th = 0;
		}

		if ( status == 14 ){
			KeyControl::printMsg();
			status = 0;
		}


		twist.linear.x = x * speed;
		twist.linear.y = y * speed;
		twist.linear.z = z * speed;
		twist.angular.x = 0; 
		twist.angular.y = 0; 
		twist.angular.z = th * turn;

		vel_pub_.publish( twist );




	}
}

char KeyControl::getKey() 
{
	struct termios old_t, new_t;
    tcgetattr(STDIN_FILENO, &old_t);
    new_t = old_t;
    new_t.c_lflag &= ~ICANON;
    new_t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

	char key;
	cin >> key;
	// cin.get(key);
	// cout << "\ngot char: " << key << "\n";

	tcsetattr(STDIN_FILENO, TCSANOW, &old_t); //This should set it back to normal.


	return key;
}


void KeyControl::printMsg() 
{
	cout << "\nReading from the keyboard  and Publishing to Twist!\n";
	cout << "---------------------------\n";
	cout << "Moving around:\n";
	cout << "   u    i    o\n";
	cout << "   j    k    l\n";
	cout << "   m    ,    .\n\n";

	cout << "anything else : stop\n\n";

	cout << "q/z : increase/decrease max speeds by 10%\n";
	cout << "w/x : increase/decrease only linear speed by 10%\n";
	cout << "e/c : increase/decrease only angular speed by 10%\n\n";

	cout << "CTRL-C to quit\n\n";
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "kates_key_control");
    KeyControl key_control;

    ros::spin();
    return(0);
}


