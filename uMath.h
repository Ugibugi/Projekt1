#pragma once
#include <complex>
namespace utl
{
	class uVec2D
	{
		float _x=0, _y=0; //standard representation

		std::complex<float> _z = { 0,0 }; //representation on complex plane

		inline void _setXY(float x, float y)
		{
			_x = x;
			_z.real = x;
			_y = y;
			_z.imag = y;
		}
	public:
		uVec2D() = default;
		uVec2D(float x, float y)
		{
			_setXY(x, y);
		}
		uVec2D(std::initializer_list<float> li) //construction from initializer list
		{
			_setXY(*(li.begin()),*(li.begin()+1));
		}
		uVec2D(const uVec2D& u)	//copy construct
		{
			_setXY(u.x,u.y);
		}
		uVec2D& operator=(const uVec2D& u) = default;//copy assignment
		~uVec2D() = default;

		//vector addition
		uVec2D operator+(const uVec2D& u)
		{
			uVec2D ret(u.x + x, u.y + y);
			return ret;
		}
		//vector scalar multiplication
		uVec2D operator* (float a)
		{
			uVec2D ret(x*a, y*a);
			return ret;
		}
		//vector dot product
		float dot(const uVec2D& u)
		{
			return u.x*x + u.y*y;
		}
		
		void rotate(float radians)
		{
			_z = std::polar<float>(std::abs(_z), std::arg(_z) + radians);
			_setXY(_z.real, _z.imag);
		}

		const float& x = _x;
		const float& y = _y;
		
	};
}