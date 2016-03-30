// $Id: read_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_READ_NODE_H__
#define __ZU_READ_NODE_H__

namespace zu {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno, lvalue_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // zu

#endif
