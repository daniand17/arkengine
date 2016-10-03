#pragma once
struct ArkSize
{
public:
	ArkSize(int width, int height) : mWidth(width), mHeight(height) {}

	void setWidth(int width) { mWidth = width; }
	void setHeight(int height) { mHeight = height; }

	int width() const { return mWidth; }
	int height() const { return mHeight; }
	int isValid() const { return mWidth >= 0 && mHeight >= 0; }
	int area() const { return mWidth * mHeight; }
	void transpose()
	{
		int temp = mWidth;
		mWidth = mHeight;
		mHeight = temp;
	}

private:
	int mWidth;
	int mHeight;
};