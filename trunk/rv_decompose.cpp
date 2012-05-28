#include <list>
#include <set>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rv_consts.h"
#include "rv_error.h"
#include "rv_decompose.h"
#include "rv_semchecker.h"
#include "rv_etc.h"
#include "rv_dbg.h"
#include "rv_graph.h"
#include "rv_macros.h"

#define RV_SECTION RV_SEC_DECOMPOSE

using namespace std;


static const char *SCC_PREFIX = "S";
static const char *NODE_PREFIX = "n";
static const bool  S_OPTIMIZATION_FLAG = true;
static const char *EOL = "\n";
//static const char *EquivColor = "green";
//static const char *EquivSyntacticColor = "green4";
//static const char *DoomedColor = "lightgrey";
static const bool HTML = false;
static const char *RV_DOTTY_FILE = "rv_out.gv";


class Console {
public:
	static void Write(const string &s);
	static void Write(int i, const string &s);
	static void Write(const string &s, int i, char c);
	static void Write(const string &s, int i);
	static void Write(const string &s1, const string &s2, int i, const string &s3);
	static void WriteLine(const string &s1, const string &s2, const string &s3);
	static void WriteLine(void);
	static void WriteLine(const string &s1, const string &s2, int i, const string &s3 = "");
	static void WriteLine(const string &s1, int i1, const string &s2, int i2, const string &s3);
	static void WriteLine(int i1, const string &s, int i2);
	static void WriteLine(const string &s, int i);
	static void WriteLine(const string &s1, int i, const string &s2);
	static void WriteLine(const string &s);
	static void WriteLine(const string &s1, const string &s2);
	static void WriteSpaceSepLine(const char *s1, const string &s2, const string &s3);
};



/// <summary>
/// Utilities used in this file
/// </summary>
class DecompUtils : private RVCommands
{
public:
	/// <summary>
	/// Prints the content of an STL container
	/// </summary>
	/// <param name="c"> the container </param>
	template <class Cont> static void print_container(const Cont& c) {
		Console::Write(Utils::containerToString(c));
	}

	/// <summary>
	/// Converts int value to string
	/// </summary>
	/// <param name="v"> the integer value </param>
	static string toString(int v) {
		static char buf[256];
		sprintf(buf, "%d", v);
		return string(buf);
	}

	static const string name(int i, int j, const vector<string>& names, const vector<string>& names_other)
	{
		string s;
		string separator = "_";
		string s1 = i >= 0 ? names.at(i) : "";
		string s2 = j >= 0 ? names_other.at(j) : "";
		s.append(s1 == s2 ? s1 : s1 + separator + s2);
		return s;
	}

	template <typename T>
	static bool container_contains(T& a, const vector<int>& b)
	{
		assert(b.size() > 0);
		if (a.empty()) return false;
		sort(a);
		for(typename T::const_iterator it = b.begin(); it != b.end(); ++it)
			if (!Utils::containsElem(a, *it)) return false;
		return true;
	}

	template <typename T> static void sort(T& v) {
		if (v.empty()) return;
		std::sort(v.begin(), v.end());
	}
};


void Console::Write(const string &s) {
	if (DBG) rv_errstrm << s;
}
void Console::Write(int i, const string &s) {
	if (DBG) Write(DecompUtils::toString(i) + s);
}
void Console::Write(const string &s, int i, char c) {
	if (DBG) Write(s + DecompUtils::toString(i) + c);
}
void Console::Write(const string &s, int i) {
	if (DBG) Write(s + DecompUtils::toString(i));
}
void Console::Write(const string &s1, const string &s2, int i, const string &s3) {
	if (DBG) Write(s1 + s2 + DecompUtils::toString(i) + s3);
}
void Console::WriteLine(const string &s1, const string &s2, const string &s3) {
	if (DBG) Write(s1 + s2 + s3 + EOL);
}
void Console::WriteLine(void) {
	if (DBG) Write(EOL);
}
void Console::WriteLine(const string &s1, const string &s2, int i, const string &s3) {
	if (DBG) Write(s1 + s2 + DecompUtils::toString(i) + s3 + EOL);
}
void Console::WriteLine(const string &s1, int i1, const string &s2, int i2, const string &s3) {
	if (DBG) Write(s1 + DecompUtils::toString(i1) + s2 + DecompUtils::toString(i2) + s3 + EOL);
}
void Console::WriteLine(int i1, const string &s, int i2) {
	if (DBG) Write(DecompUtils::toString(i1) + s + DecompUtils::toString(i2) + EOL);
}
void Console::WriteLine(const string &s, int i) {
	if (DBG) Write(s + DecompUtils::toString(i) + EOL);
}
void Console::WriteLine(const string &s1, int i, const string &s2) {
	if (DBG) Write(s1 + DecompUtils::toString(i) + s2 + EOL);
}
void Console::WriteLine(const string &s) {
	if (DBG) Write(s + EOL);
}
void Console::WriteLine(const string &s1, const string &s2) {
	if (DBG) Write(s1 + s2 + EOL);
}
void Console::WriteSpaceSepLine(const char *s1, const string &s2, const string &s3) {
	if (DBG) Write(string(s1) + " " + s2 + " " + s3 + EOL);
}


/// <summary>
/// 2-dimensional array
/// </summary>
template <typename T> class Array2d {
public:
	Array2d(void) : m_arr(NULL), m_h(0), m_w(0) {}

	~Array2d() {
		cleanUp();
	}

	void setDim(int h, int w, bool initialize = true) {
		assert(h >= 0 && w >= 0);
		m_arr = new T*[h];
		for (int i = 0; i < h; ++i) {
			m_arr[i] = new T[w];
			if (initialize)
				for (int j = 0; j < w; ++j)
					m_arr[i][j] = 0;
		}
		m_h = h;
		m_w = w;
	}

	void copy(const Array2d<T>& other) {
		cleanUp();
		setDim(other.m_h, other.m_w, false);
		for (int h = 0; h < m_h; ++h)
			for (int w = 0; w < m_w; ++w)
				m_arr[h][w] = other.m_arr[h][w];
	}

	const T& get(int h, int w) const {
		checkBounds(h, w);
		return m_arr[h][w];
	}

	void set(int h, int w, const T& v) {
		checkBounds(h, w);
		m_arr[h][w] = v;
	}

private:
	void checkBounds(int h, int w) const {
		if (!(h >= 0 && h < m_h && w >= 0 && w < m_w))
			fatal_error("Array2d::checkBounds(): out-of-bounds");
	}

	void cleanUp(void) {
		if (m_arr == NULL)
			return;
		for (int i = 0; i < m_h; ++i)
			delete[] m_arr[i];
		delete[] m_arr;
		m_arr = NULL;
	}

	T **m_arr;
	int m_h, m_w;
};


class DAG;


/// <summary>
/// API for a directed graph
/// </summary>
class mygraph : public RVIntGraph
{
protected:
	vector<int> scc;
	vector<bool> sem_checked;
	vector<bool> m_is_loop; // loops are reported as non-recursive. This flag is true if they are on the loop list.
	string m_graphName;

public:
	mygraph(void) : RVIntGraph(false) {}

	mygraph(int n)
	  : RVIntGraph(n, false)
	{
		expand_graph(n);
	}

	mygraph(const mygraph& othergraph) // copy constructor
	  : RVIntGraph(othergraph),
	    scc(othergraph.scc),
	    sem_checked(othergraph.sem_checked),
	    m_is_loop(othergraph.m_is_loop)
	{
	}

	virtual ~mygraph() {
	}

