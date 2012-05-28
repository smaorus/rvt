#ifndef RV_GRAPH_H
#define RV_GRAPH_H

/* Code for generating graphical representation of the call graph */

#include "rv_macros.h"

#include <vector>
#include <map>
#include <list>
#include <deque>
#include <string>
#include <set>
#include "rv_error.h"

#ifdef _MSC_VER
	#define THROWS(e)
#else
	#define THROWS(e) throw(e)
#endif

/// <summary>
/// API for a directed graph with indexed vertices
/// </summary>
class RVIntGraph
{
protected:
	int _size;
	bool m_bExpandable;
	std::vector<bool> node_reported;
	std::vector<std::list<int> > callers, callees;

public:
	RVIntGraph(bool expandable = true);
	RVIntGraph(int n, bool expandable = true);
	RVIntGraph(const RVIntGraph& othergraph); // copy constructor

	virtual ~RVIntGraph() {}

	/// <summary>
	/// Adds an edge to the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	void edge(int i, int j);

	/// <summary>
	/// Removes an edge from the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	void remove_edge(int i, int j);

	/// <summary>
	/// Tells if there is an edge connecting the given nodes in the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	bool is_edge(int i, int j) const;

	int indegree(int i) const;
	int outdegree(int i) const;

	/// <summary>
	/// Checks whether this graph is cyclic
	/// Complexity: O(|V|+|E|).
	/// </summary>
	bool is_cyclic(void) const;

	int size(void) const;

	bool is_node_reported(int i) const;
	void getReportedVertixIndices(std::vector<int>&) const;

	const std::list<int>& getParents(int idx) const;
	const std::list<int>& getChildren(int idx) const;

	/// <summary>
	/// Gets all the direct children of the given node
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="children"> here the children will be filled </param>
	void get_children(int i, std::vector<int>& children) const;

	/// <summary>
	/// Dumps the structure of the graph into a .gv file
	/// </summary>
	/// <param name="file_name"> the name of the resulted .gv file </param>
	void toDotty(const std::string& file_name) const;

	bool collapseVertex(int idx);

	void reverse(void);

protected:
	void expand_graph(int n); //must be non-virtual
	void tryToExpand(int i);
	bool collapseVertexLow(int selfIdx, bool makeTransitiveEdges);

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
	virtual std::string getDottyAttrsOfVertex(int i,
											  std::string &label,
											  std::string &fontcolor,
											  std::string &color,
											  std::string &shape,
											  std::string &style,
											  std::string &fillcolor) const;

	/// <summary>
	/// Retrieves dotty attributes of a graph.
	/// </summary>
	/// <return>the name of the graph </return>
	/// <param name="label"> here the label of the graph can be assigned </param>
	/// <param name="fontcolor"> here the font color of the graph label can be assigned </param>
	/// <param name="bgcolor"> here the background color of the graph space can be assigned </param>
	/// <remark> Unused attributes may be left unassigned. </remark>
	virtual std::string getDottyAttrsOfGraph(std::string &label,
			  						  	     std::string &fontcolor,
			  						         std::string &bgcolor) const;

	/// <summary>
	/// Collects nodes of all the paths from a given node until a common ancestor is reached.
	/// The common ancestor is not collected.
	/// A lasso is truncated right before its loop is closed.
	/// A loop to <paramref name="from"/> results that the common ancestor will not be found.
	/// Paths with lassos to some ancestor do not fail seeking the common ancestor.
	/// Regardless where a loop is closed, the nodes of the lasso paths are collected.
	/// </summary>
	/// <param name="from"> the index of the node where the paths begin </param>
	/// <param name="nodes"> here the nodes are collected </param>
	/// <returns> Returns the index of the common ancestor if found, otherwise -1 </returns>
	int getNodesUntilCommonAncestor(int from, std::set<int>& nodes) const;

private:
	/// <summary>
	/// Retrieves the last information about the cyclicity of this graph before destroying it
	/// Algorithm: Removes nodes with indegree 0 until no such nodes. Then checks if any node remains.
	/// Complexity: O(|V|+|E|).
	/// </summary>
	/// <returns> true <-> this graph was cyclic </returns>
	///
	bool destroy_for_checking_cyclicity_sake(void);
};




template<typename T> class RVTypedVertexInfo;


class TypeMismatchException {};


class RVVertexInfo {
public:
	RVVertexInfo(void);
	RVVertexInfo(const RVVertexInfo& other);

	virtual ~RVVertexInfo();

	virtual RVVertexInfo* clone(void) const = 0;

	template<typename T>
	void getPtr(T*& rPtr, const std::string& typeName = "") const THROWS(TypeMismatchException)
	{
		rPtr = static_cast<const RVTypedVertexInfo<T>*>(this)->getPtr(typeName);
	}

protected:
	RVVertexInfo(void *ptr, const std::string& typeName, bool cloned)
	  : m_ptr(ptr), m_typeName(typeName), m_cloned(cloned) {}

