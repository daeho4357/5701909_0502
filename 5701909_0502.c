#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void error(char* message) {
    fprintf(stderr, "%s", message);
    exit(1);
}

int is_full(QueueType* q) {
    return (q->front == ((q->rear + 1) % MAX_QUEUE_SIZE));
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        error("Queue is full\n");
    }
    else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = item;
    }
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue is empty\n");
    }
    else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return (q->data[q->front]);
    }
}

void init_stack(Stack* sptr) {
    sptr->top = -1;
}

int is_stack_empty(Stack* sptr) {
    return (sptr->top == -1);
}

int is_stack_full(Stack* sptr) {
    return (sptr->top == (MAX_STACK_SIZE - 1));
}

void push(Stack* sptr, int item) {
    if (is_stack_full(sptr)) {
        error("Stack is full\n");
    }
    else {
        sptr->data[++(sptr->top)] = item;
    }
}

int pop(Stack* sptr) {
    if (is_stack_empty(sptr)) {
        error("Stack is empty\n");
    }
    else {
        return sptr->data[(sptr->top)--];
    }
}

int main() {
    QueueType q;
    Stack sptr;
    char str[100];
    int choice;

    init_queue(&q);
    init_stack(&sptr);

    while (1) {
        printf("1. 회문 입력\n");
        printf("2. 회문 검사\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        while (getchar() != '\n'); // 입력버퍼 지우기

        switch (choice) {
        case 1:
            printf("회문을 입력하시오: ");
            scanf("%[^\n]s", str);
            break;
        case 2:
            for (int i = 0; str[i] != '\0'; i++) {
                char c = tolower(str[i]);
                if (isalpha(c)) {
                    enqueue(&q, c);
                    push(&sptr, c);
                }
            }
            while (!is_empty(&q) && !is_stack_empty(&sptr)) {
                if (dequeue(&q) != pop(&sptr)) {
                    printf("회문이 아닙니다.\n");
                    break;
                }
            }
            if (is_empty(&q) && is_stack_empty(&sptr)) {
                printf("회문입니다.\n");
            }
            init_queue(&q);
            init_stack(&sptr);
            break;
        case 3:
            printf("종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 메뉴 선택\n");
            break;
        }
    }

    return 0;
}
