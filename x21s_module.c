#include <Python.h>
#include "x21s.h"

static PyObject *x21s_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);
#if PY_MAJOR_VERSION >= 3
    x21s_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x21s_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef x21sMethods[] = {
    { "getPoWHash", x21s_getpowhash, METH_VARARGS, "Returns the proof of work hash using x21s" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef x21sModule = {
    PyModuleDef_HEAD_INIT,
    "x21s_hash",
    "...",
    -1,
    x21sMethods
};

PyMODINIT_FUNC PyInit_x21s_hash(void) {
    return PyModule_Create(&x21sModule);
}

#else

PyMODINIT_FUNC initx21s_hash(void) {
    (void) Py_InitModule("x21s_hash", x21sMethods);
}
#endif
