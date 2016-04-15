#ifndef __ZU_FUNCTION_BODY_NODE_H__
#define __ZU_FUNCTION_BODY_NODE_H__

#include "function_declaration_node.h"
#include <string>

namespace zu {

  /**
   * Class function_body describing function nodes.
   */
  class function_body_node: public zu::function_declaration_node {
    cdk::basic_node *_block;

  public:
    inline function_body_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, args), _block(block) {
    }
    inline function_body_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, args), _block(block) {
    }
    inline function_body_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, cdk::sequence_node *args, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, args), _block(block) {
    }

	/* declaration constructor TODO correct ? */
	inline function_body_node(int lineno, zu::function_declaration_node *declaration, cdk::basic_node *block) :
		zu::function_declaration_node(lineno, declaration->zu_type(), new std::string(declaration->name()), declaration->isPublic()),  _block(block) {
    }

  public:
	inline basic_type zu_type() {
		return _zu_type;
	}

    inline std::string name() {
      return _name;
    }

	inline bool isPublic() {
		return _isPublic;
	}

    inline cdk::sequence_node *args() {
      return _args;
    }

    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_body_node(this, level);
    }

  };

} // zu

#endif
