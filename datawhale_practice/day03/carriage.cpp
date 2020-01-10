#include<iostream>
#include<stack>
using std::stack;
using std::cin;
using std::cout;

const int MAX = 100;  //缓冲栈的最大数目
const int INF = 0x7fffffff;

class trainDispatch{
    public:
        trainDispatch();  //读入待排序的车厢编号数目和车厢编号，并储存在carrage[]中
        void solution();  //对待排序的车厢进行排序并不断输出
    private:
        stack<char> stackArray[MAX];  //缓冲栈
        int carrageNum;  //储存车厢数 
        int usedStackNum;  //已经使用过的缓冲轨道数
        int carrage[MAX];  //原始车厢序列
        int expectNum;  //待输出的车厢编号
        
        int findIncrementEnd(int start);  //找到carrage[start]开始的最大的递增项，返回其索引
        int findFirstEmpty(int st, int ed);  //找到第一个空的缓冲轨道 
        int findNearestBigger(int x, int st, int ed);  //遍历st到ed之间的缓冲轨道，寻找大于且最接近x的缓冲轨道编号，若存在，返回该轨道编号，否则，返回-1. 
        void move (int stIndex, int edIndex, int tempStack, int inStack);  //以tempStack为临时缓冲栈编号，inStack为目标栈编号，将stIndex到edIndex之间的车厢编号压                                                                              入inStack
        int findLargestTop(int st, int ed);  //遍历编号介于st与ed之间的缓冲轨道，寻找栈顶元素最大的轨道编号
        int findLargestLessThan(int index, int st, int ed);  //遍历编号介于st与ed之间的缓冲轨道，寻找栈顶元素最大且小于编号为index轨道的栈顶元素的轨道编号
        
        void MoveInSingle(int Index);  //只将编号为carrage[index]的车厢压入缓冲轨道
        void MoveInMoreThanOneSimple(int startIndex, int endIndex);  //将车厢编号从carrage[startIndex]到carrage[endIndex]的连续递增轨道压入缓冲轨道
        void MoveInMoreThanOneComplex(int startIndex, int endIndex);  //将车厢编号从carrage[startIndex]到carrage[endIndex]分为连续递增段并压入缓冲轨道
        void MoveOut(int&);  //遍历所有的缓冲轨道，若有符合下一个输出的元素，则将其输出
        void adjust(int st, int ed);  //对缓冲轨道进行优化
};

/*  输入所需要重排的车厢数目和车厢序列/
    车厢序列的读取方法为从左往右 */
trainDispatch::trainDispatch() {
    usedStackNum = 0;    cout << "please enter the number of the carrages:\n";
    cin >> carrageNum;
    cout << "please enter the serial number in order\n";
    for (int i = 0; i < carrageNum; i++) {
        cin >> carrage[i];
    }
}

void trainDispatch::solution() {
    int ed;
    int expectNum = 1;
    /* 从左往右依次遍历车厢号，若不符合输出，则将车厢号压入缓冲轨道/
    否则，将其输出，并遍历各个缓冲轨道，查询是否有符合条件的输出*/
    for (int i = 0; i < carrageNum ; i++) {
        if (carrage[i] != expectNum) {
            ed = findIncrementEnd(i);  //判断该车厢与其后面排列的车厢是否为递增关系，若不是则只将该车厢压入缓冲轨道
                                      // 否则将该串递增序列压入缓冲轨道
            if (ed == i) {  //无递增关系
                MoveInSingle(i);
            } else {  //i 到 ed之间为递增
                MoveInMoreThanOneComplex(i, ed); //将i-ed之间的元素压入缓冲轨道
                i = ed;
            }
        } else {
            cout << "the carrage-" << carrage[i] << " move straightly, doesn`t move into any stack\n";
            expectNum++;
            MoveOut(expectNum);  //遍历所有的缓冲轨道，查找是否有符合下一个输出
        }
        adjust(0, usedStackNum-1);  //遍历所有的缓冲轨道，根据轨道的栈顶元素，对轨道进行优化
    }
}

/*寻找以carrage[start]为始的递增序列，返回最大项的索引ed*/
int trainDispatch::findIncrementEnd(int start) {
    int ed = start;
    while (carrage[ed] < carrage[ed+1]) {
        ed++;
    }
    return ed;
}

/*寻找st到ed之间的第一个空栈，返回空栈的索引i*/
int trainDispatch::findFirstEmpty(int st, int ed) {
    int i = st;
    for (i = st; i <= ed; i++) {
        if (stackArray[i].empty()) {
            break;
        }
    }
    return i;
}

