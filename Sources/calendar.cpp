
/*
 * Copyright (C) 2000
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
 * QuantLib license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
*/

#include "calendar.h"

namespace QuantLib {

	Date Calendar::roll(RollingConvention convention, const Date& d) const {
		Date d1 = d;
		switch (convention) {
		  case Following:
		  case ModifiedFollowing:
			while (isHoliday(d1))
				d1++;
			if (convention == ModifiedFollowing && d1.month() != d.month())
				return roll(Preceding,d);
			break;
		  case Preceding:
		  case ModifiedPreceding:
			while (isHoliday(d1))
				d1--;
			if (convention == ModifiedPreceding && d1.month() != d.month())
				return roll(Following,d);
			break;
		  default:
			throw IllegalArgumentError("Unknown rolling convention");
		}
		return d1;
	}
	
	Date Calendar::advance(const Date& d, int businessDays) const {
		Date d1 = d;
		if (businessDays >= 0) {
			while (businessDays >= 0) {
				while (isHoliday(d1))
					d1++;
				businessDays--;
			}
		} else {
			while (businessDays <= 0) {
				while(isHoliday(d1))
					d1--;
				businessDays--;
			}
		}
		return d1;
	}

}
