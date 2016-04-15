#ifndef __ZU_FUNCTION_BODY_NODE_H__
#define __ZU_FUNCTION_BODY_NODE_H__

#include "function_declaration_node.h"
#include <string>

namespace zu {

  /**
   * Class function_body describing function nodes.
   */
  class function_body_node: public zu::function_declaration_node {
	zu::
    cdk::basic_node *_block;

  public:
    inline function_body_node(int lineno, const char *s, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, s, args), _block(block) {
    }
    inline function_body_node(int lineno, const std::string &s, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, s, args), _block(block) {
    }
    inline function_body_node(int lineno, const std::string *s, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, s, args), _block(block) {
    }

		/*
	inline function_body_node(int lineno, zu::function_declaration_node *declaration, cdk::basic_node *block) :
		function_body_node(lineno, declaration->
		*/

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
