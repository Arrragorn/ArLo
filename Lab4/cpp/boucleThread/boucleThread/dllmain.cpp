#include <python.h>
#include <string>
#include <iostream>
#include <dshow.h>
#include <thread>
#include <vector>
#include <iostream>

#pragma comment(lib, "Strmiids.lib")

IGraphBuilder* pGraph = NULL;
IMediaControl* pControl = NULL;
IMediaEvent* pEvent = NULL;
IMediaSeeking* pSeek = NULL;

int iterations;
int nbThreads = 4;
//void task();


class Task {
public:
    static void task(int stop) {
        std::thread::id this_id = std::this_thread::get_id();
      
        for (volatile int i = 0; i < stop; i++);
        
    }
};


static PyObject*
boucleSimple(PyObject* self, PyObject* args)
{
  

    if (!PyArg_ParseTuple(args, "i", &iterations))
    {
        printf("Argument invalide");
        return PyLong_FromLong(-1);
    }
   

    for (volatile int i = 0; i < iterations; i++);
   

    return PyLong_FromLong(-0);
}

static PyObject*
boucleThread(PyObject* self, PyObject* arg1)
{

    if (!PyArg_ParseTuple(arg1, "i", &iterations))
    {
        printf("Argument invalide");
        return PyLong_FromLong(-1);
    }


    std::vector<std::thread> vecThreads;
    std::vector<int> vecStart;
    std::vector<int> vecStop;

    for (int i = 0; i < nbThreads; i++)
    {

        vecStop.push_back(iterations / nbThreads);
        vecThreads.push_back(std::thread(&Task::task, vecStop[i]));
    }
   
    for (int i = 0; i < nbThreads; i++)
    {
        vecThreads[i].join();
    }
   
    return PyLong_FromLong(-0);
}





static PyMethodDef SpamMethods[] = {
    {"boucleSimple",  boucleSimple, METH_VARARGS,
     "run boucle simple"},
     {"boucleThread",  boucleThread, METH_VARARGS,
     "run boucle thread"},
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


