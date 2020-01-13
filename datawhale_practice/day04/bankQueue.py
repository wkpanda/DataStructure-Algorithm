import time
import threading

#号码
class Node():
    def __init__(self,x):
        self.data = x
        self.next=None
# 队列结构
class LinkedQueue():
    def __init__(self):
        self._head = None
        self._tail = None

    def is_empty(self):
        if self._head == self._tail:
            return True
        else:
            return False

    # 入队
    def enqueue(self, val):
        newNode = Node(val)
        # 如果链表队列为空
        if self._tail == None:
            self._head = newNode
        else:
            self._tail.next = newNode
        self._tail = newNode

    # 出队
    def dequeue(self):
        # 如果队列为空
        if self._head == self._tail:
            return None
        else:
            node = self._head
            self._head = self._head.next
            return node.data

    def __repr__(self):
        # 队列为空
        if self._head == self._tail:
            return '空'
        else:
            result = []
            cur = self._head
            while cur != None:
                result.append(cur.data)
                cur = cur.next
            return '->'.join(str(x) for x in result)
# 银行排队系统，存储排队号码
class LinkBankQueue(LinkedQueue):
    def __init__(self):
        LinkedQueue.__init__(self)
        self.callNumber = 0

    def getCallNumber(self):
        if self.is_empty() and self.callNumber == 0:
            self.callNumber = 1
        else:
            self.callNumber += 1
        return self.callNumber

    def getLength(self):
        if self.is_empty():
            return 0
        else:
            cur = self._head
            len = 1
            while cur != self._tail:
                cur = cur.next
                len += 1
            return len

# 服务器
class ServiceWindow(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.bankQueue = None
        self.lock = threading.Lock()

    def service(self):
        self.lock.acquire()
        while True:
            time.sleep(5)
            try:
                if not self.bankQueue.is_empty():
                    print('请 %d 号到 %s 号窗口' % (self.bankQueue._head.data, threading.current_thread().name))
                    self.bankQueue.dequeue()
                    # time.sleep(10)
                else:
                    print('队列为空哦')
            finally:
                self.lock.release()
#客户端
if __name__ == '__main__':
    bankQueue = LinkBankQueue()
    windowcount = 2
    serviceWindows = [None] * windowcount
    threadList = [None] * windowcount
    for i in range(windowcount):
        serviceWindows[i] = ServiceWindow()
        serviceWindows[i].bankQueue = bankQueue
        threadList[i] = threading.Thread(name=(i + 1), target=serviceWindows[i].service, args=())
        threadList[i].start()
    while True:
        input('请点击触摸屏获取号码：')
        callNumber = bankQueue.getCallNumber()
        if bankQueue != None:
            print('您的号码是：%d，您前面有 %d 位' % (callNumber, bankQueue.getLength()))
            bankQueue.enqueue(callNumber)
        else:
            print('您的号码是：%d，您前面有 0 位' % (callNumber))