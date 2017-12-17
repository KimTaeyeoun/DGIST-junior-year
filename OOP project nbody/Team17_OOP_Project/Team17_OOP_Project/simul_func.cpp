#include <vector>
#include <utility>
#include <iostream>
#include "class.h"
#include "common.h"
#include "simul_func.h"

using namespace std;


void print_all(vector<Particle> particle_vector)
{
	if (particle_vector.empty())
	{
		cout << "No particles" << endl;
	}
	else
	{
		for (vector<Particle>::iterator it = particle_vector.begin(); it != particle_vector.end(); ++it) {
			cout << "Particle: " << it->get_name() << endl;
			cout << "  Location: " << "(" << it->get_loc().first << "," << it->get_loc().second << ")" << endl;
			cout << "  Velocity: " << "(" << it->get_vel().first << "," << it->get_vel().second << ")" << endl;
		}
	}
}

void delete_particle(Particle p)
{
	cout << "Particle " << p.get_name() << " deleted" << endl;
	numParticles--;
	
}

void delete_all()
{
	cout << "All force deleted" << endl;
	cout << "All sets deleted" << endl;
	cout << "All particles deleted" << endl;
	numParticles = 0;
	numSets = 0;
	numForces = 0;
}

void print_time(int time)
{
	cout << "Current time is " << time << endl;
}

