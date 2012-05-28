#ifndef     RV_ARRAY_ASSUME_H
#define     RV_ARRAY_ASSUME_H

#include    <cstdio>
#include    <iostream>
#include    <string>
#include    <fstream>
#include    <sstream>
#include    <vector>
#include    <list>
#include    <cstring>
#include    <cstdlib>
#include    <cassert>
#include    <algorithm>
#include    <vector>

#include <ctool/decl.h>
#include <ctool/stemnt.h>
#include <ctool/project.h>
#include <ctool/express.h>
#include <ctool/symbol.h>
#include <ctool/Traversal.h>
#include <ctool/PrintTraversal.h>
#include <rv_ctool.h>
#include <rv_traversal.h>

class assume1 {
    public:
    std::string line_str;
    int    line_nm;

    assume1(int l_nm, std::string l_str)
    {
        line_nm = l_nm;
        line_str= l_str;
    }
    ~assume1() {}
};

class RvArrAssume : public PrintTraversal {
public:     
  RvArrAssume(std::ostream &, bool, RvTraversal *);
  virtual void traverse_binary(BinaryExpr *);
  virtual void traverse_function_definition(FunctionDef *node);
  virtual void traverse_index(IndexExpr *node);
  virtual void block(Statement *);
  virtual void traverse_expression(ExpressionStemnt *);
  virtual void traverse_if(IfStemnt *);
  virtual void traverse_switch(SwitchStemnt *);
  virtual void traverse_for(ForStemnt *);
  virtual void traverse_while(WhileStemnt *);
  virtual void traverse_do_while(DoWhileStemnt *);
  virtual void traverse_return(ReturnStemnt *node);
  void    insert_assumption(int line_num) ;
  RvTraversal *arrhooks;
  int         curr_ind;
  int         pass;
  std::vector<assume1 *> assumptions;
  void set_pass(int p) {pass = p;}
  ~RvArrAssume() {}
private:
  std::ostream &out;
  bool show_base;

};

/*  ###############################################################  */

#endif     /* RV_ARRAY_ASSUME_H */
