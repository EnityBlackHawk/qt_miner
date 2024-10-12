#ifndef SPACE_H
#define SPACE_H
#include <QObject>

namespace {
constexpr int BOMBED = -1;
}

class Space : public QObject {
    Q_OBJECT
    Q_PROPERTY(int value READ getValue  WRITE setValue  NOTIFY valueChanged)
    Q_PROPERTY(bool isOpen READ getIsOpen WRITE setIsOpen NOTIFY isOpenChanged FINAL)
public:

    Space();
    Space( int value, QObject* parent );
    Space(const Space& other);

    int getValue() const;
    void setValue(int value);

    bool getIsOpen() const;
    void setIsOpen(bool isOpen);

public slots:
    bool open();

signals:
    void explode();
    void valueChanged();
    void isOpenChanged();

private:
    int _value;
    bool _isOpen;

};

#endif // SPACE_H
