/*
 * rv_etc.cpp
 *
 *  Created on: Mar 18, 2011
 *      Author: edima
 */

#include <rv_consts.h>
#include <rv_etc.h>
#include <assert.h>
#include "rv_dbg.h"
#include "rv_error.h"
#include "rv_glob.h"


using namespace std;


/******************************************************************/
/* Implementation of methods of class RVTextFileReader            */
/******************************************************************/
RVTextFileReader::RVTextFileReader(const string &filename)
  : std::ifstream(filename.data(), ifstream::in),
    m_bSpaceCharsDelimiting(true),
    m_ignoreEmptyTokens(true),
    m_filename(filename),
    m_line(1),
    m_column(1)
{
    m_good = good();
}

RVTextFileReader::~RVTextFileReader() {
	if (is_open()) close();
}

/// <summary>
/// Declares <paramref name="name"/> among the characters that can delimit tokens
/// </summary>
RVTextFileReader& RVTextFileReader::addDelimitingChar(char c) {
	m_delimCharSet.insert(c);
	return *this;
}

/// <summary>
/// Sets if the space characters delimit tokens.
/// </summary>
RVTextFileReader& RVTextFileReader::setSpaceCharsDelimiting(bool areDelimiting) {
	m_bSpaceCharsDelimiting = areDelimiting;
	return *this;
}

/// <summary>
/// Sets if empty tokens should be ignored or reported.
/// </summary>
RVTextFileReader& RVTextFileReader::setIgnoreEmptyTokens(bool ignore) {
	m_ignoreEmptyTokens = ignore;
	return *this;
}

/// <summary>
/// Returns true iff there are no more tokens left.
/// </summary>
/// <remark> If the method returns <c>false</c>, you miss some tokens </remark>
bool RVTextFileReader::hasNoMoreTokens(void) {
	list<string> dummy;
	return !readNextLineTokens(dummy);
}

/// <summary>
/// Extracts from the next read line.
/// </summary>
/// <param name="tokens"> here the read tokens will be filled </param>
/// <returns> true iff there are tokens read </returns>
bool RVTextFileReader::readNextLineTokens(list<string>& tokens) {
	list<Location> dummy;
	return readNextLineTokens(tokens, dummy);
}

/// <summary>
/// Extracts from the next read line.
/// </summary>
/// <param name="tokens"> here the read tokens will be filled </param>
/// <param name="locs"> here the locations of the read tokens will be filled </param>
/// <returns> true iff there are tokens read </returns>
bool RVTextFileReader::readNextLineTokens(list<string>& tokens, list<Location>& locations) {
	if (eof())
        return false;
    if (!good()) 
		return m_good = false;
	char buf[RV_MAX_LINE+1];
	buf[0] = buf[RV_MAX_LINE] = 0;
	getline(buf, RV_MAX_LINE);
    tokens.clear();
    locations.clear();
    ++m_line;
	if (buf[0] == '\0' && m_ignoreEmptyTokens)
	    return readNextLineTokens(tokens, locations); // This is an empty line: try the next one

    char *startPtr = buf;
    int tokenLen = 0;
    for (char *p = buf; *p != '\0'; ++p, ++tokenLen, ++m_column) {
		if ((m_bSpaceCharsDelimiting && isspace(*p)) ||
			m_delimCharSet.find(*p) != m_delimCharSet.end())
		{
			closeToken(startPtr, tokenLen, tokens, locations);
			startPtr = p + 1;
			tokenLen = -1;
		}
	}
	closeToken(startPtr, tokenLen, tokens, locations);
	m_column = 1;
    return true;
}

void RVTextFileReader::closeToken(const char *s, int len,
	 	                        list<string>& tokens,
	 	                        list<Location>& locations) const {
    if (len != 0 || !m_ignoreEmptyTokens) {
        tokens.push_back(string(s, len));
        locations.push_back(Location(m_line, m_column, m_filename));
    }
}





  /******************************************************************/
 /* Implementation of methods of class RVGlob                     */
/******************************************************************/
stack<void*> RVGlob::ms_globs[GLOB_RV_N_ELEMS];

