//
//  main.c
//  栈和队列
//
//  Created by gxt-ios on 2020/1/9.
//  Copyright © 2020 gxt-ios. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define LEN 20
//有效的括号
bool isValid(char * s){
    if(!s || s[0] == '\0')
        return 1;
    char* stk = (char*)malloc(strlen(s));
    int top = -1;
    int i;
    for(i = 0; s[i] != '\0'; i++){
        switch(s[i]){
            case '(':
            case '[':
            case '{':
                ++top;
                stk[top] = s[i];
                break;
            case ')':
                if(top < 0 || stk[top] != '(')
                    return 0;
                top--;
                break;
            case ']':
                if(top < 0 || stk[top] != '[')
                    return 0;
                top--;
                break;
            case '}':
                if(top < 0 || stk[top] != '{')
                    return 0;
                top--;
                break;
        }
    }
    if(top >= 0)
        return 0;
    return 1;
}


//最小栈
typedef struct {
    int *data;
    int top;
} MinStack;

MinStack* minStackCreate() {
    MinStack * obj = (MinStack *)malloc(sizeof(MinStack));
    obj->data = (int *)malloc(MAXSIZE*sizeof(int));
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int x) { //push元素进入栈中
    if (obj->top == MAXSIZE-1) {
        
    }else{
        obj->top++;
        obj->data[obj->top]=x;
    }
}

void minStackPop(MinStack* obj) { //元素弹出栈
    if (obj->top==-1) {
        
    }else{
        obj->top--;
    }
}

int minStackTop(MinStack* obj) {  //获取栈顶元素
    if (obj->top == -1) {
        return 0;
    }
    return obj->data[obj->top];
}

int minStackGetMin(MinStack* obj) {//获取栈中最小的元素
    if (obj->top == -1) {
        return 0;
    }
    if (obj->top == 0) {
        return obj->data[obj->top];
    }
    int min = obj->data[0];
    for (int i = 0; i <= obj->top; i++) {
        if (min>obj->data[i]) {
            min = obj->data[i];
        }
    }
    return min;
}

void minStackFree(MinStack* obj) { //释放掉obj
    free(obj->data);
    obj->data = NULL;
    free(obj);
    obj = NULL;
}


//队列实现栈
typedef struct{
    int *data;
    int head;
    int tail;
    int size;//队列中有效元素个数
}Squeue;

typedef struct{
    Squeue *queue1;
    Squeue *queue2;
}MyStack;

//队列初始化函数
Squeue *QueueInit(int k){
    Squeue *obj = (Squeue *)malloc(sizeof(Squeue));
    obj->data = (int *)malloc(k*sizeof(int));
    obj->head = -1;
    obj->tail = -1;
    obj->size = k;
    return obj;
}
//入队列操作函数
void QueuePush(Squeue *queue,int value){
    if (queue->head == -1) {
        queue->head = 0;//队列为空的情况
    }
    queue->tail = (queue->tail+1)%queue->size;
    queue->data[queue->tail] = value;
}

//出队列操作函数
int queuePop(Squeue *queue){
    int a = queue->data[queue->head];
    if (queue->head == queue->tail) {
        queue->head = -1;
        queue->tail = -1;
        return a;
    }
    queue->head=(queue->head + 1)%queue->size;
    return a;
}

int isEmpty(Squeue *queue){
    if (queue->head == -1) {
        return 1;
    }
    else{
        return 0;
    }
}


