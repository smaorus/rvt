#ifndef RV_DECOMPOSE_H
#define RV_DECOMPOSE_H

#include <list>
#include <vector>
#include <string>
#include "rv_tuple.h"


class RVMain;



class RVT_Decompose
{	
public:
       RVT_Decompose(void) {}
   
	   /// <summary>
       /// interface for the decomposition algorithm.
       /// </summary>
       /// <param name="CG0_SIZE"> number of nodes (functions) in the call graph, side 0 </param>
       /// <param name="CG1_SIZE"> number of nodes (functions) in the call graph, side 1 </param>
       /// <param name="edges_0"> edges defining the call graph, side 0 </param>
       /// <param name="edges_1"> edges defining the call graph, side 1 </param>
       /// <param name="loop_functions_0"> functions substituting loops, side 0 </param>
       /// <param name="loop_functions_1"> functions substituting loops, side 1 </param>
       /// <param name="mapf"> mapping between the functions on the two sides </param>
       /// <param name="syntactic_equivalent_list"> functions on side 0 that are syntact. equiv. to the their counterparts</param>
       /// <param name="givenNames0"> names of functions, side 0 </param>
       /// <param name="givenNames1"> names of functions, side 1 </param>
	   /// <param name="semchecker"> callback object for semantic check </param>
       void Decompose_main(
           unsigned int CG0_SIZE, unsigned int CG1_SIZE,
           const std::list<Edge>& edges_0, const std::list<Edge>& edges_1,
	       const std::list<int>& loop_functions_0, const std::list<int>& loop_functions_1,
           const std::list<Match>& mapf,
           const std::list<int>& syntactic_equivalent_list,
           const std::vector<std::string>& givenNames0, const std::vector<std::string>& givenNames1,
           RVMain& semchecker
       );
};

#endif
