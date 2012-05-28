/*
 * rv_etc.h
 *
 *  Created on: Mar 18, 2011
 *      Author: edima
 *
 *  This file contains decalarations of small auxiliary classes and stand-
 *  alone functions for which we want to avoid creating a separate .cpp
 *  file
 */

#ifndef RV_ETC_H_
#define RV_ETC_H_

#include "rv_macros.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "ctool/location.h"
#include "rv_side.h"


/// <summary>
/// Class for parsing text files of predefined format
/// </summary>
/// <remark> See also the members of class ifstream. </remark>
class RVTextFileReader : public std::ifstream {
public:
	RVTextFileReader(const std::string &filename);
	~RVTextFileReader();

	/// <summary>
	/// Extracts from the next read line.
	/// </summary>
	/// <param name="tokens"> here the read tokens will be filled </param>
	/// <returns> true iff there are tokens read </returns>
	bool readNextLineTokens(std::list<std::string>& tokens);

	/// <summary>
	/// Extracts from the next read line.
	/// </summary>
	/// <param name="tokens"> here the read tokens will be filled </param>
	/// <param name="locs"> here the locations of the read tokens will be filled </param>
	/// <returns> true iff there are tokens read </returns>
	bool readNextLineTokens(std::list<std::string>& tokens, std::list<Location>& locs);

	/// <summary>
	/// Returns true iff there are no more tokens left.
	/// </summary>
	/// <remark> If the method returns <c>false</c>, you miss some tokens </remark>
	bool hasNoMoreTokens(void);

	/// <summary>
	/// Declares <paramref name="name"/> among the characters that can delimit tokens
	/// </summary>
	RVTextFileReader& addDelimitingChar(char c);

	/// <summary>
	/// Sets if the space characters delimit tokens.
	/// </summary>
    RVTextFileReader& setSpaceCharsDelimiting(bool areDelimiting = true);

    /// <summary>
	/// Sets if empty tokens should be ignored or reported.
	/// </summary>
	RVTextFileReader& setIgnoreEmptyTokens(bool ignore = true);

    bool errorOccurred(void) const { return !m_good; }

private:
	void closeToken(const char *s, int len,
			        std::list<std::string>& tokens,
			        std::list<Location>& locations) const;

	std::set<char>  m_delimCharSet;
	bool            m_bSpaceCharsDelimiting;
	bool            m_ignoreEmptyTokens;
	std::string     m_filename;
	int             m_line;
	int             m_column;
    bool            m_good;
};


/// <summary>
/// Utilities used in this file
/// </summary>
class Utils
{
public:
	/// <summary>
	/// Returns <b>true</b> iff the given STL container <i>c</i> contains the element <i>v</i>
	/// </summary>
	/// <param name="c"> the container </param>
	/// <param name="v"> the sought element </param>
	template <typename C,typename T> static bool containsElem(const C& c, const T& v) {
		return find(c.begin(), c.end(), v) != c.end();
	}

	///<summary> Expands a vector to the desired length </summary>
	///<param name="v"> the vector </param>
	///<param name="size"> the desired length </param>
	///<param name="defVal"> default value for filling in the appended cells </param>
	template <typename T>
	static void expandPtrVec(typename std::vector<T>& v, size_t size) {
		if (v.size() < size)
			v.resize(size, NULL);
	}

	/// <summary>
	/// Returns string representation of an STL container
	/// </summary>
	/// <param name="v"> the STL container </param>
	template <class C> static std::string containerToString(const C& v) {
		std::stringstream buf;
		buf << "{ ";
		for(typename C::const_iterator it = v.begin(); it != v.end(); ++it)
			buf << *it << " ";
		buf << "} ";
		return buf.str();
	}

