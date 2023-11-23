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

#include "Set4LibInterfaces.hh"

#include "xmlinterp.hh"

using namespace std;
using namespace xercesc;

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char *sFileName, Configuration &rConfig)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException &toCatch)
    {
        char *message = XMLString::transcode(toCatch.getMessage());
        cerr << "Error during initialization! :\n";
        cerr << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    SAX2XMLReader *pParser = XMLReaderFactory::createXMLReader();

    pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(XMLUni::fgXercesDynamic, false);
    pParser->setFeature(XMLUni::fgXercesSchema, true);
    pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

    pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

    DefaultHandler *pHandler = new XMLInterp4Config(rConfig);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try
    {

        if (!pParser->loadGrammar("config/config.xsd", xercesc::Grammar::SchemaGrammarType, true))
        {
            cerr << "!!! Plik grammar/actions.xsd, '" << endl
                 << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany." << endl;
            return false;
        }
        pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
        pParser->parse(sFileName);
    }
    catch (const XMLException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        cerr << "Informacja o wyjatku: \n"
             << "   " << sMessage << "\n";
        XMLString::release(&sMessage);
        return false;
    }
    catch (const SAXParseException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

        cerr << "Blad! " << endl
             << "    Plik:  " << sSystemId << endl
             << "   Linia: " << Exception.getLineNumber() << endl
             << " Kolumna: " << Exception.getColumnNumber() << endl
             << " Informacja: " << sMessage << endl;

        XMLString::release(&sMessage);
        XMLString::release(&sSystemId);
        return false;
    }
    catch (...)
    {
        cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
        return false;
    }

    delete pParser;
    delete pHandler;
    return true;
}

#define BUF_SIZE 512

bool ExecutePreprocessing(const char *sFileName, std::istringstream &issCommands)
{
    std::string preprocessor = "cpp -P ";
    char line_buffer[BUF_SIZE];
    std::ostringstream outStrm;

    preprocessor += sFileName;
    FILE *pProc = popen(preprocessor.c_str(), "r"); // open process

    if (!pProc)
    {
        return false;
    }

    while (fgets(line_buffer, BUF_SIZE, pProc))
    {
        outStrm << line_buffer;
    }

    issCommands.str(outStrm.str());

    return pclose(pProc) == 0;
}

int main(int argc, char const *argv[])
{

    Configuration Config;

    if (!ReadFile("config/config.xml", Config))
        return 1;

    std::cout << std::endl << std::endl << "Wczytane z XML elementy: " << std::endl;
    std::cout << std::endl;

    for (auto &i : Config._Libs)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    for (auto &i : Config._mobileObjs)
    {
        std::cout << i.GetName() << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    if (argc < 2)
    {
        std::cerr << "Zbyt malo argumentow wywolania! " << std::endl;
        return 0;
    }

    Set4LibInterfaces SetOfInterfaces;
    if (!SetOfInterfaces.Init())
    {
        return 1;
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
