/*Anjana Kummetha
117162837*/

#include "unit_tests.h"

TestSuite(student_tests, .timeout=TEST_TIMEOUT); 




/*Testing add_mats_sf*/

//adds two 2x3 matrices with mixed positive and negative values
Test(student_tests, add_rectangular_mixed_values ) 
{
    matrix_sf *A = copy_matrix(2, 3, (int[]){4, -2, 7, 0, 5, -1});
    matrix_sf *B = copy_matrix(2, 3, (int[]){-3, 8, 1, 6, -5, 2});

    matrix_sf *C = add_mats_sf(A, B);

    expect_matrices_equal(C, 2, 3, (int[]){1, 6, 8, 6, 0, 1});

    free(A);
    free(B);
    free(C);
}

//adds two 1x4 matrices where some elements cancel to zero
Test(student_tests, add_single_row_with_zeros) {
    matrix_sf *A = copy_matrix(1, 4, (int[]){0, -3, 5, 0});
    matrix_sf *B = copy_matrix(1, 4, (int[]){7, 3, -5, 2});

    matrix_sf *C = add_mats_sf(A, B);

    expect_matrices_equal(C, 1, 4, (int[]){7, 0, 0, 2});

    free(A);
    free(B);
    free(C);
}

//adds two 4x1 matrices where most values cancel to zero
Test(student_tests, add_single_column_with_canceling_values) {
    matrix_sf *A = copy_matrix(4, 1, (int[]){1, -2, 3, -4});
    matrix_sf *B = copy_matrix(4, 1, (int[]){5, 2, -3, 4});

    matrix_sf *C = add_mats_sf(A, B);

    expect_matrices_equal(C, 4, 1, (int[]){6, 0, 0, 0});

    free(A);
    free(B);
    free(C);
}

//adds a zero matrix to a nonzero matrix, result equals nonzero matrix
Test(student_tests, add_zero_matrix_to_nonzero_matrix) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){0, 0, 0, 0});
    matrix_sf *B = copy_matrix(2, 2, (int[]){9, -1, 4, -6});

    matrix_sf *C = add_mats_sf(A, B);

    expect_matrices_equal(C, 2, 2, (int[]){9, -1, 4, -6});

    free(A);
    free(B);
    free(C);
}

//adding matrices of different dimensions returns null
Test(student_tests, add_dimension_mismatch_returns_null) {
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4});
    matrix_sf *B = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});

    matrix_sf *C = add_mats_sf(A, B);

    cr_expect_eq(C, NULL);

    free(A);
    free(B);
}







/* Testing mult_mats_sf */

//multiplies a 2x3 by a 3x2 matrix to get a 2x2 result
Test(student_tests, mult_basic_rectangular) {
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = copy_matrix(3, 2, (int[]){7, 8, 9, 10, 11, 12});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 2, 2, (int[]){58, 64, 139, 154});
    free(A); free(B); free(C);
}

//multiplies a 3x1 column vector by a 1x3 row vector to get a 3x3 outer product
Test(student_tests, mult_vector_outer_product) {
    matrix_sf *A = copy_matrix(3, 1, (int[]){2, -1, 4});
    matrix_sf *B = copy_matrix(1, 3, (int[]){5, 0, -2});
    matrix_sf *C = mult_mats_sf(A, B);
    expect_matrices_equal(C, 3, 3, (int[]){10, 0, -4, -5, 0, 2, 20, 0, -8});
    free(A); free(B); free(C);
}

