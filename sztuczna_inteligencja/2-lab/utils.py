def replaceTuple(tup, prevObj, newObj):
    i = tup.index(prevObj)
    return tup[:i] + (newObj,) + tup[i + 1:]
