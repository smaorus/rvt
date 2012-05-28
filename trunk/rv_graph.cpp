#include "rv_macros.h"
#include <assert.h>
#include <limits.h>
#include <stack>
#include "rv_error.h"
#include "rv_graph.h"
#include "rv_etc.h"

using namespace std;


RVIntGraph::RVIntGraph(bool expandable)
: _size(0), m_bExpandable(expandable) {}

RVIntGraph::RVIntGraph(int n, bool expandable)
: _size(0), m_bExpandable(expandable)
{
	expand_graph(n);
}

RVIntGraph::RVIntGraph(const RVIntGraph& othergraph) // copy constructor
: _size(othergraph.size()),
  m_bExpandable(othergraph.m_bExpandable),
  callers(othergraph.callers),
  callees(othergraph.callees)
{
	//m_props
}

void RVIntGraph::tryToExpand(int i)
{
    if(i >= _size)
        m_bExpandable ? expand_graph(i+1)
        		      : fatal_error("reported edge out of range");
}

/// <summary>
/// Adds an edge to the graph
/// </summary>
/// <param name="i"> the index of the source node </param>
/// <param name="j"> the index of the destination node </param>
void RVIntGraph::edge(int i, int j)
{
    tryToExpand(i);
    tryToExpand(j);
	node_reported[i] = node_reported[j] = true;
	if (!is_edge(i, j)) {
		callees[i].push_back(j);
		callers[j].push_back(i);
	}
}

/// <summary>
/// Removes an edge from the graph
/// </summary>
/// <param name="i"> the index of the source node </param>
/// <param name="j"> the index of the destination node </param>
void RVIntGraph::remove_edge(int i, int j)
{
	if (i >= _size || j >= _size) fatal_error("in remove_edge(): reported edge out of range");
	callees[i].remove(j);
	callers[j].remove(i);
}

/// <summary>
/// Tells if there is an edge connecting the given nodes in the graph
/// </summary>
/// <param name="i"> the index of the source node </param>
/// <param name="j"> the index of the destination node </param>
bool RVIntGraph::is_edge(int i, int j) const
{
	if (i >= _size || j >= _size) fatal_error("in is_edge(): reported edge out of range");
	return Utils::containsElem(callees[i], j);
}

/// <summary>
/// Gets all the direct children of the given node
/// </summary>
/// <param name="i"> the index of the source node </param>
/// <param name="children"> here the children will be filled </param>
void RVIntGraph::get_children(int i, std::vector<int>& children) const {
	children.insert(children.end(), getChildren(i).begin(), getChildren(i).end());
}

int RVIntGraph::indegree(int i) const {
	return getParents(i).size();
}

int RVIntGraph::outdegree(int i) const {
	return getChildren(i).size();
}

/// <summary>
/// Checks whether this graph is cyclic
/// Complexity: O(|V|+|E|).
/// </summary>
bool RVIntGraph::is_cyclic(void) const {
	RVIntGraph cloned(*this);
	return cloned.destroy_for_checking_cyclicity_sake();
}

int RVIntGraph::size(void) const {
	return _size;
}

bool RVIntGraph::is_node_reported(int i) const {
	return node_reported[i];
}

void RVIntGraph::getReportedVertixIndices(std::vector<int>& vertices) const {
	vertices.resize(0);
	vertices.reserve(_size);
	for (int iExist = 0; iExist < size(); ++iExist)
		if (is_node_reported(iExist))
			vertices.push_back(iExist);
}

const list<int>& RVIntGraph::getParents(int idx) const {
	assert(idx < _size);
	return callers[idx];
}

const list<int>& RVIntGraph::getChildren(int idx) const {
	assert(idx < _size);
	return callees[idx];
}

static void appendDottyAttribute(ofstream& dotty, const string &attrValue, const string &attrName, bool &hasAttrs, const string &graphName) {
	if (attrValue.empty())
		return;

	if (hasAttrs)
		dotty << " , ";
	else {
		dotty << graphName << " [ ";
		hasAttrs = true;
	}

	string attrValueNoParenth(attrValue);
	Utils::replaceCharInString(attrValueNoParenth, '"', "\\\"");
	dotty << attrName << " = \"" << attrValueNoParenth << "\"";
}