	/// <summary>
	/// Adds edges to the graph
	/// </summary>
	/// <param name="edges"> the list of the edges to add </param>
	/// <param name="arc"> flag for arcs </param>
	void declare(const list<Edge>& edges, bool arc = false)
	{
		for(list<Edge>::const_iterator e = edges.begin(); e != edges.end(); ++e) {
			edge(e->item1, e->item2);
			if (arc) {
				assert(e -> item1 == e -> item2);
				m_is_loop[e ->item1] = true;
			}
		}

	}


	/// <summary>
	/// Purpose: shrinks S to its subset, equal to root + anything in S that can be reached from root not through
	/// any other node in S. The idea: these constitute a sufficient condition for root to fail the proof.
	/// </summary>
	/// <example>
	/// Example: scc = {f <-> g, g <-> h }, and S = {f,g,h}. If f fails, then we must remove from S either f or
	/// g, regardless of what we do with h. Hence here we return {f,g}. In the calling function
	/// (add_negated_solution), we will add a constraint that one of {f,g} should not be in S, which is more
	/// powerful than doing the same for the original S, i.e., {f,g,h}.
	/// </example>
	/// <remarks>
	/// Precondition: S cuts all cycles in scc (it will go into an infinite loop otherwise!).
	/// </remarks>
	/// <param name="S"> the vertex feedback set of <paramref name="scc"/> </param>
	/// <param name="j"> the root of the <paramref name="scc"/> </param>
	void reduceNeighbors(vector<int>& S, vector<int>& scc, int root) const
	{
		vector<int> res;
        stack<int> stck;
        set<int> visited;
		if (S.size() == 1) return; // cannot make S smaller anyway.
		DecompUtils::sort(scc);
		DecompUtils::sort(S);
		//assert(includes(scc.begin(), scc.end(), S.begin(), S.end()));
		res.push_back(root);
        visited.insert(root);
		FORINT(list, child, getChildren(root)) {
			// add immediate neighbors in scc
			if (root != *child && // root was already added to res anyway
				Utils::containsElem(scc, *child))
			{
				stck.push(*child);
			}
		}
		while (!stck.empty())
		{
			int node = stck.top();
			stck.pop();
            if (visited.find(node) != visited.end())
                continue;
            visited.insert(node);
			if (Utils::containsElem(S, node)) 
                res.push_back(node);
			else
				FORINT(list, child, getChildren(node))
				    if (Utils::containsElem(scc, *child) && 
                        visited.find(*child) == visited.end()) 
                    {
					    stck.push(*child);
                    }
		}
		if (res.size() != S.size())
		{
			Console::Write("* Generalized counterexample to: ");
			DecompUtils::print_container(res);
			Console::WriteLine();
		}
		S.assign(res.begin(), res.end());
	}

	int get_scc(int i) const {
		return scc[i];
	}

	void set_scc(int i, int scc_idx) {
		scc[i] = scc_idx;
	}

	virtual std::string getNodePrefix(void) const {
		return NODE_PREFIX;
	}

	virtual std::string getDottyAttrsOfVertex(int i,
											  std::string &label,
											  std::string &fontcolor,
											  std::string &color,
											  std::string &shape,
											  std::string &style,
											  std::string &fillcolor) const {
		stringstream out;
		out << getNodePrefix() << i;
		return out.str();

	}

	virtual string getDottyAttrsOfGraph(std::string &label,
			  						    std::string &fontcolor,
  			  						    std::string &bgcolor) const
	{
		string result = RVIntGraph::getDottyAttrsOfGraph(label, fontcolor, bgcolor);
		label.assign(m_graphName);
		bgcolor.assign("lightblue");
		fontcolor.assign("blue");
		return result;
	}

	/// <summary>
	/// Dumps the structure of the graph into a .gv file before the beginning of solving
	/// </summary>
	/// <param name="file_name"> the name of the resulted .gv file </param>
	void todotty(const string& file_name) {
		m_graphName.assign(file_name);
		toDotty(file_name);
		m_graphName.clear();
	}


	/// <summary>
	/// Dumps the structure of the graph into a .gv file when finished solving
	/// </summary>
	/// <param name="dotty"> the output stream where to dump </param>
	/// <param name="side"> the index of the side represented by this graph </param>
	/// <param name="dag"> the corresponding MSCC DAG </param>
	void todotty_final(ofstream& dotty,
			           const int side,
			           const DAG& dag,
			           const vector<bool>& is_equivalent,
			           const vector<bool>& syntactic_equivalent,
			           const list<int>& Loop_functions,
			           const vector<int>& mapf,
			           const vector<string> &names,
			           const vector<string> &names_other,
			           bool checking_partial_equiv) const;

	void set_sem_checked(int i) {
		sem_checked.at(i) = true;
	}

	bool is_loop(int idx) const {
		assert(idx < _size);
		return m_is_loop[idx];
	}

protected:
	void expand_graph(int n) {
		RVIntGraph::expand_graph(n);
		scc.resize(n, -1);
	    sem_checked.resize(n, false);
	    m_is_loop.resize(n, false);
	}

};


class DAG : public mygraph
{
	struct TarjanData {
		deque<int> stack;
		vector<int> cg_nodes_index;
		vector<int> cg_nodes_lowlink;
		int index;

		TarjanData(const mygraph& cg)
		: cg_nodes_index(cg.size(), -1),
		  cg_nodes_lowlink(cg.size(), -1),
		  index(0) {
		}
	};


	int scc_count;
	vector<bool> m_is_recursive;     // whether a node in the scc DAG is recursive
	vector<bool> m_is_doomed; // whether a node in the scc DAG should not be checked, because either it or one of its descendants are recursive and cannot be proven equivalent.
	vector<vector<int> > SCC_list;

public:
	mygraph& cg;

	DAG(mygraph& call_graph) : cg(call_graph) {
	}

	virtual ~DAG() {
	}

	bool get_is_SCC_recursive(int i) const { return m_is_recursive[i]; } // if there is more than one element it is true for all of them anyway.

	const vector<int>& get_SCC_line(int i) const { return SCC_list[i]; }

	/// <summary>
	/// Marks ancestors as doomed. Generally doomed = unchecked, other than nonmapped in SCCs.
	/// </summary>
	/// <param name="i">root</param>
	/// <param name="mark">whether to mark the root itself as doom. Generally yes other than the case in which the root was checked. </param>
	/// <param name="side0"> side 0 or 1 </param>
	void mark_ancestors_as_doomed(int i, bool mark, bool side0)
	{
		if (is_doomed(i)) return;
		if (mark) set_doomed(i, true);
		if (side0) Console::Write("Side 0:");
		else Console::Write("Side 1:");
		Console::WriteLine("SCC ", SCC_PREFIX, i, " is doomed.");
		FORINT(list, ancestor, getParents(i))
		    mark_ancestors_as_doomed(*ancestor, true, side0);
	}

	void build_DAG()
	{
		expand_graph(scc_count);
		for (int cg_i = 0; cg_i < cg.size(); ++cg_i)
			FORINT(list, cg_child, cg.getChildren(cg_i))
			if (get_map_element(cg_i) != get_map_element(*cg_child))
				edge(get_map_element(cg_i), get_map_element(*cg_child));
	}

	void compute_SCCs(void) {
		scc_count = 0;
		TarjanData td(cg);
		for (int i = 0; i < cg.size(); ++i)
			if (td.cg_nodes_index[i] == -1 && cg.is_node_reported(i))
				tarjan(i, td);
		print_SCCs(SCC_list);
		m_is_doomed.resize(scc_count, false);
	}

	int get_map_element(int i) const { return cg.get_scc(i); }

	void set_map_element(int i, int scc_idx) { cg.set_scc(i, scc_idx); }

