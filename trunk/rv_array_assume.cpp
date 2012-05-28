using namespace std;

#include <rv_array_assume.h>
#include <rv_error.h>

#define DBG_ASS 0

std::string current_function;


RvArrAssume::RvArrAssume(std::ostream &os, bool d,RvTraversal *rv_traversal)
  : PrintTraversal(os,d), out(os), show_base(true)
{
    assumptions.clear();
    arrhooks   = rv_traversal;
    curr_ind   = 0;
    current_function = "";
}

void RvArrAssume::traverse_binary(BinaryExpr *node) {

    if (node->op() == BO_Member || node->op() == BO_PtrMember)  {
      node->leftExpr()->accept(this);
      if (node->op() == BO_Member) { out << "."; }
      else { out << "->";}
      node->rightExpr()->accept(this);
    } else {
      node->print(out);
    }
}


void RvArrAssume::traverse_index(IndexExpr *node) {
  Symbol *sym;
  string new_one;
  ofstream tmp_fl ("TMP_ass");
  ifstream tmp_fli;
  assume1  *new_ass;
  int      the_sz = 17;
  bool is_array = false, is_array_func = false;


  if ((is_array = arrhooks->is_array_exp(node->array,&sym)) || 
      (is_array_func = arrhooks->find_sym_func(sym,current_function,0,&the_sz)) ) {
      if (pass == 1) {

          if (DBG_ASS) {
              rv_errstrm << "is_array = " << is_array << " is_array_func = " << is_array_func << "\n";
              rv_errstrm << "pass == 1"  << "\n";
          }
          tmp_fl << "assume(";

          if (node->_subscript->etype != ET_UnaryExpr) {
              node->_subscript->print(tmp_fl);
          } else {
              UnaryExpr *tmp_exp = (UnaryExpr  *)  node->_subscript;

              if (RVCtool::is_unary_change(tmp_exp)) 
              { 
                  tmp_exp->_operand->print(tmp_fl);
              }
              else {
                  node->_subscript->print(tmp_fl);
              }
          }

          if (is_array) { tmp_fl << " < " << arrhooks->current_fixed_array_size << " && " ;}
          else  { rv_errstrm << "The sz" << the_sz << "\n"; tmp_fl << " < " << the_sz << " && " ;}

          if (node->_subscript->etype != ET_UnaryExpr) {
              node->_subscript->print(tmp_fl);
          } else {
              UnaryExpr *tmp_exp = (UnaryExpr  *)  node->_subscript;
              if (RVCtool::is_unary_change(tmp_exp)) 
              { 
                  tmp_exp->_operand->print(tmp_fl);
              }
              else {
                  node->_subscript->print(tmp_fl);
              }
          }

          tmp_fl << " >= 0 );\n";
          tmp_fl.close();
          tmp_fli.open("TMP_ass");
          getline(tmp_fli,new_one);
          if (new_one != "") {
            if (DBG_ASS) rv_errstrm << "adding at " << node->location.line << " " <<  new_one << "\n";
            new_ass = new assume1(node->location.line,new_one);
            assumptions.push_back(new_ass);
            system("rm TMP_ass");
            if (DBG_ASS) rv_errstrm << "assumptions.sz " << assumptions.size() << "\n";
          }
      }   
  }  else {
      if (DBG_ASS) {
          rv_errstrm << node->location.line << ": NOT Array !!!!:" ;
          node->array->print(rv_errstrm);
          rv_errstrm << "\n";
      }
  }

  if (node->array->precedence() < node->precedence())
  {
    out << "(";
    node->array->accept(this);
    out << ")";
  }
  else node->array->accept(this);

  out << "[";
  node->_subscript->accept(this);
  out << "]";
}

void RvArrAssume::traverse_function_definition(FunctionDef *node)
{
  current_function = (node->decl->name->name);
  traverse_decl(node->decl);
  traverse_block(node);
}


void RvArrAssume::block(Statement *node)
{
  if (!node)
  {
//    null(); //ofer
  } 
  else if (node->isBlock()) node->accept(this);
  else
  {
    Block *blk = new Block(node->location);
    blk->add(node->dup());
    LabelVector::const_iterator    j;
    for (j=node->labels.begin(); j != node->labels.end(); j++)
        blk->addLabel((*j)->dup());
    blk->accept(this);
  }
}

void RvArrAssume::insert_assumption(int line_num) {
  unsigned sz = assumptions.size();


  if ((unsigned) curr_ind >= sz) return;

  if (pass == 1 || sz == 0) return;

  if (DBG_ASS && pass == 2) rv_errstrm << line_num << "\n";


  while (((unsigned) curr_ind < sz) && 
          (line_num == assumptions[curr_ind]->line_nm) ) {
      if (DBG_ASS) {
          std::endl(rv_errstrm << "curr_ind: " << curr_ind << " sz : " << sz);
          rv_errstrm << "pass = 2 line found " << curr_ind << "\n";
          rv_errstrm << "line_num"  << assumptions[curr_ind]->line_nm <<
                  "the line " << assumptions[curr_ind]->line_str << "\n";
      }
      //indent();
      out << assumptions[curr_ind]->line_str << "\n";
      curr_ind++;
  }
}

void RvArrAssume::traverse_expression(ExpressionStemnt *node)
{

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  //indent();
  insert_assumption(node->location.line);
  assert(node->expression);
  node->expression->accept(this);
}

void RvArrAssume::traverse_return(ReturnStemnt *node)
{
  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  insert_assumption(node->location.line);

  //indent();
  out << "return";
  
  if (node->result)
  {
    out << ' ';
    node->result->accept(this);
  }
}


void RvArrAssume::traverse_if(IfStemnt *node)
{

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

//  indent();
  insert_assumption(node->location.line);

  out << "if (";
  node->cond->accept(this);
  out << ")\n";
  block(node->thenBlk);
  
  if (node->elseBlk)
  {
    out << std::endl;
  //  indent();
    out << "else\n";
    block(node->elseBlk);
  }
}

void RvArrAssume::traverse_switch(SwitchStemnt *node)
{
  
  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  insert_assumption(node->location.line);
  //indent();
  out << "switch (";
  node->cond->accept(this);
  out << ")\n";
  
  block(node->block);
}

void RvArrAssume::traverse_for(ForStemnt *node)
{

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  insert_assumption(node->location.line);
  //indent();
  out << "for (";
  if (node->init) node->init->accept(this);
  out << "; ";

  if (node->cond) node->cond->accept(this);
  out << "; ";

  if (node->incr) node->incr->accept(this);
  out << ")\n";

  block(node->block);
}

void RvArrAssume::traverse_while(WhileStemnt *node)
{

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  //indent();
  insert_assumption(node->location.line);
  out << "while (";
  node->cond->accept(this);
  out << ")\n";
  
  block(node->block);
}

void RvArrAssume::traverse_do_while(DoWhileStemnt *node)
{

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  //indent();
  insert_assumption(node->location.line);
  out << "do ";
  
  if (!node->block->isBlock())
    out << std::endl;
  
  block(node->block);
  if (!node->block->isBlock())
    out << std::endl;
  
  //indent();
  out << "while (";
  node->cond->accept(this);
  out << ")";
}


