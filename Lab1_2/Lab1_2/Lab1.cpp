
//Projet recible
#include <iostream>
#include <dshow.h>
#include <string>

#pragma comment(lib, "Strmiids.lib")



int main()
{
    std::cout << "Hello World!\n";
    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;

    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return 1;
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return 1;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

    // Build the graph. IMPORTANT: Change this string to a file on your system.
    hr = pGraph->RenderFile(L"Example.avi", NULL);

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            std::string command;
            bool running = true;
            bool play = true;
            int delay = 10;
            while (running) {
                long evCode;
                pEvent->WaitForCompletion(delay, &evCode);
                std::cin >> command;
                if (command == "P")
                {
                    if (play)
                    {
                        pControl->Pause();
                    }
                    else {
                        pControl->Run();
                    }
                    play = ~play;
                }


            }
            // Wait for completion.
           

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

    return 0;
}