	bool is_doomed(int i) const { return m_is_doomed[i]; }

	void set_doomed(int i, bool v = true) { m_is_doomed[i] = v; }

protected:
	virtual std::string getNodePrefix(void) const {
		return SCC_PREFIX;
	}

private:
	/// <summary>
	/// Computes SCCs and updates the SCC list "SCC_list". Based on Tarjan's algorithm.
	/// </summary>
	/// <param name="v"> root</param>
	void tarjan(int v, TarjanData& td) {
		td.cg_nodes_index[v] = td.index;
		td.cg_nodes_lowlink[v] = td.index;
		++td.index;
		td.stack.push_front(v);
		FORINT(list, cg_child, cg.getChildren(v)) {
			if (td.cg_nodes_index[*cg_child] == -1)
			{
				tarjan(*cg_child, td);
				td.cg_nodes_lowlink[v] = min(td.cg_nodes_lowlink[v],
						td.cg_nodes_lowlink[*cg_child]);
			}
			else if (Utils::containsElem(td.stack, *cg_child))
				td.cg_nodes_lowlink[v] = min(td.cg_nodes_lowlink[v],
						td.cg_nodes_index[*cg_child]);
		}
		if (td.cg_nodes_lowlink[v] == td.cg_nodes_index[v])
		{
			int n;
			vector<int> component;
			do
			{
				n = td.stack.front();
				component.push_back(n);
				set_map_element(n, scc_count);
				td.stack.pop_front(); // check
			} while (n != v);
			SCC_list.push_back(component);
			m_is_recursive.push_back(component.size() > 1 || cg.is_edge(v, v));  // for each component, marks whether it is recursive
			scc_count++;
		}
	}

	void print_SCCs(const vector<vector<int> >& SCC_list)  const
	{
		Console::Write("SCCs: ");
		for (unsigned int i = 0; i < SCC_list.size(); ++i) {
			DecompUtils::print_container(SCC_list[i]);
			Console::Write(";");
		}
		Console::WriteLine();
		for (int i = 0; i < size(); ++i)
			Console::WriteLine(i, " mapped to SCC ", get_map_element(i));
	}
};


void mygraph::todotty_final(ofstream& dotty,
		const int side,
		const DAG& dag,
		const vector<bool>& is_equivalent,
		const vector<bool>& syntactic_equivalent,
		const list<int>& Loop_functions,
		const vector<int>& mapf,
		const vector<string> &names,
		const vector<string> &names_other,
		bool checking_partial_equiv) const
{
	static const string SemcheckedStyle = HTML ? "U" : "fontcolor = \"black\""; // did not go through sem. check;
	static const string NotSemcheckedStyle = HTML ? "I" : "fontcolor = \"grey\"";
	static const string SyntacticEqualStyle = "color = \"blue\", "; // cannot be empty because after this text a comma is added
	static const string NotSyntacticEqualStyle = " "; // peripheries = 2
	static const string EqualStyle = "style = \"filled\", fillcolor = \"green\"";
	static const string NotEqualStyle = "style = \"filled\", fillcolor = \"white\"";
	static const string MutTermStyle = "shape = \"octagon\", ";
	static const string NonMutTermStyle = "shape = \"ellipse\", ";

	dotty << "subgraph G" << side << "{ " << endl;
	dotty << "side"<<side << "[label = P" << side << "]" << endl;
	dotty << "node[color = black];" << endl;;
	for (int j = 0; j < _size; j++)
	{
		if (!node_reported[j]) continue;
		string node = DecompUtils::name(j, mapf[j], names, names_other);
		dotty << node << side;
		if (sem_checked[j])
		{
			if (HTML) dotty << "[label = <<" << SemcheckedStyle << ">" << node << "</" << SemcheckedStyle << ">>];" << endl;
			else dotty << "[label = \"" << node << "\"," << SemcheckedStyle << "];"<< endl;;
		}
		else
		{
			if (HTML) dotty << "[label = <<" << NotSemcheckedStyle << ">" << node << "</" << NotSemcheckedStyle << ">>];" << endl;
			else dotty << "[label = \"" << node << "\"," << NotSemcheckedStyle << "];" << endl;
		}
	}
	for (int j = 0; j < _size; j++)
	{
		if (!node_reported[j]) continue;
		dotty << DecompUtils::name(j, mapf[j], names, names_other) << side << "[";
		//shape (mutual termination):
		bool mut_terminating = !checking_partial_equiv && is_equivalent[j];
		dotty << (mut_terminating ? MutTermStyle : NonMutTermStyle);
		//color (syntactic equivalence):
		dotty << (syntactic_equivalent[j]? SyntacticEqualStyle
										 : NotSyntacticEqualStyle);
		//background (semantic equivalence):
		bool partially_equiv = checking_partial_equiv? is_equivalent[j]
		                                             : rv_ufs.isFuncPairSemanticallyEqual(j, side);
		dotty << (partially_equiv? EqualStyle : NotEqualStyle);
		dotty << "]" << endl;
	}
	for (int j = 0; j < _size; j++)
		FORINT(list, caller, getParents(j)) {
		dotty << DecompUtils::name(*caller, mapf[*caller], names, names_other) << side << "->" << DecompUtils::name(j, mapf[j], names, names_other) << side;
		if (find(Loop_functions.begin(), Loop_functions.end(), j)!= Loop_functions.end())
			dotty << "[style = dotted]" << endl;
		else
			dotty << endl;
	}
	dotty << "}" << endl;
}

class FormatException {};

class Solve
{
	const string node0, node1;
	const string Edge0_prefix, Edge1_prefix;
	int side0_size, side1_size;
	int dag0_size;
	int iteration;	// used in build_SCC_map
	vector<int> mapf0;		// mapping of functions (side 0 |-> side 1)
	vector<int> mapf1;		// reversed mapping of mapf0 (side 1 |-> side0)
	vector<int> mapm;      // mapping between SCCs

	map<string, int> map_var2idx; // for modeling the optimization problem of find_S. maps between variable names and their index in the optimization model.
	RVMain& m_semchecker;
	vector<bool> is_equivalent0;   // whether a cg0 node was proven equivalent
	vector<bool> is_equivalent1;   // whether a cg1 node was proven equivalent
	vector<bool> syntactic_equivalent;     // in the stub Check and check_recursive, this input vector determines whether the result is true or false
	list<string> negatedSolutions;

public:
	Solve(int n0, int n1, RVMain& semchecker)
	: node0("S"), node1("D"),		 // must be different
	  Edge0_prefix("es"), Edge1_prefix("ed"), // must be different
	  side0_size(n0), side1_size(n1),
	  iteration(0),
	  mapf0(0), mapf1(0), mapm(0),
	  m_semchecker(semchecker),
	  is_equivalent0(n0, false), is_equivalent1(n1, false),
	  syntactic_equivalent(n0, false)
	{
	}

	void map_functions(mygraph& cg0, mygraph& cg1, const list<Match>& mapf)
	{
		mapf0.resize(cg0.size(), -1);
		mapf1.resize(cg1.size(), -1);
		for(list<Match>::const_iterator e = mapf.begin(); e != mapf.end(); ++e) {
			if (cg0.is_node_reported(e->item1) && cg1.is_node_reported(e->item2))
				mapit(e->item1, e->item2);		
		}
	}

	void declare_syntactic_equivalent(const list<int>& syntactic_equivalent_list)
	{
		FORINT (list, it, syntactic_equivalent_list)
				   {
			if (*it >= side0_size)
				fatal_error("Reported syntactically equivalent function outside of range");
			syntactic_equivalent[*it] = true;
				   }
	}

