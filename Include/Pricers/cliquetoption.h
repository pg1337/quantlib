
/*
 * Copyright (C) 2001
 * Ferdinando Ametrano, Luigi Ballabio, Adolfo Benin, Marco Marchioro
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 *
 * QuantLib license is also available at
 * http://quantlib.sourceforge.net/LICENSE.TXT
*/

/*!  \file cliquetoption.h
   \brief Textbook example of european-style multi-period option.
  
  $Source$

  $Log$
  Revision 1.1  2001/04/04 09:48:45  marmar
  introducing cliquet option

*/

#ifndef quantlib_pricers_cliquet_option_h
#define quantlib_pricers_cliquet_option_h

#include <vector>
#include "qldefines.h"
#include "handle.h"
#include "bsmoption.h"
#include "bsmeuropeanoption.h"
namespace QuantLib 
{
    namespace Pricers 
    {
     /*!
     A cliquet option, also known as Ratchet option, is a series
     of forward-starting options where the strike for the next
     exercize date is set to the spot price at the beginning of each period.
     In the particular case in which only two dates are given the price
     of the option is the same as that of a forward-starting option
     starting at the first date and expiring at the second date.
     */
        class CliquetOption: public BSMOption 
        {
        public:
            CliquetOption(Type type, 
                          double underlying, 
                          Rate dividendYield, 
                          Rate riskFreeRate, 
                          const std::vector<Time> &dates, 
                          double volatility);
            double value() const;
            double delta() const;
            double gamma() const;
            double theta() const;
            double vega() const;
            double rho() const;
            Handle<BSMOption> clone() const;
        private:
            int numPeriods_;
            std::vector<Handle<BSMEuropeanOption> > optionlet_;
            std::vector<double> weight_;
        };
    }
}


#endif




