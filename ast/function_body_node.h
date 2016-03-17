#ifndef __ZU_FUNCTION_BODYNODE_H__
#define __ZU_FUNCTION_BODYNODE_H__

#include <cdk/ast/expression_node.h>
#include "function_slim_node.h"


namespace zu {

  /**
   * Class function_body describing function nodes.
   */
  class function_body_node: public function_slim_node {
    cdk::basic_node *_block;

  public:
    inline function_body_node(int lineno, cdk::sequence_node *args, cdk::basic_node *block) :
       function_slim_node(lineno, args), _block(block) {
    }

  public:
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_body_node(this, level);
    }

  };

} // zu

#endif
