//
//  main.c
//  tree
//
//  Created by gxt-ios on 2020/1/13.
//  Copyright © 2020 gxt-ios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef char ElemType;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

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
        printf("%c\n",T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
//中序遍历，左根右
void InOrder(BiTree T){
    if (T){
        InOrder(T->lchild);
        printf("%c\n",T->data);
        InOrder(T->rchild);
    }
}
//后序遍历，左右根
void TailOrder(BiTree T){
    if (T) {
        TailOrder(T->lchild);
        TailOrder(T->rchild);
        printf("%c\n",T->data);
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


//插入节点

//删除节点



int main(int argc, const char * argv[]) {
    // insert code here...
    BiTree T=NULL;
    creatBiTree(&T);
    printf("前序遍历\n");
    preOrder(T);
    printf("中序遍历\n");
    InOrder(T);
    printf("后序遍历:\n");
    TailOrder(T);
   
    int deep = TreeDeep(T);
    printf("树的深度是:%d\n",deep);
    
    int count = leafCount(T);
    printf("叶子节点个数是:%d\n",count);
    return 0;
}