/// <summary>
/// Dumps the structure of the graph into a .gv file
/// </summary>
/// <param name="file_name"> the name of the resulted .gv file </param>
/// <param name="prefix"> prefix of each node </param>
void RVIntGraph::toDotty(const string& file_name) const {
	string s = Utils::mkFilename(file_name, "gv"), dummy;
	ofstream dotty;
	dotty.open(s.data(), ios_base::out);
	if( !dotty.is_open() ) {
		rv_errstrm << "Unable to open dotty file: " << s << "\n";
		return;
	}

	dotty << "digraph G{" << endl;
//	dotty << file_name << "[style=filled, color = lightblue, shape = box];" << endl;
	bool hasAttrs = false;
	string g_label, g_fontcolor, g_bgcolor;
	string graphName = getDottyAttrsOfGraph(g_label, g_fontcolor, g_bgcolor);
	appendDottyAttribute(dotty, g_label, "label", hasAttrs, graphName);
	appendDottyAttribute(dotty, g_fontcolor, "fontcolor", hasAttrs, graphName);
	appendDottyAttribute(dotty, g_bgcolor, "bgcolor", hasAttrs, graphName);
	if (hasAttrs)
		dotty << " ];" << endl;

	for (int j = 0; j < _size; j++) {
        if (!node_reported[j])
            continue;
		string label, fontcolor, color, shape, style, fillcolor;
		string nodeName = getDottyAttrsOfVertex(j, label, fontcolor, color, shape, style, fillcolor);
		dotty << nodeName;
		hasAttrs = false;
		appendDottyAttribute(dotty, label, "label", hasAttrs, "");
		appendDottyAttribute(dotty, fontcolor, "fontcolor", hasAttrs, "");
		appendDottyAttribute(dotty, shape, "shape", hasAttrs, "");
		appendDottyAttribute(dotty, color, "color", hasAttrs, "");
		appendDottyAttribute(dotty, style, "style", hasAttrs, "");
		appendDottyAttribute(dotty, fillcolor, "fillcolor", hasAttrs, "");
	    dotty << (hasAttrs? " ];" : ";") << endl; // necessary for dotty to maintain a consistent layout with the final graph.
	}

	for (int j = 0; j < _size; j++) {
        if (!node_reported[j])
            continue;
		FORINT(list, ancestor, getParents(j)) {
			string jName = getDottyAttrsOfVertex(j, dummy, dummy, dummy, dummy, dummy, dummy);
			string callerName = getDottyAttrsOfVertex(*ancestor, dummy, dummy, dummy, dummy, dummy, dummy);
			dotty << callerName << "->" << jName << ";" << endl;
		}
    }

	dotty << "}" << endl;
	dotty.close();
}

/// <summary>
/// Retrieves dotty attributes of a vertex.
/// </summary>
/// <return>the name of the vertex node</return>
/// <param name="i"> the index of the vertex </param>
/// <param name="label"> here the label of the vertex can be assigned </param>
/// <param name="fontcolor"> here the font color of the vertex label can be assigned </param>
/// <param name="color"> here the color of the vertex node can be assigned </param>
/// <param name="shape"> here the shape of the vertex node can be assigned </param>
/// <param name="style"> here the style of the vertex node can be assigned </param>
/// <param name="fillcolor"> here the color to fill the vertex node can be assigned </param>
/// <remark> Unused attributes may be left unassigned. </remark>
string RVIntGraph::getDottyAttrsOfVertex(int i,
									     std::string &label,
									     std::string &fontcolor,
									     std::string &color,
										 std::string &shape,
										 std::string &style,
										 std::string &fillcolor) const
{
	stringstream out;
	out << i;
	return out.str();
}

