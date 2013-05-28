class Node:
    def __init__(self, keys=None, children=None):
        self.keys = keys or []
        self.children = children or []

class NonLeaf(Node):
    pass

class Leaf(Node):
    def __init__(self, records, keys_per_node):
        blanks = keys_per_node - len(records)

        self.keys = [record[0] for record in records] + ([None] * blanks)
        self.children = [record[1] for record in records] + ([None] * blanks)

class Tree:
    def __init__(self, keys_per_node=4):
        self.keys_per_node = keys_per_node
        self.root = NonLeaf(keys=[None]*keys_per_node, 
                            children=[None]*(keys_per_node+1) )

    def insert(self, record):
        self.root.keys[0] = record[0]
        self.root.children[0] = Leaf([record], self.keys_per_node)
