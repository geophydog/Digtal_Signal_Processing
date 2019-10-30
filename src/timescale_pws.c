#include <stdio.h>
#include <stdlib.h>
#include "seis_dsp.h"

int main(int argc, char **argv){
	if(argc != 4){
		fprintf(stderr, "Usage: time_scale_pws sacfile outfile npower\n");
		exit(1);
	}
	ts_pws(argv[1], argv[2], atof(argv[3]));
	return 0;
}
