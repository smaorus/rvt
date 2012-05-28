
// This file shows one bug in the list of outputs and one source for improvement. The difference is in hybrid_estimate, but it is still supposed to be p.e.
// 1. There is a bug in the list of outputs. in hybrid_estimate.rv.c it thinks that s0_stderr_1->flags is a global output, which it isn't.
// 2. Even after removing the above, it takes cbmc a long time to solve because of the multiplication. If 'handle_mod' could replace also multiplicaion, this would solve it. Replacing the multiplication with cprover_uninterpreted_mul solves it in less that a second.






#include <stdio.h>
#include<stdlib.h>
#include <string.h>
void assert(_Bool c);
void my_strcpy(char *, const char *);
FILE *my_fopen (const char *path, const char *mode);

char s[200], s1[200], org_file[200];
int
 debug = 0,
 hybrid = 0,
 hybrid_value = 0,
 hy_uniform = 0,
 hy_uniform_value = 0,
 real_count = 0,
 vars,
 print_allsat_solutions = 0,
 experiments = 100,
 count = 0,
 sum_hyb_est = 0,
 hy_uniform_sum = 0,
  est,
  hyb_est,
  sum_est = 0,
  t,
unsat;



FILE * cnf;



int mypower(int x, int sp) {
int result;
unsigned int p1;

 p1 = (unsigned) sp;
 for (result = 1; p1 != 0; p1 = p1>>1) {
  if (p1 & 0x1)
   result *= x;
  x = x*x;
 }
 return result;
}


void Abort(char *s, int instructions) {
 fprintf(stderr, "%s\n", s);
 if (instructions)
   fprintf(stderr, "Usage: counter <cnf file-name> [options]\n"
  "Options are: \n\n"
  "-d\t print debug information\n"
  "-hyb <k>\t Hybrid-bottom, i.e.,  (exact allsat on the (iterations - k) iteration) * 2^(iterations - k)\n"
  "-hyt <k> \t Hybrid-top. i.e., (exact allsat on the k-th iteration) * (2^k) \n"
  "-r\t return real number of solutions\n"
  "-a\t print allsat result for all iterations\n"
  "-ex\t number of experiments (default = 100)\n"
  );
 exit(1);
}



void parse_options(int argc, char **argv) {
 int i;
 if (argc < 2) Abort("Too few arguments",1);
 cnf = my_fopen(argv[1],"r");
 if (!cnf) Abort("can't open input file",1);
 fscanf(cnf,"p cnf %d", &vars);
 if (vars <= 0) Abort("can't read number of variables from input file",1);
 if (argc > 2)
 for (i = 2; i < argc; i++) {
  if (!strcmp(argv[i], "-d")) debug = 1;
  else if (!strcmp(argv[i], "-hyb")) {
   i++;
   if (i >= argc) Abort("Expecting a numeric value after -hy", 1);

   hybrid_value = atoi(argv[i]);
   if (hybrid_value < 0) Abort("hybrid value should be positive",1);
   hybrid = 1;
  }
  else if (!strcmp(argv[i], "-ex")) {
   i++;
   if (i >= argc) Abort("Expecting a numeric value after -ex", 1);
   experiments = atoi(argv[i]);
   if (experiments < 1) Abort("# of experiments should be > 0",1);
  }
  else if (!strcmp(argv[i], "-r")) real_count = 1;
  else if (!strcmp(argv[i], "-a")) print_allsat_solutions = 1;
  else if (!strcmp(argv[i], "-hyt")) {
   i++;
   if (i >= argc) Abort("Expecting a numeric value after -hu", 1);
   hy_uniform_value = atoi(argv[i]);
   if (hy_uniform_value < 0) Abort("hybrid-uniform value should be positive",1);
   hy_uniform = 1;
  }
  else Abort("unfamilar option",1);
 }
}





void normalize(int i) {
 if (debug) __CPROVER_printf("normalizing...\n");
 sprintf(s, "part2 %f %d  > norm.txt", 0.5, i);
 system(s);
 sprintf(s,"cp norm.txt ");
 system(s);
}

int allsat() {
 FILE *Fres;
 char filename[10];
 int res;
 if (debug) __CPROVER_printf("checking 'allsat %s %d'. ", filename, vars);
 sprintf(s,"./indices %d %s >  forallsat.cnf", vars, filename);
 system(s);
 sprintf(s, "batch_all_sat_only_total forallsat.cnf %d > allsat_solution.txt", vars);
 system(s);
 Fres = my_fopen("allsat_solution.txt", "r");
 if (!Fres) Abort("can't open allsat_solution.txt",0);
 if (fscanf(Fres, "Total-Number-of-solutions-found: %d", &res) != 1) Abort ("can't read allsat's output",0);
 if (debug) __CPROVER_printf("# solutions = %d.\n", res);
 fclose(Fres);
 return res;
}

