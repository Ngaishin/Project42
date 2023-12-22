#include "stepstatistisc.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>


namespace  STTT
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

void statistic(int times)
{
	using namespace STTT;

	float step_size = 5;
	vector target(45, 45);

	float distance = target.magnitude();
	vector drunk;
	int steps = 0;
	float maxs = 0, mins = 0, avgs = 0;
	int firt = times;
	srand(time(0));
	int i = 0;
	float farr[5];
	while (firt--)
	{
		drunk.reset();
		while (drunk.magnitude() < distance)
		{
			drunk.step(step_size);
			steps++;
		}
		if (times - 1 == firt)mins = steps;
		maxs = maxs > steps ? maxs : steps;
		mins = mins < steps ? mins : steps;
		avgs += steps;
		farr[i++] = steps;
		steps = 0;
	}
	std::cout << "max steps: " << maxs << '\n'
		<< "min steps: " << mins << '\n'
		<< "avg steps: " << avgs / times << '\n';
	for (i = 0; i < 5; i++)
		std::cout << farr[i] << "\n";
}