#ifndef __ZU_FOR_NODE_H__
#define __ZU_FOR_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing while-cycle nodes.
   */
  class for_node: public cdk::basic_node {
    cdk::sequence_node *_init, *_test, *_step;
    cdk::basic_node *_block;

  public:
    inline for_node(int lineno, cdk::sequence_node *init,cdk::sequence_node *test,cdk::sequence_node *step, cdk::basic_node *block) :
        basic_node(lineno), _init(init),_test(test),_step(step), _block(block) {
    }

  public:
    inline cdk::sequence_node *init() {
      return _init;
    }
    inline cdk::sequence_node *test() {
      return _test;
    }
    inline cdk::sequence_node *step() {
      return _step;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_for_node(this, level);
    }

  };

} // zu

#endif
