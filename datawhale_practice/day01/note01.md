# What Is a List?
A list is a collection of items in a particular order. You can make a list that includes the letters of the alphabet,the digits from 0-9,or the names of all the people in your family. You can put anything you want into a list,and the items in your list don't have to be related in any particular way. Because a list usually contains more than one element,it's a good idea to make the name of your list plural,such as letters,digits,or names.
In Python, square brackets([])indicate a list,and individual elements in the list are separated by commas. Here's a simple example of a list that contains a few kinds of bicycles:
```python
bicycles = ['trek','cannondale','redline','specialized']
print(bicycles)
```
If you ask Python to print a list,Python returns its representation of the list,including the square brackets:
```python
['trek','cannondale','redline','specialized']
```

# Python list implementation
This post describes the CPython implementation of the list object.CPython is the most used Python implementation.
## List object C strcture
A list object in CPython is represented by the following C structure. ob_item is a list of pointers to the list elements.allocated is the number of slots allocated in memory:
```c
typedef struct {
    PyObject_VAR_HEAD 
    PyObject **ob_item;
    Py_ssize_t allocated;
}PyListObject;
```

## List initialization
When we initialization an empty list.e.g.I = []:
```
arguments:size of the list = 0
returns list object = []
PyListNew:
    nbytes = size * size of global Python object = 0
    allocate new list object
    alloacte list of pointer (ob_item) of size nbytes = 0
    clear ob_item
    set list's allocated ar to 0 = 0 slots
    return list object
```
It is important to notice the difference between allocated slots and the size of the list.The size of a list is the same as len(I).The number of allocated slots is that has been allocated in memory.Often,you will see that allocated can be greater than size.This is to avoid needing calling realloc each time a new elements is appended to the list.We will see more about that later.
## Append 
We append an integer to the list:I.append(1).What happens?The internal C function app1() is called:
```
arguments:list object,new element
returns:0 if OK,-1 if not
app1:
    n = size of list
    call list_resize() to resize the list to size n+1 = 0 +1 =1
    list[n] = list[0] = new element
    return 0
```
Let's look at list_resize().It over-allocates memory to avoid calling list_resize too many time.The growth pattern of the list is:0,4,8,16,25,35,46,58,72,88,...
```
arguments:list object, new size
returns: 0 if OK,-1 if not
list_resize:
    new_allocated = (newsize >> 3) + (newsize < 9 ? 3:6 )=3
    new_allocated += newsize = 3+1 = 4
    resize ob_item (list of pointers) to size new_allocated
    return 0
```
4 slots are now allocated to contain elements and the first one is the integer 1.You can see on the following diagram that I[0] points to the integer object that we just appended. The dashed squares represent the slots allocated but not used yet.
Append operation amortized complexity is O(1).

