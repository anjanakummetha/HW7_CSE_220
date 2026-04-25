/*Anjana Kummetha
117162837*/
#include "hw7.h"


//Matrix operations 

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if(mat1->num_rows != mat2->num_rows){
        return NULL;
    }
    if(mat1->num_cols != mat2->num_cols){
        return NULL;
    }

    //allocating/initializing matrix 
    matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat1->num_cols * sizeof(int));
    mat3->num_rows = mat1->num_rows;
    mat3->num_cols = mat1->num_cols;
    mat3->name = '/';

    unsigned int elements = mat1->num_rows * mat1->num_cols;
    for(unsigned int i = 0; i < elements; i ++){
        //add elements together 
        int newElement = (mat1->values[i]) + (mat2->values[i]);
        mat3->values[i] = newElement;
    }
    return mat3;
}


matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {

    if(mat1->num_cols != mat2->num_rows){
        return NULL;
    }

    //allocating/initializing matrix 
    matrix_sf *mat3 = malloc(sizeof(matrix_sf) + mat1->num_rows * mat2->num_cols * sizeof(int));
    mat3->num_rows = mat1->num_rows;
    mat3->num_cols = mat2->num_cols;
    mat3->name = '/';

    //move across rows of mat1 and cols of mat2
    for(unsigned int i = 0; i < mat1->num_rows; i++){
        for(unsigned int j = 0; j < mat2->num_cols; j++){
            int sum = 0;
            for(unsigned int k = 0; k < mat1->num_cols; k++){
                //sum multiplies and adds together each cols of mat1 for a certain row by each row of mat2 for a certain col in mat2 
                sum += mat1->values[i * mat1->num_cols + k] * mat2->values[k * mat2->num_cols + j];
            }
            mat3->values[(i * (mat3->num_cols)) +  j] = sum;
        }
    }
    return mat3;
}


matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    matrix_sf *transpose_mat = malloc(sizeof(matrix_sf) + mat->num_rows * mat->num_cols * sizeof(int));
    transpose_mat->num_rows = mat->num_cols;
    transpose_mat->num_cols = mat->num_rows;
    transpose_mat->name = '/';

    for(unsigned int i = 0; i < mat->num_cols; i ++){
        for(unsigned int j = 0; j < mat->num_rows; j++){
            //new position is (old columns * new cols) + old rows 
            //olf position is (old rows * old cols) + old columns 
            transpose_mat->values[i * mat->num_rows + j] = mat->values[j * mat->num_cols + i];
        }
    }
    return transpose_mat;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    const char *p = expr; 
    char *end;
    unsigned int i = 0;

    //get the rows and cols and allocate space for a new matrix 
    unsigned int r = strtol(p, &end, 10);
    p = end;

    unsigned int c = strtol(p, &end, 10);
    p = end; 
    unsigned int totalSize = r * c;

    //allocate space for matrix with name, rows, and cols
    matrix_sf *matrix = malloc(sizeof(matrix_sf) + totalSize * sizeof(int));
    matrix->name = name;
    matrix->num_rows = r;
    matrix->num_cols = c; 

    while (i < totalSize && *p != '\0') {
        int val = strtol(p, &end, 10);

        //keep gettign values 
        if (p != end) {
            matrix->values[i] = val;
            i++;
            p = end;
        } else {
            //skip spaces, semi-colons, brackets 
            p++;
        }
    }
    return matrix;
}








//Binary Search Tree 

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    //assume mat != NULL and the matrices have different names 
    //base case 
    if (root == NULL){
        bst_sf *newNode = malloc(sizeof(bst_sf));
        newNode->mat = mat;

        newNode->left_child = NULL;
        newNode->right_child = NULL;
        return newNode;
    }
    //greater than mat
    else if(root->mat->name > mat->name){
        root->left_child = insert_bst_sf(mat, root->left_child); }
    //less than mat
    else{
        root->right_child = insert_bst_sf(mat, root->right_child);
    }
    return root; 
    }

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    //base case 
    if (root == NULL){
        return NULL;
    }
    //greater than name 
    else if(root->mat->name > name){
        return find_bst_sf(name, root->left_child); 
    }
    //less than name 
    else if(root->mat->name < name) {
        return find_bst_sf(name, root->right_child);
    }
    else{
        return root->mat; 
    }
}

void free_bst_sf(bst_sf *root) {
    if (root == NULL){
        return;
    }
    //free bst_sf struct and matrix_sf struct
    //using post order left -> right -> node and free children first
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);
    //free mat and BST node 
    free(root->mat);
    free(root);
}




