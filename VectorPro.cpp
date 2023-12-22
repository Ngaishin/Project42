#include <iostream>
#include "VectorPro.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>


namespace  myVector
{
	vector::vector(float x, float y)
	{
		_x = x;
		_y = y;


	}

	void vector::setCde(float x, float y)
	{
		double rect_to_pol = 45.0 / atan(1);
		_x = x;
		_y = y;
	}

	void vector::reset()
	{
		_x = _y = 0;
	}

	float vector::magnitude()
	{
		return 	sqrt(_x * _x + _y * _y);
	}

	float vector::angle()
	{
		double rect_to_pol = 45.0 / atan(1);
		return  atan2(_y, _x) * rect_to_pol;

	}

	vector vector::operator+(const vector& vt) const
	{
		vector tem(_x + vt._x, _y + vt._y);
		return tem;
	}

	vector& vector::operator+=(const vector& vt)
	{
		(*this).setCde(_x + vt._x, _y + vt._y);
		return *this;
	}

	vector vector::operator-() const
	{
		vector tem(-_x, -_y);
		return tem;
	}

	vector vector::operator-(const vector& vt) const
	{
		vector tem(_x - vt._x, _y - vt._y);
		return tem;
	}

	vector vector::operator*(const float& f) const
	{
		vector tem(_x * f, _y * f);
		return tem;
	}

	vector vector::operator/(const float& f) const
	{
		vector tem(_x / f, _y / f);
		return tem;
	}

	std::ostream& operator<<(std::ostream& os, const vector& vt)
	{
		std::ios_base::fmtflags f = std::cout.flags();
		std::cout << std::fixed << std::setprecision(2);

		os << "rectangular: " << '(' << vt._x << ',' << vt._y << ')' << std::endl;

		std::cout.flags(f);
		return os;
	}


	//runDrunk
	float vector::distance(vector& vt)
	{
		vector tem = vt - *this;
		return tem.magnitude();
	}


	vector& vector::step(float f)
	{
		double rect_to_pol = 45.0 / atan(1);
		float direction = fmod(rand(), 360);
		vector tem(cos(direction / rect_to_pol) * f, sin(direction / rect_to_pol) * f);
		return *this += tem;
	}
}

void vrunDrunk()
{
	using namespace myVector;

	float step_size = 5;
	vector target(45, 45);

	float distance = target.magnitude();
	vector drunk;
	int steps = 0;
	std::cout << "target magnitude: " << target.magnitude() << "\n"
		<< "target angle: " << target.angle() << "\n";
	std::ofstream fout;
	fout.open("VectorText.txt");

	fout << "Target Distance: " << distance << ", Step Size: " << step_size << '\n';
	srand(time(0));
	//while (drunk.distance(target) > 10)
	while (drunk.magnitude() < distance)
	{
		fout << steps << ": (x,y) = (" << drunk.x() << ", " << drunk.y() << ")\n";
		//<< ": (m,a) = (" << drunk.magnitude() << ", " << drunk.angle() << "бу)\n";
		drunk.step(step_size);
		steps++;
	}

	fout << "After " << steps << " steps,the subject has the following location:\n"
		<< "(x,y) = (" << drunk.x() << ',' << drunk.y() << ")\n"
		<< "or\n"
		<< "(m,a) = (" << drunk.magnitude() << ", " << drunk.angle() << "бу)\n"
		<< "Average outward distance per step = "
		<< (100.0 / steps)
		<< '\n';
	fout.close();

}