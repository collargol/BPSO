#include <iostream>
#include <ctime>

#include "particle.h"

int main()
{
	srand(time(0));

	Particle p(40);
	p.printCurrentState();

	// xi is a vector of m features
	// Vmax should be probably 6
	//
	// initialize S particles with random components from {0, 1}
	//		initialize every particle's best position as it's initial position pi <-- xi
	//		if (f(pi) < f(g))
	//			update global best position g <-- pi
	//		initialize velocity of particle ???
	//
	// MAIN ALGORITHM:
	// while (NOT stop_criteria)
	//		foreach (particle)
	//			foreach (component d in 1,2,...,m)
	//				pick random numbers
	//				update velocity of particle vi,d <-- vi,d + fi*(pi,d - xi,d) + fi*(pg,d - xi,d)   ( fi is randomly generated)
	//			update particle position xi <-- xi + vi
	//			if (f(xi) < f(pi)
	//				update particle's best known position pi <-- xi
	//				if (f(pi) < f(g))
	//					update best known global position g <-- pi
}

