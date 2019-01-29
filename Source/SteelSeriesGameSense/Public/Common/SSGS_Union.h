/**
* authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

namespace ssgs {


typedef int NullUnionMember;

// TODO add more subtypes when required
template < typename Type1, typename Type2 = NullUnionMember, typename Type3 = NullUnionMember >
class Union
{

public:

    Union() : _typeIdx( 0 ) {}
    Union( const Type1& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type2& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type3& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Union& other ) {

        switch ( other._typeIdx )
        {
        case 1: set( other._values._t1 ); break;
        case 2: set( other._values._t2 ); break;
        case 3: set( other._values._t3 ); break;
        }

    }
    ~Union() { destroyByIdx(); }

    Union& operator=( const Union& rhs ) {
        
        if ( this != &rhs ) {
            switch ( rhs._typeIdx )
            {
            case 1: set( rhs._values._t1 ); break;
            case 2: set( rhs._values._t2 ); break;
            case 3: set( rhs._values._t3 ); break;
            }
        }

        return *this;
    }
    Union& operator=( Union&& rhs ) {

        if ( this != &rhs ) {
            switch ( rhs._typeIdx )
            {
            case 1: set( rhs._values._t1 ); break;
            case 2: set( rhs._values._t2 ); break;
            case 3: set( rhs._values._t3 ); break;
            }

            rhs.destroyByIdx();
        }

        return *this;
    }

    template < typename T >
    const T& Get() const {
        T* pValue;

        if ( std::is_same< T, Type1 >::value )
            pValue = ( T* )&_values._t1;
        else if ( std::is_same< T, Type2 >::value )
            pValue = ( T* )&_values._t2;
        else if ( std::is_same< T, Type3 >::value )
            pValue = ( T* )&_values._t3;
        else {
            static_assert( std::is_same< T, Type1 >::value ||
                           std::is_same< T, Type2 >::value ||
                           std::is_same< T, Type3 >::value,
                           "No such subtype" );
        }
        
        return *pValue;
    }

    template < typename T >
    inline void Set( const T& v ) {
        set( v );
    }

private:

    void destroyByIdx() {
        
        switch ( _typeIdx )
        {
        case 1: _values._t1.~Type1(); break;
        case 2: _values._t2.~Type2(); break;
        case 3: _values._t3.~Type3(); break;
        }

        _typeIdx = 0;

    }

    template < typename T >
    void set( const T& v ) {

        destroyByIdx();

        if ( std::is_same< T, Type1 >::value ) {
            _typeIdx = 1;
        } else if ( std::is_same< T, Type2 >::value ) {
            _typeIdx = 2;
        } else if ( std::is_same< T, Type3 >::value ) {
            _typeIdx = 3;
        } else {
            static_assert( std::is_same< T, Type1 >::value ||
                           std::is_same< T, Type2 >::value ||
                           std::is_same< T, Type3 >::value,
                           "No such subtype" );
        }

        new ( &_values ) T( v );

    }

private:

    union __values
    {
#pragma warning(disable:4582)
#pragma warning(disable:4583)
        __values() {}
        ~__values() {}


        NullUnionMember _invalid;
        Type1 _t1;
        Type2 _t2;
        Type3 _t3;
#pragma warning(default:4582)
#pragma warning(default:4583)
    } _values;

    int _typeIdx;

};


}
