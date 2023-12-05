#ifndef ABSGTRACTMOBILEOBJ_HH
#define ABSGTRACTMOBILEOBJ_HH

/*!
 * \file
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractMobileObj
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractMobileObj.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

#include "Vector3D.hh"

/*!
 * \brief Definiuje interfejs dla obiektów mobilnych.
 *
 * Definiuje interfejs dla obiektów mobilnych.
 * Zakładamy, że przód obiektu jest wskazywany przez strzałkę osi OX.
 * Nazwy metod są obowiązujące.
 */
class AbstractMobileObj
{
  public:
    virtual ~AbstractMobileObj()
    {
    }

    virtual void PrintState() const = 0;

    virtual double GetAng_Roll_deg() const = 0;
    virtual double GetAng_Pitch_deg() const = 0;
    virtual double GetAng_Yaw_deg() const = 0;
    virtual void SetAng_Roll_deg(double Ang_Roll_deg) = 0;
    virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) = 0;
    virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) = 0;

    virtual const Vector3D &GetPosition_m() const = 0;
    virtual void SetPosition_m(const Vector3D &rPos) = 0;

    virtual void SetName(const char *sName) = 0;
    virtual const std::string &GetName() const = 0;

    virtual const Vector3D &GetScale() const = 0;
    virtual void SetScale(const Vector3D &rScale) = 0;

    virtual const Vector3D &GetTrans() const = 0;
    virtual void SetTrans(const Vector3D &rShift) = 0;

    virtual int GetColor_R() const = 0;
    virtual int GetColor_G() const = 0;
    virtual int GetColor_B() const = 0;

    virtual void SetColor_R(const int &rColor_R) = 0;
    virtual void SetColor_G(const int &rColor_G) = 0;
    virtual void SetColor_B(const int &rColor_B) = 0;
};

#endif
