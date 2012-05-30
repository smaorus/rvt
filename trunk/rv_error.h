#ifndef RV_ERROR_H
#define RV_ERROR_H

#include "rv_dbg.h"

extern std::ofstream rv_log;
void fatal_error(const char msg[], bool parsing = true );
void fatal_error(const char *msg, const std::string& more, bool parsing = true );
void warn(const std::string& msg, const std::string& where_);

#endif /* RV_ERROR_H */
