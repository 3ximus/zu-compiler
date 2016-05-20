#include <string>
#include "targets/stack_allocator.h"
#include <sstream>
#include "ast/all.h"

void zu::stack_allocator::do_sequence_node(cdk::sequence_node * const node, int lvl){
	for (size_t i = 0; i < node->size(); i++) node->node(i)->accept(this, lvl);
}
void zu::stack_allocator::do_block_node(zu::block_node * const node, int lvl){
	if(node->declarations() != NULL) node->declarations()->accept(this, lvl+1);
	if(node->instructions() != NULL) node->instructions()->accept(this, lvl+1);
}

//---------------------------------------------------------------------------

void zu::stack_allocator::do_variable_declaration_node(zu::variable_declaration_node * const node, int lvl) {
	_totalSize += node->type()->size();
}

void zu::stack_allocator::do_function_body_node(zu::function_body_node * const node, int lvl) {
	node->block()->accept(this, lvl+1);
}

void zu::stack_allocator::do_function_call_node(zu::function_call_node * const node, int lvl) {
	if(node->args()) node->args()->accept(this, lvl+1);
}

void zu::stack_allocator::do_for_node(zu::for_node * const node, int lvl) {
	if(node->init()) node->init()->accept(this, lvl+1);
	if(node->test()) node->test()->accept(this, lvl+1);
	if(node->step()) node->step()->accept(this, lvl+1);
	if(node->block()) node->block()->accept(this, lvl+1);
}

void zu::stack_allocator::do_if_node(zu::if_node * const node, int lvl) {
	if(node->block() != NULL) node->block()->accept(this, lvl+1);
}

void zu::stack_allocator::do_if_else_node(zu::if_else_node * const node, int lvl) {
	if(node->thenblock() != NULL) node->thenblock()->accept(this, lvl+1);
	if(node->elseblock() != NULL) node->elseblock()->accept(this, lvl+1);
}