	void mapit(int i, int j)
	{
		/*******************************************************************************************************
		   Name: mapit
		   Precondition: mapf0 and mapf1 were allocated the graph size.
		 *******************************************************************************************************/
		if (i >= side0_size || j >= side1_size)
			fatal_error("in mapit(): Attempted mapping of non existing nodes.");
		
		int check_double = -1;
		if (mapf0[i] != -1) check_double = 0;
		if (mapf1[j] != -1) check_double = 1;
		if (check_double >= 0)
		{
			string s("in mapit(): Double mapping for function ");
			s += DecompUtils::toString(check_double == 0 ? i : j);
			s += " on side ";
			s += DecompUtils::toString(check_double);
			s += ". ";
			fatal_error(s.c_str());
		}
		mapf0[i] = j;
		mapf1[j] = i;
	}

	bool build_SCC_map(DAG& dag0, DAG& dag1)
	{
		++iteration;
		Console::WriteLine("Building_SCC_map, iteration ", iteration);
		bool changed = false;
		int dag0_size = dag0.size();
		Array2d<bool> a;  // a is a matrix of size dag0.size x dag1.size. a[i,j] = true iff there is a pair (f,f') \in mapf0 such that scc(f) = i, scc(f') = j and these sccs are not doomed.
		a.setDim(dag0_size, dag1.size(), true);
		mapm.resize(dag0_size, -1);

		// filling the matrix
		for (int i = 0; i < side0_size; ++i)
			if (mapf0[i] >= 0) // some functions are mapped to -1 in mapf0, which means that they are not mapped
			{
				//if (!dag0.cg.is_node_reported(i) || !dag1.cg.is_node_reported(mapf0[i])) continue;
				int m0 = dag0.get_map_element(i), // get_map_element uses 'map' - a mapping from functions to SCCs
					m1 = dag1.get_map_element(mapf0[i]);
				if (m0 < 0 || m1 < 0) continue;
				if (!dag0.is_doomed(m0) && !dag1.is_doomed(m1)) a.set(m0, m1, true);
			}

		// examining result: vertical (dag1)
		vector<bool> dag1_matches(dag1.size(), false);
		int mycount = 0;
		for (int j = 0; j < dag1.size(); ++j)
		{
			if (!(dag1.get_is_SCC_recursive(j)))
			{
				int f = dag1.get_SCC_line(j).front();
				if (!is_mapped1(f)) dag1.set_doomed(j, true);
			}
			if (dag1.is_doomed(j)) continue;

			mycount = 0;
			for (int i = 0; i < dag0.size(); ++i) if (a.get(i, j)) mycount++;
			switch (mycount)
			{
			case 0:
				Console::WriteLine("DAG 1: S", j, " cannot be mapped and cannot be inlined. Ancestors are doomed.");
				dag1.mark_ancestors_as_doomed(j, true, false);
				changed = true;
				break;
			case 1:
				dag1_matches[j] = true;
				break;
			default:
				Console::WriteLine("DAG 1: S", j, " is mapped to more than one SCC on side 0. Ancestors are doomed.");
				dag1.mark_ancestors_as_doomed(j, true, false);
				changed = true;
				break;
			}
		}

		// examining result: horizontal (dag0)

		mycount = 0;
		for (int j = 0; j < dag0.size(); j++)
		{
			if (!(dag0.get_is_SCC_recursive(j)))
			{
				int f = dag0.get_SCC_line(j).front();
				if (!is_mapped(f))
					dag0.set_doomed(j, true);
			}
			if (dag0.is_doomed(j)) continue;
			mycount = 0;
			for (int i = 0; i < dag1.size(); ++i) if (a.get(j, i)) ++mycount;
			Console::Write("DAG 0: S", j, ' ');
			switch (mycount)
			{
			case 0:
				Console::WriteLine("cannot be mapped and cannot be inlined. Ancestors are doomed.");
				dag0.mark_ancestors_as_doomed(j, true, true);
				changed = true;
				break;
			case 1:
			{
				int to = -1;
				for (int i = 0; i < dag1.size(); ++i) if (a.get(j, i)) { to = i; break; }

				if (dag1_matches[to])
				{
					mapm[j] = to;
					Console::WriteLine("is mapped to DAG 1: S", to);
				}
				else
				{
					Console::WriteLine("can only be mapped to DAG 1: S", to, ", which is doomed. Hence ancestors are doomed.");
					dag0.mark_ancestors_as_doomed(j, true, true);
					changed = true;
				}
				break;
			}
			default:
				Console::WriteLine("is mapped to more than one SCC on side 1! ancestors are doomed.");
				dag0.mark_ancestors_as_doomed(j, true, true);
				changed = true;
				break;
			}
		}
		return changed;
	}

	const vector<int>& getMapf0(void) const {
		return mapf0;
	}

	const vector<int>& getMapf1(void) const {
		return mapf1;
	}

	/// <summary>
	/// Purpose: Given two DAGs dag0 and dag1, we want to check whether the mapping 'mapm' between them is
	///    consistent in terms of the path, i.e., whether there is a path m0 -~-> m1 in dag0 and a path n0 -~-> n1
	///    in dag1, such that (m0,n1) \in mapm and (m1, n0) \in mapm. If yes we return false and later abort. The
	///    check refers to nondoomed nodes only.
	///    precondition: bijective mapping between the nodes of the SCCs. if (i,j) \in mapm then either both are
	///    doomed or both are not.
	///    Algorithm: basically take the union of the graphs (matching nodes by mapm) and check for circularity.
	///    in practice this is done by adding edges to dag0.
	/// </summary>
	/// <param name="dag0"> SCC dag of side 0 </param>
	/// <param name="dag1"> SCC dag of side 1 </param>
	/// <returns> true <-> the mapping between the nodes of dag0 / dag1 is consistent </returns>
	bool is_map_consistent(DAG& dag0, const DAG& dag1) const
	{
		Console::WriteLine("\nChecking map consistency");
		vector<int> children;
		for (int i = 0; i < dag0_size; ++i)
		{
			if (dag0.is_doomed(i) || mapm[i] < 0) continue;
			assert(!dag1.is_doomed(mapm[i])); // undoomed cannot be mapped to doomed
			children.clear();
			dag1.get_children(mapm[i], children);
			for (unsigned int j = 0; j < children.size(); ++j)
			{
				int target = dag0_size;
				//! if we do not remove unmapped then add here: if (children[j] is unmapped add its children to children and continue)
				int child = children[j];
				if (!dag1.get_is_SCC_recursive(child))
				{
					int f = dag1.get_SCC_line(child).front();
					if (!is_mapped1(f))
					{
						vector<int> grandchildren;
						dag1.get_children(child, grandchildren);
						children.insert(children.end(), grandchildren.begin(), grandchildren.end());
						continue;
					}
				}

				for (int k = 0; k < dag0_size; ++k)
					if (mapm[k] == children[j]) {
						target = k; break;
					}
				assert(target < dag0_size); // assserting that we found it.
				dag0.edge(i, target);  /* XXX */
			}
		}
		if (DBG) dag0.todotty("consistency_check");
		return !dag0.is_cyclic();
	}

	bool compatible(const set<int>& s0, const set<int>& s1) const
	{
		/*******************************************************************************************************
		   Name: compatible
		   purpose: checks if s0 and s1 contain the same functions modulo mapf0
		 *******************************************************************************************************/
		if (s0.size() != s1.size()) return false;
		set<int> mapped_set;
		FORINT(set, it, s0) mapped_set.insert(mapf0[*it]);
		return equal(mapped_set.begin(), mapped_set.end(), s1.begin());  // XXX - learn if the order matters
	}

