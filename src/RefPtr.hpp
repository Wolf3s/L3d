
// ===============================================================================================================
// -*- C++ -*-
//
// RefPtr.hpp - Smart pointer for reference countable objects.
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

#ifndef REF_PTR_HPP
#define REF_PTR_HPP

#include <cassert>

namespace l3d
{

// Smart pointer for handling referenced counted objects.
// NOTE: This template class only works with types derived
// from the ReferenceCountable interface!
template <class T>
class RefPtr
{
  public:

    // Construct from object pointer. Takes ownership of the pointer, does NOT call AddRef()!
    RefPtr(T * object = 0)
        : data(object)
    {
    }

    // Copy constructor. Share pointer. Calls AddRef().
    RefPtr(const RefPtr<T> & rhs)
        : data(rhs.data)
    {
        if (data)
        {
            data->AddRef();
        }
    }

    // Assignment operator. Takes ownership of the pointer. Release previous, does NOT call AddRef()!
    RefPtr<T> & operator=(T * object)
    {
        if (data != object)
        {
            T * tmp = data;
            data = object;

            if (tmp)
            {
                tmp->Release();
            }
        }
        return *this;
    }

    // Assignment operator. Share pointer. Release previous, call AddRef() on new object.
    RefPtr<T> & operator=(const RefPtr<T> & rhs)
    {
        if (data != rhs.data)
        {
            T * tmp = data;
            data = rhs.data;

            if (data)
            {
                data->AddRef();
            }
            if (tmp)
            {
                tmp->Release();
            }
        }
        return *this;
    }

    // Swap this and rhs.
    void Swap(RefPtr<T> & rhs)
    {
        if (data != rhs.data)
        {
            T * tmp = data;
            data = rhs.data;
            rhs.data = tmp;
        }
    }

    // Giveup pointer ownership and return old pointer. Does NOT call Relsease()!
    T * GiveupOwnership()
    {
        T * tmp = data;
        data = 0;
        return tmp;
    }

    // Destructor releases the object.
    ~RefPtr()
    {
        if (data)
        {
            data->Release();
            data = 0;
        }
    }

    T * Get() const { return data; }

    T & operator*() const
    {
        assert(data != 0);
        return *data;
    }

    T * operator->() const
    {
        assert(data != 0);
        return data;
    }

    operator bool()  const { return data != 0; }
    bool operator!() const { return data == 0; }
    bool IsNull()    const { return data == 0; }

    bool operator == (const RefPtr<T> & rhs) const { return data == rhs.data; }
    bool operator != (const RefPtr<T> & rhs) const { return data != rhs.data; }

    bool operator >  (const RefPtr<T> & rhs) const { return data > rhs.data; }
    bool operator <  (const RefPtr<T> & rhs) const { return data < rhs.data; }

    bool operator >= (const RefPtr<T> & rhs) const { return data >= rhs.data; }
    bool operator <= (const RefPtr<T> & rhs) const { return data <= rhs.data; }

  private:

    T * data;
};

} // namespace l3d {}

#endif // REF_PTR_HPP
