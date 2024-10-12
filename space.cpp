#include "space.h"

Q_DECLARE_METATYPE(Space*)



Space::Space() : QObject(nullptr), _value(0), _isOpen(false)
{

}

Space::Space( int value, QObject* parent ) :
    QObject( parent ),
    _value( value ),
    _isOpen( false ) {}

Space::Space(const Space &other) : QObject(other.parent()), _value(other._value), _isOpen(other._isOpen)
{

}

int Space::getValue() const
{
    return _value;
}

void Space::setValue(int value) {
    if(_value == value) {
        return;
    }

    _value = value;
    emit valueChanged();
}


bool Space::getIsOpen() const
{
    return _isOpen;
}

void Space::setIsOpen(bool isOpen)
{
    if(isOpen == _isOpen) {
        return;
    }
    _isOpen = isOpen;
    emit isOpenChanged();
}

bool Space::open() {

    if ( _isOpen ) {
        return false;
    }

    if ( _value == BOMBED ) {
        emit explode();
    }
    _isOpen = true;
    emit isOpenChanged();
    return true;

}