MyStack* myStackCreate() {
    MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
    obj->queue1 = QueueInit(LEN);
    obj->queue2 = QueueInit(LEN);
    return obj;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    if (isEmpty(obj->queue1)) {
        QueuePush(obj->queue2, x);
    }else{
        QueuePush(obj->queue1, x);
    }
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
  //q2为非空的时候，q2出列直到q2中只有一个元素
    if (isEmpty(obj->queue1)) {
        while (obj->queue2->head != obj->queue2->tail) {
            QueuePush(obj->queue1, queuePop(obj->queue2));//q2出列的元素，入列q1
        }
        return queuePop(obj->queue2);
    }
    //反之q1非空
    while (obj->queue1->head != obj->queue1->tail) {
        QueuePush(obj->queue2, queuePop(obj->queue1));
    }
    return queuePop(obj->queue1);
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    if (isEmpty(obj->queue1)) {
        return obj->queue2->data[obj->queue2->tail];
    }
    else
        return obj->queue1->data[obj->queue1->tail];
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    if (isEmpty(obj->queue1)&&isEmpty(obj->queue2)) {
        return true;
    }
    else{
        return false;
    }
}

void myStackFree(MyStack* obj) {
    free(obj->queue1->data);
    obj->queue1->data = NULL;
    free(obj->queue1);
    obj->queue1 = NULL;
    free(obj->queue2->data);
    obj->queue2->data = NULL;
    free(obj->queue2);
    obj->queue2 = NULL;
    free(obj);
    obj = NULL;
}


//用栈实现队列
typedef struct {
    int top;
    int data[MAXSIZE];
}Stack;

typedef struct {
    Stack stack1;//主栈
    Stack stack2;//翻转栈
} MyQueue;


/** Initialize your data structure here. */
//栈先进后出，队列先进先出，可以采用两个栈，先将所有的数据都放入一个栈中，然后出栈放到另外一个栈中，只要最后一个元素就行，再把之前的
MyQueue* myQueueCreate() {
    MyQueue *tempQueue = (MyQueue *)malloc(sizeof(MyQueue));
    tempQueue->stack1.top = -1;
    tempQueue->stack2.top = -1;
    return tempQueue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    if (obj->stack1.top<MAXSIZE) {
        while(obj->stack1.top != -1){//把S1栈中元素压入S2实现反转
            obj->stack2.data[++(obj->stack2.top)] = obj->stack1.data[obj->stack1.top--];
        }
        obj->stack1.data[++(obj->stack1.top)] = x;//把push的元素压入S1栈中
        while (obj->stack2.top!=-1) {//再把S2栈中的元素全部反转压入S1
            obj->stack1.data[++(obj->stack1.top)] = obj->stack2.data[obj->stack2.top--];
        }
    }
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    if (obj->stack1.top!=-1) {
        return obj->stack1.data[(obj->stack1.top)--];
    }
    return 0;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    if (obj->stack1.top != -1) {
        return obj->stack1.data[obj->stack1.top];
    }
    return 0;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if (obj->stack1.top==-1) {
        return true;
    }
    return false;
}

void myQueueFree(MyQueue* obj) {
    free(obj);
}



int main(int argc, const char * argv[]) {
//    printf("isvaild = %d\n",isValid("{}]"));

//    MinStack *obj = minStackCreate();
//    minStackPush(obj, -2);
//    minStackPush(obj, 0);
//    minStackPush(obj, -3);
//
//    int num = minStackGetMin(obj);
//    printf("num = %d\n",num);
//    minStackPop(obj);
//    int top = minStackTop(obj);
//    printf("top = %d\n",top);
//    int num2 = minStackGetMin(obj);
//    printf("num2 = %d\n",num2);
    
    
//    MyStack *obj = myStackCreate();
//    myStackPush(obj, 1);
//    myStackPush(obj, 2);
//    int top = myStackTop(obj);
//    int num = myStackPop(obj);
//    bool empty = myStackEmpty(obj);
//    printf("top=%d,num = %d,empty = %d",top,num,empty);
    
    
    MyQueue *queue = myQueueCreate();
    myQueuePush(queue, 3);
    myQueuePush(queue, 2);
    myQueuePush(queue, 1);
    myQueuePush(queue, 4);

    int pop = myQueuePop(queue);
    int peek = myQueuePeek(queue);
    bool empty = myQueueEmpty(queue);
    printf("pop = %d,peek = %d,empty = %d",pop,peek,empty);
    return 0;
}
