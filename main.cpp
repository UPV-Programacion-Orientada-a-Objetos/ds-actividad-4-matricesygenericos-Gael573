#include <iostream>

template <typename T>
class Campo2D {
private:
    T** _datos;
    int _filas;
    int _columnas;

public:
    Campo2D(int f, int c) {
        _filas = f;
        _columnas = c;
        _datos = new T*[_filas];
        for(int i = 0; i < _filas; i++) {
            _datos[i] = new T[_columnas];
            for(int j = 0; j < _columnas; j++) {
                _datos[i][j] = T();
            }
        }
    }

    ~Campo2D() {
        for(int i = 0; i < _filas; i++) {
            delete[] _datos[i];
        }
        delete[] _datos;
    }

    void redimensionar(int nuevaF, int nuevaC) {
        T** nuevosDatos = new T*[nuevaF];
        for(int i = 0; i < nuevaF; i++) {
            nuevosDatos[i] = new T[nuevaC];
            for(int j = 0; j < nuevaC; j++) {
                nuevosDatos[i][j] = T();
            }
        }

        int filasCopiar = (_filas < nuevaF) ? _filas : nuevaF;
        int columnasCopiar = (_columnas < nuevaC) ? _columnas : nuevaC;

        for(int i = 0; i < filasCopiar; i++) {
            for(int j = 0; j < columnasCopiar; j++) {
                nuevosDatos[i][j] = _datos[i][j];
            }
        }

        for(int i = 0; i < _filas; i++) {
            delete[] _datos[i];
        }
        delete[] _datos;

        _datos = nuevosDatos;
        _filas = nuevaF;
        _columnas = nuevaC;
    }

    void setValor(int f, int c, T valor) {
        if(f >= 0 && f < _filas && c >= 0 && c < _columnas) {
            _datos[f][c] = valor;
        }
    }

    T getValor(int f, int c) {
        if(f >= 0 && f < _filas && c >= 0 && c < _columnas) {
            return _datos[f][c];
        }
        return T();
    }

    T calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC) {
        if(inicioF < 0 || finF >= _filas || inicioC < 0 || finC >= _columnas) {
            std::cout << "Indices fuera de rango.\n";
            return T();
        }

        if(inicioF >= finF || inicioC >= finC) {
            std::cout << "Rango invalido.\n";
            return T();
        }

        T sumaGradiente = T();
        int contadorPuntos = 0;

        for(int i = inicioF; i <= finF; i++) {
            for(int j = inicioC; j <= finC; j++) {
                T valorActual = _datos[i][j];
                T diferenciaTotal = T();
                int vecinos = 0;

                if(i + 1 <= finF) {
                    T diff = _datos[i + 1][j] - valorActual;
                    if(diff < 0) diff = -diff;
                    diferenciaTotal = diferenciaTotal + diff;
                    vecinos++;
                }

                if(j + 1 <= finC) {
                    T diff = _datos[i][j + 1] - valorActual;
                    if(diff < 0) diff = -diff;
                    diferenciaTotal = diferenciaTotal + diff;
                    vecinos++;
                }

                if(vecinos > 0) {
                    sumaGradiente = sumaGradiente + (diferenciaTotal / vecinos);
                    contadorPuntos++;
                }
            }
        }

        if(contadorPuntos > 0) {
            return sumaGradiente / contadorPuntos;
        }

        return T();
    }

    void mostrarGrid() {
        std::cout << "\nGrid Actual:\n";
        for(int i = 0; i < _filas; i++) {
            std::cout << "| ";
            for(int j = 0; j < _columnas; j++) {
                std::cout << _datos[i][j] << " | ";
            }
            std::cout << "\n";
        }
    }

    int getFilas() {
        return _filas;
    }

    int getColumnas() {
        return _columnas;
    }
};

void mostrarMenu() {
    std::cout << "\n--- Menu Principal ---\n";
    std::cout << "1. Mostrar Grid\n";
    std::cout << "2. Calcular Gradiente Promedio\n";
    std::cout << "3. Redimensionar Grid\n";
    std::cout << "4. Salir\n";
    std::cout << "\nOpcion seleccionada: ";
}

int main() {
    std::cout << "--- Simulador Generico de Campo 2D ---\n";
    std::cout << "\n>> Inicializando Campo Gravitatorio (Tipo FLOAT) <<\n";
    std::cout << "Creando Grid (FLOAT) de 3x3...\n";

    Campo2D<float> campo(3, 3);

    std::cout << "Estableciendo valores iniciales...\n";
    campo.setValor(0, 0, 10.0f);
    campo.setValor(0, 1, 8.0f);
    campo.setValor(0, 2, 5.0f);
    campo.setValor(1, 0, 12.0f);
    campo.setValor(1, 1, 9.0f);
    campo.setValor(1, 2, 6.0f);
    campo.setValor(2, 0, 15.0f);
    campo.setValor(2, 1, 11.0f);
    campo.setValor(2, 2, 7.0f);

    campo.mostrarGrid();

    int opcion = 0;
    bool continuar = true;

    while(continuar) {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1: {
                campo.mostrarGrid();
                break;
            }

            case 2: {
                int inicioF, finF, inicioC, finC;

                std::cout << "Ingrese Fila Inicial: ";
                std::cin >> inicioF;
                std::cout << "Ingrese Fila Final: ";
                std::cin >> finF;
                std::cout << "Ingrese Columna Inicial: ";
                std::cin >> inicioC;
                std::cout << "Ingrese Columna Final: ";
                std::cin >> finC;

                std::cout << "\nCalculando Gradiente Promedio en la region ["
                         << inicioF << "," << finF << "]x["
                         << inicioC << "," << finC << "]...\n";

                float gradiente = campo.calcularGradientePromedio(inicioF, finF, inicioC, finC);
                std::cout << "Gradiente Promedio calculado: " << gradiente << " unidades/metro.\n";
                break;
            }

            case 3: {
                int nuevaFilas, nuevaColumnas;

                std::cout << "Ingrese nuevas Filas: ";
                std::cin >> nuevaFilas;
                std::cout << "Ingrese nuevas Columnas: ";
                std::cin >> nuevaColumnas;

                std::cout << "Redimensionando Grid a " << nuevaFilas << "x" << nuevaColumnas << "...\n";
                campo.redimensionar(nuevaFilas, nuevaColumnas);
                std::cout << "Datos copiados. Memoria antigua liberada.\n";
                break;
            }

            case 4: {
                std::cout << "Destructor invocado. Liberando memoria de la Matriz 2D...\n";
                continuar = false;
                break;
            }

            default: {
                std::cout << "Opcion no valida.\n";
                break;
            }
        }
    }

    std::cout << "Sistema cerrado.\n";

    return 0;
}