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
spam_run(PyObject* self, PyObject* args)
{
    std::string path_s;
    const char* path;

    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        return PyLong_FromLong(-3);
    }

    if (!PyArg_ParseTuple(args, "s", &path))
        return PyLong_FromLong(-1);
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);

    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);


    // Build the graph. 
    path_s = std::string(path);
    std::wstring wpath_s(path_s.length(), L'#');
    mbstowcs(&wpath_s[0], path_s.c_str(), path_s.length());
    hr = pGraph->RenderFile(wpath_s.c_str(), NULL);

    if (SUCCEEDED(hr))
    {
        hr = pControl->Run();
        play = true;
        return PyLong_FromLong(0);
    }
    else
    {
        return PyLong_FromLong(-2);
    }
}

static PyObject*
spam_play(PyObject* self, PyObject* args)
{
    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        pControl->Run();
    }
    return PyLong_FromLong(0);
}


static PyObject*
spam_pause(PyObject* self, PyObject* args)
{
    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        pControl->Pause();
    }
    return PyLong_FromLong(0);
}


static PyObject*
spam_accelerate1(PyObject* self, PyObject* args)
{
    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        pSeek->SetRate(1.0);
    }
    return PyLong_FromLong(0);
}


static PyObject*
spam_accelerate2(PyObject* self, PyObject* args)
{
    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        pSeek->SetRate(2.0);
        }
    return PyLong_FromLong(0);
}
static PyObject*
spam_quit(PyObject* self, PyObject* args)
{
    if (pGraph != NULL || pControl != NULL || pEvent != NULL || pSeek != NULL)
    {
        pControl->Release();
        pEvent->Release();
        pGraph->Release();
        pSeek->Release();
        CoUninitialize();

        play = false;
        pControl = NULL;
        pEvent = NULL;
        pGraph = NULL;
        pSeek = NULL;
    }
    return PyLong_FromLong(0);
}

static PyObject*
spam_replay(PyObject* self, PyObject* args)
{
    REFERENCE_TIME rtNow = 0;
    pSeek->SetPositions(
        &rtNow, AM_SEEKING_AbsolutePositioning,
        NULL, AM_SEEKING_NoPositioning);
    return PyLong_FromLong(0);
}


static PyMethodDef SpamMethods[] = {
    {"run",  spam_run, METH_VARARGS,
     "run a video"},
     {"pause",  spam_pause, METH_VARARGS,
     "pause the running video"},
     {"play",  spam_play, METH_VARARGS,
     "play the running video"},
     {"replay",  spam_replay, METH_VARARGS,
     "replay the running video"},
     {"quit",  spam_quit, METH_VARARGS,
     "quit the running video"},
     {"accelerate1x",  spam_accelerate1, METH_VARARGS,
     "accelerate 1x the running video"},
     {"accelerate2x",  spam_accelerate2, METH_VARARGS,
     "accelerate 2x the running video"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};




PyMODINIT_FUNC
PyInit_spam(void)
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