![I](http://www.laurentluce.com/images/blog/list/list.png)

We continue by adding one more element:I.append(2).list_resize is called with n+1 = 2 but because the allocated size if 4,there is no need to allocate more memory.Same thing happens when we add 2 more integers:I.append(3),I.append(4).The following diagram shows what we have so far:
![I1](http://www.laurentluce.com/images/blog/list/list_4.png)

## Insert 
Let's insert a new integer(5) at position 1:I.insert(1,5), and look at what happens internally.ins1() is called:
```
arguments:list object,where,new element
returns : 0 if OK,-1 if not
ins1:
    resize list to size n+1 = 5 -> 4 more slots will be allocated
    starting at the last element up to the offset where where,right shift each element
    set new element at offset where
    return 0
```
![insert5](http://www.laurentluce.com/images/blog/list/list_insert.png)

The dashed squares represent the slots allocated but not used yet.Here,8 slots are allocated but the size or length of the list is only 5.
Insert operation complexity is O(n).

## Pop 
Wher you pop the last element:I.pop(),listpop() is called inside listpop() and if the new size is less than half of the allocated size then the list is shrunk:
```
arguments:list object
returns:element popped
listpop:
    if list empty:
        return null
    resize list with size 5 - 1 = 4.4 is not less than 8/2 so no shrinkage
    set list object size to 4
    return last element
```

Pop operation complexity is O(1).
![pop](http://www.laurentluce.com/images/blog/list/list_pop.png)

You can observe that slot 4 still points to the integer but the important thing is the size of the list which is now 4.
Let's pop one more element/In list_resize(),size-1 = 4 - 1 = 3 is less than half of the allocated slots so the list if shrunk to 6 slots and the new size of the list is now 3.
You can observe that slot 3 and 4 still point to some integers but the important thing is the size of the list which is now 3.
![pop](http://www.laurentluce.com/images/blog/list/list_pop_2.png)

## Remove
Python list object has a method to remove a specific element:I.remove(5).listremove() is called.
```
arguments : list object,element to remove
returns non if OK,null if not
listremove:
    loop through each list element:
        if correct element:
            slice list between element's slot and element's slot+1
            return none
        return null
```
To slice the list and remove the element, list_ass_slice() is called and it is interesting to see how it works. Here, low offset is 1 and high offset is 2 as we are removing the element 5 at position 1.
```
arguments:list object, low offset , high offset
returns:0 if OK
list_ass_slice:
    copy integer 5 to recycle list to dereference it 
    shift elements from slot 2 to slot 1
    resize list to 5 slots
    return 0
```
Remove operation complexity is O(n).
![remove](http://www.laurentluce.com/images/blog/list/list_remove.png)

摘自:http://www.laurentluce.com/posts/python-list-implementation/


# 练习
## 1. 利用动态数组解决数据存放问题

编写一段代码，要求输入一个整数N，用动态数组A来存放2~N之间所有5或7的倍数，输出该数组。

示例：

输入：
N = 100 

输出：
5 7 10 14 15 20 21 25 28 30 35 40 42 45 49 50 55 56 60 63 65 70 75 77 80 84 85 90 91 95 98 100

代码:
```c
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


int n,*array = 0,j=0;
void DAInput()
{
    int i = 0,num = 0;
    scanf("%d",&n);
    //动态分配内存
    array = (int *)malloc(sizeof(int)*n);
    
    if(array == 0)
    {
        printf("error");
    }

    //动态输入数组
    for(i=2;i<=n;i++)
    {
        if(i%5==0||i%7==0)
        {
            array[j]=i;
            j++;
        }
    }
}

void DAOutpu(){
    for(int i=0;i<j;i++)
        printf("%d ",array[i]);
}

int main()
{
    DAInput();
    DAOutpu();
    
    free(array);
    return 0;
}
```
## 2. 托普利茨矩阵问题

如果一个矩阵的每一方向由左上到右下的对角线上具有相同元素，那么这个矩阵是托普利茨矩阵。

给定一个M x N的矩阵，当且仅当它是托普利茨矩阵时返回True。

示例：

输入:
matrix = [
  [1,2,3,4],
  [5,1,2,3],
  [9,5,1,2]
]

输出: True
解释:

在上述矩阵中, 其对角线为: "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]"。 各条对角线上的所有元素均相同, 因此答案是True。

代码:
```c
/*
比较当前元素与邻左上角元素,不相等返回false
*/
bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize){
    for(int i = 1;i<matrixSize;i++)
    {
        for(int j=1;j<*matrixColSize;j++)
        {
            if(matrix[i-1][j-1]!=matrix[i][j])
                return false;
        }
    }
    return true;
}
```
![leetcode766](data:image/png;base64,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6VAVAUVAEVAEFIGcIKCknxP0Irh29uzZ8t1338nmzZulTJky0qxZM7n00kslJiYm0MvevXvlq6++knnz5snBgwelbt260qFDB6lQoUIEd9KmikB0IZCRkSHff/+9fPvtt5KZmSmDBg2SpKSkwwY5fPhwmThxolx44YXSpUuXkA+RlpYmY8eOld9//11QYscff7y0b99e6tevH7ju77//llGjRsmKFSskISFBzjjjDLn66qulaNGigTaLFi0ybbZt2yYnnHCCdO3aVY499tjA74z92Wefleuvv15q1qwZXcDqaBSBbCCgpJ8N0CK9ZPLkyfLZZ5+Zy2JjYyU9/dCfyr3sssvkqquuMv9OTU2Vvn37yvr1681njAEUZMmSJeXRRx+VcuXKRXpbba8IRAUCn376qUyZMiUwFi/Sx+B95JFHzD6AZJ3E6/UQb731lsydO9f8VKRIEYGc+f///vc/qVevnmzZskWee+452b9/f2Av0bZ69erywAMPSHx8vPz777/ywgsvyG233Sa1a9c2Bsf06dPlySefNPsU+e2332TOnDlyxx13RAWWOghFIKcIKOnnFMEw16PEUDIHDhyQm2++WRo1aiTLly+XIUOGCN4KSqds2bIyfvx4GTFihFFKPXv2NN7Ihx9+aLz+8847z3gaKgWHAAaYNcYKbhS5e2eIkueyBJe7vf/X22uvvWaiW0uXLpWtW7d6evo//PCDjB492njjkHAowXPv37+/MYR79+4tFStWNPuHKFnVqlXl8ccfl/fee09mzZpl9k6nTp1MNOCNN96QdevWSefOneWiiy6Sr7/+2ozn1ltvNbcDD/Yq+w8jAOO8T58+ZjxVqlTJK3i0X0UgXxHId9Jns7KxrLA5W7dubTaul2zcuFF+/PFHuemmm/IVGG6GR4KFHxcXl+17E2J89dVXpVatWnLnnXcG+hk2bJj8+uuvRqGg6KznghI75ZRTTLvt27cb7+e4446TZ555JttjiJYLUbhEPQihhhM8vz///NN4bC1btjTNSXksWbJE/vjjD2nbtu1h0Y9NmzbJpEmTjJLPbSE0XblyZTNXzBvjcMuNN95oPEi3/PXXX8Z4u/baa30Piz3CXvErkBP/eQkeMaRqBS8aogNfxhUulO53DMHarV271hizeNDMkdvTx/glmrVz5055+OGHpUaNGiFv+dNPPxmCJ0pG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)

## 3. 三数之和

https://leetcode-cn.com/problems/3sum/

给定一个包含 n 个整数的数组nums，判断nums中是否存在三个元素a，b，c，使得a + b + c = 0？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例：

给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

## 思路:
遍历数组,维护两个指针,左指针从当前元素的下一个元素开始,右指针从最后一个元素开始,判断是否三数之和为0.为了避免重复,需要进行一些处理.

## 代码:
```python
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)   
        res = []
        if(n<3 or not nums):    #如果list为空或元素数小于3则返回空list
            return res
        nums.sort()             #排序
        for i in range(n):
            if(nums[i]>0):      #如果nums[i]>0.则其后的元素均大于0,和无法为0
                return res
            if(i>0 and nums[i] == nums[i-1]):   #如果nums[i]==nums[i-1]则说明重复,为避免重复,continue
                continue
            l = i +1    #初始化左指针
            r = n - 1   #初始化右指针
            while(l<r): 
                if(nums[l]+nums[r]+nums[i] == 0):
                    res.append([nums[i],nums[l],nums[r]])
                    while(l<r and nums[l]==nums[l+1]):  #去重
                        l = l+1
                    while(l<r and nums[r]==nums[r-1]):  #去重
                        r = r-1
                    l = l+1
                    r = r-1
                elif(nums[i]+nums[l]+nums[r]>0):
                    r = r-1
                else:
                    l = l+1
        return res
```
![leetcode15](data:image/png;base64,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7rlZZjF69GgZNWqUrF69WsqWLSuNGjWS0047LY7ZWldDwBDIDgKPP/64/PPPP9KxY0epV69exKHC9mOAHTt2yPDhw+XXX3+VjRs3yqGHHiotW7aUo446Ksv4/H7ffffJ9u3b5bHHHpNy5cq5Prt375ZvvvlGvv/+e9m6dascd9xx0rp1aylUqFDGGOiNZ599Vh599NFM32cHD7t2/yJg5BwS7+XLl8sTTzwh27Ztc1d4yXndunXut/Xr1zti5vDQINUHH3xQihQp4j5zIPv16+f+39vvggsukIsvvjhjJsOGDZMvvvgiSz8OYBCRh1yCdTMEDIGQCPz555/y4osvykEHHSSQb968eQOvDNtPL3799ddl0qRJ7iNj7tq1y/33lltukdq1a2e6x2effSZffvmlHH/88dKpU6eM33766ScZMWKE3HTTTVKiRAl57733pGjRonLllVdm9Hn33XelYsWKTk9Zy5kIGDmH3Ld58+YJB+uEE04QvFovOX/88cfOyz322GOlffv2zjp+8803ZdasWdKiRQtp3Lix7Ny5U+6++25nLbdr104aNmwoM2fOlFdffdX99uSTT0qZMmUcwd97772OvG+88UZ3YDnMjFewYEHp0aOHFChQIOSsrduBhoAq+9y0bs5TWlqaOxP7q0HMEO/ll18uZ511VsTbhu3HAHPmzHHnl3PepUsXKV++vIwcOVIGDx4slStXdoa8ti1btjivmf+iNw4//PCM3/CITz75ZDnzzDPdd3j3Tz31lPTu3dsR/b///isvvfSS85rz58+/vyCz+yQZgYTJGSHr2rVrxnTeeustadq0qRO4oEYY9+uvv5ZrrrkmyUuIPRwHCCszX758sTtH6LF27VqnHCBc1uolZ7zmRYsWOe/54IMPdiPoQaxTp47cfPPNsnjxYheaqlq1qtx///0Zd8Hq/fnnn+Xaa6+Vk046SQh7v/baa+7webHq1auXC5lD3NWqVUt4Haly4fvvv++UC0opWoNsUD5Tpkxx4TvtTxrh999/d8qIkL+/kWI45ZRTXNjwQGrPP/+83HDDDVKsWDH55JNPhKiOt+EJEkYNaqRbDjnkEKlfv34oyDgLhFavv/76UP2XLFniUjqEiYPa0KFDHSFqO/HEE93e8j37Hi20HGoCITvpWcUbfeaZZyIaw2H76W0JRUPERMmIlmlDH6xatcp5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)