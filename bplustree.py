class Node:
    def __init__(self, values=None, records=None):
        self.values = values or []
        self.records = records or []

class NonLeaf(Node):
    pass

class Leaf(Node):
    pass

class Tree:
    def __init__(self):
        self.root = NonLeaf()
