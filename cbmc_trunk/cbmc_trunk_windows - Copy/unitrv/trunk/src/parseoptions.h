/*******************************************************************\

Module: Command Line Interface

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_UNITRV_PARSEOPTIONS_H
#define CPROVER_UNITRV_PARSEOPTIONS_H

#include <ui_message.h>
#include <parseoptions.h>
#include <options.h>

#include <goto-programs/goto_functions.h>
//#include <langapi/language_ui.h>

#define UNITRV_OPTIONS \
  "(function):" \
  "(debug-level):" \
  "(call-graph-dot):" \
  "(xml-ui)(claim):" \
  "(show-goto-functions)(show-claims)" \
  "(verbosity):(version)"

class unitrv_parseoptionst:
  public parseoptions_baset,
  public messaget
{
public:
  virtual int doit();
  virtual void help();

  unitrv_parseoptionst(
    int argc, const char **argv);

protected:
  virtual void register_languages();

  virtual void get_command_line_options(optionst &options);

  void set_verbosity(messaget &message);
  
  ui_message_handlert ui_message_handler;
};

#endif
