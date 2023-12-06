#include <algorithm>
#include <cassert>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>
#include <thread>

#include "Scene.hh"
#include "xmlinterp.hh"
#include "ReadUtils.hh"
#include "Sender.hh"

using namespace std;

int main(int argc, char const *argv[])
{

    Configuration Config;

    if (!ReadFile("config/config2.xml", Config))
    {
        return 1;
    }

    Scene scena(Config);

    Sender sender(&scena);

    Set4LibInterfaces SetOfInterfaces;

    for (auto &name : Config._Libs)
    {
        if (SetOfInterfaces.AddLib(name) != true)
        {
            cerr << "Nie udalo sie wczytac biblioteki: " << name << endl;
        }
        else
        {
            cout << "Wczytano biblioteke: " << name << endl;
        }
    }

    if (argc < 2)
    {
        std::cerr << "Zbyt malo argumentow wywolania! " << std::endl;
        return 0;
    }

    if (sender.OpenConnection() == false)
    {
        std::cerr << "Blad przy otwieraniu polaczenia! " << std::endl;
        return 0;
    }

    std::thread SendThread(&Sender::Watching_and_Sending, &sender);

    std::istringstream iss;
    std::string command;
    std::string keyword;

    std::vector<std::thread> threads;

    ExecutePreprocessing(argv[1], iss);

    while (std::getline(iss, command))
    {
        std::cout << "wczytano: " << command << std::endl;

        if (command == "Begin_Parallel_Actions")
        {
            while (std::getline(iss, command))
            {
                std::cout << "wczytano: " << command << std::endl;
                if (command == "End_Parallel_Actions")
                {
                    break;
                }

                std::istringstream issTemp;
                issTemp.str(command); // giving only fragment of the stream, not the whole
                issTemp >> keyword;

                try
                {
                    AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(keyword.c_str())->CreateCmd();
                    if (pCmd->ReadParams(issTemp) == false)
                    {
                        std::cerr << "nie udalo sie odczytac argumentow" << std::endl;
                    }
                    threads.push_back(std::thread(&AbstractInterp4Command::ExecCmd, pCmd, std::ref(scena)));
                    issTemp.str("\0");
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            for (int i = 0; i < threads.size(); ++i)
            {
                if (threads[i].joinable())
                    threads[i].join();
            }
            threads.clear();
        }
    }

    sender.Send("Close\n");
    sender.CancelCountinueLooping();
    for (int i = 0; i < threads.size(); ++i)
    {
        if (threads[i].joinable())
            threads[i].join();
    }

    SendThread.join();

    return 0;

    // for (auto &s : list)
    // {
    //   AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(s.c_str())->CreateCmd();

    //   std::cout << std::endl;
    //   std::cout << pCmd->GetCmdName() << std::endl;
    //   pCmd->PrintSyntax();
    //   pCmd->PrintCmd();
    //   std::cout << std::endl;

    //   delete pCmd;
    // }
}
