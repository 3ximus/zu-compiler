#ifndef __ZU_FUNCTION_DECLARATION_NODE_H__
#define __ZU_FUNCTION_DECLARATION_NODE_H__

#include <string>

namespace zu {

  /**
   * Class function_declaration describing function nodes.
   */
  class function_declaration_node: public cdk::expression_node {
  protected:
	basic_type *_zu_type;
	std::string _identifier;
	bool _isPublic;
	bool _isImported;
    cdk::sequence_node *_args;
	cdk::expression_node *_literal;

  public:
    inline function_declaration_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal) :
        cdk::expression_node(lineno), _zu_type(zu_type), _identifier(s), _isPublic(isPublic), _isImported(isImported), _args(args), _literal(literal) {
    }
    inline function_declaration_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal) :
        cdk::expression_node(lineno), _zu_type(zu_type), _identifier(s), _isPublic(isPublic), _isImported(isImported), _args(args), _literal(literal) {
    }
    inline function_declaration_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, bool isImported, cdk::sequence_node *args, cdk::expression_node *literal) :
        cdk::expression_node(lineno), _zu_type(zu_type), _identifier(*s), _isPublic(isPublic), _isImported(isImported), _args(args), _literal(literal) {
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

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // zu

#endif