/// <summary>
/// Retrieves dotty attributes of a graph.
/// </summary>
/// <return>the name of the graph </return>
/// <param name="label"> here the label of the graph can be assigned </param>
/// <param name="fontcolor"> here the font color of the graph label can be assigned </param>
/// <param name="bgcolor"> here the background color of the graph space can be assigned </param>
/// <remark> Unused attributes may be left unassigned. </remark>
string RVIntGraph::getDottyAttrsOfGraph(std::string &label,
		  						  	    std::string &fontcolor,
		  						        std::string &bgcolor) const
{
	return "graph";
}

void RVIntGraph::expand_graph(int n)
{
	if (n < _size)
		return;
	_size = n;
	node_reported.resize(n, false);
	callers.resize(n);
	callees.resize(n);
}

/// <summary>
/// Retrieves the last information about the cyclicity of this graph before destroying it
/// Algorithm: Removes nodes with indegree 0 until no such nodes. Then checks if any node remains.
/// Complexity: O(|V|+|E|).
/// </summary>
/// <returns> true <-> this graph was cyclic </returns>
///
bool RVIntGraph::destroy_for_checking_cyclicity_sake(void)
{
	int removed = 0;
	int *in_deg = new int[_size]; // in degree
	stack<int> unrefed; // stack

	for (int i = 0; i < _size; ++i)
	{
		in_deg[i] = indegree(i);
		if (in_deg[i] == 0) unrefed.push(i);
	}
	while (!unrefed.empty()) {
		int i = unrefed.top();

		unrefed.pop();
		assert(in_deg[i] == 0);
		removed++;

		vector<int> children;
		get_children(i, children);
		FORINT(vector, child, children) {
			remove_edge(i, *child);
			--in_deg[*child];
			if (in_deg[*child] == 0) unrefed.push(*child);
		}
	}
	assert(removed <= _size);
	RVDELARR(in_deg);
	return removed != _size;
}

bool RVIntGraph::collapseVertex(int selfIdx) {
	return collapseVertexLow(selfIdx, true);
}

bool RVIntGraph::collapseVertexLow(int selfIdx, bool makeTransitiveEdges) {
	bool selfLoopFound = false;
	list<int> parents(getParents(selfIdx));
	vector<int> children;
	get_children(selfIdx, children);
	list<int>::const_iterator pit = parents.begin();
	vector<int>::const_iterator cit;

	//1. Create transitive edges
	for (; pit != parents.end(); ++pit)
		if (*pit == selfIdx)
			selfLoopFound = true;
		else
		    for (cit = children.begin(); cit != children.end(); ++cit) {
		    	if (*cit == selfIdx)
		    		selfLoopFound = true;
		    	else if (makeTransitiveEdges)
		    		edge(*pit, *cit);
		    }

	//2. Remove all edges touching the collapsed vertex
	for (pit = parents.begin(); pit != parents.end(); ++pit)
		remove_edge(*pit, selfIdx);
	for (cit = children.begin(); cit != children.end(); ++cit)
		remove_edge(selfIdx, *cit);

	//3. Invalidate the vertex
	node_reported[selfIdx] = false;

	return selfLoopFound;
}

void RVIntGraph::reverse(void) {
	for (int i = 0; i < _size; ++i)
		callers[i].swap(callees[i]);
}


class RVCommonAncestorSeeker {
	enum FinishInstruction { DEPTH_REACHED = -1, CONTINUE = 0, END_REACHED = 1};
	typedef vector<int> Path;
	static const int COMMON_ANCESTOR_NOT_FOUND;

	const RVIntGraph&           m_rGraph;
	vector<Path*>               m_pPaths, m_pExtraPaths;
	vector<vector<bool>*>       m_pHits;
	int                         m_from;

public:
	RVCommonAncestorSeeker(const RVIntGraph& graph)
	  : m_rGraph(graph), m_from(COMMON_ANCESTOR_NOT_FOUND) {
	}

	~RVCommonAncestorSeeker() {
		disposeOfPaths();
	}

