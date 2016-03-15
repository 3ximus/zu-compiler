#ifndef __CDK_FORNODE_H__
#define __CDK_FORNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing while-cycle nodes.
   */
  class for_node: public cdk::basic_node {
    cdk::expression_node *_start_condition, *_stop_condition, *_step;
    cdk::basic_node *_block;

  public:
    inline for_node(int lineno, cdk::expression_node *start_condition,cdk::expression_node *stop_condition,cdk::expression_node *step cdk::basic_node *block) :
        basic_node(lineno), _start_condition(start_condition),_stop_condition(stop_condition),_step(step), _block(block) {
    }

  public:
    inline cdk::expression_node *start_condition() {
      return _start_condition;
    }
    inline cdk::expression_node *stop_condition() {
      return _stop_condition;
    }
    inline cdk::expression_node *step() {
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
