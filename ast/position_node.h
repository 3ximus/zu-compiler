// $Id: position_node.h,v 1.2 2016/03/17 17:58:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_POSITION_NODE_H__
#define __ZU_POSITION_NODE_H__

#include "ast/lvalue_node.h"

namespace zu {

  /**
   * Class for describing assignment nodes.
   */
  class position_node: public cdk::expression_node {
    zu::lvalue_node *_lvalue;

  public:
    inline position_node(int lineno, zu::lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue) {
    }

  public:
    inline zu::lvalue_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_position_node(this, level);
    }

  };

} // zu

#endif
