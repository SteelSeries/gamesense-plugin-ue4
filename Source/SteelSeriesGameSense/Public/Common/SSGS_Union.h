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


template < int >
class NullUnionMember {};

// TODO add more subtypes when required
template < typename Type1, typename Type2 = NullUnionMember< 2 >, typename Type3 = NullUnionMember< 3 >, typename Type4 = NullUnionMember< 4 >, typename Type5 = NullUnionMember< 5 >, typename Type6 = NullUnionMember< 6 > >
class Union
{

public:

    Union() : _typeIdx( 0 ) {}
    Union( const Type1& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type2& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type3& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type4& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type5& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Type6& v ) : _typeIdx( 0 ) { set( v ); }
    Union( const Union& other ) {

        switch ( other._typeIdx )
        {
        case 1: set( other._values._t1 ); break;
        case 2: set( other._values._t2 ); break;
        case 3: set( other._values._t3 ); break;
        case 4: set( other._values._t4 ); break;
        case 5: set( other._values._t5 ); break;
        case 6: set( other._values._t6 ); break;
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
            case 4: set( rhs._values._t4 ); break;
            case 5: set( rhs._values._t5 ); break;
            case 6: set( rhs._values._t6 ); break;
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
            case 4: set( rhs._values._t4 ); break;
            case 5: set( rhs._values._t5 ); break;
            case 6: set( rhs._values._t6 ); break;
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
        else if ( std::is_same< T, Type4 >::value )
            pValue = ( T* )&_values._t4;
        else if ( std::is_same< T, Type5 >::value )
            pValue = ( T* )&_values._t5;
        else if ( std::is_same< T, Type6 >::value )
            pValue = ( T* )&_values._t6;
        else {
            static_assert( std::is_same< T, Type1 >::value ||
                           std::is_same< T, Type2 >::value ||
                           std::is_same< T, Type3 >::value ||
                           std::is_same< T, Type4 >::value ||
                           std::is_same< T, Type5 >::value ||
                           std::is_same< T, Type6 >::value,
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
        case 4: _values._t4.~Type4(); break;
        case 5: _values._t5.~Type5(); break;
        case 6: _values._t6.~Type6(); break;
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
        } else if ( std::is_same< T, Type4 >::value ) {
            _typeIdx = 4;
        } else if ( std::is_same< T, Type5 >::value ) {
            _typeIdx = 5;
        } else if ( std::is_same< T, Type6 >::value ) {
            _typeIdx = 6;
        } else {
            static_assert( std::is_same< T, Type1 >::value ||
                           std::is_same< T, Type2 >::value ||
                           std::is_same< T, Type3 >::value ||
                           std::is_same< T, Type4 >::value ||
                           std::is_same< T, Type5 >::value ||
                           std::is_same< T, Type6 >::value,
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


        NullUnionMember< 0 > _invalid;
        Type1 _t1;
        Type2 _t2;
        Type3 _t3;
        Type4 _t4;
        Type5 _t5;
        Type6 _t6;
#pragma warning(default:4582)
#pragma warning(default:4583)
    } _values;

    int _typeIdx;

};


}
