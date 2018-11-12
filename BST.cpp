//
//  BST.cpp
//  화일처리
//
//  Created by SeungAe on 31/10/2018.
//  Copyright © 2018 SeungAe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//이진트리 구조체
typedef struct T
{
    //해당 key값
    int key;
    //왼쪽 자식(서브트리)
    struct T *left;
    //오른쪽 자식(서브트리)
    struct T *right;
} T;

//새로운 노드를 생성하는 함수
T* getNode()
{
    T* new_node = NULL;
    new_node = (T*)malloc(sizeof(T));
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

//해당 트리의 최소값을 찾는 함수
T* minNode(T* tree)
{
    //tree가 NULL일 때
    if(tree == NULL)
        return NULL;
    //해당 노드의 left가 없으면 그 노드가 최소값
    if(tree->left == NULL)
        return tree;
    //해당 노드의 left가 있으면 left서브트리에서 다시 min찾음(재귀)
    return minNode(tree->left);
}

//해당 트리의 최대값을 찾는 함수
T* maxNode(T* tree)
{
    //tree가 NULL일 때
    if(tree == NULL)
        return NULL;
    //해당 노드의 right가 없으면 그 노드가 최대값
    if(tree->right == NULL)
        return tree;
    //해당 노드의 right가 있으면 right서브트리에서 다시 max찾음(재귀)
    return maxNode(tree->right);
}

//해당 트리의 node개수 반환해주는 함수
int noNode(T* tree)
{
    int cnt = 0;
    //트리가 NULL일 경우
    if(tree == NULL)
        return 0;
    //왼쪽, 오른쪽 서브트리의 노드 개수를 세면서(재귀) 마지막에 자신노드의 개수 1을 더해준다.
    else
        cnt = noNode(tree->left) + noNode(tree->right) + 1;
    return cnt;
}

//해당 트리의 높이 반환해주는 함수
int height(T* tree)
{
    int h =  0;
    //빈 노드인 경우
    if(tree == NULL)
        return 0;
    else
    {
        // //왼쪽 서브트리의 높이를 얻는다.
        int left_height = height(tree->left);
        // //오른쪽 서브트리의 높이를 얻는다.
        int right_height = height(tree->right);
        //둘 중 큰 값에 1을 더해 반환한다.
        h =  1 + (left_height > right_height ? left_height : right_height);

        return h;
    }
}

//삭제할 노드와 부모를 찾는 함수
T* searchParentBST(T* tree, int searchKey, T* p, T* &q)
{
    //현재 트리가 NULL이 아닐 때
    while(p != NULL)
    {
        //현재의 key값이 찾는 key와 같으면 현재트리 p return
        if (p->key == searchKey)
            return p;
        //현재의 key값이 찾는 key보다 클 때
        else if (p->key > searchKey)
        {
            //부모 q에 p저장
            q = p;
            //p를 왼쪽 서브트리로 저장
            p = p->left;
        }
        //현재의 key값이 찾는 key보다 작을 때
        else
        {
            //부모 q에 p저장
            q = p;
            //p를 오른쪽 서브트리로 저장
            p = p->right;
        }
    }
    //찾는 key없으면 NULL return
    return NULL;
}

//BST insert 함수
void insertBST(T** tree, int newKey)
{
    //함수 안에서 사용할 p, q선언
    T *p, *q;
    //newNode 선언
    T *newNode;
    //현재 노드p에 전체트리 tree를 복사한다.
    p = *tree;

    //부모 노드가 있을 때
    if(p != NULL)
    {
        //삽입하려는 값을 가진 노드가 있는지 없는지
        if(p->key == newKey)
            return;
        q = p;
        //삽입하려는 값이 현재 노드보다 작을 때
        if(p->key > newKey)
            insertBST(&p->left, newKey);
        //삽입하려는 값이 현재 노드보다 클 때
        else
            insertBST(&p->right, newKey);
    }


    else
    {
        //삽입할 노드 생성
        newNode = getNode();

        //삽입할 값의 새로운 노드를 만든다.
        newNode->key = newKey;

        //원래 트리가 공백이원탐색트리일 경우, 삽입한 노드를 tree로 해준다.
        if(*tree == NULL)
            *tree = newNode;
        //원래 트리의 key값보다 작으면 원래 트리의 left에 삽입해준다.
        else if(q->key > newKey)
            q->left = newNode;
        //원래 트리의 key값보다 크면 원래 트리의 right에 삽입해준다.
        else
            q->right = newNode;
    }
}

//BST delete 함수
void deleteBST(T** tree, int deleteKey)
{
    //함수 안에서 사용할 p, q, r선언
    T *p, *q, *r;

    //false:left, true: right
    bool flag = false;

    p = *tree;
    q = NULL;

    //삭제할 노드가 있는지, 그의 부모를 찾는 함수
    p = searchParentBST(*tree, deleteKey, p, q);

    //현재 트리가 NULL이면 return
    if(p == NULL)
        return;

    // //삭제할 원소가 없는 경우
    //삭제할 노드의 차수가 0인 경우(리프 노드)
    if(p->left == NULL && p->right == NULL)
    {
        //부모 노드가 있을 때
        if(q != NULL)
        {
            //제거할 노드가 부모트리의 왼쪽 자식이라면 부모트리의 왼쪽 NULL
            if(q->left == p)
                q->left = NULL;
            //제거할 노드가 부모트리의 오른쪽 자식이라면 부모트리의 오른쪽 NULL
            else
                q->right = NULL;
        }
        //루트 노드만 있는 경우, 루트 삭제
        else
            *tree = NULL;
    }
    //삭제할 노드의 차수가 1인 경우
    else if(p->left == NULL || p->right == NULL)
    {
        //부모 노드가 있을 때
        if(q != NULL)
        {
            //제거하려는 노드가 왼쪽 자식을 가지고 있을 때
            if(p->left != NULL)
            {
                //제거하려는 노드가 부모트리의 왼쪽 자식일 때,
                //제거하려는 노드의 왼쪽 자식을 부모트리의 왼쪽에 붙인다.
                if(q->left == p)
                    q->left = p->left;

                //제거하려는 노드가 부모트리의 오른쪽 자식일 때,
                //제거하려는 노드의 왼쪽 자식을 부모트리의 오른쪽에 붙인다.
                else
                    q->right = p->left;
            }
            //제거하려는 노드가 오른쪽 자식을 가지고 있을 때
            else
            {
                //제거하려는 노드가 부모트리의 왼쪽 자식일 때,
                //제거하려는 노드의 오른쪽 자식을 부모트리의 왼쪽에 붙인다.
                if(q->left == p)
                    q->left = p->right;
                //제거하려는 노드가 부모트리의 오른쪽 자식일 때,
                //제거하려는 노드의 오른쪽 자식을 부모트리의 오른쪽에 붙인다.
                else
                    q->right = p->right;
            }
        }
        //부모 노드가 없을 때
        else
        {
            //제거하려는 노드가 왼쪽 자식을 가지고 있을 때
            if(p->left != NULL)
                *tree = p->left;
            //제거하려는 노드가 오른쪽 자식을 가지고 있을 때
            else
                *tree = p->right;
        }
    }
    //삭제할 노드의 차수가 2인 경우
    else
    {
        //왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이보다 클 때
        if(height(p->left) > height(p->right))
        {
            //왼쪽 서브트리에서의 가장 큰 값
            r = maxNode(p->left);
            flag = false;
        }
        //왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이보다 작을 때
        else if(height(p->left) < height(p->right))
        {
            //오른쪽 서브트리에서의 가장 작은 값
            r = minNode(p->right);
            flag = true;
        }
        //왼쪽 서브트리의 높이와 오른쪽 서브트리의 높이가 같을 때
        else if(height(p->left) == height(p->right))
        {
            //왼쪽 서브트리의 노드개수가 오른쪽 서브트리의 노드개수와 크거나 같을 때
            if(noNode(p->left) >= noNode(p->right))
            {
                //왼쪽 서브트리에서의 가장 큰 값
                r = maxNode(p->left);
                flag = false;
            }
            //왼쪽 서브트리의 노드개수가 오른쪽 서브트리의 노드개수보다 작을 때
            else if(noNode(p->left) < noNode(p->right))
            {
                //오른쪽 서브트리에서의 가장 작은 값
                r = minNode(p->right);
                flag = true;
            }
        }
        // //삭제할 노드의 자리에 넣는다.
        p->key = r->key;
        //복사 후, 복사한 값을 삭제한다.(5삭제: 5 2 10 -->> 2 2 10 --> 2 10)
        if(!flag)
            deleteBST(&p->left, r->key);
        else
            deleteBST(&p->right, r->key);
    }
}

//중위 순회(root가 가운데, 왼 root 오 )
void inOrder(T* tree)
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        printf(" %d ", tree->key);
        inOrder(tree->right);
    }
}

