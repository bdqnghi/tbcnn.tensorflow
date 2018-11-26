//
// Copyright (c) 2012 Leon Lee author. All rights reserved.
//
// Use of this source code is governed by a GPLv3 license that can be
// found in the LICENSE file.

#include "xpr_string_iterator.h"

namespace xpr
{
StringIterator::StringIterator(void)
    : mString(XPR_NULL)
{
}

StringIterator::StringIterator(xpr_tchar_t *aString)
    : mString(aString)
{
}

xpr_tchar_t& StringIterator::operator* () const
{
    return *mString;
}

xpr_tchar_t* StringIterator::operator-> () const
{
    return mString;
}

StringIterator& StringIterator::operator++ ()
{
    ++mString;

    return *this;
}

StringIterator StringIterator::operator++ (xpr_sint_t)
{
    StringIterator sIterator = *this;

    ++mString;

    return sIterator;
}

StringIterator& StringIterator::operator-- ()
{
    --mString;

    return *this;
}

StringIterator StringIterator::operator-- (xpr_sint_t)
{
    StringIterator sIterator = *this;

    --mString;

    return sIterator;
}

StringIterator& StringIterator::operator+= (xpr_sint_t aOffset)
{
    mString += aOffset;

    return *this;
}

StringIterator StringIterator::operator+ (xpr_sint_t aOffset) const
{
    StringIterator sIterator = *this;

    sIterator += aOffset;

    return sIterator;
}

StringIterator& StringIterator::operator-= (xpr_sint_t aOffset)
{
    mString -= aOffset;

    return *this;
}

StringIterator StringIterator::operator- (xpr_sint_t aOffset) const
{
    StringIterator sIterator = *this;

    sIterator -= aOffset;

    return sIterator;
}

xpr_sint_t StringIterator::operator- (const StringIterator &aIterator) const
{
    return (xpr_sint_t)(mString - aIterator.mString);
}

xpr_tchar_t& StringIterator::operator[] (xpr_sint_t aOffset) const
{
    return mString[aOffset];
}

bool StringIterator::operator== (const StringIterator &aIterator) const
{
    return (mString == aIterator.mString) ? true : false;
}

bool StringIterator::operator!= (const StringIterator &aIterator) const
{
    return (mString != aIterator.mString) ? true : false;
}

bool StringIterator::operator< (const StringIterator &aIterator) const
{
    return (mString < aIterator.mString) ? true : false;
}

bool StringIterator::operator<= (const StringIterator &aIterator) const
{
    return (mString <= aIterator.mString) ? true : false;
}

bool StringIterator::operator> (const StringIterator &aIterator) const
{
    return (mString > aIterator.mString) ? true : false;
}

bool StringIterator::operator>= (const StringIterator &aIterator) const
{
    return (mString >= aIterator.mString) ? true : false;
}










StringConstIterator::StringConstIterator(void)
    : mString(XPR_NULL)
{
}

StringConstIterator::StringConstIterator(const StringIterator &aIterator)
    : mString(aIterator.mString)
{
}

StringConstIterator::StringConstIterator(const xpr_tchar_t *aString)
    : mString(aString)
{
}

const xpr_tchar_t& StringConstIterator::operator* () const
{
    return *mString;
}

const xpr_tchar_t* StringConstIterator::operator-> () const
{
    return mString;
}

StringConstIterator& StringConstIterator::operator++ ()
{
    ++mString;

    return *this;
}

StringConstIterator StringConstIterator::operator++ (xpr_sint_t)
{
    StringConstIterator sIterator = *this;

    ++mString;

    return sIterator;
}

StringConstIterator& StringConstIterator::operator-- ()
{
    --mString;

    return *this;
}

StringConstIterator StringConstIterator::operator-- (xpr_sint_t)
{
    StringConstIterator sIterator = *this;

    --mString;

    return sIterator;
}

StringConstIterator& StringConstIterator::operator+= (xpr_sint_t aOffset)
{
    mString += aOffset;

    return *this;
}

StringConstIterator StringConstIterator::operator+ (xpr_sint_t aOffset) const
{
    StringConstIterator sIterator = *this;

    sIterator += aOffset;

    return sIterator;
}

StringConstIterator& StringConstIterator::operator-= (xpr_sint_t aOffset)
{
    mString -= aOffset;

    return *this;
}

StringConstIterator StringConstIterator::operator- (xpr_sint_t aOffset) const
{
    StringConstIterator sIterator = *this;

    sIterator -= aOffset;

    return sIterator;
}

xpr_sint_t StringConstIterator::operator- (const StringConstIterator &aIterator) const
{
    return (xpr_sint_t)(mString - aIterator.mString);
}

const xpr_tchar_t& StringConstIterator::operator[] (xpr_sint_t aOffset) const
{
    return mString[aOffset];
}

bool StringConstIterator::operator== (const StringConstIterator &aIterator) const
{
    return (mString == aIterator.mString) ? true : false;
}

bool StringConstIterator::operator!= (const StringConstIterator &aIterator) const
{
    return (mString != aIterator.mString) ? true : false;
}

bool StringConstIterator::operator< (const StringConstIterator &aIterator) const
{
    return (mString < aIterator.mString) ? true : false;
}

bool StringConstIterator::operator<= (const StringConstIterator &aIterator) const
{
    return (mString <= aIterator.mString) ? true : false;
}

bool StringConstIterator::operator> (const StringConstIterator &aIterator) const
{
    return (mString > aIterator.mString) ? true : false;
}

bool StringConstIterator::operator>= (const StringConstIterator &aIterator) const
{
    return (mString >= aIterator.mString) ? true : false;
}





StringReverseIterator::StringReverseIterator(void)
    : mString(XPR_NULL)
{
}

StringReverseIterator::StringReverseIterator(xpr_tchar_t *aString)
    : mString(aString)
{
}

xpr_tchar_t& StringReverseIterator::operator* () const
{
    return *mString;
}

xpr_tchar_t* StringReverseIterator::operator-> () const
{
    return mString;
}

StringReverseIterator& StringReverseIterator::operator++ ()
{
    --mString;

    return *this;
}

StringReverseIterator StringReverseIterator::operator++ (xpr_sint_t)
{
    StringReverseIterator sIterator = *this;

    --mString;

    return sIterator;
}

StringReverseIterator& StringReverseIterator::operator-- ()
{
    ++mString;

    return *this;
}

StringReverseIterator StringReverseIterator::operator-- (xpr_sint_t)
{
    StringReverseIterator sIterator = *this;

    ++mString;

    return sIterator;
}

StringReverseIterator& StringReverseIterator::operator+= (xpr_sint_t aOffset)
{
    mString += aOffset;

    return *this;
}

StringReverseIterator StringReverseIterator::operator+ (xpr_sint_t aOffset) const
{
    StringReverseIterator sIterator = *this;

    sIterator += aOffset;

    return sIterator;
}

StringReverseIterator& StringReverseIterator::operator-= (xpr_sint_t aOffset)
{
    mString -= aOffset;

    return *this;
}

StringReverseIterator StringReverseIterator::operator- (xpr_sint_t aOffset) const
{
    StringReverseIterator sIterator = *this;

    sIterator -= aOffset;

    return sIterator;
}

xpr_sint_t StringReverseIterator::operator- (const StringReverseIterator &aIterator) const
{
    return (xpr_sint_t)(mString - aIterator.mString);
}

xpr_tchar_t& StringReverseIterator::operator[] (xpr_sint_t aOffset) const
{
    return mString[-aOffset];
}

bool StringReverseIterator::operator== (const StringReverseIterator &aIterator) const
{
    return (mString == aIterator.mString) ? true : false;
}

bool StringReverseIterator::operator!= (const StringReverseIterator &aIterator) const
{
    return (mString != aIterator.mString) ? true : false;
}

bool StringReverseIterator::operator< (const StringReverseIterator &aIterator) const
{
    return (mString > aIterator.mString) ? true : false;
}

bool StringReverseIterator::operator<= (const StringReverseIterator &aIterator) const
{
    return (mString >= aIterator.mString) ? true : false;
}

bool StringReverseIterator::operator> (const StringReverseIterator &aIterator) const
{
    return (mString < aIterator.mString) ? true : false;
}

bool StringReverseIterator::operator>= (const StringReverseIterator &aIterator) const
{
    return (mString <= aIterator.mString) ? true : false;
}






StringConstReverseIterator::StringConstReverseIterator(void)
    : mString(XPR_NULL)
{
}

StringConstReverseIterator::StringConstReverseIterator(const StringReverseIterator &aIterator)
    : mString(aIterator.mString)
{
}

StringConstReverseIterator::StringConstReverseIterator(const xpr_tchar_t *aString)
    : mString(aString)
{
}

const xpr_tchar_t& StringConstReverseIterator::operator* () const
{
    return *mString;
}

const xpr_tchar_t* StringConstReverseIterator::operator-> () const
{
    return mString;
}

StringConstReverseIterator& StringConstReverseIterator::operator++ ()
{
    --mString;

    return *this;
}

StringConstReverseIterator StringConstReverseIterator::operator++ (xpr_sint_t)
{
    StringConstReverseIterator sIterator = *this;

    --mString;

    return sIterator;
}

StringConstReverseIterator& StringConstReverseIterator::operator-- ()
{
    ++mString;

    return *this;
}

StringConstReverseIterator StringConstReverseIterator::operator-- (xpr_sint_t)
{
    StringConstReverseIterator sIterator = *this;

    ++mString;

    return sIterator;
}

StringConstReverseIterator& StringConstReverseIterator::operator+= (xpr_sint_t aOffset)
{
    mString -= aOffset;

    return *this;
}

StringConstReverseIterator StringConstReverseIterator::operator+ (xpr_sint_t aOffset) const
{
    StringConstReverseIterator sIterator = *this;

    sIterator += aOffset;

    return sIterator;
}

StringConstReverseIterator& StringConstReverseIterator::operator-= (xpr_sint_t aOffset)
{
    mString += aOffset;

    return *this;
}

StringConstReverseIterator StringConstReverseIterator::operator- (xpr_sint_t aOffset) const
{
    StringConstReverseIterator sIterator = *this;

    sIterator -= aOffset;

    return sIterator;
}

xpr_sint_t StringConstReverseIterator::operator- (const StringConstReverseIterator &aIterator) const
{
    return (xpr_sint_t)(mString - aIterator.mString);
}

const xpr_tchar_t& StringConstReverseIterator::operator[] (xpr_sint_t aOffset) const
{
    return mString[-aOffset];
}

bool StringConstReverseIterator::operator== (const StringConstReverseIterator &aIterator) const
{
    return (mString == aIterator.mString) ? true : false;
}

bool StringConstReverseIterator::operator!= (const StringConstReverseIterator &aIterator) const
{
    return (mString != aIterator.mString) ? true : false;
}

bool StringConstReverseIterator::operator< (const StringConstReverseIterator &aIterator) const
{
    return (mString > aIterator.mString) ? true : false;
}

bool StringConstReverseIterator::operator<= (const StringConstReverseIterator &aIterator) const
{
    return (mString >= aIterator.mString) ? true : false;
}

bool StringConstReverseIterator::operator> (const StringConstReverseIterator &aIterator) const
{
    return (mString < aIterator.mString) ? true : false;
}

bool StringConstReverseIterator::operator>= (const StringConstReverseIterator &aIterator) const
{
    return (mString <= aIterator.mString) ? true : false;
}
} // namespace xpr
