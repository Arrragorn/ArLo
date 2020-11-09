#include <python.h>
#include <string>
#include <iostream>
#include <dshow.h>

#pragma comment(lib, "Strmiids.lib")

IGraphBuilder* pGraph = NULL;
IMediaControl* pControl = NULL;
IMediaEvent* pEvent = NULL;
IMediaSeeking* pSeek = NULL;

bool play = false;
bool accel = false;



static PyObject*
boucleSimple(PyObject* self, PyObject* args)
{
    const int* iterations;

    if (!PyArg_ParseTuple(args, "i", &iterations))
    {
        printf("Argument invalide");
        return PyLong_FromLong(-1);
    }
   
    int nbIterations = *iterations;

    for (int i = 0; i < nbIterations; i++)
    {
        printf("%d\n", nbIterations);
    }

    return PyLong_FromLong(-0);
}

static PyObject*
spam_play(PyObject* self, PyObject* args)
{
  
    return PyLong_FromLong(-0);
}


static PyObject*
spam_pause(PyObject* self, PyObject* args)
{
 
    return PyLong_FromLong(-0);
}




static PyMethodDef SpamMethods[] = {
    {"run",  boucleSimple, METH_VARARGS,
     "run a video"},
     {"pause",  spam_pause, METH_VARARGS,
     "pause the running video"},
     {"play",  spam_play, METH_VARARGS,
     "play the running video"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "boucleThread",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};




PyMODINIT_FUNC
PyInit_boucleThread(void)
{
    return PyModule_Create(&spammodule);
}



/*int main(int argc, char* argv[])
{
    wchar_t* program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    // Add a built-in module, before Py_Initialize
    if (PyImport_AppendInittab("spam", PyInit_spam) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    // Pass argv[0] to the Python interpreter
    Py_SetProgramName(program);

    // Initialize the Python interpreter.  Required.
    //  If this step fails, it will be a fatal error.
    Py_Initialize();

        PyMem_RawFree(program);
    return 0;
}*/


