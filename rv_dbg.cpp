/*
 * rv_dbg.cpp
 *
 *  Created on: Feb 3, 2012
 *      Author: edima
 */

#include <assert.h>
#include <string.h>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <map>
#include "ctool/decl.h"
#include "rv_dbg.h"
#include "rv_etc.h"

#define RV_SECTION RV_SEC_STREAM

using namespace std;


class RVErrStreamBuf : public stringbuf {
	typedef map<string, ostream*> RVErrStrmMap;

public:
    static void setBreakOnSeq(const char* seq) {
	    if (seq && strlen(seq) > 0) {
		    rv_debug_flags |= RV_SEC_STREAM;
		    RVErrStreamBuf::m_soughtSeq.assign(seq);
	    }
	    else
		    RVErrStreamBuf::m_soughtSeq.clear();
    }

	RVErrStreamBuf(void)
	  : m_forwardToSuper(true) {
		reset();
	}

	RVErrStreamBuf(ostream& strm)
	  : m_forwardToSuper(false) {
		reset();
		m_pTee[DEFAULT_STREAM_NAME] = &strm;
	}

    virtual ~RVErrStreamBuf() {
        //close();
    }

	void close(void) {
        forceXputsn();
		RVErrStrmMap::iterator it;
		for (it = m_pTee.begin(); it != m_pTee.end(); ++it)
			if (it->first != DEFAULT_STREAM_NAME)
				dynamic_cast<ofstream*>(it->second)->close();
			else
				it->second->flush();
	}

	void flush(void) {
        if (!m_inSpillOut)
            forceXputsn();
		RVErrStrmMap::iterator it;
		for (it = m_pTee.begin(); it != m_pTee.end(); ++it)
			it->second->flush();
	}

    void setStr(const std::string& initVal) {
	    str(initVal);
        reset();
    }

	bool tee(const string &filename, ios_base::openmode mode) {
		if (m_pTee.find(filename) != m_pTee.end())
			return false;

		m_pTee[filename] = new ofstream(filename.data(), mode);
		return true;
	}

	void untee(const string &filename) {
		RVErrStrmMap::iterator found = m_pTee.find(filename);
		if (found == m_pTee.end())
			return;
		untee(found);
	}

protected:
	virtual streamsize xsputn(const char *s, streamsize n) {
		m_inSpillOut = true;
		streamsize ret = stringbuf::xsputn(s, n);
		if (DBG) {
			string window = str();
			spillOut(window, s, n);
			searchForSeq(window, s, (size_t)(n));
			if(m_breakpointHit)
				breakpoint(s, n);
		}
        m_inSpillOut = false;
        return ret;
    }

    virtual int overflow(int c) {
        int ret = stringbuf::overflow(c);
        forceXputsn();
        return ret;
    }
private:
    void forceXputsn(void) {
    	if ( m_inSpillOut && (rv_debug_flags & RV_SEC_STREAM) )
    		return;
    	RVDebugFlagMask orig_rv_debug_flags = rv_debug_flags;
    	rv_debug_flags |= RV_SEC_STREAM;
        xsputn("", 0);
        rv_debug_flags = orig_rv_debug_flags;
    }

    void reset() {
        m_breakpointHit = m_inSpillOut = false;
        m_latestPos = UINT_MAX;
        m_lastKnowSize = 0;
    }

    void spillOut(const string & window, const char *s, streamsize n) {
        string unshown;
        size_t newSz = window.size() - m_lastKnowSize;
        if((streamsize)(newSz) > n) {
			unshown = window.substr(m_lastKnowSize);
			s = unshown.data();
			n = newSz;
		}
        else if (n == 0)
            return;

		RVErrStrmMap::iterator it;
		for (it = m_pTee.begin(); it != m_pTee.end(); ++it) {
			it->second->write(s, n);
            if (DBG) it->second->flush();
        }

		m_lastKnowSize = window.size();
	}

	void untee(RVErrStrmMap::iterator found) {
		delete found->second;
		m_pTee.erase(found);
	}

	void searchForSeq(const string& window, const char *s, size_t n) {
		if (m_soughtSeq.empty())
			return;
        if (m_latestPos == UINT_MAX)
            m_latestPos = 0;
		if (window.size() > n + m_soughtSeq.size())
			m_latestPos = max(m_latestPos, window.size()-n-m_soughtSeq.size());
		if (window.find(m_soughtSeq, m_latestPos) != string::npos) {
			m_breakpointHit = true;
            m_latestPos = window.rfind(m_soughtSeq) + 1;
        }
	}

	streamsize breakpoint(const char *s, streamsize n);

