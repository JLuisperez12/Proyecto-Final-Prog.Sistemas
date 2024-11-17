// Proyecto Final Prog.Sistemas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <string>
#include <limits>

using namespace std;

string DecimalaBinaro(int decimalNum) {
    string ResultBi;
    char bits[8]; // Almacenará hasta 8 bits

    // Inicializamos el arreglo a ceros
    for (int i = 0; i < 8; ++i) {
        bits[i] = '0'; // Llenara con ceros
    }

    __asm {
        mov eax, decimalNum           ; Cargar el número decimal en EAX
        mov ecx, 8                    ; Configurar el contador para 8 bits
        xor edx, edx                  ; Inicializar el índice en 0 (usando EDX)

        conversion_loop:
        shr eax, 1                    ; Dividir eax por 2 y almacenar el residuo en CF
            jnc zero_bit              ; Si CF no está configurado, el bit es 0
            mov bits[edx], '1'        ; Si CF está configurado, el bit es 1
            jmp store_bit
            zero_bit :
        mov bits[edx], '0'            ; Si CF no está configurado, el bit es 0

            store_bit:
        inc edx                       ; Incrementar el índice para el siguiente bit
            dec ecx                   ; Decrementar el contador
            jnz conversion_loop       ; Repetir hasta que ecx llegue a 0
    }

    // Invertir los bits y construir la cadena de resultado
    for (int i = 7; i >= 0; --i) {
        ResultBi += bits[i]; // Agregar los bits en orden inverso
    }

    return ResultBi;
}

int main() {
    int decimalNum;
    char repeat=0;

    do {
        cout << "Ingresa el numero a convertir: ";
        cin >> decimalNum;

        // Verificar que el número ingresado sea válido
        if (cin.fail() || decimalNum < 0 || decimalNum > 255) {
            cout << "Ingresa un numero decimalentre 0 y 255." <<endl;
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar entrada inválida
            continue; // Volver a pedir el número
        }

        // Convertir y mostrar el resultado en binario
        string binary = DecimalaBinaro(decimalNum);
        cout << "El numero en binario es: " << binary << endl;

        // Preguntar si el usuario desea ingresar otro número
        cout << "Deseas intentar de nuevo? (s / n): ";
        cin >> repeat;
    } while (repeat == 's' || repeat == 'S');

    cout << "Gracias por usar el conversor." <<endl;
    return 0;
}