#include "physics/models/airplane.hpp"
#include "physics/simulation_buffer.hpp"
#include "gyroscope.hpp"

#include <iostream>

void determinismTest()
{
	Physics::Airplane airplane{Common::AirplaneTypeName::mustang};

	Common::State initialState;
	constexpr glm::vec3 initialVelocity{0, 0, -100};
	initialState.velocity = initialVelocity;
	airplane.setState(initialState);

	constexpr int simulationTimeSec = 10;
	
	for (int i = 0; i < simulationTimeSec * Physics::framesPerSecond; ++i)
	{
		airplane.update(airplane);
	}
	Common::State state1 = airplane.getState();

	airplane.setState(initialState);
	
	for (int i = 0; i < simulationTimeSec * Physics::framesPerSecond; ++i)
	{
		airplane.update(airplane);
	}
	Common::State state2 = airplane.getState();

	std::array<float, Common::State::stateLength> state1Arr{};
	std::array<float, Common::State::stateLength> state2Arr{};
	state1.toArray(state1Arr);
	state2.toArray(state2Arr);
	if (state1Arr == state2Arr)
	{
		std::cout << "SUCCESS\n";
	}
	else
	{
		std::cout << "FAILURE\n";
	}
}

void gyroscopeTest()
{
	constexpr float mass = 1;
	constexpr glm::mat3 momentOfInertia
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	Gyroscope gyroscope{mass, momentOfInertia};
	
	gyroscope.translate(glm::vec3{0, 6, 0});
	gyroscope.rotatePitch(70);
	Common::State initialState = gyroscope.getState();
	initialState.velocity = glm::vec3{0, 0, 0};
	initialState.angVelocityRad = glm::vec3{0, 0, 30};
	gyroscope.setState(initialState);

	constexpr int simulationTimeSec = 210;
	
	int st = 0;
	int start{};
	int count = 0;
	float sum = 0;
	float min = 50 * Physics::framesPerSecond;
	float max = 0;
	for (int t = 0; t < simulationTimeSec * Physics::framesPerSecond; ++t)
	{
		gyroscope.update(gyroscope);
		Common::State state = gyroscope.getState();

		switch (st)
		{
		case 0:
			if (state.direction().z < 0)
			{
				start = t;
				st = 1;
			}
			break;
		case 1:
			if (state.direction().z > 0)
			{
				st = 2;
			}
			break;
		case 2:
			if (state.direction().z < 0)
			{
				float duration = (float)(t - start) / Physics::framesPerSecond;
				if (duration < 5) break;
				if (duration < min) min = duration;
				if (duration > max) max = duration;
				count++;
				sum += duration;
				std::cout << "single:\t" << duration << '\n';
				std::cout << "avg:\t" << sum / count << '\n';
				std::cout << "count:\t" << count << '\n';
				std::cout << "min:\t" << min << '\n';
				std::cout << "max:\t" << max << '\n';
				std::cout << std::endl;
				start = t;
				st = 1;
			}
			break;
		}
	}
}

int main()
{
	gyroscopeTest();
	return 0;
}
