#ifndef RV_DBG_H_
/*
 * rv_dbg.h
 *
 *  Created on: May 23, 2011
 *      Author: edima
 */

#define RV_DBG_H_

#include <iostream>
#include <sstream>

/* debug flags: */
/* ------------ */

typedef unsigned RVDebugFlagMask;
extern RVDebugFlagMask rv_debug_flags;
#define DBG ((rv_debug_flags & RV_SECTION) != 0)
#define RV_SEC_MAIN      00000001
#define RV_SEC_PARSE     00000002
#define RV_SEC_COMMANDS  00000004
#define RV_SEC_FUNCPAIR  00000010
#define RV_SEC_COLLECT   00000020
#define RV_SEC_REPLACE   00000040
#define RV_SEC_TREECOMP  00000100
#define RV_SEC_FUNCDFS   00000200
#define RV_SEC_FUNCNODE  00000400
#define RV_SEC_LOOPS     00001000
#define RV_SEC_GEN       00002000
#define RV_SEC_PROPAGATE 00004000
#define RV_SEC_TOKENS    00010000
#define RV_SEC_ARRAYS    00020000
#define RV_DBG_CALLGRAPH 00040000
#define RV_DBG_GRAPH     00100000
#define RV_SEC_DECOMPOSE 00200000
#define RV_SEC_STREAM    00400000



/* at the head of each .cpp file
   define RV_SECTION to the right value of the #defines above. */


// For ease of debug
//
#define DBG_INFO        dbgInfo(__FILE__, __FUNCTION__, __LINE__)
#define PRT_VAR(str, t) rv_errstrm << DBG_INFO << " " << str  << ":" << t << " \n"
#define PRT_NL          std::endl(rv_errstrm);

#ifdef RVT_OPTIMIZE
    #define tryRepProcBreakpoint(macro, where_)
    #define dbgInfo(file, function, line)
#else
    extern void tryRepProcBreakpoint(const char *macro, const std::string& where_);
    extern std::string dbgInfo(const char *file, const char *function, int line);
#endif

extern void breakOnSeq(const char* seq);

class Symbol;
class SymEntry;
class RVErrStreamBuf;

extern class RVErrStrm : public std::ostream {
public:
	RVErrStrm(void);
	RVErrStrm(std::ostream&);
	~RVErrStrm();

	void close(void);
	RVErrStrm& flush(void);
	std::string str(void) const;
	void str(const std::string&);

	virtual RVErrStrm& operator<< (const std::string&);
	virtual RVErrStrm& operator<< (const char *);
	virtual RVErrStrm& operator<< (const int);
	virtual RVErrStrm& operator<< (const unsigned);
	virtual RVErrStrm& operator<< (const long);
	virtual RVErrStrm& operator<< (const unsigned long);
	virtual RVErrStrm& operator<< (const float);
	virtual RVErrStrm& operator<< (const double);
	virtual RVErrStrm& operator<< (const char);
	virtual RVErrStrm& operator<< (const unsigned char);
	virtual RVErrStrm& operator<< (const Symbol *);
	virtual RVErrStrm& operator<< (const SymEntry *);

	bool tee(const std::string &filename, std::ios_base::openmode mode = std::ios_base::out);
	void untee(const std::string& filename);

private:
	RVErrStrm& spillOut(const std::string& s);

	template<typename T> RVErrStrm& printLow(const T& x) {
		std::ostringstream buf;
		buf << x;
        return spillOut(buf.str());
	}

	RVErrStreamBuf *m_pBuf;
} rv_errstrm;


/* abstract */ class RVStatus {
protected:
	RVStatus(void) {}
	void breakpoint(const char *sVal, const std::string &what, bool dbg) const;
};

class RVIntStatus : protected RVStatus {
public:
	explicit RVIntStatus(int status, const std::string &what = "", bool dbg = false);
	RVIntStatus(const RVIntStatus &);
	operator int (void) const;

private:
	int m_status;
};

class RVBoolStatus : protected RVStatus {
public:
	explicit RVBoolStatus(bool status, const std::string &what = "", bool dbg = false);
	RVBoolStatus(const RVBoolStatus &);
	RVBoolStatus& assign(bool, const std::string &where_, bool dbg);
	operator bool (void) const;

private:
	bool m_status;
};


#endif /* RV_DBG_H_ */
