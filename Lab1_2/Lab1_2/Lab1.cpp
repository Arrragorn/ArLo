
//Projet recible
#include <iostream>
#include <dshow.h>
#include <string>

#pragma comment(lib, "Strmiids.lib")


void afficherMenu();

void main()
{
    std::cout << "Hello World!\n";
    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;
    IMediaSeeking* pSeek = NULL;

    // Initialize the COM library.
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
            bool accel = false;
            int delay = 10;
                long evCode;

                pEvent->WaitForCompletion(INFINITY, &evCode);
                while (running) {
                    afficherMenu();
                std::cin >> command;
                command = toupper(command[0]);
                if (command == "P")
                {
                    if (play)
                    {
                        pControl->Pause();
                    }
                    else {
                        pControl->Run();
                    }
                    play = !play;
                }
                else if (command == "Q")
                {
                    running = false;
                }
                else if (command == "R")
                {
                    REFERENCE_TIME rtNow = 0;
                    hr = pSeek->SetPositions(
                        &rtNow, AM_SEEKING_AbsolutePositioning,
                        NULL, AM_SEEKING_NoPositioning);
                }
                else if(command == "A"){
                    if (accel)
                    {
                        pSeek->SetRate(1.0);
                    }
                    else
                    {
                        pSeek->SetRate(2.0);

                    }
                    accel = !accel;
               
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
    pSeek->Release();
    CoUninitialize();

}

void afficherMenu(){

    std::cout << "Menu des commandes" << std::endl;
    std::cout << "P - Play ou Pause" << std::endl;
    std::cout << "A - Avance acceleree" << std::endl;
    std::cout << "R - Retour au debut" << std::endl;
    std::cout << "Q - Quitter" << std::endl;

}