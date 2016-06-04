/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <type_eq.h>

#include <goto-symex/goto_symex.h>
#include <goto-symex/symex_target_equation.h>
#include <goto-symex/build_goto_trace.h>

#include <solvers/sat/satcheck.h>
#include <solvers/flattening/bv_pointers.h>
#include <expr_util.h>
#include <ansi-c/c_types.h>

#include "compare.h"

/*******************************************************************\

Function: make_auto_object

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

unsigned auto_object_counter=0;

exprt make_auto_object(
  const typet &type,
  symbol_tablet &new_symbol_table)
{
  auto_object_counter++;

  // produce auto-object symbol
  symbolt symbol;

  symbol.base_name="auto_object"+i2string(auto_object_counter);
  symbol.name="unitrv::"+id2string(symbol.base_name);
  symbol.is_lvalue=true;
  symbol.type=type;
  symbol.mode=ID_C; // C language

  new_symbol_table.add(symbol);

  return symbol_exprt(symbol.name, symbol.type);
}

/*******************************************************************\

// currently auto_object are either null or new addresses, i.e., no aliasing possible. To change, go to auto_objects.cpp: goto_symext::initialize_auto_object.

Function: initialize_input

  Inputs:

 Outputs:

 Purpose: adds constraints about inputs to the two fcuntions

\*******************************************************************/

void initialize_input( 
  const exprt &expr,
  const namespacet &ns,
  symbol_tablet &new_symbol_table,
  goto_programt &dest)
{
  static int my_array_counter = 0;
  const typet &type=ns.follow(expr.type()); // walks through typedefs etc.

  // if we want to allow sending array pointers, we need to catch them here, and replace their type with an infinite array.
  // declare a new object of type array and size inifinity. pass the address of the first element. 
  // array_typet at(p.subtype(), exprt(ID_infinity));  // p is the pointer; exprt is a constructor for expressions.
  // need to create an object of this type, and assign its first element to expr:
  // produce auto-object symbol
  //symbolt symbol;

  //symbol.base_name="myarray"+i2string(myarray_counter);
  //symbol.name="unitrv::"+id2string(symbol.base_name);
  //symbol.is_lvalue=true;
  //symbol.type=at;
  //symbol.mode=ID_C; // C language
  // new_symbol_table.add(symbol);
  // expr = index_exprt(symbol_exprt(symbol.name, symbol.type), gen_zero(index_type())); // more genrally there is from_integer(num,index_type()) where num is just a constant.
  
  if(type.id()==ID_pointer) // if it is not a pointer we do not do anything
  {
    const typet &subtype=ns.follow(type.subtype()); 
                    
    // we don't like function pointers and
    // we don't like void *
    if(subtype.id()!=ID_code && // function pointer
       subtype.id()!=ID_empty) // void pointer
    {
      #if 0
      if(true)
      {  // replace with code that identifies that it is actually a pointer to an array, e.g. with the argument name RVT_array_...    
        array_typet at(type.subtype(), exprt(ID_infinity));  // p is the pointer; exprt is a constructor for expressions.
        // need to create an object of this type, and assign its first element to expr:
        // produce symbol
        symbolt symbol;
        symbol.base_name="myarray"+i2string(my_array_counter);
        symbol.name="unitrv::"+id2string(symbol.base_name);
        symbol.is_lvalue=true;
        symbol.type=at;
        symbol.mode=ID_C; // C language
        new_symbol_table.add(symbol);
        address_of_exprt rhs = address_of_exprt(index_exprt(symbol_exprt(symbol.name, symbol.type), gen_zero(index_type()))); // more genrally there is from_integer(num,index_type()) where num is just a constant.
    
        goto_programt::targett t_s=  // adding a node to the cfg
          dest.add_instruction(ASSIGN); 
        t_s->code=code_assignt(expr, rhs); // assign the if expression declared above to the input.
        t_s->location=locationt();
        t_s->location.set_file("from pointer to array");
        return; // currently no support for an array pf pointers. So we have to assume that this is an array of other things; hence no auto_objects.
      }
      #endif
    
      address_of_exprt address_of_expr=
        address_of_exprt(make_auto_object(type.subtype(), new_symbol_table)); // the subtype is what the pointer points to. 

      // either NULL or an auto-object
      if_exprt rhs(  // produces an if expression
        nondet_exprt(bool_typet()), // nondet choice
        null_pointer_exprt(to_pointer_type(type)), // between null
        address_of_expr); // and the address of the auto_object

      goto_programt::targett t_s=
        dest.add_instruction(ASSIGN); 
      t_s->code=code_assignt(expr, rhs); // assign the if expression declared above to the input.
      t_s->location=locationt();
      t_s->location.set_file("harness-set-up-inputs");
    }
  }
}

