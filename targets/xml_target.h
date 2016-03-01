// $Id: xml_target.h,v 1.1 2016/02/19 19:29:48 david Exp $
#ifndef __ZU_SEMANTICS_XML_EVALUATOR_H__
#define __ZU_SEMANTICS_XML_EVALUATOR_H__

#include <cdk/basic_target.h>
#include <cdk/compiler.h>
#include "targets/xml_writer.h"

namespace zu {

  class xml_target: public cdk::basic_target {
    static xml_target _self;

  private:
    inline xml_target() :
        cdk::basic_target("xml") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      // this symbol table will be used to check identifiers
      // an exception will be thrown if identifiers are used before declaration
      cdk::symbol_table<zu::symbol> symtab;

      xml_writer writer(compiler, symtab);
      compiler->ast()->accept(&writer, 0);
      return true;
    }

  };

} // zu

#endif
