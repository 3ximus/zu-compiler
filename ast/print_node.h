// $Id: print_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_PRINT_NODE_H__
#define __ZU_PRINT_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline print_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // zu

#endif
