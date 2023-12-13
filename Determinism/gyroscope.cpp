#include "gyroscope.hpp"

Gyroscope::Gyroscope(float mass, const glm::mat3& momentOfInertia) :
	m_dynamics{mass, momentOfInertia}
{ }

void Gyroscope::update(const Gyroscope& previousGyroscope)
{
	setState(m_dynamics.computeNewState(previousGyroscope.getState()));
}
