cdef extern from "Test.h":
	int add(int a, int b)
	int multipy(int a, int b)

print add(2,3)
print multipy(2,3)

cpdef py_add(int a, int b):
	return add(a, b)
