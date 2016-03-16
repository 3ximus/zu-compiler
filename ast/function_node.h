#ifndef __ZU_FUNCTIONNODE_H__
#define __ZU_FUNCTIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class function describing function nodes.
   */
  class function_node: public cdk::expression_node {
    cdk::sequence_node *_args;
    cdk::basic_node *_block;

  public:
    inline function_node(int lineno, cdk::sequence_node *args, cdk::basic_node *block) :
        expression_node(lineno), _args(args), _block(block) {
    }

  public:
    inline cdk::sequence_node *args() {
      return _args;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_node(this, level);
    }

  };

} // zu

#endif
