#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
class Matrix {

    using ConstantRefType = const T&;
    using ReferenceType = T&;
    using PointerType = T*;
    using ConstantPointerType = const T*;
    using CopyType = T;

public:


    class Item {

    public:
        PointerType data() {
            return _data;
        }
        int line() {
            return _line;
        }
        int column() {
            return _column;
        }

        int getIndex() {
            return _index;
        }

        Item( int line, int column, int index, PointerType data ) : _line(line), _column(column), _data(data), _index(index) {
        }

    private:
        int _line;
        int _column;
        int _index;
        PointerType _data;

    };

    Matrix() = delete;

    Matrix( int line, int column ) :
        _line( line ),
        _column( column ) {
        _matrix.reserve( line * column );
    }

    void push_at(int line, int column, ConstantRefType value) {
        _matrix.insert( getItAtPos(line, column) , value);
    }

    void push_at(int line, int column, T&& value) {
        _matrix.insert( getItAtPos(line, column) , std::move( value ));
    }

    template< typename... Args>
    void emplace(int line, int column, Args... args) {
        _matrix.emplace( getItAtPos(line, column) , args... );
    }

    ReferenceType operator[](int index) {
        return _matrix[index];
    }

    ReferenceType operator()(int line, int column) {
        return _matrix[ line * _column + column ];
    }

    CopyType operator()(int line, int column) const{
        return _matrix[ line * _column + column ];
    }

    std::vector<Item> getBoundariesOf(int index) {
        int linha = index / _column;
        int coluna = index % _column;

        return getBoundariesOf(linha, coluna);
    }

    std::vector<Item> getBoundariesOf(int line, int column) {

        std::vector<Item> result;

        int minLine = std::max(0, line - 1);
        int maxLine = std::min(_line - 1, line + 1);
        int minColumn = std::max(0, column - 1);
        int maxColumn = std::min(_column - 1, column + 1);


        for (int i = minLine; i <= maxLine; i++) {
            for (int j = minColumn; j <= maxColumn; j++) {
                if (i != line || j != column) { // Evita verificar a célula alvo
                    result.emplace_back( i, j, calculateIndex(i, j),  &_matrix[ i * _column + j ] );
                }
            }
        }

        return result;
    }

    ConstantRefType at(int index) const {
        return _matrix[index];
    }

    int getLine() const {
        return _line;
    }

    int getColumn() const {
        return _column;
    }

    int size() const {
        return _matrix.size();
    }

    int count() const {
        return _matrix.size();
    }

    std::vector<CopyType> toVector() const {
        return _matrix;
    }

    auto begin() {
        return _matrix.begin();
    }

    auto end() {
        return _matrix.end();
    }

    auto cbegin() const {
        return _matrix.cbegin();
    }

    auto cend() const {
        return _matrix.cend();
    }

    int calculateIndex(int line, int column) {
        return line * _column + column;
    }

private:

    auto getItAtPos(int line, int column) {
        return _matrix.begin() + (line * _column + column );
    }

    int _line;
    int _column;
    std::vector< CopyType > _matrix;

};

#endif // MATRIX_H