/* 遍历所有的缓冲轨道，寻找与所要入栈的元素x最接近且大于该元素的符合条件的缓冲轨道，返回该轨道的索引munNum*/
int trainDispatch::findNearestBigger(int x, int st, int ed) {
    int i;
    int min = INF;
    int minNum = -1;
    for (i = st; i <= ed; i++) {
        if (!stackArray[i].empty() && stackArray[i].top() > x) {
            if (min > stackArray[i].top()-x) {
                min = stackArray[i].top()-x;
                minNum = i;
            }
        }
    }
    return minNum;
}

/*遍历编号介于st与ed之间的缓冲轨道，寻找栈顶元素最大且小于编号为index轨道的栈顶元素的轨道编号,返回该轨道编号num*/
int trainDispatch::findLargestLessThan(int index, int st, int ed) {
    int num = -1;
    int largest = 0;
    for (int i = st; i <= ed; i++) {
        if (!stackArray[i].empty() && stackArray[i].top() < stackArray[index].top())
            if (largest < stackArray[i].top()) {
                largest = stackArray[i].top();
                num = i;
            }
    }
    return num;
}

/*将carrage[stIndex]与carrage[edIndex]之间的元素压入栈；
  tempStack作为临时栈的编号，inStack作为目标栈的编号*/
/*将递增车厢从stIndex~edIndex-1先压入一个缓冲栈stackArray[tempStack],
  将最大项直接压入目标栈stackArray[inStack]*/
/*逐个遍历缓冲栈stackArray[tempStack]中的元素，并将其压入最优缓冲轨道
  对于缓冲栈最后一个元素，考虑可能将其压回该缓冲栈的情况*/
void trainDispatch::move (int stIndex, int edIndex, int tempStack, int inStack) {
    for (int i = stIndex; i < edIndex; i++) {
        stackArray[tempStack].push(carrage[i]);
        cout << "the carrage-" << carrage[i] << " move into the stack-" << tempStack+1 << "\n";
    }
    stackArray[inStack].push(carrage[edIndex]);
    cout << "the carrage-" << carrage[edIndex] << " move into the stack-" << inStack+1 << "\n";
    for (int i = edIndex-1; i > stIndex; i--) {
        int temp = stackArray[tempStack].top();
        stackArray[tempStack].pop();
        int in = findNearestBigger(temp, tempStack+1, usedStackNum-1);
        stackArray[in].push(carrage[i]);
        cout << "the carrage-" << carrage[i] << " move out of stack-" << tempStack+1
             << ", then move in the stack-" << in+1<< "\n";
    }

    stackArray[tempStack].pop();
    int in = findNearestBigger(carrage[stIndex], tempStack, usedStackNum-1);
    stackArray[in].push(carrage[stIndex]);
    if (in != tempStack) {
        cout << "the carrage-" << carrage[stIndex] << " move out of stack-" << tempStack+1
             << ", then move in the stack-" << in+1<< "\n";
    }
}

/*遍历编号st到ed间的缓冲轨道，寻找栈顶车厢编号最大的栈，返回该栈的索引num*/
int trainDispatch::findLargestTop(int st, int ed) {
    int num = -1;
    int largest = 0;
    for (int i = st; i <= ed; i++) {
        if (! stackArray[i].empty()) {
            if (largest < stackArray[i].top()) {
                largest = stackArray[i].top();
                num = i;
            }
        }
    }
    return num;
}

/*只将一个车厢压入缓冲轨道*/
/*在所有的缓冲轨道中找不到比要入栈元素更大的栈；则寻找第一个空栈*/
/*若原有栈的数目不够，即没有空栈，则再创建一个空栈*/
void trainDispatch::MoveInSingle(int Index) {
    int emptyIndex;
    int in = findNearestBigger(carrage[Index], 0,usedStackNum-1);
    if (in == -1) {  
        emptyIndex = findFirstEmpty(0, usedStackNum-1);
        if (emptyIndex >= usedStackNum) { 
            usedStackNum++;
        }
        stackArray[emptyIndex].push(carrage[Index]);
        cout << "the carrage-" << carrage[Index] << " move into the stack-" << emptyIndex+1 << "\n";
    } else {
        stackArray[in].push(carrage[Index]);
        cout << "the carrage-" << carrage[Index] << " move into the stack-" << in+1 << "\n";
    }
}

/*将连续递增的车厢压入缓冲轨道*/
/*遍历所有缓冲轨道，若有符合条件的非空栈，则将其作为目标栈
  否则，寻找空栈作为目标栈*/
