/*
 * rv_options.h
 *
 *  Created on: Feb 10, 2011
 *      Author: edima
 */

#ifndef RV_OPTIONS_H_
#define RV_OPTIONS_H_

#include <rv_main.h>

class RVOptions : public RVMain {
public:
	RVOptions(int argc, char* const argv[]);
	virtual ~RVOptions() { delete m_pLog; delete &accessDirectives(); }

	int getErrorStatus(void) const;
	bool readyToRun(void) const;

private:
	void print_options(void);
	void print_help(const char *prog_name) const;
	bool parse_options(int argc, char* const argv[]);
	int  detectPathDelimiter(const char *arg0);
	void detectRvtPath(const char *arg0);
	bool isStringFieldInitialized(const std::string& field) const;

	bool        m_bOk;
	std::string m_pathDelim;
};

#endif /* RV_OPTIONS_H_ */
