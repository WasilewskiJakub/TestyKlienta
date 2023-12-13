#pragma once

#include "physics/model_dynamics/rigid_body_dynamics.hpp"

class GyroscopeDynamics : public Physics::RigidBodyDynamics
{
public:
	GyroscopeDynamics(float mass, const glm::mat3& momentOfInertia);
	virtual void computeNetForceAndNetTorque(const Common::State& state, glm::vec3& netForce,
		glm::vec3& netTorque) const override;
};
