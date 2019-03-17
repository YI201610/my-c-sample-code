/****************************************************
 *  Math.c                                         
 *  Created on: 06-5-2008 22:26:18                      
 *  Implementation of the Class Math       
 *  Original author: imamura                     
 ****************************************************/

#include "Math.h"
#include "Task.h"

//Math_dir {{{
//------------------------------------------------------------
// <desc>   v1 -> v2 へのベクトルを求める 
// <in>     v1, v2
// <out>    dir
// <memo>   
//------------------------------------------------------------
void Math_dir(Vector v1, Vector v2, Vector* dir)
{
    dir->x = v2.x - v1.x;
    dir->y = v2.y - v1.y;
    dir->z = v2.z - v1.z;
}
//}}}


//Math_crossproduct {{{
//------------------------------------------------------------
// <desc>   外積を求める
// <in>     v1, v2
// <out>    n
// <memo>   法線ベクトル
//------------------------------------------------------------
void Math_crossproduct(Vector v1, Vector v2, Vector* n)
{
    n->x = v1.y*v2.z - v1.z*v2.y;
    n->y = v1.z*v2.x - v1.x*v2.z;
    n->z = v1.x*v2.y - v1.y*v2.x;
}
//}}}

//Math_magnitude {{{
//------------------------------------------------------------
// <desc>   ベクトルの長さを求める
// <in>     
// <out>    
// <memo>   
//------------------------------------------------------------
float Math_magnitude(Vector v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
//}}}

//Math_distance {{{
float Math_distance(Vector v1, Vector v2)
{
	return sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y) + (v1.z-v2.z)*(v1.z-v2.z));
}
//}}}


//destとsrcのなす角度を求める [弧度]
float Math_angle2D(Vector dest, Vector src){
	return -1*atan2(dest.y - src.y, dest.x - src.x)*180/PI;
}


//比較
int Math_Vector_compare2D(Vector v1, Vector v2){
	//dp("v1(%f, %f), v2(%f, %f)", v1.x, v1.y, v2.x, v2.y);
	if(v1.x == v2.x && v1.y == v2.y){
		return 0;
	}else{
		return -1;
	}
}


//Math_normalize {{{
//------------------------------------------------------------
// <desc>   ベクトルの正規化
// <in>     
// <out>    
// <memo>   単位ベクトル化する
//------------------------------------------------------------
void Math_normalize(Vector* v)
{
    float len = Math_magnitude(*v);

    v->x /= len;
    v->y /= len;
    v->z /= len;
}
//}}}


//Math_invert {{{
//------------------------------------------------------------
// <desc>   逆ベクトルを求める
// <in>     
// <out>    
// <memo>   
//------------------------------------------------------------
void Math_invert(Vector* a)
{
    a->x *= -1;
    a->y *= -1;
    a->z *= -1;
}
//}}}


//------------------------------------------------------------
// <name>
// <desc>   ベクトルの除算
// <in>     
// <out>    
// <memo>   
//------------------------------------------------------------
void Math_division(Vector* src, int n)
{
    if(n != 0)
    {
        src->x /= n;
        src->y /= n;
        src->z /= n;
    }
}

Vector* Math_add(Vector* src, Vector v)
{
    src->x += v.x;
    src->y += v.y;
    src->z += v.z;

	return src;
}

Vector* Math_scale(Vector* src, float n)
{
    src->x *= n;
    src->y *= n;
    src->z *= n;
	return src;
}

//Math_rotate_xz_rad {{{
//X-Z平面に関して、指定されたベクトルをTheta分だけ回転する
Vector Math_rotate_xz_rad(Vector* src, float rad)
{
	Vector ret;
	//float rad = PI/180*theta;
	float c = cos(rad);
	float s = sin(rad);

	Vector_set(&ret, 
			src->x*c - src->z*s, 
			src->y, 
			src->x*s + src->z*c);

	return ret;
}
//}}}
//Math_rotate_xz_theta {{{
//X-Z平面に関して、指定されたベクトルをTheta分だけ回転する
Vector Math_rotate_xz_theta(Vector* src, float theta)
{
	Vector ret;
	float rad = PI/180*theta;
	float c = cos(rad);
	float s = sin(rad);

	Vector_set(&ret, 
			src->x*c - src->z*s, 
			src->y, 
			src->x*s + src->z*c);

	return ret;
}
//}}}