//main 함수
int main()
{
    T *tree = NULL;

    printf("---------- 최초 삽입 ----------\n");

    // 삽입
    insertBST(&tree, 8);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 18);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 11);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 5);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 15);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 4);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 9);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 1);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 7);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 17);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 6);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 14);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 10);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 3);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 19);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 20);
    inOrder(tree);
    printf("\n");

    //삭제(순서 동일)
    deleteBST(&tree, 8);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 18);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 11);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 5);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 15);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 4);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 9);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 1);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 7);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 17);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 6);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 14);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 10);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 3);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 19);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 20);
    inOrder(tree);
    printf("\n");

    printf("---------- 재삽입 ----------\n");

    //재삽입
    insertBST(&tree, 8);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 18);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 11);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 5);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 15);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 4);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 9);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 1);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 7);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 17);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 6);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 14);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 10);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 3);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 19);
    inOrder(tree);
    printf("\n");
    insertBST(&tree, 20);
    inOrder(tree);
    printf("\n");

    //삭제(순서 역순)
    deleteBST(&tree, 20);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 19);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 3);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 10);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 14);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 6);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 17);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 7);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 1);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 9);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 4);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 15);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 5);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 11);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 18);
    inOrder(tree);
    printf("\n");
    deleteBST(&tree, 8);
    inOrder(tree);
    printf("\n");
}