	/// <summary>
	/// Expands the given string <paramref name="s"/> to <paramref name="min_len"/> by appending (or inserting) <paramref name="delimiter"/>s.
	/// If the length of the given string exceeds <paramref name="min_len"/>, then <paramref name="s"/> is returned unchanged.
	/// </summary>
	/// <param name="s"> the given string </param>
	/// <param name="min_len"> the index of the side represented by this graph </param>
	/// <param name="align_left"> flag whether to append (or insert) the expanding <paramref name="delimiter"/>s </param>
	/// <param name="delimiter"> the expanding delimiters </param>
	static string string_min_length(const string& s, size_t min_len,
			bool align_left = true, char delimiter = ' ')
	{
		if (s.length() >= min_len) return s;
		if (align_left)
			return string(s).append(min_len-s.length(), delimiter);
		return string(s).insert(0, min_len-s.length(), delimiter);
	}

	static void appendToString(string& res, const string& appendix) {
		if (!res.empty())
			res.append(1, ' ');
		res.append(appendix);
	}

	struct ThreeStrings {
		ThreeStrings(const string &name0, const string &name1, const string &res_)
		: col0(name0), col1(name1), res(res_) {}

		string col0, col1, res;
	};

	/// <summary>
	/// Produces fuf file for all the function pairs for which we could prove their partial equivalence
	/// </summary>
	/// <param name="syntactic_equivalent1"> syntactic equivalence bit-set at side 1 </param>
	/// <param name="names0"> function node names at side 0 </param>
	/// <param name="names1"> function node names at side 1 </param>
	void report_final_results(const vector<bool>& syntactic_equivalent1,
							  const vector<string>& names0,
							  const vector<string>& names1,
							  bool partial_equiv_check) const
	{
		list<ThreeStrings> out;
		size_t col0_maxLen = 4, col1_maxLen = 4;

		for(int f0 = 0; f0 < side0_size; ++f0) {
			int f1 = mapf0[f0];
			if (f1 < 0) continue; // some functions are mapped to -1 in mapf0, which means that they are not mapped

			string res;
			if (syntactic_equivalent.at(f0)) {
				assert(syntactic_equivalent1.at(f1));
				res = SYNTACTICALLY_EQUAL;
			}
			if (is_equivalent0.at(f0)) {
				assert(is_equivalent1.at(f1));
				appendToString(res, partial_equiv_check ? PARTIALLY_EQUIVALENT
						                                : MUTUALLY_TERMINATING);
			}

			out.push_back(ThreeStrings(names0.at(f0), names1.at(f1), res));
			col0_maxLen = max(col0_maxLen, names0[f0].length());
			col1_maxLen = max(col1_maxLen, names1[f1].length());
		}

		++col0_maxLen; //Ensures at least a space character after the longest elements
		++col1_maxLen; //   "    "    "   ...

		if (out.empty())
			return;

		ofstream outfile(partial_equiv_check ? "rv_pe.fuf" : "rv_mt.fuf", ios_base::out);
		outfile << string_min_length("`P0", col0_maxLen) << string_min_length("P1", col1_maxLen) << "Result" << EOL;
		outfile << "`" << string_min_length(" ", col0_maxLen-1, false, '-') << string_min_length(" ", col1_maxLen, false, '-') << "------" << EOL;
		for(list<ThreeStrings>::const_iterator it = out.begin(); it != out.end(); ++it)
			outfile << string_min_length(it->col0, col0_maxLen) << string_min_length(it->col1, col1_maxLen) << it->res << EOL;
		outfile.close();
	}

	/// <summary>
	/// Checks that f0 and its counterpart (mapf0(f0)) call the same UFs.
	/// Otherwise this path will be doomed.
	/// Algorithm: builds lists uf0, uf1 of UFs: all the children that are
	/// equivalent or in S. BUT: because of
	/// inlining, the children of the inlined functions also matter.
	/// For example f -> g -> h, where we currently
	/// check f and g is inlined. If h is equivalent or in S then it will also enter uf0.
	/// </summary>
	/// <remarks>
	///   <list type="number">
	///     <item> There are three types of inlining:
	///      <list type="bullet">
	///        <item> unmatched non-recursive functions. These are eliminated before getting here, in remove_unmapped().</item>
	///        <item> matched non-recursive that failed equivalence check.</item>
	///        <item> nodes in the SCC which are not in S.</item>
	///      </list>
	///     </item>
	///     <item> When f0 + mapf0(f0) are not recursive, will be called with S = 0.</item>
	///   </list>
	/// </remarks>
	bool check_UF_compatibility(int f0,
			const vector<int>& S,
			const DAG& dag0,
			const DAG& dag1,			
			set<int>& uf0,
			set<int>& uf1,
			bool& all_children_equiv) const
	{
		vector<int> children;
		set<int> inlined0, inlined1;
		const mygraph& cg0 = dag0.cg; 
		const mygraph& cg1 = dag1.cg;

		// side 0
		cg0.get_children(f0, children);
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			int child = children[i];
			if (is_equivalent0[child] &&
					(!m_semchecker.is_refined() || // user did not set the flag 'refined'
							dag0.get_is_SCC_recursive(cg0.get_scc(child)))) { // child is recursive
				uf0.insert(child);
				continue;
			}
			if (Utils::containsElem(S, child)) { uf0.insert(child); continue; }
			inlined0.insert(child);
			vector<int> grandchildren;
			cg0.get_children(child, grandchildren);
            FORINT(vector, grandchildit, grandchildren) 
                if (!Utils::containsElem(children, *grandchildit)) {
			        children.push_back(*grandchildit);
			        all_children_equiv = false;
                }
		}