bool RVGlob::flags(flag_tag flag, char set /*= -1*/) {
	static bool flag_array[GLBL_LAST_FLAG] = {
			true, // GLBL_OUTLINE
			true // GLBL_OUTLINE_NOW			
		};
	bool currVal = flag_array[flag];
	if (set == -1) return currVal;

	assert(set == 0 || set == 1);
	flag_array[flag] = (set == 1);			
	return currVal; // just to supress warning.
}

int RVGlob::counters(counter_tag counter, int set /*= -1*/) {
	static int counter_array[GLBL_LAST_COUNTER] = {
		0 // GLBL_EXTERNAL_INPUT			
	};
	int curVal = counter_array[counter];
	if (set != -1)
		counter_array[counter] = set;
	return curVal;
}
		
RVGlobalUniqueId RVGlob::allocUniqId(size_t sizeofType) {
	RVGlobalUniqueId *pCounter = static_cast<RVGlobalUniqueId*>(getPtr(GLOB_ID_COUNTER));
	if (pCounter == NULL) {
		pCounter = new RVGlobalUniqueId;
		*pCounter = 0;
		pushPtr(GLOB_ID_COUNTER, pCounter);
	}
	static const size_t MAX_SIZEOF = 10000;
	if (sizeofType > MAX_SIZEOF)
		sizeofType = MAX_SIZEOF;
	RVGlobalUniqueId id = (*pCounter += MAX_SIZEOF) + sizeofType;
    return id;
}

void RVGlob::pushPtr(RvGlobtype typeId, void *ptr) {
	ms_globs[typeId].push(ptr);
}

void* RVGlob::popPtr(RvGlobtype typeId) {
	void *prev = getPtr(typeId);
	ms_globs[typeId].pop();
	return prev;
}

void* RVGlob::getPtr(RvGlobtype typeId) {
	return ms_globs[typeId].empty()? NULL : ms_globs[typeId].top();
}





/******************************************************************/
/* Implementation of methods of class Globals                     */
/******************************************************************/
struct ReplaceSpaceCharacter : public unary_function<string::reference, void> {
	ReplaceSpaceCharacter(const char with, string& src)
	  : m_substitution(with), m_resIt(src.begin()) {}

	void operator() (string::reference rC) {
		char c = rC;
		switch(rC) {
		case '\n': case '\r': return;
		case ' ':  case '\t': ; c = m_substitution;
		}
		*(m_resIt++) = c;
	}

private:
	const char m_substitution;
	string::iterator m_resIt;
};

/// <summary>
/// Returns legal filename without space characters
/// </summary>
/// <param name="base"> the base part of the filename </param>
/// <param name="extension"> the filename extension </param>
/// <param name="spaceSubstitution"> the character substituting space characters in the filename </param>
std::string Utils::mkFilename(const std::string& base,
			                  const std::string& extension,
			                  const char spaceSubstitution) {

	string s(base), ending(".");
	ending.append(extension);
	if (base.compare(base.length() - ending.length(), ending.length(), ending))
		s.append(ending);
	for_each(s.begin(), s.end(), ReplaceSpaceCharacter(spaceSubstitution, s));
	return s;
}

/// <summary>
/// Converts integer to string.
/// </summary>
/// <param name="n"> the integer </param>
std::string Utils::itoa(int n) {
	if (n == 0) return "0";

	std::string res;
	bool negative = n < 0;
	if (negative)
		n = -n;

	while (n > 0) {
		res.insert(0, 1, '0' + n % 10);
		n /= 10;
	}

	return negative? res.insert(0, 1, '-') : res;
}

/// <summary>
/// Replaces a character with a given string in a string.
/// </summary>
/// <param name="in"> the string whose characters are to be replaced </param>
/// <param name="what"> the character to be replaced </param>
/// <param name="with"> the substituting string </param>
void Utils::replaceCharInString(string& in, char what, const string& with) {
	size_t withLen = with.size();
	size_t pos = in.find_first_of(what);
	while (pos != in.npos) {
		in.replace(pos, 1, with);
		pos = in.find_first_of(what, pos + withLen);
	}
}

