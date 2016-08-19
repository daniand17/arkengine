
struct Vec2
{
public:
	double x;
	double y;

	void operator+=(Vec2 & other);
	void operator-=(Vec2 & other);
	void operator*=(float scalar);
	void operator/=(float scalar);

private:

};