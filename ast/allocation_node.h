// $Id: allocation_node.h,v 1.1 2016/03/16 22:16:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_ALLOCATION_NODE_H__
#define __ZU_ALLOCATION_NODE_H__

namespace zu {

  /**
   * Class for describing allocation nodes.
   */
  class allocation_node: public cdk::expression_node {
    cdk::expression_node *_size;

  public:
    inline allocation_node(int lineno, cdk::expression_node *size) :
        cdk::expression_node(lineno), _size(size) {
    }

  public:
    inline cdk::expression_node *size() {
      return _size;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_allocation_node(this, level);
    }

  };

} // zu

#endif
