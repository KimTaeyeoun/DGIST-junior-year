#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <vector>
#include <utility>
#include "common.h"

using namespace std;

class Particle
{
private:
	int name; // particle number
	pair<double, double> loc; // loc vector includes (x, y) location
	pair<double, double> vel; // vel vector includes (x_v, y_v) velocity
	double mass; // mass of this particle
	bool fixed;
	pair <double, double> external_force;
	pair <double, double> original_vel;

public:
	Particle(int n_ = 0, double loc_x = 0, double loc_y = 0, double vel_x = 0, double vel_y = 0, double mass_ = 0, bool fixed_ = 0, double for_x = 0, double for_y = 0);
	~Particle(); // dp
	void print_particle();
	void configure_particle(bool fixed_); // cp
	int get_name() { return name; } // get name of particle
	pair<double, double> get_loc() { return loc; } // get location of particle
	pair<double, double> get_vel() { return vel; } // get velocity of particle
	double get_mass() { return mass; } // get mass of particle
	bool get_fixed() { return fixed; }
	pair <double, double> get_external_force() { return external_force; }
	void update_force(pair<double, double> &external_force, pair<double, double> new_force);
	void update_loc(pair<double, double> new_location);
	void update_vel(pair<double, double> new_velocity);

	void set_location(pair<double, double> loc_);
	void set_velocity(pair<double, double> vel_);

};


class Set
{
private:
	int set_name;
	vector<Particle> particle_vector; // 생성함수에서 particle을 받고 vector을 만든다.
	int force_name;
	pair<double, double> force; // 각 Set마다 안에 있는 모든 힘들을 저장해야 하므로, Set class 안에 이게 있어야 할 것
	double for_x;
	double for_y;
public:
	Set(int name, double for_x = 0, double for_y = 0, int for_n = NIL); // as
	~Set(); 
	int get_set_name() { return set_name; }  //set_name을 얻는다.
	vector<Particle> get_particle_vector() { return particle_vector; } //particle_vector을 얻는다.  
	void print_set();
	void add_particle_to_set(Particle &p); // ae
	void delete_particle_from_set(vector<Particle> default_Particles, vector<Set> default_Set, int particle_name, int set_name); 
 
	void add_force(int name, double x, double y);
	void delete_force();

	int get_force_name() { return force_name; }
	void print_force();

};

void calculate(vector<Particle> &default_Particles, int timetick, bool gravity);

#endif // _FUNCTIONS_H_