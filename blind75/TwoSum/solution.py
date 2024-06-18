class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hash = {}
        for i in range(len(nums)):
            hash.setdefault(nums[i], []).append(i)

        for i in range(len(nums)):
            if target-nums[i] in hash:
                if target-nums[i] == nums[i] and len(hash[nums[i]]) > 1:
                    return [i, hash[target-nums[i]][1]]
                elif target-nums[i] != nums[i]:
                    return [i, hash[target-nums[i]][0]]