from collections import Counter
import random


def mmap(f, l):
    return list(map(f, l))


colours = ['S', 'H', 'D', 'C']
blotkarz_num = list(map(lambda x: str(x), list(range(10))))
figurant_num = ['A', 'K', 'D', 'J']

blotkarz_set = []
figurant_set = []
for c in colours:
    for n in blotkarz_num:
        blotkarz_set.append(c + n)
    for n in figurant_num:
        figurant_set.append(c + n)


def colors(hand):
    return list(map(lambda x: x[0], hand))


def nums(hand):
    return list(map(lambda x: x[1], hand))


def isPair(hand):
    hand = Counter(nums(hand)).values()
    return 2 in hand


def isTwoPairs(hand):
    hand = Counter(nums(hand)).values()
    if 2 in hand:
        hand.remove(2)
        return 2 in hand
    return False


def isThree(hand):
    hand = Counter(nums(hand)).values()
    return 3 in hand


def isQuads(hand):
    hand = Counter(nums(hand)).values()
    return 4 in hand


def isFullHouse(hand):
    hand = Counter(nums(hand)).values()
    if 3 in hand:
        hand.remove(3)
        return 2 in hand
    return False


def isColor(hand):
    hand = Counter(colors(hand)).values()
    return 5 in hand


def isStrit(hand):
    hand = sorted(mmap(lambda x: ord(x), nums(hand)))
    val = hand[0]
    hand.remove(hand[0])
    while len(hand) > 0:
        if hand[0] == val + 1:
            val += 1
            hand.remove(hand[0])
        else:
            return False
    return True


def isPoker(hand):
    return isColor(hand) and isStrit(hand)


checks = [
    isPoker,
    isQuads,
    isFullHouse,
    isColor,
    isStrit,
    isThree,
    isTwoPairs,
    isPair
]



def whichBeter(data):
    resB = mmap(lambda item: item(data['blotkarz']), checks)
    resF = mmap(lambda item: item(data['figurant']), checks)
    # print(data['blotkarz'])
    # print(resB)
    for i in range(len(resB)):
        if resB[i] is resF[i]:
            continue
        if resB[i] is True:
            return 'blotkarz'
        if resF[i] is True:
            return 'figurant'
    return 'figurant'


def genHand(set):
    res = []
    while len(res) < 5:
        x = random.choice(set)
        if not(x in res):
            res.append(x)
    return res


def run_test(matches, bl_deck, fg_deck):
    wins = {
        'blotkarz': 0,
        'figurant': 0
    }
    for i in range(matches):
        data = {
            'blotkarz': genHand(bl_deck),
            'figurant': genHand(fg_deck)
        }
        wins[whichBeter(data)] += 1
    return (float(wins['blotkarz']) / float(matches)) * 100.0
    # return float(wins['blotkarz']) / 3.0


def gen_deck(colors, nums):
    res = []
    for x in colors:
        for y in nums:
            res.append(x + y)
    return res

MATCHES = 50000

a = run_test(MATCHES, blotkarz_set, figurant_set)
print(a)
b = run_test(MATCHES, gen_deck(['H'], blotkarz_num), figurant_set)
print(b)
c = run_test(MATCHES, gen_deck(['H'], list(map(lambda x: str(x), [0, 1, 2, 3, 4]))),
    figurant_set)
print(c)
d = run_test(MATCHES, gen_deck(colours, list(map(lambda x: str(x), [3, 4, 5,6 , 7, 8, 9 ]))),
    figurant_set)
print(d)
