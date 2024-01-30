# # TC 2C 6C TS KC QS QC 3C KD 8D JH JS KH
# # 5D JD 2S 8S AS 9S 3D 5H 9C AH 4D 4C KS
# # JC 4S 7S 6D 2H 7C 8C 7D AD 7H TH 2D QH
# # 8H 9H 5C TD 3S 6H 3H QD 5S 9D 4H 6S AC

# arr = list(map(str,input().split(" ")))
# arr += list(map(str,input().split(" ")))
# arr += list(map(str,input().split(" ")))
# arr += list(map(str,input().split(" ")))


# # compare function
# def cmp(a, b):
#     if a[0] == b[0] or a[1] == b[1]:
#         return True
#     return False

# def test():
#     print(arr)
#     def searchList(found, cards):
#         print('hi')
#         for j in range(3, 0, -1):
#             print("j = ", j)
#             if not found:
#                 for i in range(cards-j, 0, -1):
#                     if cmp(arr[i], arr[i+j]):
#                         #we found a match
#                         print(arr)
#                         print('i = ', i)
#                         print('j = ', j)
#                         print('FOUND MATCH: ', arr[i], arr[i+j])
#                         found = True
#                         k = j
#                         c = 0
#                         while c < j+1:
#                             print(arr)
#                             if len(arr) - 1 <= k: del(arr[k])
#                             else: del(arr[len(arr) - 1])
#                             c += 1
#                             cards -= 1
#                         print(arr)
#                         break
#             else: break
#         return found, cards

#     found, cards = searchList(False, 7)
    
#     while cards != len(arr):
#         print("TURNING OVER A CARD", len(arr) - cards)
#         while found: 
#             found, cards = searchList(False, cards)
#         if not found:
#             cards += 1
#             found = True
#     print(arr)
  

# test()


def recurse(hand):
    if len(hand) >= 4:
        for i in range(len(hand)-1,2,-1):
            # value
            if hand[i][0] == hand[i-3][0]:
                del hand[i-3]
                del hand[i-3]
                del hand[i-3]
                del hand[i-3]
                return recurse(hand)

        for i in range(len(hand)-1,2,-1):
            # suit
            if hand[i][1] == hand[i-3][1]:
                del hand[i-3]
                del hand[i-1]
                return recurse(hand)
    return hand

arr = (input() + " " + input() + " " + input() + " " + input()).split()
hand = []

for card in arr:
    hand.append(card)

    # check new card
    if len(hand) < 4:
        continue

    # value
    if hand[-1][0] == hand[-4][0]:
        hand.pop()
        hand.pop()
        hand.pop()
        hand.pop()

    # suit
    elif hand[-1][1] == hand[-4][1]:
        hand.pop()
        del hand[-3]
        recurse(hand)
            
    
print(len(hand), end=" ")
for i in hand: print(i, end=" ")
