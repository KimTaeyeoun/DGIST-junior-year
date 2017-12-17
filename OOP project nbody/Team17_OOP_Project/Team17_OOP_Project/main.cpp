#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>

#include "class.h"
#include "common.h"
#include "simul_func.h"
#include <Windows.h>

using namespace std;

int timetick = 0;
int time = 0;
int numParticles = 0;
int numSets = 0;
int numForces = 0;
bool gravity = true;

vector<Particle> default_Particles; // Particle을 만들면, 일단 여기에 들어간다. Set과 상관없이 존재. Set에 있는 particle을 지우면 여기에서도 지워져야 한다.
vector<Set> default_Set; // Set을 만들면, 일단 여기에 들어간다. Set에 관한 명령어를 입력했을 때 그 Set을 검색하기 위해 모아놓은 벡터

bool has_only_spaces(const std::string& str) {
	return str.find_first_not_of(' ') == str.npos;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void commander(istream& is) {
	cout << "Enter a command: ";
	for (string line; getline(is, line); ) {
		
		if (line == "qq") {
			/* da */
			default_Particles.clear();
			default_Set.clear();
			numParticles = 0; numSets = 0; numForces = 0;
			cout << "All Forces deleted" << endl;
			cout << "All sets deleted" << endl;
			cout << "All particles deleted" << endl;

			/* pm */
			cout << "Particles: " << numParticles << endl;
			cout << "Sets: " << numSets << endl;
			cout << "Forces: " << numForces << endl;

			cout << "Done\n";
			system("pause");
			break;

		}

		istringstream iss{ line };
		vector<string> words{ istream_iterator<string> {iss},
			istream_iterator<string> {} };

		if (line.empty() || has_only_spaces(line)) {
			cout << "Please Input Command\n";
			continue;
		}

		bool fERR = 0; // Format ERR
		bool parameter = 0; // Parameter exists or not

		/* Print Commands */
		if (words[0] == "pa"){ // pa
			print_all(default_Particles);
		}
		else if (words[0] == "pp"){ // pp <particle>
			int i = 0;
			int particle_name;
			bool exist = false;
			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						particle_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				// particle number로 default_Particles 벡터에서 해당 particle을 검색해야 한다.
				for (vector<Particle>::iterator it = default_Particles.begin(); it != default_Particles.end(); ++it) {
					if (it->get_name() == particle_name) {
						it->print_particle();
						exist = true;
						break;
					}
				}
				if (!exist)
					cout << "No particle with that number\n";
			}
			ParCheck;

		}
		else if (words[0] == "ps") { // ps <set>
			int set_number;
			int i = 0;
			bool exist = false;
			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						set_number = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			for (vector<Set>::iterator it = default_Set.begin(); it != default_Set.end(); ++it) {
				if (it->get_set_name() == set_number) {
					it->print_set();
					exist = true;
					break;
				}
			}
			if (!exist)
				cout << "No set with that number\n";
		}
		else if (words[0] == "pf") { // pf
			
			int force_number;
			int i = 0;
			bool exist = false;
			for (string& w : words) {
				if (i == 1)		force_number = atoi(w.c_str());
				i++;
			}
			for (vector<Set>::iterator it = default_Set.begin(); it != default_Set.end(); ++it) {
				if (it->get_force_name() == force_number) {
					it->print_force();
					exist = true;
					break;
				}
			}
			if (!exist)
				cout << "No forces\n";
		}
		else if (words[0] == "pt") { // pt
			print_time(time);
		}
		else if (words[0] == "pm") { // pm
			cout << "Particles: " << numParticles << endl;
			cout << "Sets: " << numSets << endl;
			cout << "Forces: " << numForces << endl;
		}
		else if (words[0] == "pg") { // pg
			if (gravity)
				cout << "Gravity is active now" << endl;
			else
				cout << "Gravity is inactive now" << endl;
		}

		/* Add Commands */
		else if (words[0] == "ap"){ // ap <particle> <mass> <x> <y> <v_x> <v_y>
			int i = 0;
			int particle_name;
			double locX, locY, velX, velY, mass;
			for (string& w : words) {
				try
				{
					double w_double = stod(w);

					if (i == 1)		particle_name = atoi(w.c_str());
					else if (i == 2)	mass = w_double;
					else if (i == 3)	locX = w_double;
					else if (i == 4)	locY = w_double;
					else if (i == 5)	velX = w_double;
					else if (i == 6) {
						velY = w_double;
						ParExists;
					}
				}
				catch (...)
				{
					if (is_num) {
						if (i == 1)		particle_name = atoi(w.c_str());
						else if (i == 2)	mass = stod(w);
						else if (i == 3)	locX = stod(w);
						else if (i == 4)	locY = stod(w);
						else if (i == 5)	velX = stod(w);
						else if (i == 6) {
							velY = stod(w);
							ParExists;
						}
					}
					is_not_number;
				}
				i++;
			}
			if (particle_name < 0)
				cout << "Particle number is not in range!\n";
			else if (NOERR) {
				Particle p1(particle_name, static_cast<double>(locX), locY, velX, velY, static_cast<double>(mass), false); 
				default_Particles.push_back(p1);
				cout << "Particle " << p1.get_name() << " added" << endl;
				numParticles++;
			}
			ParCheck;
			
		}

		else if (words[0] == "as") { // as <set>
			int i = 0;
			int set_name;
			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						set_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				Set s(set_name);
				default_Set.push_back(set_name);
				cout << "Set " << s.get_set_name() << " added" << endl;
			}
			ParCheck;
			numSets++;
		}
		else if (words[0] == "ae") { // ae <set> <particle>		ae 1 0 means add particle '0' to set '1'
			int i = 0;
			int set_name;
			int particle_name;
			bool set_exist = false;
			bool particle_exist = false;
			for (string& w : words) {
				if (is_num) {
					if (i == 1)
						set_name = atoi(w.c_str());
					else if (i == 2) {
						particle_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				vector<Set>::iterator it_Set = default_Set.begin(); // Find the Set
				for (; it_Set != default_Set.end(); ++it_Set) {
					if (it_Set->get_set_name() == set_name) {
						set_exist = true;
						break;
					}
				}
				if (set_exist) {
					vector<Particle>::iterator it_Particle = default_Particles.begin(); // Find the Particle to add to Set
					for (; it_Particle != default_Particles.end(); ++it_Particle) {
						if (it_Particle->get_name() == particle_name) {
							it_Set->add_particle_to_set(*it_Particle); // Add found Particle to found Set
							cout << "Particle " << particle_name << " added to set " << set_name << endl;
							particle_exist = true;
							break;
						}
					}
					if (!particle_exist)
						cout << "No particle with that number!\n";
				}
				else
					cout << "No set with that number!\n";

			}
			ParCheck;
		}

		else if (words[0] == "af") { // af <force> <set> <f_x> <f_y>
			int i = 0;
			int force_name;
			int set_name;
			double forceX, forceY;

			for (string& w : words) {
				try
				{
					if (i == 1)
						force_name = atoi(w.c_str());
					else if (i == 2)	set_name = atoi(w.c_str());
					else if (i == 3)	forceX = stod(w);
					else if (i == 4) {
						forceY = stod(w);
						ParExists;
					}
				}
				catch (...)
				{
					if (is_num) {
						if (i == 1)
							force_name = atoi(w.c_str());
						else if (i == 2)	set_name = atoi(w.c_str());
						else if (i == 3)	forceX = stod(w);
						else if (i == 4) {
							forceY = stod(w);
							ParExists;
						}
					}
					is_not_number;
				}
				i++;
			}

			if (NOERR) {
				for (vector<Set>::iterator it = default_Set.begin(); it != default_Set.end(); ++it)
					if (it->get_set_name() == set_name) {
						it->add_force(force_name, forceX, forceY);
						cout << "Force " << force_name << " added\n";
						break;
					}
			}
			ParCheck;
		}

		/* Delete Commands */
		else if (words[0] == "dp") { // dp <particle>
			int i = 0;
			int particle_name;

			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						particle_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			
			if (NOERR) {
				bool exist = false;
				vector<Particle>::iterator it = default_Particles.begin();
				for (; it != default_Particles.end();) {
					if (it->get_name() == particle_name) {
						if (it == default_Particles.end() - 1) {
							default_Particles.pop_back();
						}
						else {
							default_Particles.erase(it);
						}
						cout << "Particle " << particle_name << " deleted" << endl;
						numParticles--;
						exist = true;
						break;
					}
					else 
						++it;
				}
				if (!exist) // You try to delete nonexisting particle
					cout << "No particle with that number!\n";
			}
			ParCheck;
		}
		else if (words[0] == "de") { // de <set> <particle>
			int i = 0;
			int set_name;
			int particle_name;
			bool particle_exist = false;
			for (string& w : words) {
				if (is_num) {
					if (i == 1)
						set_name = atoi(w.c_str());
					else if (i == 2) {
						particle_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				vector<Set>::iterator it_Set = default_Set.begin(); // Find the Set
				for (; it_Set != default_Set.end(); ++it_Set) {
					if (it_Set->get_set_name() == set_name) {
						particle_exist = true;
						it_Set->delete_particle_from_set(default_Particles, default_Set, particle_name, set_name);
						break;
					}
				}
				if (!particle_exist)
					cout << "No particle with that number!\n";
			}
			ParCheck;
		}
	
		else if (words[0] == "df") { // df <force>
			int i = 0;
			int force_name;

			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						force_name = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				for (vector<Set>::iterator it = default_Set.begin(); it != default_Set.end(); ++it)
					if (it->get_force_name() == force_name) {
						it->delete_force();
						cout << "Force " << force_name << " deleted" << endl;
					}
			}
			ParCheck;
		}

		else if (words[0] == "da") { // da
			default_Particles.clear();
			default_Set.clear();
			cout << "All Forces deleted" << endl;
			cout << "All sets deleted" << endl;
			cout << "All particles deleted" << endl;
		}

		else if (words[0] == "ct") { // ct <tick>
			int i = 0;
			int timetick_;
			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						timetick_ = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				timetick = timetick_;
			}
			ParCheck;
		}

		else if (words[0] == "cg") { // cg <bool>
			int i = 0;
			bool gravity_;

			for (string& w : words) { 
				if (i == 1) {
					if (w == "true")	gravity_ = true;
					else if (w == "false")	gravity_ = false;
					else if (w == "0")	gravity_ = false;
					else if (w == "1")	gravity_ = true;
					else	formatERR;
					ParExists;
				}
				i++;
			}
			if (NOERR) {
				gravity = gravity_;
				if (gravity_)
					cout << "Gravity enabled\n";
				else
					cout << "Gravity disabled\n";
			}
			ParCheck;
		}

		else if (words[0] == "cp") { // cp <particle> <bool>
			int i = 0;
			int particle_name;
			bool fixed__;
			for (string& w : words) {
				if (i == 1) {
					particle_name = atoi(w.c_str());
				}
				else if (i == 2) {
					if (w == "true")	fixed__ = true;
					else if (w == "false")	fixed__ = false;
					else if (w == "0")	fixed__ = false;
					else if (w == "1")	fixed__ = true;
					else	formatERR;
					ParExists;
				}
				i++;
			}
			if (NOERR) {
				// Change the 'fixed' member variable of Particle corresponding to particle_name
				vector<Particle>::iterator it_particle = default_Particles.begin();
				for (; it_particle != default_Particles.end(); ++it_particle) //find proper particle vector 
					if (it_particle->get_name() == particle_name)
						break;
				if (fixed__) {
					it_particle->configure_particle(true);
					cout << "Particle " << particle_name << " is set to fixed" << endl;
				}
				else{
					it_particle->configure_particle(false);
					cout << "Particle " << particle_name << " is set to movable" << endl;
				}
			}
			ParCheck;
		}
		else if (words[0] == "ru") { // ru <duration>
			int i = 0;
			int duration;

			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						duration = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				int for_size = duration / timetick;
				for (int j = 0; j < for_size; ++j) {
					calculate(default_Particles, timetick, gravity);
				}
			}
			ParCheck;
		}
		else if (words[0] == "rv") { // rv <duration>
			int i = 0;
			int duration;

			for (string& w : words) {
				if (is_num) {
					if (i == 1) {
						duration = atoi(w.c_str());
						ParExists;
					}
				}
				is_not_number;
				i++;
			}
			if (NOERR) {
				int for_size = duration / timetick;
				for (int j = 0; j < for_size; ++j) {
					calculate(default_Particles, timetick, gravity);
					for (vector<Particle>::iterator it = default_Particles.begin(); it != default_Particles.end(); ++it) {
						cout << "P" << it->get_name() << "," << timetick*j << "," << it->get_loc().first << "," << it->get_loc().second << endl;
					}
				}
			}
			ParCheck;
		}
		else {
			cout << "Unrecognized command!\n";
		}
		cout << "\nEnter a command: ";
	}
}

int main(void)
{
	cout << "Start N-body Simulators.." << endl;

	commander(cin);
}