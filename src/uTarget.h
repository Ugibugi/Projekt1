#pragma once
namespace utl
{
	struct uTarget
	{
		int x, y, z;//xyz coordinates
		int w, h, d; //width height and depth
		float rotx, roty, rotz, rotw; // rotations

		inline void setXY(int x, int y) { this->x = x; this->y = y; }
		inline void setXYZ(int x, int y, int z) { this->x = x; this->y = y; this->z = z; }

		inline void setCenter(int x, int y) { this->x = x + this->w / 2;  this->y = y + this->h / 2; }

		inline void setWH(int w, int h) { this->w = w; this->h = h; }
		inline void setWHD(int w, int h, int d) { this->w = w; this->h = h; this->d = d; }

	};
	
}