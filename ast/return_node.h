// $Id: return_node.h,v 1.1 2016/03/17 17:58:35 ist169481 Exp $
#ifndef __ZU_RETURN_NODE_H__
#define __ZU_RETURN_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing return nodes.
   */
  class return_node: public cdk::expression_node {
	cdk::expression_node *_value;

  public:
    inline return_node(int lineno) :
        cdk::expression_node(lineno){
    }

    inline cdk::expression_node *value() {
      return _value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // zu

#endif