	/// <summary>
	/// Returns string representation of an STL container holding pointers
	/// </summary>
	/// <param name="v"> the STL container </param>
	template <class C> static std::string containerOfPtrsToString(const C& v) {
		std::stringstream buf;
		buf << "{ ";
		for(typename C::const_iterator it = v.begin(); it != v.end(); ++it)
			if (*it)
				buf << **it << " ";
			else
				buf << "NULL ";
		buf << "} ";
		return buf.str();
	}

	template <typename T> struct Deleter : public std::unary_function<T,void> {
		void operator() (T ptr) { RVDELETE( ptr ); }
	};

	template <typename C> static void deleteElems(C& v) {
		std::for_each(v.begin(), v.end(), Deleter<typename C::value_type>());
	}

	template <typename Map> static void deleteValues(Map& m) {
		for (typename Map::iterator it = m.begin(); it != m.end(); ++it)
			RVDELETE( it->second );
	}

	/// <summary>
	/// Returns legal filename without space characters
	/// </summary>
	/// <param name="base"> the base part of the filename </param>
	/// <param name="extension"> the filename extension </param>
	/// <param name="spaceSubstitution"> the character substituting space characters in the filename </param>
	static std::string mkFilename(const std::string& base,
			                      const std::string& extension = "",
			                      const char spaceSubstitution = '-');

	/// <summary>
	/// Converts integer to string.
	/// </summary>
	/// <param name="n"> the integer </param>
	static std::string itoa(int n);

	/// <summary>
	/// Replaces a character with a given string in a string.
	/// </summary>
	/// <param name="in"> the string whose characters are to be replaced </param>
	/// <param name="what"> the character to be replaced </param>
	/// <param name="with"> the substituting string </param>
	static void replaceCharInString(std::string& in, char what, const std::string& with);

	/// <summary>
	/// Replaces a character with a given string in a string.
	/// </summary>
	/// <param name="in"> the string whose substring is to be replaced </param>
	/// <param name="what"> the substring to be replaced </param>
	/// <param name="with"> the substituting string </param>
	static void replaceSubstringInString(std::string& in, const std::string& what, const std::string& with);

	static bool stringBeginsWith(const std::string& str, const std::string &prefix);
};


///<summary>
///Backs up a value. Upon destruction, restores the stored value.
///Useful for temporary change of some value inside a function when the
///function might have several return points.
///</summary>
///<seealso cref="RVForLoopUninitializer"/>
template <typename T> class RVLocalBackup {
public:
	RVLocalBackup(T& ref) : m_ref(ref), m_backUpVal(ref), m_restore(true) {}

	RVLocalBackup(T& ref, const T& newVal) : m_ref(ref), m_backUpVal(ref), m_restore(true)
	{
		ref = newVal;
	}

	~RVLocalBackup() {
		if (m_restore) m_ref = m_backUpVal;
	}

	const T& getOrigVal(void) const {
		return m_backUpVal;
	}

	void setRestoreFlag(bool flag) { m_restore = flag; }

private:
	T&   m_ref;
	T    m_backUpVal;
	bool m_restore;
};


class RVDischarger;

interface RVIDischargee {
	virtual ~RVIDischargee() {}
	virtual void discharge(RVDischarger&) = 0;
};

template <typename T> struct RVTypedDischargee : public RVIDischargee {
	RVTypedDischargee(T* ptr) : m_ptr(ptr) {}
	virtual ~RVTypedDischargee() {}
	virtual void discharge(RVDischarger&) { delete m_ptr; m_ptr = NULL; }
private:
	T* m_ptr;
};

class RVDischarger {
	typedef std::map<RVIDischargee*, bool> DischargeMap;

public:
	RVDischarger(void) : m_inDestructor(false) {}
	virtual ~RVDischarger();
	void addDischargee(RVIDischargee&);
	void addDischargeeHeapPtr(RVIDischargee*);
	void removeDischargeeByPtr(RVIDischargee* pDischargee);

private:
	DischargeMap m_pDischargees;
	bool         m_inDestructor;
};

#endif /* RV_ETC_H_ */