		// side 1
		vector<int> S1; // The S set for side 1
		for (unsigned int j = 0; j < S.size(); ++j) S1.push_back(mapf0[S[j]]);
		children.clear();
		cg1.get_children(mapf0[f0], children);
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			int child = children[i];
			if (is_equivalent1[child] && // see above
					(!m_semchecker.is_refined() || dag1.get_is_SCC_recursive(cg1.get_scc(child)))) { 
						uf1.insert(child); 
						continue; 
			}
			if (Utils::containsElem(S1, child)) { uf1.insert(child); continue; }
			inlined1.insert(child);
			vector<int> grandchildren;
			cg1.get_children(child, grandchildren);
			FORINT(vector, grandchildit, grandchildren)
				if (!Utils::containsElem(children, *grandchildit)) {
					children.push_back(*grandchildit);
					all_children_equiv = false;
				}
		}

        all_children_equiv = inlined0.empty() && inlined1.empty(); //DIMAXXX

		if (compatible(uf0, uf1))
		{   // example: let f1 = mapf0[f0]. Suppose f0,f1 are in S, but f0 has self loop and f1 doesn't. Then f0 calls a UF(f0) which f1 doesn't. Such cases have little chance to succeed.
			Console::Write("Side 0: calls to ");
			DecompUtils::print_container(uf0);
			Console::WriteLine(" are replaced with UFs");
			Console::Write("Side 0: the following are inlined:");
			DecompUtils::print_container(inlined0);
			Console::WriteLine();
			Console::Write("Side 1: calls to ");
			DecompUtils::print_container(uf1);
			Console::WriteLine(" are replaced with UFs");
			Console::Write("Side 1: the following are inlined:");
			DecompUtils::print_container(inlined1);
			Console::WriteLine();

			//#ifdef LOOPS_NOT_RECURSIVE
			// not so easy because the loop function can also be called from other functions as part of an mscc.
			// It seems to work anyhow, because the UF is not generated if it is a call just from the loop itself.
			//			   if (cg0.is_loop[f0]) uf0.erase(f0);
			//			   if (cg0.is_loop[mapf0[f0]]) uf1.erase(mapf0[f0]);
			//#endif


			return true;
		}
		else return false;
	}

	bool Check(int f0, const vector<int>& S, const DAG& dag0, const DAG& dag1) const
	{
		RVSemChecker semchecker(m_semchecker);
		Console::WriteLine("Check (", f0, ",", mapf0[f0], ")");
		
		set<int> uf[2];
		bool all_children_equiv = true;
		if (!check_UF_compatibility(f0, S, dag0, dag1, uf[0], uf[1], all_children_equiv))
		{
			char c = semchecker.get_completeness();
			char threshold = 0;
			Console::WriteLine("Side0 (", f0, ") calls the following UFs:");
			DecompUtils::print_container(uf[0]);
			Console::WriteLine("Side1 (", mapf0[f0], ") calls the following UFs:");
			DecompUtils::print_container(uf[1]);
			Console::WriteLine("Different sets of UFs.");

			Console::WriteLine("The branch will be aborted if completeness level <= ", threshold);
			Console::WriteLine("completeness level = ", c);

			if (c <= threshold)  // aborting branch if they call different UFs
				return false;
		}

		Console::Write("Syntactic-equivalence test: ");
		if (syntactic_equivalent[f0] && all_children_equiv)
		{
			Console::WriteLine("passed.");
			return true;
		}

		dag0.cg.set_sem_checked(f0);
		dag1.cg.set_sem_checked(mapf0[f0]);
		Console::WriteLine("failed.");
		Console::WriteLine("Semantic equivalence check:");
		Console::WriteLine("-*-*-*-*-*-*-*  In  -*-*-*-*-*-*-*-*-*-*-");
		RVCommands::ResCode res = semchecker.check_semantic_equivalence(f0, uf);  // !!
		Console::WriteLine("-*-*-*-*-*-*-*  Out -*-*-*-*-*-*-*-*-*-*-");
		return res == RVCommands::SUCCESS;
	}

	void mark_equivalent(int i)
	{
		int other = mapf0[i];
		is_equivalent0[i] = true;
		is_equivalent1[other] = true;
		Console::WriteLine("mark_equivalent(", i, ",", mapf0[i], ")");
	}

	void report (int f, bool result, const vector<string>& names0, const vector<string>& names1) {
		endl(rv_errstrm << "( " << names0.at(f) << ", " << names1.at(mapf0[f]) << " ) : "
			  	        << (result? "passed" : "failed"));
	}
	
	void decompose(DAG& dag0, DAG& dag1, const vector<string> &names0, const vector<string> &names1)
	{
		// assumes DAG is sorted bottom up
		vector<int> S;
		mygraph& cg0 = dag0.cg;
		mygraph& cg1 = dag1.cg;

		Console::WriteLine("==== Decomposing ====");
		for (int scc_index = 0; scc_index < dag0.size(); ++scc_index)
		{
			Console::Write("\nNow solving SCC ", SCC_PREFIX, scc_index, " ");
			vector<int> scc0 = dag0.get_SCC_line(scc_index);

			if (dag0.is_doomed(scc_index))
			{
				Console::WriteLine(": doomed");
				for (size_t i = 0; i < scc0.size(); i++)  {
					if (mapf0[scc0[i]] > 0)
						report(scc0[i], false, names0, names1);
				}
				continue;
			}

			vector<int> scc1 = dag1.get_SCC_line(mapm[scc_index]);
			DecompUtils::print_container(scc0);
			if (!dag0.get_is_SCC_recursive(scc_index)) Console::Write(" -- non-recursive");
			Console::WriteLine();

			// if (m0,m0) \in mapm and one is recursive whereas the other is not, we doom the path.
			if (dag0.get_is_SCC_recursive(scc_index) != dag1.get_is_SCC_recursive(mapm[scc_index]))
			{
				Console::Write("Side 0: S", scc_index);
				if (dag0.get_is_SCC_recursive(scc_index)) Console::Write(" is "); else Console::Write(" is not ");
				Console::Write("recursive, whereas ");
				Console::Write("Side 1: S", mapm[scc_index]);
				if (dag1.get_is_SCC_recursive(mapm[scc_index])) Console::Write(" is "); else Console::Write(" is not ");
				Console::WriteLine(" recursive. Aborting branch.");
				dag0.mark_ancestors_as_doomed(scc_index, true, true);
				dag1.mark_ancestors_as_doomed(mapm[scc_index], true, false);
				continue;
			}

			if (!dag0.get_is_SCC_recursive(scc_index))
			{ // trivial MSSCs
				S.clear(); // This is the only difference from the recursive case.
				if (Check(scc0[0], S, dag0, dag1/*, cg0, cg1*/)) {
					mark_equivalent(scc0[0]);
					report(scc0[0], true, names0, names1);
				}
				else report (scc0[0], false, names0, names1);
			}
			else
			{
				bool ok_flag;
				vector<vector<int> > save_solutions(cg0.size());
				negatedSolutions.clear();
				while (true)
				{
					int failing_node = -1;
					ok_flag = true;
					Find_S(S, scc_index, cg0, cg1, scc0, scc1);
					// stub_find_S(scc0, scc0); // if we want to avoid minisat, can use this alternative, which returns the intersection between scc0, scc0. This is unsound if the intersection does not break all cycles.
					if (S.size() == 0) { ok_flag = false; break; }
					// "for all <f,g> \in S if !Check1(f,g,S) abort."
					for (unsigned int i = 0; i < S.size(); ++i)
					{
						if (S_OPTIMIZATION_FLAG)
						{
							if (DecompUtils::container_contains(save_solutions[S[i]], S))
							{
								Console::WriteLine("* Recycled solution for ", NODE_PREFIX, S[i]);
								continue;
							}
							else
							{
								ok_flag = Check(S[i], S, dag0, dag1);
								if (ok_flag) {
									save_solutions[S[i]].resize(S.size());
									save_solutions[S[i]].assign(S.begin(), S.end());
								}
							}
						}
						else ok_flag = Check(S[i], S, dag0, dag1);
						if (!ok_flag)
						{
							failing_node = S[i];
							break;
						}
					}
					if (ok_flag || !S_OPTIMIZATION_FLAG || scc0.size() == 1) break;
					Console::WriteLine("\nTrying a different set S");
					add_negated_solution(S, scc0, cg0, failing_node);
					S.clear();
				}
				if (!ok_flag)
				{
					Console::WriteLine("failed on recursive functions. Aborting this branch.");
					dag0.mark_ancestors_as_doomed(scc_index, false, true);
					dag1.mark_ancestors_as_doomed(mapm[scc_index], false, false);
				}
				//  for all <f,g> \in S mark <f,g> as "equivalent"
				else
					FORINT (vector, it, S) {
					mark_equivalent(*it);
					report(*it, true, names0, names1);
				}
			}

		}
	}

	bool is_mapped(int i) const { return mapf0[i] >= 0; }

	bool is_mapped1(int i) const { return mapf1[i] >= 0; }

	//A caller is responsible of releasing the result of this method:
	vector<bool>* alloc_syntactic_equivalent1(int n1) const
			   {  // we only hold this info for side 0. So this method converts this info to side 1.
		vector<bool> *p_synt_equiv1 = new vector<bool>(n1, false);
		for (int i = 0; i < side0_size; ++i)
			if (syntactic_equivalent[i] && mapf0[i] >= 0)
				(*p_synt_equiv1)[mapf0[i]] = true;
		return p_synt_equiv1;
			   }

	const vector<bool>& get_syntactic_equivalence0(void) const {
		return syntactic_equivalent;
	}

	const vector<bool>& get_equivalence_vec0(void) const {
		return is_equivalent0;
	}

	const vector<bool>& get_equivalence_vec1(void) const {
		return is_equivalent1;
	}

	void set_dag0_size(int dag0_size_) { dag0_size = dag0_size_; }

