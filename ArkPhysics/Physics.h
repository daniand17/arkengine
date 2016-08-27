
namespace Physics
{
	enum ForceType
	{
		Force,			// mass * distance / time ^ 2 (over time)
		Acceleration,	// distance / time ^ 2	(instantly)
		Impulse,		// mass * distance / time
		VelocityChange	// Distance / Time
	};

	Vec3 const gravity = Vec3(0.0f, 9.81f, 0.0f);

};