#pragma once
#include "Math.h"

/*
	Contains a 3-Dimensional Vector.
	Vec3s can be added and subtracted from each other, multiplied by scalars.
	Vec3s can also be divided, where if divided by 2 it would be the same as multiplying by 0.5.
	
	Norm functions have been implemented.
	Dot product and Cross product have been implemented.	
	Vector reflection function is also implemented, requires a normal to reflect over.
*/

//	A Ray class has been implemented at the bottom that is just a class containing two Vec3s and a pointAt function.

class Vec3 {

public:

	Vec3(){
		
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}
	
	Vec3(float X, float Y, float Z) : X(X), Y(Y), Z(Z) {}

	Vec3 operator+(Vec3 other){
		
		return Vec3(X + other[0], Y + other[1], Z + other[2]);
	}
	
	Vec3 operator-(Vec3 other){
		
		return Vec3(X - other[0], Y - other[1], Z - other[2]);
	}
	
	Vec3 operator*(float scalar){
		
		return Vec3(X * scalar, Y * scalar, Z * scalar);
	}
	
	Vec3 operator/(float scalar){
		
		return Vec3(X / scalar, Y / scalar, Z / scalar);
	}
	
	Vec3& operator+=(Vec3 other){
		
		X += other[0];
		Y += other[1];
		Z += other[2];
		return *this;
	}
	
	Vec3& operator-=(Vec3 other){
		
		X -= other[0];
		Y -= other[1];
		Z -= other[2];
		return *this;
	}
	
	Vec3& operator*=(float scalar){
		
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		return *this;
	}
	
	Vec3& operator/=(float scalar){
		
		X /= scalar;
		Y /= scalar;
		Z /= scalar;
		return *this;
	}
	
	float operator[](int index){
		
		if(index == 0) return X;
		if(index == 1) return Y;
		if(index == 2) return Z;
		return -1.0f;
	}
	
	float dot(Vec3 other){
		
		return (X * other[0]) + (Y * other[1]) + (Z * other[2]);
	}
	
	Vec3 cross(Vec3 other){
		
		float rX = Y*other[2] - Z*other[1];
		float rY = Z*other[0] - X*other[2];
		float rZ = X*other[1] - Y*other[0];
		return Vec3(rX, rY, rZ);
	}
	
	float norm(){
		
		return sqrt((X * X) + (Y * Y) + (Z * Z));
	}
	
	Vec3 normalized(){
		
		float length = norm();
		return Vec3(X / length, Y / length, Z / length);
	}
	
	Vec3& normalize(){
		
		float length = norm();
		X /= length;
		Y /= length;
		Z /= length;
		return *this;
	}
	
	Vec3 reflect(Vec3 N){
		
		return ((N * 2.0f) * (N.dot(*this)) - *this) * -1.0f;
	}

private:

	float X;
	float Y;
	float Z;
};

class Ray3 {

public:
	
	Ray3(Vec3 O, Vec3 D) : O(O), D(D) {}
	
	Vec3 pointAt(float T){
		
		return O + (T * D);
	}
	
	Vec3 O;
	Vec3 D;
};

class Mat4 {

public:

	Mat4(){


	}

	Mat4(float diagonal){

		matrix[0][0] = diagonal;
		matrix[1][1] = diagonal;
		matrix[2][2] = diagonal;
		matrix[3][3] = diagonal;
	}

	Mat4 operator+(Mat4 other){

		Mat4 returnMat();

		for(int row = 0; row < 4; ++row){
			for(int col = 0; col < 4; ++col){

				returnMat[row][col] = matrix[row][col] + other[row][col];
			}
		}

		return returnMat;
	}

	Mat4 operator-(Mat4 other){

		Mat4 returnMat();

		for(int row = 0; row < 4; ++row){
			for(int col = 0; col < 4; ++col){

				returnMat[row][col] = matrix[row][col] - other[row][col];
			}
		}

		return returnMat;
	}

private:

	float matrix[4][4];
}

Vec3 operator*(float scalar, Vec3 V);