// $Id: variable_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_VARIABLENODE_H__
#define __ZU_VARIABLENODE_H__

#include <string>
#include "lvalue_node.h"

namespace zu {

  /**
   * Class for describing variable nodes.
   */
  class variable_node: public lvalue_node {

  public:
    inline variable_node(int lineno, const std::string &s):
	lvalue_node(lineno,s) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