	int collect(int from, set<int>& nodes) {
		const list<int>& callees = m_rGraph.getChildren(from);
		if (callees.size() <= 1) {
			nodes.insert(from);
			return callees.empty()? COMMON_ANCESTOR_NOT_FOUND : callees.front();
		}

		m_from = from;
		FinishInstruction finish = CONTINUE;
		Path path;
		path.reserve(m_rGraph.size());

		for (long maxDepth = 10; finish != END_REACHED && maxDepth < INT_MAX; maxDepth <<= 2) {
			vector<bool> hit(m_rGraph.size());
			nodes.clear();
			path.clear();
			disposeOfPaths();
			finish = forward(from, path, maxDepth, hit);
			int found = seekCommonPrefix(nodes);
			if (found != COMMON_ANCESTOR_NOT_FOUND)
				return found;
		}

		labelNodesUntil(NULL, nodes);
		return COMMON_ANCESTOR_NOT_FOUND;
	}

private:
	FinishInstruction forward(int v, Path& rPath, long depthCountBack,
			                  vector<bool>& rHit) {
		if (rHit.at(v)) {
			endReached(rPath, rHit, v == m_from);
			return END_REACHED;
		}

		rPath.push_back(v);
		rHit[v] = true;
		FinishInstruction r = descend(v, rPath, depthCountBack-1, rHit);
		rHit[v] = false;
		rPath.pop_back();
		return r;
	}

	FinishInstruction descend(int v, Path& rPath, long depthCountBack,
				              vector<bool>& rHit) {
		const list<int>& callees = m_rGraph.getChildren(v);
		if (callees.empty() || depthCountBack <= 0) {
			//Leaf node or the bottom of descending has been reached
			endReached(rPath, rHit, true);
			return depthCountBack <= 0? DEPTH_REACHED : END_REACHED;
		}

		list<int>::const_iterator it = callees.begin();
		FinishInstruction r = END_REACHED;
		for (; it != callees.end(); ++it)
			r = min(r, forward(*it, rPath, depthCountBack, rHit));

		return r;
	}

	void endReached(const Path& rPath, const vector<bool>& hits, bool primary) {
		Path::const_iterator it = rPath.begin();
		Path *added = new Path(++it, rPath.end());
		(primary? m_pPaths : m_pExtraPaths).push_back(added);
		if (primary)
			m_pHits.push_back(new vector<bool>(hits));
	}

	void disposeOfPaths(void) {
		vector<Path*>::iterator it;
		vector<vector<bool>*>::iterator hit;

		for (it = m_pPaths.begin(); it != m_pPaths.end(); ++it)
			delete *it;
		for (hit = m_pHits.begin(); hit != m_pHits.end(); ++hit)
			delete *hit;
		for (it = m_pExtraPaths.begin(); it != m_pExtraPaths.end(); ++it)
			delete *it;

		m_pPaths.clear();
		m_pHits.clear();
		m_pExtraPaths.clear();
	}

	int seekCommonPrefix(set<int>& rNodes) const {
		Path *shortest = NULL;
		size_t shortestLen = UINT_MAX;
		vector<Path*>::const_iterator it;
		for (it = m_pPaths.begin(); it != m_pPaths.end(); ++it)
			if ((*it)->size() < shortestLen) {
				shortest = *it;
				shortestLen = shortest->size();
			}

		assert(shortest != NULL);

		Path::iterator eit = shortest->begin();
		for (; eit != shortest->end(); ++eit) {
			bool found = true;
			vector<vector<bool>*>::const_iterator hit;
			for (hit = m_pHits.begin(); found && hit != m_pHits.end(); ++hit)
				found = (*hit)->at(*eit);
			if (!found)
                continue;
			labelNodesUntil(*eit, rNodes);
			return *eit;
		}

		return COMMON_ANCESTOR_NOT_FOUND;
	}

	void labelNodesUntil(int common, set<int>& rNodes) const {
		rNodes.insert(m_from);
		labelNodesUntilInPaths(common, m_pPaths, rNodes);
		labelNodesUntilInPaths(common, m_pExtraPaths, rNodes);
	}