//multiplying a matrix by the identity matrix returns the original
Test(student_tests, mult_by_identity) {
    matrix_sf *A = copy_matrix(3, 3, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix_sf *I = copy_matrix(3, 3, (int[]){1, 0, 0, 0, 1, 0, 0, 0, 1});
    matrix_sf *C = mult_mats_sf(A, I);
    expect_matrices_equal(C, 3, 3, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    free(A); free(I); free(C);
}

//multiplies a 1x3 by a 3x1 to get a 1x1 dot product result
Test(student_tests, mult_dot_product_1x1_result) {
    matrix_sf *A = copy_matrix(1, 3, (int[]){2, -1, 4});
    matrix_sf *B = copy_matrix(3, 1, (int[]){3, 5, -2});
    matrix_sf *C = mult_mats_sf(A, B);
    /* 2*3 + (-1)*5 + 4*(-2) = 6 - 5 - 8 = -7 */
    expect_matrices_equal(C, 1, 1, (int[]){-7});
    free(A); free(B); free(C);
}

//multiplying any matrix by the zero matrix yields the zero matrix
Test(student_tests, mult_by_zero_matrix) 
{
    matrix_sf *A = copy_matrix(2, 2, (int[]){5, -3, 8, 2});
    matrix_sf *Z = copy_matrix(2, 2, (int[]){0, 0, 0, 0});
    matrix_sf *C = mult_mats_sf(A, Z);
    expect_matrices_equal(C, 2, 2, (int[]){0, 0, 0, 0});
    free(A); free(Z); free(C);
}







/* Testing transpose_mat_sf */

//transposes a 3x2 matrix into a 2x3 matrix
Test(student_tests, transpose_non_square) {
    matrix_sf *A = copy_matrix(3, 2, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *B = transpose_mat_sf(A);
    expect_matrices_equal(B, 2, 3, (int[]){1, 3, 5, 2, 4, 6});
    free(A); free(B);
}

//transposes a 1x4 row into a 4x1 column
Test(student_tests, transpose_single_row_to_column) {
    matrix_sf *A = copy_matrix(1, 4, (int[]){7, -2, 0, 5});
    matrix_sf *B = transpose_mat_sf(A);
    expect_matrices_equal(B, 4, 1, (int[]){7, -2, 0, 5});
    free(A); free(B);
}

//transposes a 3x3 square matrix across its diagonal
Test(student_tests, transpose_square_matrix) {
    matrix_sf *A = copy_matrix(3, 3, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix_sf *B = transpose_mat_sf(A);
    expect_matrices_equal(B, 3, 3, (int[]){1, 4, 7, 2, 5, 8, 3, 6, 9});
    free(A); free(B);
}

//transposes a 3x1 column into a 1x3 row
Test(student_tests, transpose_single_column_to_row) {
    matrix_sf *A = copy_matrix(3, 1, (int[]){-5, 10, 0});
    matrix_sf *B = transpose_mat_sf(A);
    expect_matrices_equal(B, 1, 3, (int[]){-5, 10, 0});
    free(A); free(B);
}

//transposing twice returns the original matrix
Test(student_tests, transpose_double_returns_original) {
    matrix_sf *A  = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *T  = transpose_mat_sf(A);
    matrix_sf *TT = transpose_mat_sf(T);
    expect_matrices_equal(TT, 2, 3, (int[]){1, 2, 3, 4, 5, 6});
    free(A); free(T); free(TT);
}





/* Testing create_matrix_sf */

//parses a 2x3 matrix string with spaces and negative values
Test(student_tests, create_matrix_with_spacing_and_negatives) {
    matrix_sf *A = create_matrix_sf('A', "2 3 [ 1 -2 3 ; 4 0 -6 ; ]" );

    expect_matrices_equal(A, 2, 3, (int[]){1, -2, 3, 4, 0, -6});
    cr_expect_eq(A->name, 'A');
    free(A);
}

//parses a 4x1 single-column matrix string
Test(student_tests, create_single_column_matrix) {
    matrix_sf *B = create_matrix_sf('B', "4 1 [ 9 ; -1 ; 0 ; 5 ; ]");
    expect_matrices_equal(B, 4, 1, (int[]){9, -1, 0, 5});
    cr_expect_eq(B->name, 'B');
    free(B);
}

//parses a 1x5 single-row matrix string
Test(student_tests, create_single_row_matrix) {
    matrix_sf *C = create_matrix_sf('C', "1 5 [ 3 -7 0 12 -4 ; ]");
    expect_matrices_equal(C, 1, 5, (int[]){3, -7, 0, 12, -4});
    cr_expect_eq(C->name, 'C');
    free(C);
}

//parses a 3x3 matrix string with no spaces around semicolons
Test(student_tests, create_matrix_no_spaces_around_semicolons) {
    matrix_sf *D = create_matrix_sf('D', "3 3 [1 2 3;4 5 6;7 8 9;]");
    expect_matrices_equal(D, 3, 3, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    cr_expect_eq(D->name, 'D');
    free(D);
}

//parses a 1x1 matrix string with a single negative value
Test(student_tests, create_1x1_matrix) {
    matrix_sf *E = create_matrix_sf('E', "1 1 [ -42 ; ]");
    expect_matrices_equal(E, 1, 1, (int[]){-42});
    cr_expect_eq(E->name, 'E');
    free(E);
}






/* Testing insert_bst_sf */
//inserts three nodes and verifies each can be found by name
Test(student_tests, bst_insert_and_find_existing) {
    bst_sf *root = NULL;
    matrix_sf *M = copy_matrix(1, 1, (int[]){1}); M->name = 'M';
    matrix_sf *A = copy_matrix(1, 1, (int[]){2}); A->name = 'A';
    matrix_sf *Z = copy_matrix(1, 1, (int[]){3}); Z->name = 'Z';
    root = insert_bst_sf(M, root);
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(Z, root);
    cr_expect_eq(find_bst_sf('M', root), M);
    cr_expect_eq(find_bst_sf('A', root), A);
    cr_expect_eq(find_bst_sf('Z', root), Z);
    free_bst_sf(root);
}

//inserting one node creates a root with no children
Test(student_tests, bst_insert_single_node_becomes_root) {
    bst_sf *root = NULL;
    matrix_sf *K = copy_matrix(1, 1, (int[]){7}); K->name = 'K';
    root = insert_bst_sf(K, root);
    cr_expect_neq(root, NULL);
    cr_expect_eq(root->mat, K);
    cr_expect_eq(root->left_child, NULL);
    cr_expect_eq(root->right_child, NULL);
    free_bst_sf(root);
}

//a node with a smaller name goes to the left child
Test(student_tests, bst_insert_smaller_goes_left) {
    bst_sf *root = NULL;
    matrix_sf *M = copy_matrix(1, 1, (int[]){1}); M->name = 'M';
    matrix_sf *A = copy_matrix(1, 1, (int[]){2}); A->name = 'A';
    root = insert_bst_sf(M, root);
    root = insert_bst_sf(A, root);
    /* A < M so A must be left child of M */
    cr_expect_neq(root->left_child, NULL);
    cr_expect_eq(root->left_child->mat, A);
    free_bst_sf(root);
}

//a node with a larger name goes to the right child
Test(student_tests, bst_insert_larger_goes_right) 
{
    bst_sf *root = NULL;
    matrix_sf *M = copy_matrix(1, 1, (int[]){1}); M->name =  'M' ;
    matrix_sf *Z = copy_matrix(1, 1, (int[]){2}); Z->name = 'Z';
    root = insert_bst_sf(M, root);
    root = insert_bst_sf(Z, root);
    /* Z > M so Z must be right child of M */
    cr_expect_neq(root->right_child, NULL);
    cr_expect_eq(root->right_child->mat, Z);
    free_bst_sf(root);
}

//inserts eight nodes and verifies all are findable in correct bst order
Test(student_tests, bst_insert_many_maintains_sorted_order) {
    bst_sf *root =  NULL;
    char names[] = "GTHRNBVC";
    matrix_sf *mats[8];
    for (int i = 0; i < 8; i++) {
        mats[i] = copy_matrix(1, 1, (int[]){i});
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    for (int i = 0; i < 8; i++)
        cr_expect_eq(find_bst_sf(names[i], root), mats[i]);
    free_bst_sf(root);
}






/* Testing find_bst_sf */

//searching for a name not in the tree returns null
Test( student_tests, bst_find_missing_returns_null) {
    bst_sf *root = NULL;
    matrix_sf *B = copy_matrix(1, 1, (int[]){4}); B->name = 'B';
    root = insert_bst_sf(B, root);
    cr_expect_eq(find_bst_sf('Q', root), NULL);
    free_bst_sf(root);
}

//searching an empty tree returns null
Test(student_tests, bst_find_absent_in_empty_tree) {
    cr_expect_eq(find_bst_sf('X', NULL), NULL);
}

//finding the root node returns the correct matrix pointer
Test(student_tests, bst_find_root_node) {
    bst_sf *root = NULL;
    matrix_sf *P = copy_matrix(1, 1, (int[]){5}); P->name = 'P';
    root = insert_bst_sf(P, root);
    cr_expect_eq(find_bst_sf('P', root), P);
    free_bst_sf(root);
}

//finds both a left and right child by name
Test(student_tests, bst_find_left_and_right_children) {
    bst_sf *root = NULL;
    matrix_sf *M = copy_matrix(1, 1, (int[]){1}); M->name = 'M';
    matrix_sf *A = copy_matrix(1, 1, (int[]){2}); A->name = 'A';
    matrix_sf *Z = copy_matrix(1, 1, (int[]){3}); Z->name = 'Z';
    root = insert_bst_sf(M, root);
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(Z, root);
    cr_expect_eq(find_bst_sf('A', root), A);
    cr_expect_eq(find_bst_sf('Z', root), Z);
    free_bst_sf(root);
}

//find returns the exact matrix pointer and its contents are correct
Test(student_tests, bst_find_returns_correct_matrix_pointer) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4}); A->name =  'A';
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8}); B->name = 'B';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    matrix_sf *found = find_bst_sf('B', root);
    cr_expect_eq(found, B);
    expect_matrices_equal(found, 2, 2, (int[]){5, 6, 7, 8});
    free_bst_sf(root);
}









/* Testing free_bst_sf */

//frees a single-node bst with no memory errors
Test(student_tests, free_bst_single_node) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst01"));
}

