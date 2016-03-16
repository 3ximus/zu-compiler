// $Id: and_node.h,v 1.1 2016/03/16 22:16:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_ANDNODE_H__
#define __ZU_ANDNODE_H__

namespace zu {

  /**
   * Class for describing and nodes.
   */
  class and_node: public cdk::binary_expression_node {

  public:
    inline and_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
        binary_expression_node(lineno, lvalue, rvalue) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_and_node(this, level);
    }

  };

} // zu

#endif