	void labelNodesUntilInPaths(int common, const vector<Path*>& pathPtrs,
			                    set<int>& rNodes) const {
		vector<Path*>::const_iterator pit;
		for (pit = pathPtrs.begin(); pit != pathPtrs.end(); ++pit) {
			Path::const_iterator eit = (*pit)->begin();
			for (; eit != (*pit)->end() && *eit != common; ++eit)
				rNodes.insert(*eit);
		}
	}
};

const int RVCommonAncestorSeeker::COMMON_ANCESTOR_NOT_FOUND = -1;




/// <summary>
/// Collects nodes of all the paths from a given node until a common ancestor is reached.
/// A lasso is truncated right before its loop is closed.
/// A loop to <paramref name="from"/> results that the common ancestor will not be found.
/// Paths with lassos to some ancestor do not fail seeking the common ancestor.
/// Regardless where a loop is closed, the nodes of the lasso paths are collected.
/// </summary>
/// <param name="from"> the index of the node where the paths begin </param>
/// <param name="nodes"> here the nodes are collected </param>
/// <returns> Returns the index of the common ancestor if found, otherwise -1 </returns>
int RVIntGraph::getNodesUntilCommonAncestor(int from, set<int>& nodes) const {
	RVCommonAncestorSeeker seeker(*this);
	return seeker.collect(from, nodes);
}


const RVNoVertexInfo RVIntGraphWData::ms_emptyInfo;

RVIntGraphWData::RVIntGraphWData(bool expandable)
  : RVIntGraph(expandable)
{
}

RVIntGraphWData::RVIntGraphWData(const RVIntGraphWData& o) // copy constructor
 : RVIntGraph(o)
{
	PropByName::const_iterator it = o.m_defaultProp.begin();
	for (; it != o.m_defaultProp.end(); ++it)
		setDefaultProperty(it->first, *it->second);
	for (int i = 0; i < _size; ++i)
		copyProperties(i, o.m_props, i);
}

RVIntGraphWData::~RVIntGraphWData() {
    deleteProps(m_defaultProp);
    for_each(m_props.begin(), m_props.end(), deleteProps);
}

void RVIntGraphWData::setDefaultProperty(const std::string& prop, const RVVertexInfo& val) {
	setPropertyLow(m_defaultProp, prop, val);
}

void RVIntGraphWData::setProperty(int idx, const std::string& prop, const RVVertexInfo& val) {
	assert(idx < _size && idx >= 0);
	expandProperties(idx);
	setPropertyLow(m_props.at(idx), prop, val);
}

void RVIntGraphWData::setPropertyLow(PropByName& where, const std::string& prop, const RVVertexInfo& val) {
	if (hasProperty(where, prop))
		RVDELETE( where.at(prop) );
    where[prop] = val.clone();
}

const RVVertexInfo& RVIntGraphWData::getProperty(int idx, const string& prop) const {
	assert(idx < _size && idx >= 0);
	if( (size_t)idx < m_props.size() && hasProperty(m_props[idx], prop) )
		return *m_props[idx].at(prop) ;

	PropByName::const_iterator it = m_defaultProp.find(prop);
	if ( it != m_defaultProp.end() )
        return *it->second;
    return ms_emptyInfo; 
}

bool RVIntGraphWData::hasProperty(const PropByName& where, const string& prop) const {
	return where.find(prop) != where.end();
}

void RVIntGraphWData::clearProperty(int idx, const std::string& prop) {
	assert(idx < _size && idx >= 0);
	expandProperties(idx);
	if (hasProperty(m_props[idx], prop)) {
		RVDELETE( m_props[idx].at(prop) );
		m_props[idx].erase(prop);
	}
}

void RVIntGraphWData::renameProperty(int idx, const string& oldName, const string& newName) {
	if (oldName.compare(newName)) {
		setProperty(idx, newName, getProperty(idx, oldName));
		clearProperty(idx, oldName);
	}
}