//frees a multi-node bst with no memory errors
Test(student_tests, free_bst_multiple_nodes) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst02"));
}

//frees a full bst with no memory errors
Test(student_tests, free_bst_full_tree) {
    expect_no_valgrind_errors(run_with_valgrind("free_bst03"));
}

//freeing a null root does not crash
Test(student_tests, free_bst_null_root_no_crash) {
    free_bst_sf(NULL);
    cr_expect(1);
}

//inserting three nodes then freeing causes no leaks
Test(student_tests, free_bst_no_leak_after_insert) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4}); A->name = 'A';
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8}); B->name = 'B';
    matrix_sf *C = copy_matrix(2, 2, (int[]){9, 10, 11, 12}); C->name = 'C';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    root = insert_bst_sf(C, root);
    free_bst_sf(root);
    cr_expect(1);
}







/* Testing infix2postfix_sf */

//converts simple a+b infix to ab+ postfix
Test(student_tests, postfix_simple_add) {
    char *actual = infix2postfix_sf("A+B");
    cr_expect_str_eq(actual, "AB+");
    free(actual);
}

//multiplication has higher precedence than addition
Test(student_tests, postfix_precedence_mult_over_add) {
    char *actual = infix2postfix_sf("A+B*C");
    cr_expect_str_eq(actual, "ABC*+");
    free(actual);
}

