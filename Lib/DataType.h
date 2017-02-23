#ifndef DATATYPE_H
#define DATATYPE_H


#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#include <hge.h>
#include <hgeSprite.h>

typedef				char		char8;

typedef signed		char		sInt8;
typedef signed		short		sInt16;
typedef signed		int			sInt32;

typedef unsigned	char		uInt8;
typedef unsigned	short		uInt16;
typedef unsigned	int			uInt32;

typedef				float		float32;
typedef				double		float64;

typedef				HTEXTURE	rawTEXTURE;
typedef				hgeSprite	SPRITE;

#define MAXDRAWITEMS 300

class fVector2
{
public:
	float	x,y;

	fVector2(float32 _x, float32 _y){ x=_x; y=_y; }
	fVector2()						{ x=0; y=0; }

	fVector2	operator-  ()						const	{ return fVector2(-x, -y);		}
	fVector2	operator-  (const fVector2 &v)		const	{ return fVector2(x-v.x, y-v.y); }
	fVector2	operator+  (const fVector2 &v)		const	{ return fVector2(x+v.x, y+v.y); }
	fVector2&	operator-= (const fVector2 &v)				{ x-=v.x; y-=v.y; return *this;	}
	fVector2&	operator+= (const fVector2 &v)				{ x+=v.x; y+=v.y; return *this;	}
	bool		operator== (const fVector2 &v)		const	{ return (x==v.x && y==v.y);}
	bool		operator!= (const fVector2 &v)		const	{ return (x!=v.x || y!=v.y);}

	fVector2	operator/  (const float32 scalar)	const	{ return fVector2(x/scalar, y/scalar);	}
	fVector2&	operator/= (const float32 scalar)			{ x/=scalar; y/=scalar; return *this;	}
	fVector2	operator*  (const float32 scalar)	const	{ return fVector2(x*scalar, y*scalar);	}
	fVector2&	operator*= (const float32 scalar)			{ x*=scalar; y*=scalar; return *this;	}
	fVector2	Lerp(fVector2 const& a, fVector2 const& b, float t) { return a*(1 - t) + b*t; }
	float		Distance(fVector2 const& a, fVector2 const& b) {
		float x = b.x - a.x;
		float y = b.y - a.y;
		return sqrt(x*x + y*y);
	}
	float		Length() { return sqrt(x*x + y*y); }
	
};




#endif