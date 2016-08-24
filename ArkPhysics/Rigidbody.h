#include "Vec3.h"
#include "Quaternion.h"


class Rigidbody
{
private:	// Members
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;
	Quaternion rotation;

	float mass;
	float drag;
	float angularDrag;

public:
	enum ForceType {
		Force,			// mass * distance / time ^ 2 (over time)
		Acceleration,	// distance / time ^ 2	(instantly)
		Impulse,		// mass * distance / time
		VelocityChange	// Distance / Time
	};
	void addForce(Vec3 force, ForceType forceType = ForceType::Force);
	void addTorque(Vec3 torque, ForceType forceType = ForceType::Force);
};