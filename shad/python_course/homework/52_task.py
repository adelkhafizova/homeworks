class Stack(object):
    def __init__(self, elements=None):
        if elements is None:
            self.elements = []
        else:
            self.elements = elements
    def push(self, el):
        self.elements.append(el)
    def pop(self):
        return self.elements.pop()
    def __len__(self):
        return len(self.elements)

a = []
s = Stack()
s.push(1)
s1 = Stack()
print(len(s1))
print s1.pop()
print s.pop()
print len(s)

