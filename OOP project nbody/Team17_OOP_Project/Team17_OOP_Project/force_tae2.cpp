#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include "class.h"
#include "common.h"
#include "math.h"

using namespace std;

void calculate (vector<Particle> &default_Particles, int timetick, bool gravity)  
{
	int size = default_Particles.size();
	vector<int> names;
	vector<double> x_loc;
	vector<double> y_loc;
	vector<double> x_vel;
	vector<double> y_vel;
	vector<double> mass;
	vector<double> force;
	vector<double> vec_x;
	vector<double> vec_y;
	for (int i = 0; i < size; ++i)  //계산하기 위해서 set의 모든 정보들을 뽑아오는 과정
	{
		int name = default_Particles[i].get_name();
		pair<double, double> loc = default_Particles[i].get_loc();
		pair<double, double> vel = default_Particles[i].get_vel();
		double m = default_Particles[i].get_mass();
		double x_loc1 = loc.first;
		double y_loc1 = loc.second;
		double x_vel1 = vel.first;
		double y_vel1 = vel.second;
		names.push_back(name);
		x_loc.push_back(x_loc1);
		y_loc.push_back(y_loc1);
		x_vel.push_back(x_vel1);
		y_vel.push_back(y_vel1);
		mass.push_back(m);
	}
	if (gravity == 1)
	{
		for (int i = 0; i < size; ++i)
		{
			if (default_Particles[i].get_fixed() == 0) //fix 안 되어 있을 때만 계산
			{
				for (int j = 0; j < size; ++j)
				{
					if (i != j)
					{
						//거리 구하기
						double r_sq = pow(x_loc[i] - x_loc[j], 2) + pow(y_loc[i] - y_loc[j], 2);
						//힘 구하기
						double F = G*mass[i] * mass[j] / r_sq;
						if ( F < 0)
						{
							F = MAX_DOUBLE;
						}
						//단위 벡터 구하기
						double vec_x1 = (x_loc[j] - x_loc[i]) / sqrt(r_sq); // pow(r_sq, 0.5);
						double vec_y1 = (y_loc[j] - y_loc[i]) / sqrt(r_sq); // pow(r_sq, 0.5);
						force.push_back(F);
						vec_x.push_back(vec_x1);
						vec_y.push_back(vec_y1);
					}
				}
				double f_x = 0.;
				double f_y = 0.;

				int forcesize = force.size();
				for (int j = 0; j < forcesize; ++j)
				{
					//합력 구하기
					f_x = f_x + force[j] * vec_x[j];
					f_y = f_y + force[j] * vec_y[j];
				}
				pair<double, double> external_force = default_Particles[i].get_external_force();
				//외력 더해주기
				f_x = f_x + external_force.first;
				f_x = f_x + external_force.second;
				//가속도 구하기
				double a_x = f_x / mass[i];
				double a_y = f_y / mass[i];
				//나중속도 구하기
				double vel_x_later = x_vel[i] + a_x * timetick;
				double vel_y_later = y_vel[i] + a_y * timetick;
				//이동거리 구하기
				double s_x = (x_vel[i] + vel_x_later)*timetick / 2;
				double s_y = (y_vel[i] + vel_y_later)*timetick / 2;
				// 이동 후 위치 구하기
				double x_loc_later = x_loc[i] + s_x;
				double y_loc_later = y_loc[i] + s_y;
				pair<double, double> location = make_pair(x_loc_later, y_loc_later);
				pair<double, double> velocity = make_pair(vel_x_later, vel_y_later);

				default_Particles[i].update_loc(location);
				default_Particles[i].update_vel(velocity);
				force.clear();
				vec_x.clear();
				vec_y.clear();
			}

		}
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			if (default_Particles[i].get_fixed() == 0) //fix 안 되어 있을 때만 계산
			{
				pair<double, double> external_force = default_Particles[i].get_external_force();
				if (external_force.first == 0. && external_force.second == 0.)
				{
					double x_loc_later = x_loc[i] + x_vel[i] * timetick;
					double y_loc_later = y_loc[i] + y_vel[i] * timetick;
					pair<double, double> location = make_pair(x_loc_later, y_loc_later);
					default_Particles[i].update_loc(location);
				}
				else
				{
					double f_x = external_force.first;
					double f_y = external_force.second;
					//가속도 구하기
					double a_x = f_x / mass[i];
					double a_y = f_y / mass[i];
					//나중속도 구하기
					double vel_x_later = x_vel[i] + a_x * timetick;
					double vel_y_later = y_vel[i] + a_y * timetick;
					//이동거리 구하기
					double s_x = (x_vel[i] + vel_x_later)*timetick / 2;
					double s_y = (y_vel[i] + vel_y_later)*timetick / 2;
					// 이동 후 위치 구하기
					double x_loc_later = x_loc[i] + s_x;
					double y_loc_later = y_loc[i] + s_y;
					//timetick이후의 정보 업데이트 해주기  particle에 추가 함수 필요
					pair<double, double> location = make_pair(x_loc_later, y_loc_later);
					pair<double, double> velocity = make_pair(vel_x_later, vel_y_later);
					default_Particles[i].update_loc(location);
					default_Particles[i].update_vel(velocity);
				}
			}
		}
	}
}
