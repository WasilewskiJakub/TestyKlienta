#include<iostream>
#include <fstream>
#include <string>

#include"runge_kutta.hpp"
#include"RK_test.h"
#include<cmath>

using namespace Physics;

float sollution_t1(float t) {
	return exp(-t * t);
}
float sollution_t2(float t) {
	return exp(-3 * t) + 2*t + 3;
}

float sollutionx_t3(float t) {
	return cos(t) + 3*sin(t);
}

float sollutiony_t3(float t) {
	return cos(t) - 2 * sin(t);
}

int main(int argc, char** argv) {
	RungeKutta_Test1 test1;
	RungeKutta_Test2 test2;
	RungeKutta_Test3 test3;

	std::array<float, 1> value_test1 = {1};
	std::array<float, 1> next_value_test1;
	std::array<float, 1> value_test2 = {4};
	std::array<float, 1> next_value_test2;
	std::array<float, 2> value_test3 = {1,1};
	std::array<float, 2> next_value_test3;

	std::ofstream csvFile1("test1.csv");
	std::ofstream csvFile2("test2.csv");
	std::ofstream csvFile3("test3.csv");

	csvFile1.imbue(std::locale("German_germany"));
	csvFile2.imbue(std::locale("German_germany"));
	csvFile3.imbue(std::locale("German_germany"));

	for (float time = 0; time < 1; time += 0.01) {
		
		//TEST 1:
		RungeKutta<1>::RK4(time, 0.01, value_test1, test1, next_value_test1);
		csvFile1 << sollution_t1(time) << ";" << value_test1[0] << std::endl;
		value_test1 = next_value_test1;

		//TEST 2:
		RungeKutta<1>::RK4(time, 0.01, value_test2, test2, next_value_test2);
		csvFile2 << sollution_t2(time) << ";" << value_test2[0] << std::endl;
		value_test2 = next_value_test2;

		//TEST 3:
		RungeKutta<2>::RK4(time, 0.01, value_test3, test3, next_value_test3);
		csvFile3 << sollutionx_t3(time) << ";" << value_test2[0] << ";" << sollutiony_t3(time) << ";" << value_test1[1] << std::endl;
		value_test3 = next_value_test3;
	}
	
	csvFile1.close();
	csvFile2.close();
	csvFile3.close();
	return 0;
}