#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include <map>
#include <memory>
#include <exception>
#include <vector>
#include <algorithm>

#include "Set4LibInterfaces.hh"

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
  std::string word;

  ExecutePreprocessing(argv[1], iss);

  while (std::getline(iss, command))
  {
    std::cout << "wczytano: " << command << std::endl;
    std::istringstream issTemp;
    issTemp.str(command); // giving only fragment of the stream, not the whole 
    issTemp >> word;

    if (std::find(list.begin(), list.end(), word) != list.end())
    {
      AbstractInterp4Command *pCmd = SetOfInterfaces.get_pLibInterface(word.c_str())->CreateCmd();
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
