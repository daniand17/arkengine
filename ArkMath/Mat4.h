#pragma once



#include <glm\glm.hpp>
struct Mat4
{
private:
	glm::mat4 mMat;

public:
	Mat4() : mMat(0.0f) {}
	Mat4(Mat4 const & matrix) { mMat = matrix.mMat; }
	Mat4(glm::mat4 const & mat);
	glm::mat4 const & data() const { return mMat; }
	void operator += (Mat4 const & matrix) { mMat += matrix.mMat; }
	void operator -= (Mat4 const & matrix) { mMat -= matrix.mMat; }
	void operator *= (Mat4 const & matrix);
	void operator *= (float scalar) { mMat *= scalar; }
	void operator /= (float scalar) { mMat /= scalar; }
	void operator = (Mat4 const & matrix) { mMat = matrix.mMat; }
	//void operator = (float arr[16]) { mMat = arr; } // TODO implement later

	glm::vec4 const & operator [] (unsigned short index) const { if ( index < 16 ) return mMat[index]; else return mMat[0]; };
	Mat4 operator - ();

	Mat4 transpose() const;
	Mat4 inverse() const;
	static Mat4 identity() { return Mat4(glm::mat4(1.0f)); }
};

Mat4 operator + (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator - (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator * (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator * (Mat4 const & lhs, float scalar);
Mat4 operator * (float scalar, Mat4 const & lhs);
Mat4 operator / (Mat4 const & lhs, float scalar);
bool operator == (Mat4 const & lhs, Mat4 const & rhs);
bool operator != (Mat4 const & lhs, Mat4 const & rhs);