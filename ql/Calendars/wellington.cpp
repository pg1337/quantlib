

/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email ferdinando@ametrano.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
/*! \file wellington.cpp
    \brief Wellington calendar

    \fullpath
    ql/Calendars/%wellington.cpp
*/

// $Id$

#include <ql/Calendars/wellington.hpp>

namespace QuantLib {

    namespace Calendars {

        bool Wellington::WelCalendarImpl::isBusinessDay(const Date& date)
          const {
            Weekday w = date.weekday();
            Day d = date.dayOfMonth(), dd = date.dayOfYear();
            Month m = date.month();
            Year y = date.year();
            Day em = easterMonday(y);
            if ((w == Saturday || w == Sunday)
                // New Year's Day (possibly moved to Monday or Tuesday)
                || ((d == 1 || (d == 3 && (w == Monday || w == Tuesday))) &&
                    m == January)
                // Day after New Year's Day (possibly Monday or Tuesday)
                || ((d == 2 || (d == 4 && (w == Monday || w == Tuesday))) &&
                    m == January)
                // Anniversary Day, Monday nearest January 22nd
                || ((d >= 19 && d <= 25) && w == Monday && m == January)
                // Waitangi Day. February 6th
                || (d == 6 && m == February)
                // Good Friday
                || (dd == em-3)
                // Easter Monday
                || (dd == em)
                // ANZAC Day. April 25th
                || (d == 25 && m == April)
                // Queen's Birthday, first Monday in June
                || (d <= 7 && w == Monday && m == June)
                // Labour Day, fourth Monday in October
                || ((d >= 22 && d <= 28) && w == Monday && m == October)
                // Christmas, December 25th (possibly Monday or Tuesday)
                || ((d == 25 || (d == 27 && (w == Monday || w == Tuesday)))
                    && m == December)
                // Boxing Day, December 26th (possibly Monday or Tuesday)
                || ((d == 26 || (d == 28 && (w == Monday || w == Tuesday)))
                    && m == December))
                    return false;
            return true;
        }

    }

}