//comverting infix to postfix 
//implement stack based algorithm
char* infix2postfix_sf(char *infix) {
    int len = strlen(infix);
    int output = 0;
    int stkTop = -1;
    char *postfix = malloc((len + 1) * sizeof(char));
    char *stk = malloc((len + 1)* sizeof(char));

    while(*infix != '\0'){
        //add to postfix if its a matrix 
        if(*infix >= 'A' && *infix <= 'Z'){
            postfix[output++] = *infix;
            infix++;
        }
        //check the top stack operator and make sure to pop if the top has higher or equal precedence  
        else if(*infix == '+' || *infix == '\''  || *infix == '*' ){
            while(stkTop != -1 && stk[stkTop] != '(' ){
                int precedenceCur; 
                //' has a higher precedence than + and *
                if (*infix == '\'') {
                    precedenceCur = 3;
                } else if (*infix == '*') {
                    precedenceCur = 2;
                } else {
                    precedenceCur = 1;
                }

                int precedenceTop;
                if (stk[stkTop] == '\'') {
                    precedenceTop = 3;
                } else if (stk[stkTop] == '*') {
                    precedenceTop = 2;
                } else {
                    precedenceTop = 1;
                }

                if (precedenceCur <= precedenceTop) {
                    postfix[output++] = stk[stkTop--];
                } else {
                    break; 
                }
            }

            stk[++stkTop] = *infix;
            infix++;
        }

        //add to the stack 
        else if(*infix == '('){
            stk[++stkTop] = *infix;
            infix++;
        }
        //pop from the stack until you reach (
        else if(*infix == ')'){
            while(stkTop != -1 && stk[stkTop] != '(' ){
                postfix[output++] = stk[stkTop--];
            }
            if (stkTop != -1 && stk[stkTop] == '(' ) {
                    stkTop--;
                }
            infix++;
        }
        else{
            infix++;
        }
    }

    while (stkTop != -1) {
        postfix[output++] = stk[stkTop--];
    }

    free(stk);
    postfix[output] = '\0';
    return postfix;
}


matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    //first convert from infix to postfix
    char *postfix = infix2postfix_sf(expr);
    //allocate space and create a stack of pointers 
    matrix_sf **stk = malloc((strlen(postfix) + 1) * sizeof(matrix_sf *));
    //move through string without losing original pointer 
    char *p = postfix; 
    int top = -1;

    while(*p != '\0'){
        //push matrix to stack 
        if(*p >= 'A' && *p <= 'Z')
        {
            stk[++top] = find_bst_sf(*p, root);
        }
        //multiplication or addition operation 
        else if(*p == '*' || *p == '+')
        {
            matrix_sf *right = stk[top--];
            matrix_sf *left = stk[top--];
            matrix_sf *res;
            //multiplying matricies 
            if (*p == '*') {
                res = mult_mats_sf(left, right);
            } 
            //adding matricies 
            else {
                res = add_mats_sf(left, right);
            }
            res->name = '/';

            //check if left is a temp matrix
            if (!(left->name >= 'A' && left->name <= 'Z'))  {
                free(left);
            }
            //check if right is a temp matrix 
            if (!(right->name >= 'A' && right->name <= 'Z')) {
                free(right);
            }
            stk[++top] = res;
        }

        //transpose means pop a matrix transpose it and push to the stack
        else if(*p == '\'') {
            //pop one matrix 
            matrix_sf *matrix = stk[top--];
            matrix_sf *res = transpose_mat_sf(matrix);
            //make temporary result 
            res->name = '/';
            //if the matrix we popped from the stack was temp free it 
            if (!(matrix->name >= 'A' && matrix->name <= 'Z')) 
            {
                free(matrix);
            }
            stk[++top] = res;
        } 
        p++;
    }


    free(postfix); 
    matrix_sf *ans = stk[top];
    ans->name = name;
    free(stk);

    return ans;

}




matrix_sf *execute_script_sf(char *filename) {
    //open file 
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        return NULL;
    }
    matrix_sf *endingMatrix = NULL;
    //buffer
    char *lineptr = NULL;
    size_t lineSize = 0;
    bst_sf *root = NULL;

    //use getline (gets a line of text and stores it in a dynamically allocated buffer)
    //read lines until you have reached the end 
    while( getline(&lineptr, &lineSize, file)!= -1){
        char *p = lineptr; 
        //the name is first letter 
        char name = lineptr[0];
        //get to the value after the equal sign 
        while (*p != '=') {
            p++;
        }
        p++;
        while (*p == ' ' || *p == '\t') {
            p++;
        }
        //after equals sign if you see a number create a new matrix    
        if (*p >= '0' && *p <= '9') {
            endingMatrix = create_matrix_sf(name, p);
        } 
        else 
        //if you see another matrix calculate this and add it into BST
        {
            endingMatrix = evaluate_expr_sf(name, p, root);
        }
        root = insert_bst_sf(endingMatrix, root);
    }
        matrix_sf *ans = NULL;

        //make a copy of the matrix because we need to free bst later 
        if(endingMatrix != NULL) {
            ans = malloc(sizeof(matrix_sf) + ((endingMatrix->num_rows * endingMatrix->num_cols) * sizeof(int)));
            ans->num_rows = endingMatrix->num_rows;
            ans->num_cols = endingMatrix->num_cols;
            ans->name = endingMatrix->name;
            for (unsigned int i = 0; i < (endingMatrix->num_rows * endingMatrix->num_cols); i++)
            {
                ans->values[i] = endingMatrix->values[i];
            }
        }

    //free buffer (deallocate memeory from getline)
    free(lineptr);
    //close file 
    fclose(file);
    free_bst_sf(root);
    return ans;
}


// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
