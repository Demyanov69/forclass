#include <iostream>
#include <amp.h>
#include <vector>
#include <numeric>

using namespace concurrency;

// Функция для перемножения матриц на GPU с помощью AMP
std::vector<std::vector<float>> multiplyMatricesAMP(const std::vector<std::vector<float>>& a, const std::vector<std::vector<float>>& b) {
    if (a[0].size() != b.size()) {
        throw std::runtime_error("Несовместимые размеры матриц");
    }

    int rowsA = a.size();
    int colsA = a[0].size();
    int colsB = b[0].size();

    // Преобразование в одномерные векторы
    std::vector<float> a_flat(rowsA * colsA);
    std::vector<float> b_flat(colsA * colsB);
    std::vector<float> c_flat(rowsA * colsB, 0.0f); // Инициализация нулями

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            a_flat[i * colsA + j] = a[i][j];
        }
    }
    for (int i = 0; i < colsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            b_flat[i * colsB + j] = b[i][j];
        }
    }


    // Создание массивов AMP
    array_view<float, 1> a_amp(rowsA * colsA, a_flat);
    array_view<float, 1> b_amp(colsA * colsB, b_flat);
    array_view<float, 1> c_amp(rowsA * colsB, c_flat);


    parallel_for_each(c_amp.extent, [=](index<1> idx) restrict(amp) {
        int i = idx[0] / colsB;
        int j = idx[0] % colsB;
        float sum = 0;
        for (int k = 0; k < colsA; ++k) {
            sum += a_amp[i * colsA + k] * b_amp[k * colsB + j];
        }
        c_amp[idx] = sum;
    });

    c_amp.synchronize();

    // Преобразование результата обратно в двумерный вектор
    std::vector<std::vector<float>> result(rowsA, std::vector<float>(colsB));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            result[i][j] = c_amp[i * colsB + j];
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<float>> matrixA = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    std::vector<std::vector<float>> matrixB = {{5.0f, 6.0f}, {7.0f, 8.0f}};

    try {
        std::vector<std::vector<float>> result = multiplyMatricesAMP(matrixA, matrixB);
        for (const auto& row : result) {
            for (float val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::runtime_error& error) {
        std::cerr << "Ошибка: " << error.what() << std::endl;
    }

    return 0;
}
