#include <stdio.h>
#include <cstdlib>

#define N 5

int main()
{
    int **A = new int *[N];
    int **B = new int *[N];

    for (int i = 0; i < N; ++i)
    {
        A[i] = new int[N];
        B[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            A[i][j] = rand() % 9;
            B[i][j] = 0;
        }
    }

    printf("Begin matrix: \n");

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            printf("%d  ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nTransform matrix:\n");

    __asm__
    (
        "	mov	$0, %%rax\n\t"                // i = 0
        ".outer:\n\t"
        "	cmp	%%rcx, %%rax\n\t"
        "	jge	.end_asm\n\t"
        "	mov	$0, %%rbx\n\t"                // j = 0
        ".into:\n\t"
        "	cmp	%%rcx, %%rbx\n\t"
        "	jge	increment\n\t"
        "	mov (%%rsi, %%rax, 8), %%r9\n\t"  // A[i]
        "	mov (%%r9, %%rbx, 4), %%r8d\n\t"  // A[i][j]
        "	mov %%rcx, %%r10\n\t"             // N
        "	sub %%rax, %%r10\n\t"             // N - i
        "	sub $1, %%r10\n\t"                // N - i - 1
        "	mov (%%rdi, %%rbx, 8), %%r13\n\t" // B[j]
        "	mov %%r8d, (%%r13, %%r10, 4)\n\t" // B[j][N - i - 1]
        "	add $1, %%rbx\n\t"                // ++j
        "	jmp	.into\n\t"
        "increment:\n\t"
        "	add $1, %%rax\n\t"                // ++i
        "	jmp	.outer\n\t"
        ".end_asm:\n\t"
        :
        : "S"(A), "D"(B), "c"(N)
        :
    );

    // for (int i = 0; i < N; ++i){
    //	for (int j = 0; j < N; ++j){
    //		B[j][N - i - 1] = A[i][j];
    //	}
    // }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            printf("%d  ", B[i][j]);
        }

        printf("\n");
    }

    for (int i = 0; i < N; ++i)
    {
        delete A[i];
        delete B[i];
    }
    delete A;
    delete B;

    return 0;
}