
namespace Physics
{
	enum ForceType
	{
		Force,			// mass * distance / time ^ 2 (over time)
		Acceleration,	// distance / time ^ 2	(instantly)
		Impulse,		// mass * distance / time
		VelocityChange	// Distance / Time
	};

};