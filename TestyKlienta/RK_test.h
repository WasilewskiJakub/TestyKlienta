#pragma once
#include"runge_kutta_right_hand_side.hpp"
namespace Physics
{
	class RungeKutta_Test1 : public RungeKuttaRightHandSide<1>
	{
		virtual void rightHandSide(float time, const std::array<float, 1>& state, std::array<float, 1>& stateDerivative) const {
			stateDerivative[0] = - 2 * time * state[0];
		}
	};
	class RungeKutta_Test2 : public RungeKuttaRightHandSide<1>
	{
		virtual void rightHandSide(float time, const std::array<float, 1>& state, std::array<float, 1>& stateDerivative) const {
			stateDerivative[0] = 6 * time + 11 - 3 * state[0];
		}
	};
	class RungeKutta_Test3 : public RungeKuttaRightHandSide<2>
	{
		virtual void rightHandSide(float time, const std::array<float, 2>& state, std::array<float, 2>& stateDerivative) const {
			stateDerivative[0] = state[0] + 2 * state[1];
			stateDerivative[1] = -state[0] - state[1];
		}
	};
}

