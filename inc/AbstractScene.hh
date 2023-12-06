#ifndef ABSTRACTSCENE_HH
#define ABSTRACTSCENE_HH

#include <memory>
#include "Cuboid.hh"
#include "AccessControl.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractScene
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractScene.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

/*!
 * \brief Definiuje interfejs klasy modelującej scenę roboczą.
 *
 * Definiuje interfejs klasy modelującej scenę roboczą,
 * która zawiera kolekcję obiektów mobilnych.
 */
class AbstractScene : public AccessControl
{
public:
        virtual ~AbstractScene() {}

        /*!
         * \brief Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
         *
         *  Wyszukuje obiekt o podanej pełnej kwalifikowanej nazwie.
         *  \param[in] sName - pełna kwalifikowana nazwa obiektu.
         *  \return Jeśli obiekt zostanie znaleziony, to zwracany jest wskaźnik
         *          na niego. W przypadku przeciwnym zwracany jest wskaźnik \p nullptr.
         */
        virtual std::shared_ptr<Cuboid> FindMobileObj(const char *sName) = 0;

        /*!
         * \brief Dodaje do sceny nowy obiekt.
         *
         *  Dodaje do sceny nowy obiekt. Obiekt ten musi mieć poprawnie
         *  skonstruowaną pełną kwalifikowaną nazwę.
         *  \param[in] pMobObj - wskaźnik na istniejący obiekt.
         */
        virtual void AddMobileObj(Cuboid *pMobObj) = 0;
};

#endif