	void             *m_ptr;
	std::string       m_typeName;
	bool              m_cloned;

private:
	RVVertexInfo& operator= (const RVVertexInfo& other);
};


template<typename T> class RVTypedVertexInfo : public RVVertexInfo {
public:
	RVTypedVertexInfo(const T& obj, const std::string& typeName = "")
	  : RVVertexInfo(new T(obj), typeName, true) {}

	RVTypedVertexInfo(T *ptr, const std::string& typeName = "")
	  : RVVertexInfo(ptr, typeName, false) {}

	RVTypedVertexInfo(const RVTypedVertexInfo<T>& other)
	  : RVVertexInfo(other)
	{
		if (m_ptr != NULL && m_cloned)
			m_ptr = new T(*getPtr());
	}

	virtual ~RVTypedVertexInfo() THROWS(TypeMismatchException) {
		if (m_cloned && m_ptr != NULL)
			RVDELETE(getPtr());
	}

	T* getPtr(const std::string& typeName = "") const THROWS(TypeMismatchException) {
		if (typeName.empty() || typeName.compare(m_typeName) == 0)
			return static_cast<T*>(m_ptr);
		throw TypeMismatchException();
	}

	virtual RVVertexInfo* clone(void) const {
		return new RVTypedVertexInfo<T>(*this);
	}
};


struct RVStringVertexInfo : public RVTypedVertexInfo<std::string> {
	static const std::string ms_typeName;

	RVStringVertexInfo(const std::string& s);
	RVStringVertexInfo(const char *s);

	std::string& getString(void) const THROWS(TypeMismatchException);
};

struct RVIntVertexInfo : public RVTypedVertexInfo<int> {
	static const std::string ms_typeName;

	RVIntVertexInfo(int val);

	int getInt(void) const THROWS(TypeMismatchException);
};

struct RVFlagVertexInfo : public RVTypedVertexInfo<bool> {
	static const std::string ms_typeName;

	RVFlagVertexInfo(bool flag);

	bool getFlag(void) const THROWS(TypeMismatchException);
};

template <typename T>
struct RVSetVertexInfo : public RVTypedVertexInfo<typename std::set<T> > {
	static const std::string ms_typeName;

	RVSetVertexInfo(const std::set<T>& src) :
		RVTypedVertexInfo<std::set<T> >(src, ms_typeName) {}
};


class RVNoVertexInfo : public RVVertexInfo {
	virtual RVVertexInfo* clone(void) const {
		return new RVNoVertexInfo;
	}
};




class RVIntGraphWData : public RVIntGraph {
    typedef std::map<std::string, RVVertexInfo*> PropByName;
public:
	RVIntGraphWData(bool expandable = true);
	RVIntGraphWData(const RVIntGraphWData& othergraph); // copy constructor

	virtual ~RVIntGraphWData();

	void setDefaultProperty(const std::string& prop, const RVVertexInfo& val);
	void setProperty(int idx, const std::string& prop, const RVVertexInfo& val);
	void clearProperty(int idx, const std::string& prop);
	void renameProperty(int idx, const std::string& oldName, const std::string& newName);
	const RVVertexInfo& getProperty(int idx, const std::string& prop) const;

	std::pair<int, int> split(int srcIdx);
	int reincarnate(int srcIdx);

private:
	void copyProperties(int idx, const std::vector<PropByName>& fromV, int fromIdx);
	void expandProperties(int upToIndex);
	bool hasProperty(const PropByName& where, const std::string& prop) const;
	void setPropertyLow(PropByName& where, const std::string& prop, const RVVertexInfo& val);
	int duplicateVertex(int idx);
	static void deleteProps(PropByName&);

	static const RVNoVertexInfo ms_emptyInfo;
	std::vector<PropByName> m_props;
	PropByName m_defaultProp;
};




