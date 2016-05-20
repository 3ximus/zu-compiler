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

void zu::stack_allocator::do_variable_node(zu::variable_node * const node, int lvl) {
	_alloc += node->zu_type()->size();
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

void zu::stack_allocator::do_integer_node(cdk::integer_node * const node, int lvl){}
void zu::stack_allocator::do_double_node(cdk::double_node * const node, int lvl){}
void zu::stack_allocator::do_string_node(cdk::string_node * const node, int lvl){}
void zu::stack_allocator::do_neg_node(cdk::neg_node * const node, int lvl){}
void zu::stack_allocator::do_not_node(zu::not_node * const node, int lvl){}
void zu::stack_allocator::do_identity_node(zu::identity_node * const node, int lvl){}
void zu::stack_allocator::do_position_node(zu::position_node * const node, int lvl){}
void zu::stack_allocator::do_and_node(zu::and_node * const node, int lvl){}
void zu::stack_allocator::do_or_node(zu::or_node * const node, int lvl){}
void zu::stack_allocator::do_allocation_node(zu::allocation_node * const node, int lvl){}
void zu::stack_allocator::do_index_node(zu::index_node * const node, int lvl){}
void zu::stack_allocator::do_id_node(zu::id_node * const node, int lvl){}
void zu::stack_allocator::do_lvalue_node(zu::lvalue_node * const node, int lvl){}
void zu::stack_allocator::do_add_node(cdk::add_node * const node, int lvl){}
void zu::stack_allocator::do_sub_node(cdk::sub_node * const node, int lvl){}
void zu::stack_allocator::do_mul_node(cdk::mul_node * const node, int lvl){}
void zu::stack_allocator::do_div_node(cdk::div_node * const node, int lvl){}
void zu::stack_allocator::do_mod_node(cdk::mod_node * const node, int lvl){}
void zu::stack_allocator::do_lt_node(cdk::lt_node * const node, int lvl){}
void zu::stack_allocator::do_le_node(cdk::le_node * const node, int lvl){}
void zu::stack_allocator::do_ge_node(cdk::ge_node * const node, int lvl){}
void zu::stack_allocator::do_gt_node(cdk::gt_node * const node, int lvl){}
void zu::stack_allocator::do_ne_node(cdk::ne_node * const node, int lvl){}
void zu::stack_allocator::do_eq_node(cdk::eq_node * const node, int lvl){}
void zu::stack_allocator::do_function_declaration_node(zu::function_declaration_node * const node, int lvl){}
void zu::stack_allocator::do_evaluation_node(zu::evaluation_node * const node, int lvl){}
void zu::stack_allocator::do_print_node(zu::print_node * const node, int lvl){}
void zu::stack_allocator::do_read_node(zu::read_node * const node, int lvl){}
void zu::stack_allocator::do_assignment_node(zu::assignment_node * const node, int lvl){}
void zu::stack_allocator::do_break_node(zu::break_node * const node, int lvl){}
void zu::stack_allocator::do_continue_node(zu::continue_node * const node, int lvl){}
void zu::stack_allocator::do_return_node(zu::return_node * const node, int lvl){}
