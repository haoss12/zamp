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

    if (!ReadFile("config/config.xml", Config))
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

    if (sender.OpenConnection() == false)
    {
        std::cerr << "Blad przy otwieraniu polaczenia! " << std::endl;
        return 0;
    }

    std::thread SendThread(&Sender::Watching_and_Sending, &sender);

    while (true)
    {
    }

    if (argc < 2)
    {
        std::cerr << "Zbyt malo argumentow wywolania! " << std::endl;
        return 0;
    }

    // test if all of the components in set are working properly

    std::vector<std::string> list{"Move", "Set", "Rotate", "Pause"};

    std::istringstream iss;
    std::string command;
    std::string keyword;

    ExecutePreprocessing(argv[1], iss);

    while (std::getline(iss, command))
    {
        std::cout << "wczytano: " << command << std::endl;
        std::istringstream issTemp;
        issTemp.str(command); // giving only fragment of the stream, not the whole
        issTemp >> keyword;

        try
        {
            AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(keyword.c_str())->CreateCmd();
            std::cout << std::endl;
            if (pCmd->ReadParams(issTemp) == false)
            {
                std::cerr << "nie udalo sie odczytac argumentow" << std::endl;
            }
            pCmd->PrintCmd();
            std::cout << std::endl;

            delete pCmd;
            issTemp.str("\0");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

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
