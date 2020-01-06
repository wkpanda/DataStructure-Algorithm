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
