/*******************************************************************\

Module: 

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <context.h>
#include <message.h>

#include <goto-programs/goto_functions.h>

void compare(
  const symbol_tablet &symbol_table,
  const goto_functionst &goto_functions,
  const irep_idt &f1, const irep_idt &f2,
  message_handlert &message_handler);