//parentheses and transpose operator are handled correctly
Test(student_tests, postfix_parentheses_and_transpose) {
    char *actual = infix2postfix_sf("(A+B)'*C");
    cr_expect_str_eq(actual, "AB+'C*");
    free(actual);
}

//single transpose on one matrix converts correctly
Test(student_tests, postfix_single_transpose) {
    char *actual = infix2postfix_sf("A'");
    cr_expect_str_eq(actual, "A'");
    free(actual);
}

//parentheses on both sides of multiplication convert correctly
Test(student_tests, postfix_paren_both_sides) {
    char *actual = infix2postfix_sf("(A+B)*(C+D)");
    cr_expect_str_eq(actual, "AB+CD+*");
    free(actual);
}






/* Testing evaluate_expr_sf */

//evaluates a+b expression and returns the correct sum matrix
Test(student_tests, evaluate_simple_add) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4}); A->name = 'A';
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8}); B->name = 'B';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    matrix_sf *C = evaluate_expr_sf('C', "A + B", root);
    expect_matrices_equal(C, 2, 2, (int[]){6, 8, 10, 12});
    cr_expect_eq(C->name, 'C');
    free(C);
    free_bst_sf(root);
}

//evaluates transpose expression and returns the correct transposed matrix
Test(student_tests, evaluate_transpose) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6}); A->name = 'A';
    root = insert_bst_sf(A, root);
    matrix_sf *B = evaluate_expr_sf('B', "A'", root);
    expect_matrices_equal(B, 3, 2, (int[]){1, 4, 2, 5, 3, 6});
    cr_expect_eq(B->name, 'B');
    free(B);
    free_bst_sf(root);
}

