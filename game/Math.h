/****************************************************
 *  Math.h                                         
 *  Created on: 06-5-2008 22:26:18                      
 *  Implementation of the Class Math       
 *  Original author: imamura                     
 ****************************************************/

#if !defined(EA_F57E1BDD_1D17_42df_A665_674804CD69DF__INCLUDED_)
#define EA_F57E1BDD_1D17_42df_A665_674804CD69DF__INCLUDED_

#include "Model.h"
#include <math.h>

#define PI 3.1415926


typedef struct Math
{
	int mode;
} Math;

//---------------
//ベクトル系
//---------------

//加算
Vector* Math_add(Vector* src, Vector v);

//除算
void Math_division(Vector* src, int n);

//乗算
Vector* Math_scale(Vector* src, float n);

//長さ
float Math_magnitude(Vector v1);
        
//距離
float Math_distance(Vector v1, Vector v2);	

//正規化
void Math_normalize(Vector* v);

//内積
float Math_dotproduct(Vector v1, Vector v2);

//比較
int Math_Vector_compare2D(Vector v1, Vector v2);

//外積
void Math_crossproduct(Vector v1, Vector v2, Vector* n);

//逆ベクトル
void Math_invert(Vector* v);

//方向ベクトル
void Math_dir(Vector v1, Vector v2, Vector* dir);

//なす角度[弧度]
float Math_angle2D(Vector dest, Vector src);

//面積
float Math_triangle_area(Vector a, Vector b, Vector c);

//回転: X-Z平面に関して、指定されたベクトルをラジアン分だけ回転する
Vector Math_rotate_xz_rad(Vector* src, float rad);
Vector Math_rotate_xz_theta(Vector* src, float theta);

//---------------
//行列系
//---------------
int Math_initmat(float* dest);  //単位行列化
int Math_invertmat(float* dest, float* src);  //逆行列取得


#endif /*!defined(EA_F57E1BDD_1D17_42df_A665_674804CD69DF__INCLUDED_)*/
 
