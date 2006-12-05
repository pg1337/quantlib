/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/TermStructures/piecewiseyieldcurve.hpp>
#ifdef QL_DISABLE_DEPRECATED
#include <ql/Quotes/simplequote.hpp>
#else
#include <ql/quote.hpp>
#endif

namespace QuantLib {

    RateHelper::RateHelper(const Handle<Quote>& quote)
    : quote_(quote), termStructure_(0) {
        registerWith(quote_);
    }

    RateHelper::RateHelper(Real quote)
    : quote_(Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(quote)))),
      termStructure_(0) {
        registerWith(quote_);
    }

    void RateHelper::setTermStructure(YieldTermStructure* t) {
        QL_REQUIRE(t != 0, "null term structure given");
        termStructure_ = t;
    }

    Real RateHelper::quoteError() const {
        return quote_->value()-impliedQuote();
    }

}
