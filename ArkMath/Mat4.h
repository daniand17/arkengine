#pragma once
struct Mat4
{
private:
	float mElements[16];

public:
	Mat4() { for ( unsigned short i = 0; i < 16 ; i++ ) mElements[i] = 0.0f; }
	Mat4(Mat4 const & matrix) { for ( unsigned short i = 0 ;  i < 16 ; i++ ) mElements[i] = matrix.mElements[i]; }
	Mat4(float array[16]) { for ( unsigned short i = 0 ; i < 16 ; i++ ) mElements[i] = array[i]; }
	void operator += (Mat4 const & matrix) { for ( unsigned short i = 0; i < 16 ; i++ ) mElements[i] += matrix.mElements[i]; }
	void operator -= (Mat4 const & matrix) { for ( unsigned short i = 0; i < 16 ; i++ ) mElements[i] -= matrix.mElements[i]; }
	void operator *= (Mat4 const & matrix);
	void operator *= (float scalar) { for ( unsigned short i = 0 ; i < 16 ; i++ ) mElements[i] *= scalar; }
	void operator /= (float scalar) { for ( unsigned short i = 0 ; i < 16 ; i++ ) mElements[i] /= scalar; }
	void operator = (Mat4 const & matrix) { for ( unsigned short i = 0; i < 16 ; i++ ) mElements[i] = matrix.mElements[i]; }
	void operator = (float arr[16]) { for ( unsigned short i = 0 ; i < 16 ; i++ ) mElements[i] = arr[i]; }
	float const & operator [] (unsigned short index) const { if ( index < 16 ) return mElements[index]; else return mElements[0]; };
	float & operator [] (unsigned short index);
	Mat4 operator - ();

	Mat4 transpose() const;
	Mat4 inverse() const;
	static Mat4 identity()
	{
		Mat4 mat; mat.mElements[0] = 1.0f;
		mat.mElements[5] = 1.0f;
		mat.mElements[10] = 1.0f;
		mat.mElements[15] = 1.0f;
		return mat;
	}
};

Mat4 operator + (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator - (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator * (Mat4 const & lhs, Mat4 const & rhs);
Mat4 operator * (Mat4 const & lhs, float scalar);
Mat4 operator * (float scalar, Mat4 const & lhs);
Mat4 operator / (Mat4 const & lhs,float scalar);
bool operator == (Mat4 const & lhs, Mat4 const & rhs);
bool operator != (Mat4 const & lhs, Mat4 const & rhs);