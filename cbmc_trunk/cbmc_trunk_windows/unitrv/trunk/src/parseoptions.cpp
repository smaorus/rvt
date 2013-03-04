/*******************************************************************\

Module: Command Line Interface

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <cstdlib>
#include <fstream>
#include <memory>
#include <iostream>

#include <i2string.h>
#include <config.h>
#include <symbol_table.h>

#include <langapi/mode.h>

#include <ansi-c/ansi_c_language.h>
#include <cpp/cpp_language.h>
#include <goto-programs/goto_convert_functions.h>
#include <goto-programs/goto_check.h>

#include "parseoptions.h"
#include "version.h"
#include "compare.h"

/*******************************************************************\

Function: unitrv_parseoptionst::unitrv_parseoptionst

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

unitrv_parseoptionst::unitrv_parseoptionst(
  int argc, const char **argv):
  parseoptions_baset(UNITRV_OPTIONS, argc, argv),
  ui_message_handler(
    cmdline.isset("xml-ui")?ui_message_handlert::XML_UI:ui_message_handlert::PLAIN,
    "Unitrv " UNITRV_VERSION)
{
}
  
/*******************************************************************\

Function: unitrv_parseoptionst::set_verbosity

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void unitrv_parseoptionst::set_verbosity(messaget &message)
{
  int v=8;
  
  if(cmdline.isset("verbosity"))
  {
    v=atoi(cmdline.getval("verbosity"));
    if(v<0)
      v=0;
    else if(v>9)
      v=9;
  }
  
  message.set_verbosity(v);
}

/*******************************************************************\

Function: unitrv_parseoptionst::get_command_line_options

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void unitrv_parseoptionst::get_command_line_options(optionst &options)
{
  if(config.set(cmdline))
  {
    usage_error();
    exit(1);
  }

  if(cmdline.isset("debug-level"))
    options.set_option("debug-level", cmdline.getval("debug-level"));

  #if 0
  // use assumptions instead of assertions?
  if(cmdline.isset("assert-to-assume"))
    options.set_option("assert-to-assume", true);
  else
    options.set_option("assert-to-assume", false);

  // check array bounds
  if(cmdline.isset("bounds-check"))
    options.set_option("bounds-check", true);
  else
    options.set_option("bounds-check", false);

  // check division by zero
  if(cmdline.isset("div-by-zero-check"))
    options.set_option("div-by-zero-check", true);
  else
    options.set_option("div-by-zero-check", false);

  // check overflow/underflow
  if(cmdline.isset("signed-overflow-check"))
    options.set_option("signed-overflow-check", true);
  else
    options.set_option("signed-overflow-check", false);

  // check overflow/underflow
  if(cmdline.isset("unsigned-overflow-check"))
    options.set_option("unsigned-overflow-check", true);
  else
    options.set_option("unsigned-overflow-check", false);

  // check for NaN (not a number)
  if(cmdline.isset("nan-check"))
    options.set_option("nan-check", true);
  else
    options.set_option("nan-check", false);

  // check pointers
  if(cmdline.isset("pointer-check"))
    options.set_option("pointer-check", true);
  else
    options.set_option("pointer-check", false);
  #else
  options.set_option("assert-to-assume", true);
  options.set_option("bounds-check", true);
  options.set_option("div-by-zero-check", true);
  options.set_option("signed-overflow-check", true);
  options.set_option("unsigned-overflow-check", false);
  options.set_option("pointer-check", true);
  #endif

  // check assertions
  options.set_option("assertions", true);

  // use assumptions
  options.set_option("assumptions", true);
}

/*******************************************************************\

Function: unitrv_parseoptionst::register_langauges

  Inputs:

 Outputs:

 Purpose: 

\*******************************************************************/

void unitrv_parseoptionst::register_languages()
{
  register_language(new_ansi_c_language);
  register_language(new_cpp_language);
}

/*******************************************************************\

Function: unitrv_parseoptionst::doit

  Inputs:

 Outputs:

 Purpose: invoke main modules

\*******************************************************************/

int unitrv_parseoptionst::doit()
{
  if(cmdline.isset("version"))
  {
    std::cout << UNITRV_VERSION << std::endl;
    return 0;
  }

  register_languages();

  // command line options

  optionst options;
  get_command_line_options(options);
  set_verbosity(*this);
  set_message_handler(ui_message_handler);

  if(cmdline.args.size()!=3)
  {
    usage_error();
    return 10;
  }

  ansi_c_languaget language;
  
  std::ifstream in(cmdline.args[0].c_str());
  
  if(!in)
  {
    error("failed to open "+cmdline.args[0]);
    return 10;
  }
  
  if(language.parse(in, cmdline.args[0], ui_message_handler))
    return 10;

  symbol_tablet symbol_table;

  if(language.typecheck(symbol_table, cmdline.args[0], ui_message_handler))
    return 10;

  //if(language.final(symbol_table, ui_message_handler))
  //  return 10;
  
  try
  {
    goto_functionst goto_functions;
    goto_convert(symbol_table, goto_functions, ui_message_handler); // converts programs to control-flow graphs
  
    // add checks for pointers, bounds, etc.
    {
      namespacet ns(symbol_table);
      goto_check(ns, options, goto_functions);
    }

    irep_idt f1="c::"+cmdline.args[1];
    irep_idt f2="c::"+cmdline.args[2];

    compare(symbol_table, goto_functions, f1, f2, ui_message_handler);
  }
  
  catch(const char *e)
  {
    error(e);
    return 10;
  }

  catch(const std::string &e)
  {
    error(e);
    return 10;
  }

  return 0;
}

/*******************************************************************\

Function: unitrv_parseoptionst::help

  Inputs:

 Outputs:

 Purpose: display command line help

\*******************************************************************/

void unitrv_parseoptionst::help()
{
  std::cout <<
    "\n"
    "* *           UNITRV " UNITRV_VERSION " - Copyright (C) 2012-2012           * *\n"
    "* *                     Daniel Kroening                     * *\n"
    "* *      Oxford University, Computer Science Department     * *\n"
    "* *                 kroening@kroening.com                   * *\n"
    "\n"
    "Usage:                       Purpose:\n"
    "\n"
    " unitrv [-?] [-h] [--help]    show help\n"
    " unitrv file.c f1 f2          compare functions f1 and f2\n"
    "\n"
    "Other options:\n"
    " --version                    show version and exit\n"
    "\n";
}
