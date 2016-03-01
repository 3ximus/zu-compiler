// $Id: assignment_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_ASSIGNMENTNODE_H__
#define __ZU_ASSIGNMENTNODE_H__

#include "ast/lvalue_node.h"

namespace zu {

  /**
   * Class for describing assignment nodes.
   */
  class assignment_node: public cdk::expression_node {
    zu::lvalue_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline assignment_node(int lineno, zu::lvalue_node *lvalue, cdk::expression_node *rvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue), _rvalue(rvalue) {
    }

  public:
    inline zu::lvalue_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *rvalue() {
      return _rvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_assignment_node(this, level);
    }

  };

} // zu

#endif