private:
	/******************************** find_S *************************************************/

	string E(const string& a, const string& b, const string& c)
	{
		return a + "_" + b + "_" + c;
	}
	
	/* XXX base offset for the indices must be aligned */
	void map_var_to_idx(const vector<int>& scc0, const vector<int>& scc1)
	{
		int size0 = scc0.size(),
				size1 = scc1.size();
		int idx = 1;
		string s, s1;
		for (int i = 0; i < size0; ++i) // nodes side 0
			map_var2idx[node0 + DecompUtils::toString(scc0[i])] = idx++;

		for (int i = 0; i < size1; ++i) // nodes side 1

			map_var2idx[node1 + DecompUtils::toString(scc1[i])] = idx++;
		for (int i = 0; i < size0; ++i) // edges side 0
			for (int j = 0; j < size0; ++j)
				map_var2idx[E(Edge0_prefix, DecompUtils::toString(scc0[i]), DecompUtils::toString(scc0[j]))] = idx++;

		for (int i = 0; i < size1; ++i) // edges side 1
			for (int j = 0; j < size1; ++j)
				map_var2idx[E(Edge1_prefix, DecompUtils::toString(scc1[i]), DecompUtils::toString(scc1[j]))] = idx++;
	}
	
	void imply(ofstream& cnf, const string& lhs0, const string& lhs1, const string& rhs) {
		cnf << " -1*v" << map_var2idx[lhs0] << "  -1*v" << map_var2idx[lhs1] << " +1*v" << map_var2idx[rhs] << " >= -1;" << endl;
	}
	
	void negunit(ofstream& cnf, const string& st) {
		cnf << "-1*v" << map_var2idx[st] << " >= 0;" << endl;
	}
	
	void make_equal(ofstream& cnf, const string& s0, const string& s1) {
		cnf << "+1*v" <<  map_var2idx[s0] << "  -1*v" << map_var2idx[s1] << " >= 0;" << endl;
		cnf << " -1*v" << map_var2idx[s0] << "+ 1*v" << map_var2idx[s1] << " >= 0;" << endl;
	}
	
	/// <remark> There was a bug that storing reduced solutions only in the
	///          negated solutions results in yielding the same failing
	///          solution again by the solver => infinite loop.
	///          Solution: store both the original and the redused S. </remark>
	void add_negated_solution(vector<int>& S, vector<int>& scc0, const mygraph& cg0, int failing_node)
	{
		size_t initialSize = S.size();
		addNegatedSolutionLow(S, scc0);
		cg0.reduceNeighbors(S, scc0, failing_node); // optimization. Generalizes the counterexample.
		if (S.size() != initialSize)
			addNegatedSolutionLow(S, scc0);
	}

	void addNegatedSolutionLow(const vector<int>& S, const vector<int>& scc0) {
		string s;
		for (unsigned int i = 0; i < S.size(); ++i) {
			unsigned int j;
			for (j = 0; j < scc0.size(); ++j) if (scc0[j] == S[i]) break;
			unsigned int idx = j;
			assert(idx < scc0.size()); // we found it;
			s.append(" +1*v");
			j = idx + 1;
			s.append(DecompUtils::toString(j));
		}
		s.append(" >= 1;");
		negatedSolutions.push_back(s);
	}
	
	void appendNegatedSolutionsToFile(ofstream& cnf) {
		if (S_OPTIMIZATION_FLAG && !negatedSolutions.empty()) {
			cnf << "* negated solutions: " << endl;
			list<string>::const_iterator it;
			for (it = negatedSolutions.begin(); it != negatedSolutions.end(); ++it)
				cnf << *it << endl;
		}
	}

	void add_constraints(ofstream& cnf,
			const mygraph& cg0, const mygraph& cg1,
			const vector<int>& scc0, const vector<int>& scc1)
	{
		int size0 = scc0.size(),
				size1 = scc1.size();
		vector<bool> mapped(1 + size0 + size1, false);
		cnf << "* minimize chosen mapped nodes:" << endl;
		cnf << "min: ";

		for (int i = 0; i < size0; i++)
		{
			if (is_mapped(scc0[i]))
			{
				cnf << "+1*v";
				int t = i + 1; // the +1 is because the variables begin with 1, not 0.
				cnf << t;
				// now we store which variables are mapped:
				int j0, j1;
				j0 = map_var2idx[node0 + DecompUtils::toString(scc0[i])];
				j1 = map_var2idx[node1 + DecompUtils::toString(mapf0[scc0[i]])];
				assert(j0 <= size0 + size1 && j1 <= size0 + size1); // based on the assumption that the nodes are mapped to the lower indices of variables.
				mapped[j0] = mapped[j1] = true;
			}
		}
		cnf << ";" << endl;
		cnf << "* unmapped variables are in:" << endl;
		for (int i = 1; i <= size0 + size1; ++i)  // unmapped variables are in.
			if (!mapped[i]) cnf << "+1*v" << i << " >= 1;" << endl;

		cnf << "* edges side 0:" << endl;
		for (int i = 0; i < size0; ++i) // edges side 0
			for (int j = 0; j < size0; ++j)
			{
				if (cg0.is_edge(scc0[i], scc0[j]))
				{
					string s(DecompUtils::toString(scc0[i])),
							s1(DecompUtils::toString(scc0[j]));
					imply(cnf, node0 + s, node0 + s1, E(Edge0_prefix, s, s1));
				}
			}
		cnf << "* edges side 1:" << endl;
		for (int i = 0; i < size1; ++i) // edges side 1
			for (int j = 0; j < size1; ++j)
			{
				if (cg1.is_edge(scc1[i], scc1[j]))
				{
					string s(DecompUtils::toString(scc1[i])),
							s1(DecompUtils::toString(scc1[j]));
					imply(cnf, node1 + s, node1 + s1, E(Edge1_prefix, s, s1));
				}
			}

		cnf << "* transitive closure side 0:" << endl;
		for (int i = 0; i < size0; ++i) // transitive closure side 0
			for (int j = 0; j < size0; ++j)
			{
				if (i == j) continue;
				for (int k = 0; k < size0; ++k)
				{
					if (j == k) continue;
					string s(DecompUtils::toString(scc0[i])),
							s1(DecompUtils::toString(scc0[j])),
							s2(DecompUtils::toString(scc0[k]));
					imply(cnf, E(Edge0_prefix, s, s1), E(Edge0_prefix, s1, s2), E(Edge0_prefix, s, s2));
				}
			}

		cnf << "* transitive closure side 1:" << endl;
		for (int i = 0; i < size1; ++i) // transitive closure side 1
			for (int j = 0; j < size1; ++j)
			{
				if (i == j) continue;
				for (int k = 0; k < size1; ++k)
				{
					if (j == k) continue;
					string s(DecompUtils::toString(scc1[i])),
							s1(DecompUtils::toString(scc1[j])),
							s2(DecompUtils::toString(scc1[k]));
					imply(cnf, E(Edge1_prefix, s, s1), E(Edge1_prefix, s1, s2), E(Edge1_prefix, s, s2));
				}
			}

		cnf << "* side0: self loops not allowed:" << endl;
		for (int i = 0; i < size0; ++i)
		{ // side0: self loops not allowed
			string s(DecompUtils::toString(scc0[i]));
			negunit(cnf, E(Edge0_prefix, s, s));
		}

		cnf << "* side1: self loops not allowed:" << endl;
		for (int i = 0; i < size1; ++i)
		{ // side0: self loops not allowed
			string s(DecompUtils::toString(scc1[i]));
			negunit(cnf, E(Edge1_prefix, s, s));
		}

		cnf << "* force mapping:" << endl;
		for (unsigned int i = 0; i < scc0.size(); ++i)
		{  // force mapping
			if (is_mapped(scc0[i]))
			{
				string s(DecompUtils::toString(scc0[i])),
						s1(DecompUtils::toString(mapf0[scc0[i]]));
				make_equal(cnf, node0 + s, node1 + s1);
			}
		}
	}

	void readMinisatOutput(list<string>& tokens, const string &assignmentFile) const {
		RVTextFileReader reader(assignmentFile);
		reader.addDelimitingChar('v');
		assert(reader.readNextLineTokens(tokens));
		assert(reader.hasNoMoreTokens());
	}

	unsigned int convertStringToPositiveInt(const string& s) {
		unsigned int res = 0;
		for (unsigned int i = 0; i < s.size(); ++i) {
			char c = s.at(i);
			if (isdigit(c))
				res += res*10 + c - '0';
			else
				throw FormatException();
		}
		return res;
	}

	vector<int> extract_minisat_solution(const string &assignmentFile,
			const vector<int>& scc0)
			{
		/*
		   Assumptions about minisat+'s solution: has the form v -v1 v4 v2 -v5 ... // not ordered.
		 */
		string s;
		list<string> split;
		readMinisatOutput(split, assignmentFile);
		bool neg = false;
		unsigned int num = 0;
		vector<int> solution;
		for (list<string>::iterator it = split.begin(); it != split.end(); ++it)
		{
			// Should we trim the string?
			// if (s1 == "") continue; Empty tokens are impossible
			if (*it == "-") neg = true;
			else
			{
				try { num = convertStringToPositiveInt(*it); }
				catch (FormatException) { fatal_error("Something wrong in output of minisat+."); }
				if ((num  < scc0.size() + 1) && neg)
					solution.push_back(scc0[num - 1]);
				neg = false;
			}
		}


		Console::Write("Solution: "); DecompUtils::print_container(solution); Console::WriteLine();
		return solution;
			}

	void Find_S(vector<int>& res, int n, const mygraph& cg0, const mygraph& cg1, const vector<int>& scc0, const vector<int>& scc1)
	{
		res.clear();
		if (scc0.size() == 1 && scc1.size() == 1) {
			//if (DBG)
			Console::WriteLine("Single recursive function in SCC");
			res.clear();
			res.push_back(scc0[0]);
			return;
		}

		string opbFile("S" + DecompUtils::toString(n) + ".opb");
		map_var_to_idx(scc0, scc1);
		ofstream cnf(opbFile.data(), ios_base::out);
		add_constraints(cnf, cg0, cg1, scc0, scc1);
		appendNegatedSolutionsToFile(cnf);
		cnf.close();

		string assignmentFile("assignment");
		Console::WriteSpaceSepLine("running: run_minisat", opbFile, assignmentFile);
		int ret = rv_commands.run_minisat(opbFile, assignmentFile);

		Console::Write("Result: ");
		if (ret == 0) {
			Console::WriteLine("sat ");
			res = extract_minisat_solution(assignmentFile, scc0);
		}
		else
			Console::WriteLine("unsat! Cannot find S. ");
	}

};


