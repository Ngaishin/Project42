#pragma once
#include <iostream>

namespace VECTORC
{
	enum cdtMode { rect, polar };
	class vector
	{
	private:
		float _x;
		float _y;
		float _mag;
		float _ang;
	public:
		vector()
			:_x(0), _y(0), _mag(0), _ang(0) {}
		vector(float x, float y = 0, cdtMode coordinate = rect);
		void setCde(float x, float y, cdtMode coordinate = rect);
		void reset();
		float x() { return _x; }
		float y() { return _y; }
		float magnitude() { return _mag; }
		float angle() { return _ang; }
		vector operator+(const vector& vt) const;
		vector& operator+=(const vector& vt);
		vector operator-() const;
		vector operator-(const vector& vt) const;
		vector operator*(const float& f) const;
		vector operator/(const float& f) const;
		friend std::ostream& operator<<(std::ostream& os, const vector& vt);

		float distance(vector& vt);
		vector& step(float f, const vector&);
	};

}

void runDrunkChange();