/*******************************************************************\

Function: compare

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void compare(
  const symbol_tablet &symbol_table,
  const goto_functionst &goto_functions,
  const irep_idt &f1, const irep_idt &f2,
  message_handlert &message_handler)
{
  messaget message(message_handler);
  
  goto_functionst::function_mapt::const_iterator f_it1;
  goto_functionst::function_mapt::const_iterator f_it2;
  
  f_it1=goto_functions.function_map.find(f1); // function_map: mapping from functions names to a CFG of that function
  f_it2=goto_functions.function_map.find(f2);
  
  if(f_it1==goto_functions.function_map.end()) // not found
    throw std::string("failed to find ")+id2string(f1);

  if(f_it2==goto_functions.function_map.end())
    throw std::string("failed to find ")+id2string(f2);

  symbol_tablet new_symbol_table;  // symbol_tablet is a class mapping names to symbols, where symbol is one of {function, typedef, variable, ...}
  namespacet ns(symbol_table, new_symbol_table); // class for looking for symbols in symbol_tables (symbol_table = symbol table). The two parameters here are the symbol_tables in which to look. It will be used for mapping a string to symbol.
  
  const symbolt &symbol_f1=ns.lookup(f1); // look for f1 in ns (see above)
  const symbolt &symbol_f2=ns.lookup(f2);

  if(symbol_f1.type.id() != ID_code) 
    throw std::string("the command-line declared entry points are not functions");

  if(!type_eq(symbol_f1.type, symbol_f2.type, ns)) // checks equivalence of full signature (I + O), incl. parameters, return value.
    throw std::string("the types of the functions are different");
  
  const code_typet &code_type=
    to_code_type(symbol_f1.type); // an upward typecast, declaring it as a function type.
    
  exprt return_value=nil_exprt(); // initialization

  if(code_type.return_type()!=empty_typet()) 
  {
    // produce new symbol for return value
    symbolt new_symbol;
    new_symbol.base_name="$return_value";
    new_symbol.name="unitrv::"+id2string(new_symbol.base_name);
    new_symbol.type=code_type.return_type();
    new_symbol.is_argument=false;
    new_symbol.is_static_lifetime=true;
    new_symbol.is_state_var=true;
    
    return_value=new_symbol.symbol_expr();
    new_symbol_table.move(new_symbol);  // adding the new symbol to the symbol table. 
  }

  code_function_callt::argumentst args;
  
  args.reserve(code_type.arguments().size());

  std::set<irep_idt> argument_inputs;
  
  for(code_typet::argumentst::const_iterator
      it=code_type.arguments().begin();
      it!=code_type.arguments().end();
      it++)  // going over the arguments of the two functions
  {
    // look up
    const symbolt &symbol=ns.lookup(it->get_identifier());
    
    // produce new symbol // for each argument
    symbolt new_symbol=symbol; 
    new_symbol.base_name=id2string(symbol.base_name)+"$argument_input";
    new_symbol.name="unitrv::"+id2string(new_symbol.base_name);
    new_symbol.is_argument=false;
    new_symbol.is_static_lifetime=true;
    new_symbol.is_state_var=true;
    
    argument_inputs.insert(new_symbol.name);
    
    args.push_back(new_symbol.symbol_expr());
    new_symbol_table.move(new_symbol);
  }
  
  // call first function
  
  goto_programt tmp_test_harness1; // declaring a new program

  auto_object_counter=0;

  // we do some work on the input arguments
  for(code_function_callt::argumentst::const_iterator
      it=args.begin();
      it!=args.end();
      it++)
  {
    initialize_input(*it, ns, new_symbol_table, tmp_test_harness1); // initializes pointer arguments with auto_objects
  }

  code_function_callt call1; 
  call1.lhs()=return_value; 
  call1.arguments()=args;
  call1.function()=symbol_f1.symbol_expr();
  
  tmp_test_harness1.add_instruction(FUNCTION_CALL)->code=call1;
  tmp_test_harness1.add_instruction(END_FUNCTION);
  
  // call second function
  
  goto_programt tmp_test_harness2;

  code_function_callt call2;
  call2.lhs()=return_value;
  call2.arguments()=args;
  call2.function()=symbol_f2.symbol_expr();
  
  tmp_test_harness2.add_instruction(FUNCTION_CALL)->code=call2;
  tmp_test_harness2.add_instruction(END_FUNCTION);
  
  symex_target_equationt tmp_equation(ns); // symex_target_equationt is a list of constraints. ns is sent just that it can print the names later.
  goto_symext tmp_goto_symex(ns, new_symbol_table, tmp_equation); // produces ssa. 1st and 2nd arguments are the old and new symbol tables. The new one will be added additional symbols by the executer. 
  goto_symext::statet tmp_state;  // declaring the state of the symbolic executer.
  message.status("First symex 1"); 
  tmp_goto_symex(tmp_state, goto_functions, tmp_test_harness1); // do execution. tmp_state is only necessary because we want to execute two functions in a row, without restarting the counter. goto_functions are the input functions; tmp_test_harness is the generated program.
  tmp_state.new_frame();
  message.status("First symex 2");
  tmp_goto_symex(tmp_state, goto_functions, tmp_test_harness2); // same

  // now we know the modified globals,
  // because we did symbolic execution,
  // and can save them
  
  std::set<irep_idt> variables, modified;
  tmp_state.level2.get_variables(variables);  // there are 3 renaming levels: 0: threads, 1:functions, 2: ssa. // for example in a recrusve call we need to also rename locals.  
  
  for(std::set<irep_idt>::const_iterator   // iterate over those variables
      v_it=variables.begin();
      v_it!=variables.end();
      v_it++)
  {
    irep_idt original=tmp_state.get_original_name(*v_it);  
    if(original=="goto_symex::\\guard") continue;  // something internal
    if(argument_inputs.find(original)!=argument_inputs.end()) continue;
    const symbolt &symbol=ns.lookup(original); // look in the symbol_table
    std::cout << "Modified: " << symbol.name << std::endl; 
    modified.insert(symbol.name); // only modified (written-to) variables are renamed, hence they are in this list. 
  }

  goto_programt test_harness; // that will be the final produced program 
  locationt location;
  
  auto_object_counter=0;

  // we do some work on the input arguments
  for(code_function_callt::argumentst::const_iterator
      it=args.begin();
      it!=args.end();
      it++)
  {
    initialize_input(*it, ns, new_symbol_table, test_harness); // initializes pointer arguments with auto_objects
  }

  // constraints for global inputs
  for(std::set<irep_idt>::const_iterator
      v_it=modified.begin();
      v_it!=modified.end();
      v_it++)
  {
    const symbolt &symbol=ns.lookup(*v_it);
    if(symbol.base_name=="$return_value") continue;
    initialize_input(symbol.symbol_expr(), ns, new_symbol_table, test_harness); // same thing for global pointers (currently only for modified ones)
  }

  // save the global inputs
  for(std::set<irep_idt>::const_iterator  // all modified variables (altough not all of them are necessarily inputs, i.e., they are written-to before read)
      v_it=modified.begin();
      v_it!=modified.end();
      v_it++)
  {
    const symbolt &symbol=ns.lookup(*v_it);
    if(symbol.base_name=="$return_value") continue;

    // produce new symbol
    symbolt new_symbol=symbol;
    new_symbol.base_name=id2string(symbol.base_name)+"$global_input";
    new_symbol.name="unitrv::"+id2string(new_symbol.base_name);
    new_symbol.is_argument=false;
    new_symbol.is_static_lifetime=true;
    new_symbol.is_lvalue=true;
    new_symbol.is_state_var=true;
  
    exprt saved_value=new_symbol.symbol_expr();
    new_symbol_table.move(new_symbol);

    // save original // to be used with the second function
    goto_programt::targett t_s=
      test_harness.add_instruction(ASSIGN);
    t_s->code=code_assignt(saved_value, symbol.symbol_expr());
    t_s->location=location;
    t_s->location.set_file("harness-save-inputs");
  }

  // add call to f1
  test_harness.add_instruction(FUNCTION_CALL)->code=call1;

  for(std::set<irep_idt>::const_iterator  
      v_it=modified.begin();
      v_it!=modified.end();
      v_it++)   // iterating over modified variables, in order to save the output of f1.
  {
    const symbolt &symbol=ns.lookup(*v_it);

    // produce new symbol
    symbolt new_symbol=symbol;
    new_symbol.base_name=id2string(symbol.base_name)+"$f1_output";
    new_symbol.name="unitrv::"+id2string(new_symbol.base_name);
    new_symbol.is_argument=false;
    new_symbol.is_static_lifetime=true;
    new_symbol.is_lvalue=true;
    new_symbol.is_state_var=true;
  
    exprt f1_output=new_symbol.symbol_expr();
    new_symbol_table.move(new_symbol);

    // record output
    goto_programt::targett t_rec=
      test_harness.add_instruction(ASSIGN);
    t_rec->code=code_assignt(f1_output, symbol.symbol_expr());
    t_rec->location=location;
    t_rec->location.set_file("harness-save-outputs");

    if(symbol.base_name!="$return_value")
    {
      exprt original=
        ns.lookup("unitrv::"+id2string(symbol.base_name)+"$global_input").
          symbol_expr();

      // restore  // restoring the inputs
      goto_programt::targett t_res=
        test_harness.add_instruction(ASSIGN);
      t_res->code=code_assignt(symbol.symbol_expr(), original);
      t_res->location=location;
      t_res->location.set_file("harness-restore-inputs");
    }
  }

  // call f2
  test_harness.add_instruction(FUNCTION_CALL)->code=call2;

  for(std::set<irep_idt>::const_iterator
      v_it=modified.begin();
      v_it!=modified.end();
      v_it++) // comparing the outputs of f2 to the outputs of f1
  {
    const symbolt &symbol=ns.lookup(*v_it);

    exprt f1_output=
      ns.lookup("unitrv::"+id2string(symbol.base_name)+"$f1_output").
        symbol_expr();

    // compare
    goto_programt::targett t_c=
      test_harness.add_instruction(ASSERT);
    t_c->guard=equal_exprt(f1_output, symbol.symbol_expr()); // adds an equality 
    t_c->location=location;
    t_c->location.set_file("harness-assertions");
  }

  test_harness.add_instruction(END_FUNCTION);
  
  test_harness.update();
  
  std::cout << "Harness:" << std::endl;  
  test_harness.output(ns, "", std::cout); // printing the harness to the screen

  message.status("Symex on harness"); // now symbolically executing the harness
  goto_symex_statet state;
  symex_target_equationt equation(ns);
  goto_symext goto_symex(ns, new_symbol_table, equation);
  goto_symex(state, goto_functions, test_harness);

  std::cout << std::endl;  
  equation.output(std::cout);  
  std::cout << std::endl;  
  
  if(equation.count_assertions()==0)
  {
    message.result("PROGRAMS ARE EQUIVALENT");
    return;
  }

  satcheckt satcheck;
  satcheck.set_message_handler(message_handler);
  
  bv_pointerst dec(ns, satcheck);  // constructior: a decision procedure for the type bv+pointers+arrays
  dec.set_message_handler(message_handler);

  equation.convert(dec); // passing equation to the decision procedure. 
  
  switch(dec.dec_solve())  // solving
  {
  case decision_proceduret::D_UNSATISFIABLE:
    message.result("PROGRAMS ARE EQUIVALENT");
    break;

  case decision_proceduret::D_SATISFIABLE:
    message.result("PROGRAMS ARE NOT EQUIVALENT");

    message.status("Building error trace");

    {
      goto_tracet goto_trace;
      build_goto_trace(equation, dec, ns, goto_trace);  // dec will provide the assignment. 
      show_goto_trace(std::cout, ns, goto_trace); 
    }

    break;

  default:
    message.error("decision procedure failed");
  }
}

