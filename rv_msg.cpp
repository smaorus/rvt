/*
 * rv_msg.cpp
 *
 *  Created on: Jul 05, 2011
 *      Author: edima
 */

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <vector>
#include <map>
#include <sstream>
#include "rv_error.h"
#include "rv_msg.h"

using namespace std;

RV_LOC_MSGS_ENG_BEGIN
	{0, "Sample message: %0s.\n"},
RV_LOC_MSGS_ENG_END(NULL);

enum RVMsgArgType { MAT_String, MAT_Long, MAT_Double, MAT_Char, MAT_Ptr, MAT_Void };

const RvMsgArg RvMsgArg::RvMsgVoidArg;

RvMsgArg::RvMsgArg(const std::string& s) : m_type(MAT_String)
{
	m_pVal = new string(s);
}

RvMsgArg::RvMsgArg(const char *s) : m_type(MAT_String)
{
	m_pVal = new string(s);
}

RvMsgArg::RvMsgArg(long d) : m_type(MAT_Long)
{
	m_pVal = new long(d);
}

RvMsgArg::RvMsgArg(double f) : m_type(MAT_Double)
{
	m_pVal = new double(f);
}

RvMsgArg::RvMsgArg(char c) : m_type(MAT_Char)
{
	m_pVal = new char(c);
}

RvMsgArg::RvMsgArg(const void *p) : m_type(MAT_Ptr)
{
	m_pVal = const_cast<void*>(p);
}

RvMsgArg::RvMsgArg(const RvMsgArg& other)
  : m_type(other.m_type), m_pVal(other.m_pVal)
{
	if (m_pVal == NULL)
		return;

	switch(m_type) {
	case MAT_String: m_pVal = new string(other.toString()); return;
	case MAT_Long:   m_pVal = new long(other.toLong()); return;
	case MAT_Double: m_pVal = new double(other.toDouble()); return;
	case MAT_Char:   m_pVal = new char(other.toChar()); return;
	case MAT_Ptr:    return;
	case MAT_Void:
		if (m_pVal != NULL)
			fatal_error("RvMsgArg::RvMsgArg() : m_pVal != NULL for void RvMsgArg");
		return;
	default:
		fatal_error("RvMsgArg::~RvMsgArg() : unsupported m_type");
	}
}

RvMsgArg::RvMsgArg(void)
  : m_type(MAT_Void), m_pVal(NULL) {}

RvMsgArg::~RvMsgArg() {
	if (m_pVal != NULL)
		switch(m_type) {
		case MAT_String: delete static_cast<string*>(m_pVal); return;
		case MAT_Long:   delete static_cast<long*>(m_pVal); return;
		case MAT_Double: delete static_cast<double*>(m_pVal); return;
		case MAT_Char:   delete static_cast<char*>(m_pVal); return;
		case MAT_Ptr:    return;
		case MAT_Void:
			if (m_pVal != NULL)
				fatal_error("RvMsgArg::~RvMsgArg() : m_pVal != NULL for void RvMsgArg");
			return;
		default:
			fatal_error("RvMsgArg::~RvMsgArg() : unsupported m_type");
		}
}

RvMsgArg* RvMsgArg::clone(void) const {
	return new RvMsgArg(*this);
}

long RvMsgArg::toLong(void) const {
	assertValueType(MAT_Long);
	return *static_cast<const long*>(m_pVal);
}

char RvMsgArg::toChar(void) const {
	assertValueType(MAT_Char);
	return *static_cast<const char*>(m_pVal);
}

double RvMsgArg::toDouble(void) const {
	if (m_type == MAT_Long)
		return double(toLong());
	assertValueType(MAT_Double);
	return *static_cast<const double*>(m_pVal);
}

const std::string& RvMsgArg::toString(void) const {
	assertValueType(MAT_String);
	return *static_cast<const string*>(m_pVal);
}

const void *RvMsgArg::toPtr(void) const {
	if (m_type == MAT_Long)
		return (const void*)toLong();
	assertValueType(MAT_Ptr);
	return m_pVal;
}

void RvMsgArg::assertValueType(unsigned expected) const {
	assert(m_type == expected);
	assert(m_pVal != NULL);
}

