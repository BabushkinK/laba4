#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>

class Matrix {
private:
    int** data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        data = new int* [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new int[n];
        }
    }

    Matrix() {
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fillRandom() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = std::rand() % 10;
            }
        }
    }

    int* operator[](unsigned int index) {
        return data[index];
    }

    Matrix& operator+=(const Matrix& rhs) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] += rhs.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
        lhs += rhs;
        return lhs;
    }

    Matrix& operator-=(const Matrix& rhs) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] -= rhs.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator-(Matrix lhs, const Matrix& rhs) {
        lhs -= rhs;
        return lhs;
    }

    // Простая реализация умножения матриц без оптимизаций
    Matrix operator*(const Matrix& rhs) const {
        Matrix result(m, rhs.n);
        for (unsigned int i = 0; i < result.m; ++i) {
            for (unsigned int j = 0; j < result.n; ++j) {
                result.data[i][j] = 0;
                for (unsigned int k = 0; k < n; ++k) {
                    result.data[i][j] += data[i][k] * rhs.data[k][j];
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix& rhs) const {
        if (m != rhs.m || n != rhs.n) return false;
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if (data[i][j] != rhs.data[i][j]) return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << std::setw(4) << matrix.data[i][j];
            }
            os << std::endl;
        }
        return os;
    }
};
template<typename T>
class Matrix {
private:
    T** data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        data = new T * [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new T[n];
        }
    }

    ~Matrix() {
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fillRandom() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = static_cast<T>(std::rand() % 10);
            }
        }
    }

    T* operator[](unsigned int index) const {
        return data[index];
    }

    Matrix & operator+=(const Matrix& rhs) {
        // Оставляем реализацию без изменений
    }

    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
        // Оставляем реализацию без изменений
    }

    // Продолжаем реализацию остальных операторов аналогично
};

// Для использования с float или double, нужно будет модифицировать метод fillRandom,
// чтобы генерировать случайные значения в соответствующем диапазоне.

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Инициализация генератора случайных чисел

    // Пример использования
    Matrix<int> matInt(3, 3);
    matInt.fillRandom();
    std::cout << matInt << std::endl;

    // Аналогично можно создать и использовать матрицы других типов
}
template<typename T>
class Matrix {
private:
    T** data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        data = new T * [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new T[n];
        }
    }

    ~Matrix() {
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Улучшенный метод fillRandom, поддерживающий вещественные числа
    void fillRandom() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if constexpr (std::is_floating_point<T>::value) {
                    T randomValue = static_cast<T>(std::rand()) / static_cast<T>(RAND_MAX);
                    data[i][j] = randomValue * 10.0; // Пример для вещественных чисел в диапазоне [0, 10)
                }
                else {
                    data[i][j] = static_cast<T>(std::rand() % 10); // Для целых чисел
                }
            }
        }
    }

    T* operator[](unsigned int index) const {
        return data[index];
    }

    Matrix& operator+=(const Matrix& rhs) {
        // Реализация остается без изменений
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] += rhs.data[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {
        lhs += rhs;
        return lhs;
    }

    // Добавляем реализацию оператора -=
    Matrix& operator-=(const Matrix& rhs) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] -= rhs.data[i][j];
            }
        }
        return *this;
    }

    // Добавляем реализацию оператора -
    friend Matrix operator-(Matrix lhs, const Matrix& rhs) {
        lhs -= rhs;
        return lhs;
    }

    // Реализация оператора умножения остается без изменений
    Matrix operator*(const Matrix& rhs) const {
        // Реализация остается без изменений
    }

    bool operator==(const Matrix& rhs) const {
        // Реализация остается без изменений
    }

    bool operator!=(const Matrix& rhs) const {
        // Реализация остается без изменений
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << std::setw(8) << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Инициализация генератора случайных чисел

    // Пример использования для целых чисел
    Matrix<int> matInt(3, 3);
    matInt.fillRandom();
    std::cout << "Integer matrix:\n" << matInt << std::endl;

    // Пример использования для вещественных чисел
    Matrix<double> matDouble(3, 3);
    matDouble.fillRandom();
    std::cout << "Double matrix:\n" << matDouble << std::endl;

    return 0;
}
template<typename T>
class Vector {
private:
    T* data;
    unsigned int size;

public:
    // Конструктор
    Vector(unsigned int size) : size(size) {
        data = new T[size];
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Доступ к элементам через оператор []
    T& operator[](unsigned int index) const {
        return data[index];
    }

    // Скалярное произведение
    T dot(const Vector& rhs) const {
        T result = 0;
        for (unsigned int i = 0; i < size; ++i) {
            result += data[i] * rhs.data[i];
        }
        return result;
    }

    // Векторное произведение (только для трёхмерных векторов)
    Vector cross(const Vector& rhs) const {
        if (size != 3) throw std::invalid_argument("Cross product is defined only for 3D vectors.");

        Vector result(3);
        result[0] = data[1] * rhs.data[2] - data[2] * rhs.data[1];
        result[1] = data[2] * rhs.data[0] - data[0] * rhs.data[2];
        result[2] = data[0] * rhs.data[1] - data[1] * rhs.data[0];
        return result;
    }

    // Длина вектора
    T length() const {
        T sum = 0;
        for (unsigned int i = 0; i < size; ++i) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }
};

int main() {
    Vector<double> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    Vector<double> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    std::cout << "Dot product: " << v1.dot(v2) << std::endl;

    Vector<double> vCross = v1.cross(v2);
    std::cout << "Cross product: (" << vCross[0] << ", " << vCross[1] << ", " << vCross[2] << ")" << std::endl;

    std::cout << "Length of v1: " << v1.length() << std::endl;

    return 0;
}