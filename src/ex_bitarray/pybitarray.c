/* Crossover code to create the interface for bitarray as a Python object */
#include "Python.h"
#include "bitarray.h"

/* Define fields for a BitArray type */
typedef struct {
    PyObject_HEAD /* Python gubbins */
    void *bitarray_pointer; 
    unsigned int num_elements; /* length (individual bits) */
} BitArray;

/* Behaviour of BitArray.__init__(num_elements) */
static int
BitArray_init(BitArray *self, PyObject *args, PyObject *kwds) {
    const unsigned int num_elements;

    /* parse single argument; long unsigned integer into num_elements */
    if(!PyArg_ParseTuple(args, "I", &num_elements))
        return -1;

    /* pack initial values into BitArray struct */
    self->num_elements = num_elements;
    self->bitarray_pointer = ba_build(num_elements);

    if(NULL == self->bitarray_pointer) {
        PyErr_NoMemory();
    }
    return 0;
}

/* Behaviour of BitArray.__del__() */
static void
BitArray_dealloc(BitArray *self) {
    free(self->bitarray_pointer);
    self->ob_type->tp_free((PyObject*) self);
}

/* Behaviour of BitArray.set(index) */
static PyObject *
BitArray_set(BitArray *self, PyObject *args) {
    const unsigned int index;
    if(!PyArg_ParseTuple(args, "I", &index))
        return NULL;
    
    if(index > self->num_elements) {
        PyErr_SetString(PyExc_IndexError, "Index out of array bounds");
        return NULL;
    }

    ba_set(self->bitarray_pointer, index);
    return Py_BuildValue("");
}

/* Behaviour of BitArray.get(index) */
static PyObject *
BitArray_get(BitArray *self, PyObject *args) {
    const unsigned int index;
    if(!PyArg_ParseTuple(args, "I", &index))
        return NULL;

    if(index > self->num_elements) {
        PyErr_SetString(PyExc_IndexError, "Index out of bounds");
        return NULL;
    }
    int result = (int)ba_get(self->bitarray_pointer, index);
    return Py_BuildValue("i", result);
}

static PyMethodDef
BitArray_methods[] = {
    { "set", (PyCFunction) BitArray_set, METH_VARARGS, "Set an index to TRUE" },
    { "get", (PyCFunction) BitArray_get, METH_VARARGS, "Get value for an index" },
    { NULL }
};

static PyTypeObject
BitArrayType = {
   PyObject_HEAD_INIT(NULL)
   0,                         /* ob_size */
   "BitArray",                /* tp_name */
   sizeof(BitArray),          /* tp_basicsize */
   0,                         /* tp_itemsize */
   (destructor)BitArray_dealloc, /* tp_dealloc */
   0,                         /* tp_print */
   0,                         /* tp_getattr */
   0,                         /* tp_setattr */
   0,                         /* tp_compare */
   0,                         /* tp_repr */
   0,                         /* tp_as_number */
   0,                         /* tp_as_sequence */
   0,                         /* tp_as_mapping */
   0,                         /* tp_hash */
   0,                         /* tp_call */
   0,                         /* tp_str */
   0,                         /* tp_getattro */
   0,                         /* tp_setattro */
   0,                         /* tp_as_buffer */
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags*/
   "BitArray object",        /* tp_doc */
   0,                         /* tp_traverse */
   0,                         /* tp_clear */
   0,                         /* tp_richcompare */
   0,                         /* tp_weaklistoffset */
   0,                         /* tp_iter */
   0,                         /* tp_iternext */
   BitArray_methods,          /* tp_methods */
   //BitArray_members,          /* tp_members */
   0,   // tp_members
   0,                         /* tp_getset */
   0,                         /* tp_base */
   0,                         /* tp_dict */
   0,                         /* tp_descr_get */
   0,                         /* tp_descr_set */
   0,                         /* tp_dictoffset */
   (initproc)BitArray_init,   /* tp_init */
   0,                         /* tp_alloc */
   0,                         /* tp_new */
};

/* Initialise the module */
void
initbitarray(void) {
    /* Create the module object */
    PyObject *module;
    module = Py_InitModule3("bitarray", NULL, "Really small binary arrays");
    if(NULL == module)
        return;

    // Fill in some slots in the BitArray type
    BitArrayType.tp_new = PyType_GenericNew;
    if(PyType_Ready(&BitArrayType) < 0)
        return;

    // Add the BitArray type to the module
    Py_INCREF(&BitArrayType);
    PyModule_AddObject(module, "BitArray", (PyObject*)&BitArrayType);
}
