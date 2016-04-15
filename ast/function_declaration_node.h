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
	std::string *_name;
    cdk::sequence_node *_args;
	bool _isPublic;

  public:
    inline function_declaration_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _zu_type(zu_type), _name(s), _isPublic(isPublic), _args(args) {
    }
    inline function_declaration_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _zu_type(zu_type), _name(s), _isPublic(isPublic), _args(args) {
    }
    inline function_declaration_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _zu_type(zu_type), _name(*s), _isPublic(isPublic), _args(args) {
    }

  public:
	inline basic_type *zu_type() {
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


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // zu

#endif