/// <summary>
/// Replaces a character with a given string in a string.
/// </summary>
/// <param name="in"> the string whose substring is to be replaced </param>
/// <param name="what"> the substring to be replaced </param>
/// <param name="with"> the substituting string </param>
void Utils::replaceSubstringInString(string& in, const string& what, const string& with) {
	size_t withLen = with.size();
	size_t pos = in.find(what);
	while (pos != in.npos) {
		in.replace(pos, what.size(), with);
		pos = in.find(what, pos + withLen);
	}
}

bool Utils::stringBeginsWith(const string& str, const string &prefix)
{
	size_t prefixLen = prefix.length();
	return str.length() >= prefixLen && !str.compare(0, prefixLen, prefix);
}


  /******************************************************************/
 /* Implementation of methods of class RVDischarger                */
/******************************************************************/
RVDischarger::~RVDischarger(void) {
	m_inDestructor = true;
	DischargeMap::iterator it;
	for (it = m_pDischargees.begin(); it != m_pDischargees.end(); ++it) {
		it->first->discharge(*this);
		if (it->second)
			delete it->first;
	}
}

void RVDischarger::addDischargee(RVIDischargee& dischargee) {
	m_pDischargees.insert(DischargeMap::value_type(&dischargee, false));
}

void RVDischarger::addDischargeeHeapPtr(RVIDischargee* pDischargee) {
    if (pDischargee != NULL)
	    m_pDischargees.insert(DischargeMap::value_type(pDischargee, true));
}

void RVDischarger::removeDischargeeByPtr(RVIDischargee* pDischargee) {
	if (!m_inDestructor)
		m_pDischargees.erase(pDischargee);
}



  /******************************************************************/
 /* Implementation of methods of class RVSide                      */
/******************************************************************/
RVSide::RVSide(int num) : m_index(num) {
	switch(num) {
	case 0: m_name = "0"; return;
	case 1: m_name = "1"; return;
	}

	badIndexError("RVSide(int)");
}

RVSide& RVSide::operator= (const RVSide& o) {
	m_name.assign(o.m_name);
	m_index = o.m_index;
	return *this;
}

int RVSide::index(void) const {
	if (isIllegalIndex())
		badIndexError("index()");
	return m_index;
}

string RVSide::toString(const char *prefix) const {
	return prefix && !m_name.empty() ? string(prefix) + m_name : m_name;
}

const char* RVSide::get_rvact_name(void) const {
  static const char* prefixes[] = {"RVSAVE", "RVCHECK"};
  if( isIllegalIndex() )
	  badIndexError("get_rvact_name()");
  return prefixes[m_index];
}

const char* RVSide::get_side_prefix(void) const {
  static const char* prefixes[] = {RV_SIDE0_PREFIX, RV_SIDE1_PREFIX};
  if( isIllegalIndex() )
	  badIndexError("get_side_prefix()");
  return prefixes[m_index];
}

const char* RVSide::get_side_ufprefix(void) const {
  static const char* prefixes[] = {RV_SIDE0_UFPREFIX, RV_SIDE1_UFPREFIX};
  if( isIllegalIndex() )
	  badIndexError("get_side_ufprefix()");
  return prefixes[m_index];
}

const char* RVSide::get_semchk_prefix(void) const {
  static const char* prefixes[] = {RV_SEMCHK0_PREFIX, RV_SEMCHK1_PREFIX};
  if( isIllegalIndex() )
	  badIndexError("get_semchk_prefix()");
  return prefixes[m_index];
}

string RVSide::insert_side_ufprefix(const string& id) const {
  std::string tmp( get_side_ufprefix() );
  tmp += id;
  return tmp;
}

const char* RVSide::get_main_prefix(bool semchk) const {
  return semchk ? get_semchk_prefix() : get_side_prefix();
}

void RVSide::badIndexError(const char *where) const {
	ostringstream err;
	err << "RVSide::" << where << " : illegal side number: " << m_index;
	fatal_error(err.str().data());
}

