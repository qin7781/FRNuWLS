#include "basis_pms.h"
#include "build.h"
#include "pms.h"
#include "heuristic.h"
#include <signal.h>

ISDist s;
//int seed = 1;
long long best_known;
long long total_step = 0;
long long consecutive_better_soft = 0;
char * file_name = NULL;
void interrupt(int sig)
{
	if (s.verify_sol() == 1)
		cout << "c verified" << endl;
	s.print_best_solution();
	s.free_memory();
	exit(10);
}

int main(int argc, char *argv[])
{

	if(argc != 4)
	{
		cout << "The number of command line arguments is inappropriate. It should be 4: solver instance seed cutoff." << endl;
		exit(-1);
	}

	start_timing();

	char * instance_file_name = argv[1];

	int seed = atoi(argv[2]);

	int cutoff_time = atoi(argv[3]);

	signal(SIGTERM, interrupt);

	// sscanf(argv[2], "%d", &seed);
	// srand(seed);
	s.build_instance(instance_file_name);

	s.settings(seed, cutoff_time);

	s.parse_parameters2(argc, argv);
	s.local_search_with_decimation(instance_file_name);

	//s.simple_print();

	//s.free_memory();

	return 0;
}
