
/*
 * Copyright (C) 2000, 2001
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

/*! \file bsmoption.h
    \brief common code for option evaluation

    $Source$
    $Name$
    $Log$
    Revision 1.11  2001/02/19 12:16:48  marmar
    Vega is not required for implied volatility calculations

    Revision 1.10  2001/02/15 15:58:03  marmar
    Defined QL_MIN_VOLATILITY 0.0005 and
    QL_MAX_VOLATILITY 3.0

    Revision 1.9  2001/02/15 15:27:10  marmar
    New constructor with default values for maxVolatility
    and minVolatility

    Revision 1.8  2001/02/14 13:54:23  marmar
    Some spaces have been added

    Revision 1.7  2001/02/14 10:57:57  marmar
    BSMOption has  a cleaner constructor

    Revision 1.6  2001/02/13 10:02:17  marmar
    Ambiguous variable name underlyingGrowthRate changed in
    unambiguos dividendYield

    Revision 1.5  2001/01/17 14:37:56  nando
    tabs removed

    Revision 1.4  2000/12/27 14:05:56  lballabio
    Turned Require and Ensure functions into QL_REQUIRE and QL_ENSURE macros

    Revision 1.3  2000/12/14 12:32:30  lballabio
    Added CVS tags in Doxygen file documentation blocks

*/

#ifndef BSM_option_pricer_h
#define BSM_option_pricer_h

#include "qldefines.h"
#include "options.h"
#include "date.h"
#include "rate.h"
#include "handle.h"
#include "solver1d.h"

#define QL_MIN_VOLATILITY 0.0005
#define QL_MAX_VOLATILITY 3.0

namespace QuantLib {

    namespace Pricers {

        class BSMOption : public Option {
          public:
            BSMOption(Type type, double underlying, double strike, 
                Rate dividendYield, Rate riskFreeRate, Time residualTime, 
                double volatility);
            virtual ~BSMOption() {}    // just in case
            // modifiers
            void setVolatility(double newVolatility) ;
            void setRiskFreeRate(Rate newRate) ;
            // accessors
            virtual double value() const = 0;
            virtual double delta() const = 0;
            virtual double gamma() const = 0;
            virtual double theta() const = 0;
            virtual double vega() const = 0;
            virtual double rho() const = 0;
            double impliedVolatility(double targetValue, 
                double accuracy = 1e-4, int maxEvaluations = 100,
                double minVol = QL_MIN_VOLATILITY, 
                double maxVol = QL_MAX_VOLATILITY) const ;
            virtual Handle<BSMOption> clone() const = 0;
          protected:
            // input data
            Type type_;
            double underlying_, strike_;
            Rate dividendYield_, riskFreeRate_;
            Time residualTime_;
            double volatility_;
            // results
            // declared as mutable to preserve the logical
            mutable bool hasBeenCalculated_;    
            mutable double value_;
          private:
            class BSMFunction;
            friend class BSMFunction;
        };

        class BSMOption::BSMFunction : public ObjectiveFunction {
          public:
            BSMFunction(const Handle<BSMOption>& tempBSM, double price);
            double value(double x) const;
          private:
            mutable Handle<BSMOption> bsm;
            double thePrice;
        };

        BSMOption::BSMFunction::BSMFunction(
                const Handle<BSMOption>& tempBSM, double price) {
            bsm = tempBSM;
            thePrice = price;
        }
        
        inline double BSMOption::BSMFunction::value(double x) const {
            bsm -> setVolatility(x);
            return (bsm -> value() - thePrice);
        }

    }

}

#endif