template<typename T> class RVGraphWData : public RVIntGraphWData {
public:
	RVGraphWData(bool expandable = true)
	  : RVIntGraphWData(expandable) {}

	RVGraphWData(const RVGraphWData<T>& othergraph)
	  : RVIntGraphWData(othergraph),
		m_indexer(othergraph.m_indexer),
		m_deindexer(othergraph.m_deindexer) {}

	virtual ~RVGraphWData() {}

	/// <summary>
	/// Adds an edge to the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	void edge(const T& i, const T& j) {
		int i_idx = makeIndex(i), j_idx = makeIndex(j);
		RVIntGraphWData::edge(i_idx, j_idx);
	}

	/// <summary>
	/// Removes an edge from the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	void remove_edge(const T& i, const T& j) {
		RVIntGraphWData::remove_edge(makeIndex(i), makeIndex(j));
	}

	/// <summary>
	/// Tells if there is an edge connecting the given nodes in the graph
	/// </summary>
	/// <param name="i"> the index of the source node </param>
	/// <param name="j"> the index of the destination node </param>
	bool is_edge(const T& i, const T& j) const {
		return RVIntGraphWData::is_edge(getIndex(i), getIndex(j));
	}

	int indegree(const T& i) const {
		return RVIntGraphWData::indegree(getIndex(i));
	}

	int outdegree(const T& i) const {
		return RVIntGraphWData::outdegree(getIndex(i));
	}

	void getCallers(const T& id, std::vector<T>& callers) const {
		const std::list<int>& callerIds = getParents(getIndex(id));
		std::list<int>::const_iterator it = callerIds.begin();
		callers.resize(callerIds.size());
		for (int i = 0; it != callerIds.end(); ++it, ++i)
			callers[i] = fromIndex(*it);
	}

	void getCallees(const T& id, std::vector<T>& callees) const {
		const std::list<int>& calleeIds = getChildren(getIndex(id));
		std::list<int>::const_iterator it = calleeIds.begin();
		callees.resize(calleeIds.size());
		for (int i = 0; it != calleeIds.end(); ++it, ++i)
			callees[i] = fromIndex(*it);
	}

	void setDefaultProperty(const std::string& prop, const RVVertexInfo& val) {
		RVIntGraphWData::setDefaultProperty(prop, val);
	}

	void setProperty(const T& id, const std::string& prop, const RVVertexInfo& val) {
		RVIntGraphWData::setProperty(makeIndex(id), prop, val);
	}


	const RVVertexInfo& getProperty(const T& id, const std::string& prop) const {
		return RVIntGraphWData::getProperty(getIndex(id), prop);
	}

	bool collapseVertex(const T& id) {
		return RVIntGraph::collapseVertex(makeIndex(id));
	}

	std::pair<int, int> split(const T& id, const T& newId1, const T& newId2) {
		std::pair<int, int> newIds = RVIntGraphWData::split(getIndex(id));
		updateMapping(newId1, newIds.first);
		updateMapping(newId2, newIds.second);
		return newIds;
	}

	int reincarnate(const T& id) {
		int newIdx = RVIntGraphWData::reincarnate(getIndex(id));
		updateMapping(id, newIdx);
		return newIdx;
	}

	void getVertices(std::vector<T>& vertices) const {
		std::vector<int> indices;
		getReportedVertixIndices(indices);
		vertices.resize(0);
		vertices.reserve(indices.size());
		for (std::vector<int>::iterator it = indices.begin(); it != indices.end(); ++it)
			vertices.push_back(fromIndex(*it));
	}

	const T& fromIndex(int idx) const {
		assert(idx >= 0 && static_cast<size_t>(idx) < m_deindexer.size());
		return m_deindexer[idx];
	}

	/// <summary>
	/// Collects nodes of all the paths from a given node until a common ancestor is reached.
	/// A lasso is truncated right before its loop is closed.
	/// A loop to <paramref name="from"/> results that the common ancestor will not be found.
	/// Paths with lassos to some ancestor do not fail seeking the common ancestor.
	/// Regardless where a loop is closed, the nodes of the lasso paths are collected.
	/// </summary>
	/// <param name="from"> the node where the paths begin </param>
	/// <param name="rNodes"> here the node indices are collected </param>
	/// <returns> Returns the index of the common ancestor if found, otherwise -1 </returns>
    /// <remark> The node <paramref name="from"/> is excluded from <paramref name="rNodes"/>. </remark>
	int getNodesTillCommonAncestor(const T& from, std::set<int>& rNodes) const {
		int common = getNodesUntilCommonAncestor(getIndex(from), rNodes);
        rNodes.erase(getIndex(from));
        return common;
	}

private:
	int getIndex(const T& id) const {
		typename std::map<T, int>::const_iterator it = m_indexer.find(id);
		if (it != m_indexer.end())
			return it->second;
		fatal_error("RVGraphWData::getIndex(): unregistered id");
        return 0;
	}


	int makeIndex(const T& id) {
		typename std::map<T, int>::const_iterator it = m_indexer.find(id);
		if (it != m_indexer.end())
			return it->second;
		int result = m_deindexer.size();
		updateMapping(id, result);
		tryToExpand(result);
		return result;
	}

	void updateMapping(const T& id, int idx) {
		m_indexer[id] = idx;
		m_deindexer.push_back(id);
	}

private:
	std::map<T, int> m_indexer;
	std::deque<T> m_deindexer;
};



#endif /* RV_GRAPH_H */