//evaluates a*b multiplication and returns the correct product matrix
Test(student_tests, evaluate_multiply) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 3, (int[]){1, 0, 2, 3, 1, 0}); A->name = 'A';
    matrix_sf *B = copy_matrix(3, 2, (int[]){1, 2, 0, 1, 4, 0}); B->name = 'B';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    matrix_sf *C = evaluate_expr_sf('C', "A * B", root);
    /* Row0: [1*1+0*0+2*4, 1*2+0*1+2*0] = [9, 2]
       Row1: [3*1+1*0+0*4, 3*2+1*1+0*0] = [3, 7] */
    expect_matrices_equal(C, 2, 2, (int[]){9, 2, 3, 7});
    cr_expect_eq(C->name, 'C');
    free(C);
    free_bst_sf(root);
}

//evaluates transpose followed by multiplication, checks combined result
Test(student_tests, evaluate_transpose_then_multiply) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(3, 2, (int[]){1, 2, 3, 4, 5, 6}); A->name = 'A';
    matrix_sf *B = copy_matrix(3, 2, (int[]){1, 0, 0, 1, 1, 1}); B->name = 'B';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    /* A'(2x3) * B(3x2) = (2x2)
       A'=[1,3,5; 2,4,6]
       [0,0]=1*1+3*0+5*1=6  [0,1]=1*0+3*1+5*1=8
       [1,0]=2*1+4*0+6*1=8  [1,1]=2*0+4*1+6*1=10 */
    matrix_sf *C = evaluate_expr_sf('C', "A' * B", root);
    expect_matrices_equal(C, 2, 2, (int[]){6, 8, 8, 10});
    cr_expect_eq(C->name, 'C');
    free(C);
    free_bst_sf(root);
}

//evaluates parenthesized addition then multiplication by identity matrix
Test(student_tests, evaluate_paren_add_then_mult) {
    bst_sf *root = NULL;
    matrix_sf *A = copy_matrix(2, 2, (int[]){1, 2, 3, 4}); A->name = 'A';
    matrix_sf *B = copy_matrix(2, 2, (int[]){5, 6, 7, 8}); B->name = 'B';
    matrix_sf *C = copy_matrix(2, 2, (int[]){1, 0, 0, 1}); C->name = 'C';
    root = insert_bst_sf(A, root);
    root = insert_bst_sf(B, root);
    root = insert_bst_sf(C, root);
    /* (A+B)*I = [6,8;10,12]*I = [6,8;10,12] */
    matrix_sf *R = evaluate_expr_sf('R', "(A + B) * C", root);
    expect_matrices_equal(R, 2, 2, (int[]){6, 8, 10, 12});
    cr_expect_eq(R->name, 'R');
    free(R);
    free_bst_sf(root);
}







/* Testing execute_script_sf */

//runs script01 and checks addition output correctness
Test(student_tests, execute_script_add_correctness) {
    run_script_without_valgrind("script01");
}

//runs script01 under valgrind for memory errors
Test(student_tests, execute_script_add_valgrind1) {
    expect_no_valgrind_errors(run_script_with_valgrind("script01"));
}

//runs script09 under valgrind for memory errors
Test(student_tests, execute_script_add_valgrind2) {
    expect_no_valgrind_errors(run_script_with_valgrind("script09"));
}

//runs script03 and checks multiplication output correctness
Test(student_tests, execute_script_mult_correctness) {
    run_script_without_valgrind("script03");
}

//runs script05 and checks transpose output correctness
Test(student_tests, execute_script_trans_correctness) {
    run_script_without_valgrind("script05");
}

//runs script14 with a complex expression under valgrind for memory errors
Test(student_tests, execute_script_complex_expr_valgrind) {
    expect_no_valgrind_errors(run_script_with_valgrind("script14"));
}