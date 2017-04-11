//
//  main.c
//  ArithmeticRecursionAndStack
//
//  Created by CSX on 2017/4/7.
//  Copyright © 2017年 宗盛商业. All rights reserved.
//

#include <stdio.h>


//函数调用主要依靠ebp和esp的堆栈互动来实现的

//递归，最主要的特色就是函数自己调用自己。如果一个函数调用的是自己本身，那么这个函数就是递归函数

/*无论是数据库，还是普通的ERP系统，查找功能数据处理的一个基本功能。
 （1） 普通的数据查找
 设想有一个1M的数据，我们如何在里面找到我们想要的那个数据。此时数据本身没有特征，所以我们需要的那个数据可能出现在数组的各个位置，可能在数据的开头位置，也可能在数据的结束位置。这种性质要求我们必须对数据进行遍历之后才能获取到对应的数据。由于我们不清楚这个数据判断究竟需要多少次。但是，我们知道，这样一个数据查找最少需要1次，那么最多需要n次，平均下来可以看成是（1+n）/2，差不多是n的一半。我们把这种比较次数和n成正比的算法复杂度记为o（n）。
 
 （2）上面的数据没有任何特征，这导致我们的数据排列地杂乱无章。试想一下，如果数据排列地非常整齐，那结果会是什么样的呢？就像在生活中，如果平时不注意收拾整齐，那么找东西的时候非常麻烦，效率很低；但是一旦东西放的位置固定下来，所有东西都归类放好，那么结果就不一样了，我们就会形成思维定势，这样查找东西的效率就会非常高。那么，对一个有序的数组，我们应该怎么查找呢？二分法就是最好的方法。这种方法最少是1次，那么最多需要多少次呢？我们发现最多需要log（n+1）/log（2）即可。
 
 （3）上面的查找是建立在连续内存基础之上的，那么如果是指针类型的数据呢？怎么办呢？那么就需要引入排序二叉树了。排序二叉树的定义很简单：（1）非叶子节点至少一边的分支非NULL；（2）叶子节点左右分支都为NULL；（3）每一个节点记录一个数据，同时左分支的数据都小于右分支的数据。可以看看下面的定义：

*/

//二叉树
typedef struct _NODE{
    int data;
    struct _NODE *left;
    struct _NODE *right;
}NODE;


//查找
const NODE *find_data(const NODE *pNode, int data){
    if (pNode == NULL) {
        return NULL;
    }
    
    if (data == pNode->data) {
        return pNode;
    }else if (data < pNode->data){
        return find_data(pNode->left, data);
    }else{
        return find_data(pNode->right, data);
    }
    
}


/*
 （4）同样，我们看到（2）、（3）都是建立在完全排序的基础之上，那么有没有建立在折中基础之上的查找呢？有，那就是哈希表。哈希表的定义如下：1）每个数据按照某种聚类运算归到某一大类，然后所有数据链成一个链表；2）所有链表的头指针形成一个指针数组。这种方法因为不需要完整排序，所以在处理中等规模数据的时候很有效。其中节点的定义如下：
 
 分析：
 hash表因为不需要排序，只进行简单的归类，在数据查找的时候特别方便。查找时间的大小取决于mod的大小。mod越小，那么hash查找就越接近于普通查找；那么hash越大呢，那么hash一次查找成功的概率就大大增加。
 */



typedef struct _LINK_NODE{
    int data;
    struct _LINK_NODE *next;
}LINK_NODE;

//hash查找
LINK_NODE *hash_find(LINK_NODE *array[], int mod, int data){
    
    int index = data % mod;               //取余
    
    if (array[index] == NULL) {
        return NULL;
    }
    
    LINK_NODE *pLinkNode = array[index];
    while (pLinkNode) {
        if (data == pLinkNode->data) {
            return pLinkNode;
        }
         pLinkNode = pLinkNode->next;
    }
    return pLinkNode;
}

/*
 *Hash表存在的优点显而易见，能够在常数级的时间复杂度上进行查找，并且插入数据和删除数据比较容易。但是它也有某些缺点，比如不支持排序，一般比用线性表存储需要更多的空间，并且记录的关键字不能重复。
 */


//冒泡排序
void bubble_sort(int array[], int length){
    int inner = 0, outer = 0;
    int median = 0;
    if (array == NULL || length == 0) {
        return;
    }
    
    for (outer = length-1; outer >= 1; outer--) {
        for (inner = 0 ; inner < outer; inner ++) {
            if (array[inner] > array[inner + 1]) {
                median = array[inner];
                array[inner] = array[inner + 1];
                array[inner + 1] = median;
            }
        }
    }
}


//插入排序
void insert_sort(int array[], int length){
    int inner = 0;
    int outer = 0;
    int median = 0;
    if (array == NULL || length == 0) {
        return;
    }
    
    for (outer = 0; outer < length; outer ++) {
        for (inner = outer; inner >= 1; inner -- ) {
            if (array[inner] < array[inner -1]) {
                median = array[inner];
                array[inner] = array[inner - 1];
                array[inner - 1] = median;
            }else{
                break;
            }
        }
    }
}


//希尔排序法
/*
 希尔排序，我个人认为可以看成是冒泡排序的变种。它的基本思想是：首先按照一个序列递减的方法逐渐进行排序。比如说有10个数据，我们按照序列5、3、1的顺序进行排序。首先是5，那么我们对1和6、2和7、3和8、4和9、5和10进行排列；第二轮是3，那么对数据1、4、7、10排列，再对2、5、8进行排列，以及3、6、9排列；第三轮就和冒泡排序一样了，以此对每个数据进行排列。它的优势就是让整个队列基本有序，减少数据移动的次数，从而降低算法的计算复杂度。
 */

void shell_sort(int array[], int length, int step){
    
    int inner = 0;
    int outer = 0;
    int median = 0;
    
    if (array == NULL || length == 0) {
        return;
    }
    
    for (; step >= 1; step-=2) {
        for (int index = 0; index < step; index ++) {
            if ((length -1) < (index + step)) {
                continue;
            }else{
                outer = index + step;
                while ((outer + step) <= (length - 1)) {
                    outer += step;
                }
            }
            
            for (; outer >= (index + step);  outer -= step) {
                for (inner = index;  inner <= outer - step; inner += step) {
                    if (array[inner] >= array[inner + step]) {
                        median = array[inner];
                        array[inner] = array[inner + step];
                        array[inner +step] = median;
                    }
                }
            }
        }
    }
}







int main(int argc, const char * argv[]) {
    // insert code here...
    
    

    
    printf("Hello, World!\n");
    return 0;
}