void trainDispatch::MoveInMoreThanOneSimple(int startIndex, int endIndex) {
    int in = findNearestBigger(carrage[endIndex], 0, usedStackNum-1);
    if (in > 0 && in < usedStackNum) {
        move(startIndex, endIndex, 0, in);
    }
    if (in == -1) {
        int firempty = findFirstEmpty(0, usedStackNum-1);
        if (firempty == usedStackNum) {  //所用过的栈中无空栈 
            //用过的栈的数目为0
            if (usedStackNum == 0) {
                usedStackNum+=2; //创建两个新栈，一个作为临时缓冲栈，一个作为目标栈
                move(startIndex,endIndex, 0, 1);
            } else {  //用过的栈不为空，且用过的栈的数目大于0 
                usedStackNum++;
                move(startIndex,endIndex, 0, usedStackNum-1);
            }
        } else {  //所用过的栈中有空栈
            if (firempty == 0) {  //第一个是空栈 
                int secEmpty = findFirstEmpty(firempty+1, usedStackNum-1); //再次寻找另一个空栈
                if (secEmpty == usedStackNum) {
                    usedStackNum++;
                }
                move(startIndex,endIndex, firempty, secEmpty);
            } else {
                move(startIndex,endIndex, 0, firempty); //第一个不是空栈，将第一个作为临时缓冲栈
            }
        }
    }
    if (in == 0) {
        in = findNearestBigger(carrage[endIndex], 1, usedStackNum-1);
        if (in >= 1 && in < usedStackNum) {
            move(startIndex, endIndex, 0, in);
        } else {
            int firempty = findFirstEmpty(1, usedStackNum-1);
            if (firempty == usedStackNum) {
                usedStackNum++;
            }
            move(startIndex,endIndex, 0, firempty);
        }
    }
}

/*将递增序列车厢压入缓冲轨道*/
/*将该段递增序列不同的连续递增段*/
/*例如：原缓冲轨道中有编号6的车厢，待压入的递增序列为34578，此时以6位界限，将其分为345和78分别压入缓冲轨道*/
void trainDispatch::MoveInMoreThanOneComplex(int startIndex, int endIndex) {
    int div;
    int in;
    for (div = endIndex; div >= startIndex; div--) {
        in = findNearestBigger(carrage[div], 0, usedStackNum-1);
        if (in > 0 && in < usedStackNum) {
            if (startIndex == div) {
                MoveInSingle(div);
            } else {
                MoveInMoreThanOneSimple(startIndex, div);
            }
            if (div+1 == endIndex) {
                MoveInSingle(endIndex);
            }
            if (div+1 < endIndex) {
                MoveInMoreThanOneSimple(div+1, endIndex);
            }
            break;
        }
    }
    if (div < startIndex) {
        MoveInMoreThanOneSimple(startIndex, endIndex);
    }
}

/*遍历所有的缓冲轨道，将符合下一个输出条件的车厢输出至出轨*/
void trainDispatch::MoveOut(int& expectNum) {
    bool con = true;
    while (con) {
        con = false;
        for (int k = 0; k < usedStackNum; k++) {
            if (!stackArray[k].empty()) {
                if (stackArray[k].top() == expectNum) {
                    con = true;
                    stackArray[k].pop();
                    cout << "the carrage-" << expectNum << " move out of the stack-" << k+1 << "\n";
                    expectNum++;
                }
            }
        }
    }
}

/*遍历编号从st到ed之间的所有缓冲轨道，尽可能对其进行优化*/
void trainDispatch::adjust(int st, int ed) {
    int largest = findLargestTop(st, ed);
    if (largest == -1) {  //若均为空栈，不用调整 
        return;
    }
    while (largest != -1) {
        int leftLargest = findLargestLessThan(largest, st, largest-1);
        while (leftLargest != -1) {
            int temp = stackArray[leftLargest].top();
            stackArray[leftLargest].pop();
            if (stackArray[leftLargest].empty() || stackArray[leftLargest].top() > stackArray[largest].top()) {
                stackArray[largest].push(temp);
                cout << "the carrage-" << temp << " move out of stack-" << leftLargest+1
                      << ", then move in the stack-" << largest+1<< "\n";
                largest = findLargestTop(st, ed);
                break;
            } else {
                stackArray[leftLargest].push(temp);
                leftLargest = findLargestLessThan(leftLargest, st, largest-1);
            }
        }
        if (leftLargest == -1) {
            largest = findLargestLessThan(largest, st, ed);
        }
    }
}

int main() {
    trainDispatch t;
    t.solution();
    return 0;
}