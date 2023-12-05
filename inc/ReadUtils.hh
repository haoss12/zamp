#ifndef READUTILS_HH
#define READUTILS_HH

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
bool ReadFile(const char *sFileName, Configuration &rConfig);

#define BUF_SIZE 512

bool ExecutePreprocessing(const char *sFileName, std::istringstream &issCommands);

#endif // READUTILS_HH