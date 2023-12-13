#pragma once

#include "gyroscope_dynamics.hpp"
#include "physics/models/model.hpp"

class Gyroscope : public Physics::Model
{
public:
	Gyroscope(float mass, const glm::mat3& momentOfInertia);
	void update(const Gyroscope& previousGyroscope);

private:
	GyroscopeDynamics m_dynamics;
};
