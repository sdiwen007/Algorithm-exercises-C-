//
//  main.c
//  tree
//
//  Created by gxt-ios on 2020/1/13.
//  Copyright © 2020 gxt-ios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 100

typedef char ElemType;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;




typedef struct seqstack{
    BiTree data[MAXSIZE];
    int tag[MAXSIZE];//为后续遍历准备的
    int top;//top为数组的下标
}seqstack;

void push(seqstack *s,BiTree t){
  if(s->top == MAXSIZE){
    printf("the stack is full\n");
  }else{
    s->top++;
    s->data[s->top]=t;
  }
}
BiTree pop(seqstack *s){
  if(s->top == -1){
    return NULL;
  }else{
    s->top--;
    return s->data[s->top+1];
  }
}

typedef struct Queue{
    int front;
    BiTNode *data[MAXSIZE];
    int rear;
}Squeue;
void enter(Squeue *q,BiTree t){
    if (q->rear == MAXSIZE) {
        printf("the queue is full\n");
    }
    else{
        q->data[q->rear] = t;
        q->rear++;
    }
}
BiTree del(Squeue *q){
    if (q->front == q->rear) {
        return NULL;
    }
    else{
        q->front++;
        return q->data[q->front-1];
    }
}

//遍历实现层序遍历
void level_tree(BiTree t){
    Squeue q;
    q.front = q.rear = 0;
    if (!t) {
        printf("the tree is empty\n");
        return;
    }
    enter(&q, t);
    while (q.front != q.rear) {
        t = del(&q);
        printf("%c ",t->data);
        if (t->lchild) {
            enter(&q, t->lchild);
        }
        if (t->rchild) {
            enter(&q, t->rchild);
        }
    }
}


//二叉树的建立(按照先序方式建立)
void creatBiTree(BiTree *T) {
    ElemType c;
    scanf("%c", &c);
    if (c != '#'){
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = c;
        creatBiTree(&(*T)->lchild);
        creatBiTree(&(*T)->rchild);
    }else{
        *T = NULL;
    }
}
//先序遍历,根左右
void preOrder(BiTree T){
    if (T){
        printf("%c ",T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

//先序遍历，采用非递归的实现，因为当遍历过根结点之后还要回来，所以必须将其存起来。考虑到后进先出的特点，选用栈存储。数量确定，采用顺序栈存储。

void preOrder_dev(BiTree t){
    seqstack s;
    s.top = -1;
    if (!t) {
        printf("the tree is empty");
    }
    else{
        while (t || s.top != -1) {
            while (t) {
                printf("%c ",t->data);
                push(&s, t);
                t = t->lchild;
            }
            t = pop(&s);
            t = t->rchild;
        }
    }
}


//中序遍历，左根右
void InOrder(BiTree T){
    if (T){
        InOrder(T->lchild);
        printf("%c ",T->data);
        InOrder(T->rchild);
    }
}

//中序非递归遍历
void Midorder(BiTree t){
  seqstack s;
  s.top = -1;
  if(!t){
    printf("the tree is empty!\n");
  }else{
    while(t || s.top != -1){
      while(t){
        push(&s,t);
        t = t->lchild;
      }
      t=pop(&s);
      printf("%c ",t->data);
      t=t->rchild;
    }
  }
}


//后序遍历，左右根
void TailOrder(BiTree T){
    if (T) {
        TailOrder(T->lchild);
        TailOrder(T->rchild);
        printf("%c ",T->data);
    }
}

//后续遍历非递归的实现
//因为后续遍历最后还要访问根结点一次，所以要访问根结点两次。采取夹标志位的方法解决这个问题
void TailOrder_dev(BiTree t){
    seqstack s;
    s.top = -1;
    if (!t) {
        printf("the tree is empty");
    }else{
        while (t || s.top != -1) {
            while (t) {
                push(&s, t);
                s.tag[s.top] = 0;//设置访问标记，0为第一次访问，1为第二次访问
                t = t->lchild;
            }
            if (s.tag[s.top] == 0) {//第一次访问时，转向同层右结点
                t = s.data[s.top]; //左走到底时t是为空的，必须有这步！
                s.tag[s.top] = 1;
                t = t->rchild;
            }else{
                while (s.tag[s.top] == 1) {//找到栈中下一个第一次访问的结点，退出循环时并没有pop所以为其左子结点
                    t = pop(&s);
                    printf("%c ",t->data);
                }
                t = NULL;//必须将t置空。跳过向左走，直接向右走。
            }
        }
    }
}



//二叉树的深度
int TreeDeep(BiTree T){
    int deep = 0;
    if (T!=NULL) {
        int leftDeep = TreeDeep(T->lchild);
        int rightDeep = TreeDeep(T->rchild);
        deep = leftDeep>=rightDeep?leftDeep+1:rightDeep+1;
    }
    return deep;
}

//叶子节点个数
int leafCount(BiTree T){
    static int count;
    if (T!=NULL) {
        if (T->lchild == NULL && T->rchild == NULL) {
            count++;
        }
        leafCount(T->lchild);
        leafCount(T->rchild);
    }
    return count;
}

//统计结点个数
int count_tree(BiTree T){
    if (T) {
        return count_tree(T->lchild)+count_tree(T->rchild)+1;
    }
    return 0;
}

//二叉树的查找
BiTree search_tree(BiTree t,char ch){
    if (!t) {
        return NULL;
    }
    if (t->data == ch) {
        return t;
    }else{
        if (!search_tree(t->lchild, ch)) {
            return search_tree(t->rchild, ch);
        }
        return t;
    }
}

//比较两个二叉树是否相同
int is_equal(BiTree t1,BiTree t2){
    if (!t1 && !t2) {//都为空即相等
        return 1;
    }
    if (t1 && t2 && t1->data == t2->data) {
        if (is_equal(t1->lchild, t2->lchild)) {
            if (is_equal(t1->rchild, t2->rchild)) {
                return 1;
            }
        }
    }
    return 0;
}



int main(int argc, const char * argv[]) {
    printf("测试代码\n");
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTNode));
    printf("请给二叉树按照先序方式依次输入结点的值(空结点为#)：\n");
    creatBiTree(&T);
    printf("\n前序遍历:");
    preOrder(T);
    printf("\n非遍历实现前序遍历:");
    preOrder_dev(T);
    
    
    printf("\n中序遍历:");
    InOrder(T);
    printf("\n非遍历实现中序遍历:");
    Midorder(T);
    printf("\n后序遍历:");
    TailOrder(T);
    printf("\n非递归实现后序遍历:");
    TailOrder_dev(T);
    
    printf("\n递归实现层序遍历：");
    level_tree(T);
    
    int deep = TreeDeep(T);
    printf("\n树的深度是:%d\n",deep);

    int count = leafCount(T);
    printf("叶子节点个数是:%d\n",count);
    
    int countTree = count_tree(T);
    printf("树的所有结点数:%d\n",countTree);
    
    BiTree temp = search_tree(T,'B');
    printf("查找的结点是:%c\n",temp->data);

    
    return 0;
}
