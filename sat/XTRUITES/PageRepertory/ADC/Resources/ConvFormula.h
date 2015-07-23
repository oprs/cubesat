#ifndef _QB50_XTRUITES_CONV_FORMULA_H_
#define _QB50_XTRUITES_CONV_FORMULA_H_

namespace qb50
{

  namespace XTRUITES
  {

    class ConvFormula
    {
      public:
        ConvFormula(char const * unitVal, float coefficientVal, float offsetVal);

        virtual ~ConvFormula();

        char const * unit;
        float       coefficient;
        float       offset;

        virtual float conv(unsigned char digitalValue);
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_CONV_FORMULA_H_ */


/*EoF*/
