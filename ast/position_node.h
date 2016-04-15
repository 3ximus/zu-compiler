// $Id: position_node.h,v 1.2 2016/03/17 17:58:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_POSITION_NODE_H__
#define __ZU_POSITION_NODE_H__

#include "ast/lvalue_node.h"

namespace zu {

  /**
   * Class for describing referenece nodes.
   */
  class position_node: public cdk::unary_expression_node {

  public:
    inline position_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_position_node(this, level);
    }

  };

} // zu

#endif
