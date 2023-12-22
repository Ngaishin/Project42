#pragma once
#include <iostream>

namespace STTT
{
	class vector
	{
	private:
		float _x;
		float _y;
	public:
		vector()
			:_x(0), _y(0){}
		vector(float x, float y = 0);
		void setCde(float x, float y);
		void reset();
		float x() { return _x; }
		float y() { return _y; }
		float magnitude();
		float angle();
		vector operator+(const vector& vt) const;
		vector& operator+=(const vector& vt);
		vector operator-() const;
		vector operator-(const vector& vt) const;
		vector operator*(const float& f) const;
		vector operator/(const float& f) const;
		friend std::ostream& operator<<(std::ostream& os, const vector& vt);

		float distance(vector& vt);
		vector& step(float f);

	};

}


void statistic(int time);



