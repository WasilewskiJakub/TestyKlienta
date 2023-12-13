#include "gyroscope_dynamics.hpp"

GyroscopeDynamics::GyroscopeDynamics(float mass, const glm::mat3& momentOfInertia) :
	RigidBodyDynamics{mass, momentOfInertia}
{ }

void GyroscopeDynamics::computeNetForceAndNetTorque(const Common::State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	glm::vec3 gravityForce{0, -10, 0};
	glm::vec3 leverArm{0, 0, 1};
	netForce = glm::vec3{0, 0, 0};
	netTorque = glm::cross(leverArm, glm::conjugate(state.orientation) * -gravityForce);
}
