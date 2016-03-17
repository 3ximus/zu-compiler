#ifndef __ZU_FUNCTION_BODY_NODE_H__
#define __ZU_FUNCTION_BODY_NODE_H__

#include "function_slim_node.h"
#include <string>

namespace zu {

  /**
   * Class function_body describing function nodes.
   */
  class function_body_node: public function_slim_node {
    cdk::basic_node *_block;

  public:
    inline function_body_node(int lineno, cdk::sequence_node *args, cdk::basic_node *block, const char *s) :
       function_slim_node(lineno, args, s), _block(block) {
    }
    inline function_body_node(int lineno, cdk::sequence_node *args, cdk::basic_node *block, const std::string &s) :
       function_slim_node(lineno, args, s), _block(block) {
    }
    inline function_body_node(int lineno, cdk::sequence_node *args, cdk::basic_node *block, const std::string *s) :
       function_slim_node(lineno, args, s), _block(block) {
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