void RVIntGraphWData::expandProperties(int upToIndex) {
	if (m_props.size() <= (size_t)upToIndex)
		m_props.resize(upToIndex + 1);
}

int RVIntGraphWData::duplicateVertex(int idx) {
	assert(idx < _size && idx >= 0);
	int newVertexIdx = size();
	tryToExpand(newVertexIdx);
	copyProperties(newVertexIdx, m_props, idx);
	return newVertexIdx;
}

void RVIntGraphWData::copyProperties(int toIdx,
		                             const vector<PropByName>& fromV,
		                             int fromIdx) {
	expandProperties(toIdx);
	deleteProps(m_props.at(toIdx));
	const PropByName& src = fromV.at(fromIdx);
	for (PropByName::const_iterator it = src.begin(); it != src.end(); ++it)
		setPropertyLow(m_props[toIdx], it->first, *it->second);
}

void RVIntGraphWData::deleteProps(PropByName& propsByName) {
    PropByName::iterator it = propsByName.begin();
    for (; it != propsByName.end(); ++it)
        if (it->second != NULL) RVDELETE( it->second );
    propsByName.clear();
}

pair<int, int> RVIntGraphWData::split(int srcIdx) {
	list<int>::const_iterator it;

	int newId1 = duplicateVertex(srcIdx);
	const list<int>& parents = getParents(srcIdx);
	for (it = parents.begin(); it != parents.end(); ++it)
		edge(*it, newId1);

	int newId2 = duplicateVertex(srcIdx);
	const list<int>& children = getChildren(srcIdx);
	for (it = children.begin(); it != children.end(); ++it)
		edge(newId2, *it);

	if (collapseVertexLow(srcIdx, false))
		edge(newId1, newId2);
	return pair<int, int>(newId1, newId2);
}

int RVIntGraphWData::reincarnate(int srcIdx) {
	list<int>::const_iterator it;

	int newId = duplicateVertex(srcIdx);
	const list<int>& parents = getParents(srcIdx);
	for (it = parents.begin(); it != parents.end(); ++it)
		edge(*it, newId);

	const list<int>& children = getChildren(srcIdx);
	for (it = children.begin(); it != children.end(); ++it)
		edge(newId, *it);

	collapseVertexLow(srcIdx, false);
	return newId;
}




RVVertexInfo::RVVertexInfo(void)
  : m_ptr(NULL), m_cloned(false) {}

RVVertexInfo::RVVertexInfo(const RVVertexInfo& other)
  : m_ptr(other.m_ptr), m_typeName(other.m_typeName), m_cloned(other.m_cloned) {}

RVVertexInfo::~RVVertexInfo() {
	m_ptr = NULL;
}

RVVertexInfo& RVVertexInfo::operator= (const RVVertexInfo& other) {
	return *this;
}




const std::string RVStringVertexInfo::ms_typeName = "std::string";

RVStringVertexInfo::RVStringVertexInfo(const string& s)
  : RVTypedVertexInfo<string>(s, ms_typeName) {}

RVStringVertexInfo::RVStringVertexInfo(const char *s)
  : RVTypedVertexInfo<std::string>(string(s), ms_typeName) {}

string& RVStringVertexInfo::getString(void) const THROWS(TypeMismatchException) {
	return *getPtr(ms_typeName);
}


const std::string RVIntVertexInfo::ms_typeName = "int";

RVIntVertexInfo::RVIntVertexInfo(int val)
  : RVTypedVertexInfo<int>(val, ms_typeName) {}

int RVIntVertexInfo::getInt(void) const THROWS(TypeMismatchException) {
	return *getPtr(ms_typeName);
}


const std::string RVFlagVertexInfo::ms_typeName = "bool";

RVFlagVertexInfo::RVFlagVertexInfo(bool val)
  : RVTypedVertexInfo<bool>(val, ms_typeName) {}

bool RVFlagVertexInfo::getFlag(void) const THROWS(TypeMismatchException) {
	return *getPtr(ms_typeName);
}