bool RvMsgArg::isVoid(void) const {
	return m_type == MAT_Void;
}


static void streamOut(stringstream &buf, const RvMsgArg* a, const string &format, size_t typePos) {
	if (typePos >= format.length())
		fatal_error("streamOut() : a type identification character must follow %<digit>");
	switch(format.at(typePos)) {
	case 'l':
	case 'd': buf << a->toLong(); return;
	case 's': buf << a->toString().data(); return;
	case 'f': buf << a->toDouble(); return;
	case 'c': buf << a->toChar(); return;
	case 'x': buf << a->toPtr(); return;
	}

	stringstream errmsg(ios_base::out);
	errmsg << "streamOut() : an unrecognizable type identification character \'" << format.at(typePos) << "\'";
	fatal_error(errmsg.str().data());
}

static string parseMsg(const string &format, const vector<RvMsgArg*>& argv) {
	size_t pos = 0, latestStop = 0;
	stringstream buf(ios::out);
	while (latestStop < format.length() &&
		   (pos = format.find_first_of('%', latestStop)) != format.npos)
	{
		buf << format.substr(latestStop, pos - latestStop);
		latestStop = pos + 1;
		if (latestStop >= format.length())
			break;
		char c = format.at(latestStop);
		++latestStop;
		if (c == '%') {
			buf << c;
			continue;
		}
		if (isdigit(c))
			streamOut(buf, argv.at(c - '0'), format, latestStop++);
		else
			fatal_error("parseMsg() : % or a digit must follow %");
	}

	buf << format.substr(latestStop, format.length() - latestStop);
	return buf.str();
} 


typedef const RVIdMsgPair* (*RvMsgArrRetriever)();

static bool inEnglish(void) {
	return true;
}

typedef map<const char *, map<unsigned, string> > RVLocalMsgMap;

string RVMsgBase::retrieveMessageBase(bool rec) {
	static RVLocalMsgMap knownSourceFiles;

	RVLocalMsgMap::iterator it = knownSourceFiles.find(m_whereDefined);
    if (it != knownSourceFiles.end())
    	return it->second.at(m_id);

    if (rec)
    	fatal_error("RVMsgBase::retrieveMessageBase() : cannot find a message");

	RVLocalMsgMap::mapped_type& msgsOfFile = knownSourceFiles[m_whereDefined];
    if (inEnglish()) {
    	for (unsigned i = 0; i < m_nLocMsgs; ++i)
    		msgsOfFile.insert(
    			RVLocalMsgMap::mapped_type::value_type(m_locMsgsEng[i].m_id, string(m_locMsgsEng[i].m_msg)));
    }
    else
    	/* TODO load message file */;

	return retrieveMessageBase(true);
}

RVMsgBase::RVMsgBase(unsigned id,
					 const RVIdMsgPair* locMsgsEng,
					 unsigned n_locMsgs,
					 const char *whereDefined)
 : m_id(id),
   m_nLocMsgs(locMsgsEng == NULL ? sizeof(_RV_Local_Messages_Eng_)/sizeof(RVIdMsgPair) : n_locMsgs),
   m_locMsgsEng(locMsgsEng == NULL ? _RV_Local_Messages_Eng_ : locMsgsEng),
   m_whereDefined(whereDefined)
{
}

RVMsgBase::~RVMsgBase() {
	vector<RvMsgArg*>::iterator it;
	for(it = m_argv.begin(); it != m_argv.end(); ++it)
		delete *it;
}

void RVMsgBase::args(const RvMsgArg& a1, const RvMsgArg& a2,
                     const RvMsgArg& a3, const RvMsgArg& a4,
		             const RvMsgArg& a5)
{
	if (!a1.isVoid()) {
		m_argv.push_back(a1.clone());
		if (a2.isVoid()) {
			m_argv.push_back(a2.clone());
			if (a3.isVoid()) {
				m_argv.push_back(a3.clone());
				if (a4.isVoid()) {
					m_argv.push_back(a4.clone());
					if (a5.isVoid()) {
						m_argv.push_back(a5.clone());
					}
				}
			}
		}
	}

	const string format(retrieveMessageBase(false));
	m_out.assign(parseMsg(format, m_argv));
}
