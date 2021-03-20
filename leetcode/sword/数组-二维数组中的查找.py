class Solution:
    # array 二维列表
    def Find(self, target, array):
        while(True):
            try:
                if target < array[0][-1]:
                    array = [h[:-1] for h in array ]
                elif target == array[0][-1]:
                    return True
                else:
                    array = array[1:]
            except:
                return False