void add_constraint(int size, int i) {

 if (i == 1) sprintf(s, "cp %s previous.txt", org_file);
 else sprintf(s, "cp previous.txt");
 system(s);

 sprintf(s, "./part3 %d %d 0  < previous.txt > ", size, i);
 system(s);
 normalize(i);

 sprintf(s, "./part3 %d %d 1  < %s >> ", size, i, org_file);
 system(s);

    if (hybrid) {

  sprintf(s,"cp .%d", i);
  system(s);
    }
}


int hybrid_estimate(int iterations, char *filename) {
 int res;
 if (0 > iterations) {
   if (debug) __CPROVER_printf("MIN_ITERATIONS larger than actual iterations. Skipping experiment");
   return -1;
 }
 res = iterations - hybrid_value;
 res = (res > 0 ? res: 0);
 if (res == 0) sprintf(s1,org_file);
 else sprintf(s1,"%s.%d", filename, res);
 return (allsat() * mypower(2,res));
}


int satisfiable(char *filename) {
 FILE *sat;
 if (debug) __CPROVER_printf("starting minisat..");
 sprintf(s,"%s %s > sat.txt", "minisat", filename);
 system(s);
 sat = my_fopen("sat.txt", "r");
 if (!sat) Abort("can't open sat.txt",0);
 fscanf(sat, "%s", s);
 if (debug) __CPROVER_printf("result is %s\n", s);
 fclose(sat);
 return strcmp(s, "UNSATISFIABLE");
}


void loops(char *s) {
 int
  i,
  j;
for (j = 0; j < experiments ; j++){
   if (debug) __CPROVER_printf("Experiment #%d\n", j);
   i = 0;
   unsat = 0;
   my_strcpy(org_file, s);

 while (unsat == 0)
 {
   i = i + 1;
   add_constraint(t,i);
   if (print_allsat_solutions || hy_uniform) count = allsat();

   if (print_allsat_solutions) __CPROVER_printf("%d %d %d\n", j, i, count);
   if (hy_uniform_value == i) hy_uniform_sum += count;

 if (!satisfiable("cnfi.txt")) {
   if (hybrid) {
     hyb_est = hybrid_estimate(i-1, "cnfi.txt");
     if (hyb_est == -1) { j--; goto cancel_experiment;}
     if (debug) __CPROVER_printf( "%d hybrid estimation = %d \n", j, hyb_est);
     if (debug) __CPROVER_printf("%d hybrid estimation = %d \n", j, hyb_est);
     sum_hyb_est += hyb_est;
   }
   est = mypower(2, i-1);
   sum_est += est;
   if (debug) __CPROVER_printf( "%d estimation = %d \n", j, est);

   unsat = 1;
 }
 }

 if (debug) __CPROVER_printf("iterations = %d \n", i - 1);

  cancel_experiment:
 sprintf(s,"rm %s", "cnfi.txt");
 system(s);

    }

}

int main(int argc, char **argv) {
FILE *ESTIMATION;

 sprintf(s,"echo > %s", "cnfi.txt");
 system(s);

 parse_options(argc, argv);

 if (real_count) {
   __CPROVER_printf("Solving allsat on original problem...\n");
   __CPROVER_printf("Real number of solutions: %d\n", allsat());
   Abort(" ",0);
 }

 ESTIMATION = my_fopen("estimation.txt","w");

 t = vars/2;
 if (!(t % 2)) t++;
 if (debug) __CPROVER_printf("number of variables = %d, number of variables in the cardinality constraint = %d\n",vars,t);

 if (print_allsat_solutions) __CPROVER_printf("experiment  iteration   solutions\n");


 loops(argv[1]);

 __CPROVER_printf("Estimated count: %d\n", (int) (sum_est / experiments));
 check_point_1a:
 if (hybrid) __CPROVER_printf("Hybrid estimated count: %d\n", (int) (sum_hyb_est / experiments));
 if (hy_uniform) __CPROVER_printf("Hybrid-uniform estimated count: %d\n", ((int) (hy_uniform_sum / experiments)) * mypower(2, hy_uniform_value));
}
