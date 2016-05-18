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
    inline function_body_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, isImported, args, literal), _block(block) {
    }

    inline function_body_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, isImported, args, literal), _block(block) {
    }

    inline function_body_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal, cdk::basic_node *block) :
       zu::function_declaration_node(lineno, zu_type, s, isPublic, isImported, args, literal), _block(block) {
    }

	inline function_body_node(int lineno, zu::function_declaration_node *declaration, cdk::basic_node *block) :
		zu::function_declaration_node(lineno, declaration->zu_type(), new std::string(declaration->identifier()), declaration->isPublic(), declaration->isImported(), declaration->args(), declaration->literal()),  _block(block) {
    }

  public:
	inline basic_type *zu_type() {
		return _zu_type;
	}

    inline std::string identifier() {
      return _identifier;
    }

	inline bool isImported() {
		return _isImported;
	}

	inline bool isPublic() {
		return _isPublic;
	}

    inline cdk::sequence_node *args() {
      return _args;
    }

	inline cdk::expression_node *literal() {
		return _literal;
	}

    inline cdk::basic_node *block() {
      return _block;
    }

	inline zu::function_declaration_node *function_declaration() {
			return new zu::function_declaration_node(lineno(), zu_type(), new std::string(identifier()), isPublic(), isPublic(), args(), literal());

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_body_node(this, level);
    }

  };

} // zu

#endif
