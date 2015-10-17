
// ===============================================================================================================
// -*- C++ -*-
//
// ReferenceCountable.hpp - A base class for all reference countable objects.
//
// Copyright (c) 2012 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#ifndef REFERENCE_COUNTABLE_HPP
#define REFERENCE_COUNTABLE_HPP

namespace l3d
{

// This class provides reference counting through the methods AddRef() and Release().
// If you no longer need the object, you have to call Release() on it.
// This will destroy the object, if AddRef() was not called in another part
// of your program, signaling that the object is still in use.
class ReferenceCountable
{
  public:

    // Increment the reference count by one, indicating that this object has another pointer which is referencing it.
    // \return The current reference count (number of pointers referencing this object).
    unsigned long AddRef() const
    {
        return ++refCounter;
    }

    // Decrement the reference count by one, indicating that a pointer to this object is no longer referencing it.
    // If the reference count goes to zero, it is assumed that this object is no longer in use and it is automatically deleted.
    // \return The current reference count (number of pointers referencing this object).
    // If the return is equal to zero, the object was deleted.
    unsigned long Release() const
    {
        if ((--refCounter) == 0)
        {
            // No longer in use, delete self:
            delete this;
            return 0;
        }
        return refCounter;
    }

    // Return the number pointers currently referencing this object.
    unsigned long ReferenceCount() const
    {
        return refCounter;
    }

  protected:

    // Construction and destruction are protected
    explicit ReferenceCountable(unsigned long startCount = 1)
        : refCounter(startCount)
    { }

    // Not allowed to be directly deleted.
    virtual ~ReferenceCountable() {}

  private:

    mutable unsigned long refCounter;
};

} // namespace l3d {}

#endif // REFERENCE_COUNTABLE_HPP
