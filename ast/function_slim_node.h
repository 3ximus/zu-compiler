#ifndef __ZU_FUNCTION_SLIM_NODE_H__
#define __ZU_FUNCTION_SLIM_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class function_slim describing function nodes.
   */
  class function_slim_node: public cdk::expression_node {
    cdk::sequence_node *_args;

  public:
    inline function_slim_node(int lineno, cdk::sequence_node *args) :
        expression_node(lineno), _args(args) {
    }

  public:
    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_slim_node(this, level);
    }

  };

} // zu

#endif
