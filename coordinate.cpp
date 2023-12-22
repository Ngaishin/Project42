#include "coordinate.h"
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>


namespace VECTOR
{
	vector::vector(float x, float y, cdtMode coordinate)
	{
		double rect_to_pol = 45.0 / atan(1);
		if (coordinate == rect)
		{
			_x = x;
			_y = y;
			_mag = sqrt(x * x + y * y);
			_ang = atan2(y, x) * rect_to_pol;
		}
		else if (coordinate == polar)
		{
			_mag = x;
			_ang = fmod(y, 360);
			_y = _mag * sin(_ang / rect_to_pol);
			_x = _mag * cos(_ang / rect_to_pol);
		}
		else
		{
			_x = _y = _mag = _ang = 0;
			std::cout << "Incorrect input!\nall parameter were set 0.\n";
		}
	}

	void vector::setCde(float x, float y, cdtMode coordinate)
	{
		double rect_to_pol = 45.0 / atan(1);
		if (coordinate == rect)
		{
			_x = x;
			_y = y;
			_mag = sqrt(x * x + y * y);
			_ang = atan2(y, x) * rect_to_pol;
		}
		else if (coordinate == polar)
		{
			_mag = x;
			_ang = fmod(y, 360);
			_y = _mag * sin(_ang / rect_to_pol);
			_x = _mag * cos(_ang / rect_to_pol);
		}
		else
		{
			_x = _y = _mag = _ang = 0;
			std::cout << "Incorrect input!\nall parameter were set 0.\n";
		}
	}

	void vector::reset()
	{
		_x = _y = _mag = _ang = 0;
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
		os << "polar: " << '(' << vt._mag << ',' << vt._ang << "бу)\n" << std::endl;

		std::cout.flags(f);
		return os;
	}


	//runDrunk
	float vector::distance(vector& vt)
	{
		vector tem = vt - *this;
		return tem._mag;
	}


	vector& vector::step(float f)
	{
		float direction = fmod(rand(), 360);
		vector tem(f, direction, cdtMode::polar);
		return *this += tem;
	}
}

void runDrunk()
{
	float distance = 100;
	float step_size = 20;

	using namespace VECTOR;
	vector target(100, 45, cdtMode::polar);
	vector drunk;
	int steps = 0;
	std::ofstream fout;
	fout.open("Drunk_gohome.txt");

	fout << "Target Distance: " << distance << ", Step Size: " << step_size << '\n';
	srand(time(0));
	//while (drunk.distance(target) > 10)
	while (drunk.magnitude() < distance)
	{
		fout << steps << ": (x,y) = (" << drunk.x() <<", " << drunk.y() << ")\n";
		//<< ": (m,a) = (" << drunk.magnitude() << ", " << drunk.angle() << "бу)\n";
		drunk.step(20);
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