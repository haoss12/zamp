#ifndef COMMAND4ROTATE_HH
#define COMMAND4ROTATE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "AbstractInterp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluj47e ...
 */
class Interp4Rotate : public AbstractInterp4Command
{
  std::string _ObjName;

  /*
   * Os obrotu dla obiektu - dozwolone wartosci to X, Y oraz Z
   */
  char _Axis;

  /**
   * Szybkosc obrotu wyrazona w stopniach na sekunde
   */
  double _Speed_degS;

  /**
   * Kat obrotu w stopniach
   */
  double _Angle_deg;

public:
  /*!
   * \brief
   */
  Interp4Rotate();

  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const override;

  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const override;

  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() const override {}

  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char *GetCmdName() const override;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   *
   * Wykonuje polecenie oraz wizualizuje jego realizację.
   * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
   * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
   * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
   * \retval true - operacja powiodła się,
   * \retval false - w przypadku przeciwnym.
   */
  virtual bool ExecCmd(AbstractScene &rScn) override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream &Strm_CmdsList) override;

  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static AbstractInterp4Command *CreateCmd();
};

#endif
