#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include "class.h"
#include "common.h"
#include <string>

using namespace std;

/* Particle */
/*********************************************************************************/
Particle::Particle(int n_, double loc_x, double loc_y, double vel_x, double vel_y, double mass_, bool fixed_ , double for_x, double for_y)  
{
	/* �����ڸ� ���� member variable �ʱ�ȭ. ap(add particle) */
	name = n_;
	loc = make_pair(loc_x, loc_y);
	vel = make_pair(vel_x, vel_y);
	mass = mass_;
	fixed = fixed_;
	external_force = make_pair(for_x, for_y);
}                         

Particle::~Particle()
{
	//Destructor
}
void Particle::print_particle()
{
	cout << "Particle: " << name << endl;
	cout << "	Location: (" << loc.first << ", " << loc.second << ")" << endl;
	cout << "	Velocity: (" << vel.first << ", " << vel.second << ")" << endl;
}

void Particle::configure_particle(bool fixed_)
{
	fixed = fixed_;
}

void Particle::update_force(pair<double, double> &external_force, pair<double, double> new_force)
{
	double force_x = new_force.first;
	double force_y = new_force.second;
	double external_force_x = external_force.first + force_x;
	double external_force_y = external_force.second + force_y;
	external_force = make_pair(external_force_x, external_force_y);
}

void Particle::update_loc(pair<double, double> new_location)
{
	this->loc = new_location;
}
void Particle::update_vel(pair<double, double> new_velocity)
{
	this->vel = new_velocity;
}
void Particle::set_location(pair<double, double>loc_) // No use but in UML
{
	loc = loc_;

	cout << "loc_: " << loc_.first << " " << loc_.second << endl;
	cout << "loc: " << loc.first << " " << loc.second << endl;
	cout << "get_loc: " << get_loc().first << " " << get_loc().second << endl;
}
void Particle::set_velocity(pair<double, double>vel_)
{
	vel = vel_;
}
/*********************************************************************************/

/* Set */
/*********************************************************************************/
Set::Set(int name,  double for_x, double for_y, int for_n)	//as ��ɾ� �����ڷ� ����, particle�� ���ڷ� �ް� ���ο��� ���͸� �����.
{
	set_name = name;
	force = make_pair(for_x, for_y);
	force_name = for_n;
}

Set::~Set()
{
	//destructor
}
void Set::print_set()
{
	cout << "- - - Set " << set_name << " - - -" << endl;
	for (vector<Particle>::iterator it = particle_vector.begin(); it != particle_vector.end(); ++it) //for������ vector�ȿ� �ִ� particle�� ���� ���� ���  //minjae) iterator�� �� ������  //misnu) �̷���?
	{
		cout << "Particle :" << it->get_name() << endl;
		cout << "	Location: (" << it->get_loc().first << "," << it->get_loc().second << ")" << endl;
		cout << "	Velocity: (" << it->get_vel().first << "," << it->get_vel().second << ")" << endl;
	}
}

void Set::add_force(int name, double x, double y)
{
	force = make_pair(x,y);
	force_name = name;
	int size = particle_vector.size();
	for (int i = 0; i < size; ++i)
	{
		particle_vector[i].update_force(particle_vector[i].get_external_force(), force);
	}
	numForces++;
}
void Set::delete_force() 
{
	force.first = -1*force.first;
	force.second = -1*force.second;
	int size = particle_vector.size();
	for (int i = 0; i < size; ++i)
	{
		particle_vector[i].update_force(particle_vector[i].get_external_force(), force);
	}
	force.first = 0;
	force.second = 0;
	force_name = NIL;  
	numForces--;
}

void Set::print_force()
{
	cout << "Force " << force_name << " applied to set " << force_name << ": (" << force.first << "," << force.second << ")\n";
}


void Set::add_particle_to_set(Particle &p)
{
	particle_vector.push_back(p); //���ο� particle�� vector�� �߰����� 
}

void Set::delete_particle_from_set(vector<Particle> default_Particles, vector<Set> default_Set, int particle_name, int set_name)
{
	vector<Particle>::iterator it_Particle = default_Particles.begin(); // Find the Particle to add to Set
	for (; it_Particle != default_Particles.end(); ++it_Particle) {
		if (it_Particle->get_name() == particle_name) {

			if (it_Particle == default_Particles.end() - 1) {
				particle_vector.pop_back();
			}

			else {
				it_Particle = particle_vector.erase(it_Particle);
			}
			cout << "Particle " << particle_name << " deleted from set " << set_name << endl;
			break;
		}
	}

}

/*********************************************************************************/