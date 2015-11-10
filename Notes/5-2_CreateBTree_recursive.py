'''
A module that construct binary tree recursively using nested tuple
as argument.
Frequently used helper function when learning binary tree data
structure.
'''

class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

    def __repr__(self):
        return str(self.val)

tree = ('a', ('b', 'd', ('e', ('f', None, 'g'), None)), 'c')

def CreateBTree(infoset):
    '''
    Take a tuple contains binary tree structure information as
    argument, construct tree recursively and return the root.
    '''
    # print('infoset:', infoset)
    if infoset:
        try:
            root, leftsub, rightsub = infoset
        except ValueError:
            root = infoset[0]
            leftsub = None
            rightsub = None
    else:
        return None
    root = TreeNode(root)
    if not root:
        return None
    else:
        root.left = CreateBTree(leftsub)
        root.right = CreateBTree(rightsub)
    return root

def postorder(root):
    if root:
        postorder(root.left)
        postorder(root.right)
        print(root.val, end=' ')

if __name__ == '__main__':
    
    test = CreateBTree(tree)

    postorder(test)


