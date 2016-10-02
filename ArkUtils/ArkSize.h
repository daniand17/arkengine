#pragma once
struct ArkSize
{
public:
	ArkSize(int width, int height) : mWidth(width), mHeight(height) {}

	void setWidth(int width) { mWidth = width; }
	void setHeight(int height) { mHeight = height; }

	int width() { return mWidth; }
	int height() { return mHeight; }
	int isValid() { return mWidth >= 0 && mHeight >= 0; }
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