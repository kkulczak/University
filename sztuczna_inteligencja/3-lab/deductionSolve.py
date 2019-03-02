from picture import *

if __name__ == '__main__':
    try:
        p = Picture()
        p.genPerms()
        # while not p.isSolved():
        p.detuctAll()
        p.saveOtput()
    except ImpossibleConstraints as e:
        print('COYGHT')
        pass

