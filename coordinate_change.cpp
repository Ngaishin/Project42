#include "coordinate_change.h"
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>


namespace VECTORC
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
		os << "polar      : " << '(' << vt._mag << ',' << vt._ang << "бу)\n" << std::endl;

		std::cout.flags(f);
		return os;
	}


	//runDrunk
	float vector::distance(vector& vt)
	{
		vector tem = vt - *this;
		return tem._mag;
	}


	vector& vector::step(float f, const vector& vt)
	{
		vector tem = vt - *this;
		float direction = fmod(rand(), 90);
		if ((tem.angle() < 90 and tem.angle() >= 0) or (tem.angle() < -270 and tem.angle() >= -360));
		else if ((tem.angle() < 180 and tem.angle() >= 90) or (tem.angle() < -180 and tem.angle() >= -270))direction += 90;
		else if ((tem.angle() < 270 and tem.angle() >= 180) or (tem.angle() < -90 and tem.angle() >= -180))direction += 180;
		else if ((tem.angle() < 360 and tem.angle() >= 270) or (tem.angle() < 0 and tem.angle() >= -90))   direction += 270;
		this->_ang = 0;
		tem.setCde(f, direction, cdtMode::polar);
		return *this += tem;
	}
}

void runDrunkChange()
{
	srand(time(0));
	//target:
	float distance = fmod(rand(), 300.0);
	float angle = rand() % 360;
	//drunk
	float step_size = 5;
	float accuracy = 0.1;

	using namespace VECTORC;
	vector target(distance, angle, cdtMode::polar);
	vector drunk;
	int steps = 0;

	std::ofstream fout;
	fout.open("Drunk_gohome_line.txt");
	fout << target.x() << ", " << target.y() << "\n";

	//std::cout << "Target Distance: " << distance << ", Step Size: " << step_size << '\n';
	//fout << "Target Distance: " << distance << ", Step Size: " << step_size << '\n';

	//while (drunk.magnitude() < distance)
	while (drunk.distance(target) > accuracy)
	{
		//fout << steps << ": (x,y) = (" << drunk.x() << ", " << drunk.y() << ")\n";
		fout << drunk.x() << ", " << drunk.y() << "\n";
		//std::cout << steps << ": (x,y) = (" << drunk.x() << ", " << drunk.y() << ")\n";
		//std::cout << steps << ": (m,a) = (" << drunk.magnitude() << ", " << drunk.angle() << "бу)\n";
		drunk.step(step_size, target);
		steps++;
	}
	float agl;
	if ((drunk.angle() > 0 and target.angle() > 0) or (drunk.angle() < 0 and target.angle() < 0)) agl = drunk.angle();
	else if (drunk.angle() > 0 and target.angle() < 0) agl = drunk.angle() - 360;
	else agl = 360 + drunk.angle();
	//std::cout << "After " << steps << " steps,the subject has the following location:\n"
	//fout << "After " << steps << " steps,the subject has the following location:\n"
	//	<< "Target: \n"
	//	<< "(tx,ty) = (" << target.x() << ", " << target.y() << ")\n"
	//	<< "Result: \n"
	//	<< "(x , y) = (" << drunk.x() << ", " << drunk.y() << ")\n"
	//	<< "or\n"
	//	<< "Target: \n"
	//	<< "(tm,ta) = (" << target.magnitude() << ", " << target.angle() << "бу)\n"
	//	<< "(m , a) = (" << drunk.magnitude() << ", " << agl << "бу)\n"
	//	<< "Average outward distance per step = "
	//	<< (100.0 / steps)
	//	<< '\n';
	fout.close();

}