static void add_recursive_calls(list<Edge>& edges, const list<int>& loop_functions) {
	for(list<int>::const_iterator it = loop_functions.begin(); it != loop_functions.end(); it++)
		edges.push_back(Edge(*it, *it));
}


/// <summary>
/// interface for the decomposition algorithm.
/// </summary>
/// <param name="CG0_SIZE"> number of nodes (functions) in the call graph, side 0 </param>
/// <param name="CG1_SIZE"> number of nodes (functions) in the call graph, side 1 </param>
/// <param name="edges_0"> edges defining the call graph, side 0 </param>
/// <param name="edges_0"> edges defining the call graph, side 1 </param>
/// <param name="loop_functions_0"> list of loop functions on side 0 </param>
/// <param name="loop_functions_1"> list of loop functions on side 1 </param>
/// <param name="mapf"> mapping between the functions on the two sides </param>
/// <param name="syntactic_equivalent_list"> functions on side 0 that are syntact. equiv. to the their counterparts</param>
/// <param name="givenNames0"> names of functions, side 0 </param>
/// <param name="givenNames1"> names of functions, side 1 </param>
/// <param name="semchecker"> reference to the object to perform the semantic checks </param>
void RVT_Decompose::Decompose_main(
		unsigned int CG0_SIZE, unsigned int CG1_SIZE,
		const list<Edge>& edges_0, const list<Edge>& edges_1,
		const list<int>& loop_functions_0, const list<int>& loop_functions_1,
		const list<Match>& mapf,
		const list<int>& syntactic_equivalent_list,
		const vector<string>& givenNames0, const vector<string>& givenNames1,
		RVMain& semchecker
)
{
	assert(givenNames0.size() == CG0_SIZE && givenNames1.size() == CG1_SIZE);
	mygraph cg0(CG0_SIZE), cg1(CG1_SIZE);
	DAG dag0(cg0), dag1(cg1);
	Solve sl(CG0_SIZE, CG1_SIZE, semchecker);

	cg0.declare(edges_0); cg1.declare(edges_1);

#ifdef LOOPS_NOT_RECURSIVE  
	// with this optimization loops are reported without the recursive call. These lines add these edges back.
	// We need to see them as recursive because the decomposition alg. makes decisions accordingly (e.g., in find_S).
	list<Edge> self0, self1;
	add_recursive_calls(self0, loop_functions_0);
	add_recursive_calls(self1, loop_functions_1);
	cg0.declare(self0, true); cg1.declare(self1, true);
#endif
	cg0.todotty("cg0");   cg1.todotty("cg1");
	sl.map_functions(cg0, cg1, mapf);

	dag0.compute_SCCs(); dag1.compute_SCCs();
	dag0.build_DAG(); dag1.build_DAG();
	dag0.todotty("dag0");  dag1.todotty("dag1");
	sl.set_dag0_size(dag0.size());
	while (sl.build_SCC_map(dag0, dag1)) ; // builds map while removing doomed, until fixpoint.
	if (!sl.is_map_consistent(dag0, dag1))
		fatal_error("main(): SCC mapping is cyclic.");
	sl.declare_syntactic_equivalent(syntactic_equivalent_list);

	sl.decompose(dag0, dag1, givenNames0, givenNames1); // This is the main workhorse.

	// generating the graph:
	ofstream dotty(RV_DOTTY_FILE, ios_base::out);
	dotty << "digraph G{" << endl;
	cg0.todotty_final(dotty, 0, dag0, sl.get_equivalence_vec0(),
			          sl.get_syntactic_equivalence0(), loop_functions_0,
			          sl.getMapf0(), givenNames0, givenNames1,
			          semchecker.is_checking_partial_equiv());
	vector<bool>* p_syntactic_equivalent1 = sl.alloc_syntactic_equivalent1(CG1_SIZE);
	cg1.todotty_final(dotty, 1, dag1, sl.get_equivalence_vec1(),
			          *p_syntactic_equivalent1, loop_functions_1,
			          sl.getMapf1(), givenNames1, givenNames0,
			          semchecker.is_checking_partial_equiv());
	sl.report_final_results(*p_syntactic_equivalent1, givenNames0, givenNames1,
							semchecker.is_checking_partial_equiv());
	delete p_syntactic_equivalent1;
	dotty << "}" << endl;
	dotty.close();

	endl(rv_errstrm << "Output graph written to " << RV_DOTTY_FILE);
}