	static const string   DEFAULT_STREAM_NAME;
    static string         m_soughtSeq;
	bool                  m_forwardToSuper, m_breakpointHit;
	bool                  m_inSpillOut;
	size_t                m_latestPos, m_lastKnowSize;
    RVErrStrmMap          m_pTee;
};

string RVErrStreamBuf::m_soughtSeq;
const string RVErrStreamBuf::DEFAULT_STREAM_NAME;

streamsize RVErrStreamBuf::breakpoint(const char *s, streamsize n) {
	//static const string onHit("\n/************** HIT ***************/\n");
    m_breakpointHit = false;
	//streamsize ret = xsputn(onHit.data(), onHit.size());
    flush();
    return n;
}


void breakOnSeq(const char* seq) {
	RVErrStreamBuf::setBreakOnSeq(seq);
}



  /******************************************************************/
 /* Implementation of methods of class RVErrStrm                   */
/******************************************************************/
RVErrStrm rv_errstrm(std::cerr);

RVErrStrm::RVErrStrm(void)
  : ostream(new RVErrStreamBuf),
    m_pBuf(static_cast<RVErrStreamBuf*>(rdbuf()))
{
}

RVErrStrm::RVErrStrm(std::ostream& underlie)
  : ostream(new RVErrStreamBuf(underlie)),
    m_pBuf(static_cast<RVErrStreamBuf*>(rdbuf()))
{
}

RVErrStrm::~RVErrStrm() {
	close();
    delete m_pBuf;
}

void RVErrStrm::close(void) {
	m_pBuf->close();
}

RVErrStrm& RVErrStrm::flush(void) {
	m_pBuf->flush();
	return *this;
}

bool RVErrStrm::tee(const string &filename, ios_base::openmode mode) {
	return m_pBuf->tee(filename, mode);
}

void RVErrStrm::untee(const string &filename) {
	m_pBuf->untee(filename);
}

RVErrStrm& RVErrStrm::operator<< (const std::string& s) {
	return spillOut(s);
}

RVErrStrm& RVErrStrm::operator<< (const char *s) {
	return spillOut(s);
}

RVErrStrm& RVErrStrm::operator<< (const int v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const unsigned v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const long v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const unsigned long v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const float v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const double v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const char v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const unsigned char v) {
	return printLow(v);
}

RVErrStrm& RVErrStrm::operator<< (const Symbol *symb) {
	return symb? operator<< (symb->name) : operator<< ("NULL");
}

RVErrStrm& RVErrStrm::operator<< (const SymEntry *se) {
	return se? operator<< (se->name) : operator<< ("NULL");
}

string RVErrStrm::str(void) const {
	return m_pBuf->str();
}

void RVErrStrm::str(const std::string& initVal) {
	m_pBuf->setStr(initVal);
}

RVErrStrm& RVErrStrm::spillOut(const string& s) {
	m_pBuf->sputn(s.data(), s.size());
	return *this;
}



  /******************************************************************/
 /* Implementation of methods of class hierarchy RVStatus          */
/******************************************************************/
void RVStatus::breakpoint(const char *sVal, const string &what, bool dbg) const {
	if (dbg)
		rv_errstrm << "Warning: a suspecious value " <<  sVal << what << ".\n";
}


RVIntStatus::RVIntStatus(int status, const string &where_, bool dbg)
  : m_status(status)
{
	if (status != 0)
		breakpoint(Utils::itoa(status).append("is being returned by ").data(), where_, dbg);
}

RVIntStatus::RVIntStatus(const RVIntStatus &other)
  : m_status(other.m_status)
{}

RVIntStatus::operator int(void) const {
	return m_status;
}


RVBoolStatus::RVBoolStatus(bool status, const string &where_, bool dbg)
  : m_status(status)
{
	if (!status)
		breakpoint("false is being returned by ", where_, dbg);
}

RVBoolStatus::RVBoolStatus(const RVBoolStatus &other)
  : m_status(other.m_status)
{}

RVBoolStatus& RVBoolStatus::assign(bool v, const string &where_, bool dbg) {
	if (m_status && !v)
		breakpoint("false is being assigned in ", where_, dbg);
	m_status = v;
	return *this;
}

RVBoolStatus::operator bool(void) const {
	return m_status;
}



  /******************************************************************/
 /* Implementation of global functions                             */
/******************************************************************/
void tryRepProcBreakpoint(const char *macro, const string& where_) {
	static unsigned long counter = 0;
	++counter;
	rv_errstrm << where_
			   << " - either try_replace() or process() returned false (macro "
			   << macro <<")\n";
}

std::string dbgInfo(const char *file, const char *function, int line) {
	ostringstream buf;
	buf << file << "(" << function << "):" << line << " ";
	return buf.str();
}
