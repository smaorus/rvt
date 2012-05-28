#ifndef _RvTypeEqMac_h
#define _RvTypeEqMac_h

#include <ctool/decl.h>
#include <ctool/stemnt.h>
#include <ctool/project.h>
#include <ctool/express.h>
#include <ctool/symbol.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define SYM_2_TYPE(sym) sym->entry->uVarDecl->form
#define SYM_2_NAME(sym) sym->name

class RvTypeEqMac 
{
public:
  RvTypeEqMac(std::ostream &);

  std::ostream &out;
  int  link_depth; // for linked lists
  std::map<std::string, Type *> by_name;
  std::map<Type *, std::string> by_type;

  string convertInt(int number)
  {
      stringstream ss;//create a stringstream
      ss << number;//add number to the stream
      return ss.str();//return a string with the contents of the stream
  }

  void insert(string name, Type *t);
  string type_2_name(Type *t);
  Type* get_by_name(string name);

  string get_by_type(Type *ty)
  {
      std::map<Type*, std::string>::iterator i;
      std::string ret;

      i = by_type.find(ty);
      if( i == by_type.end() ) {ret =  "no_type";}
      else { ret = (*i).second;}

      ty->printType(out, NULL, true, 0);
      out << "ret = " << ret << "\n";

      return ret;
  }

  void gen_chk_code(Type *t, int array_sz, bool is_top );
  void create_enum();
  int  get_array_size(Expression *exp);

};

#endif


