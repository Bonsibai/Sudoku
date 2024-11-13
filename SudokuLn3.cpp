#include <bits/stdc++.h>

using namespace std;

int N; // Tamaño del tablero
int SQRT_N; // Tamaño de la subcuadrícula

void DeleteNumer(int **board, int cantidadAEliminar) {
    int eliminados = 0;
    while (eliminados < cantidadAEliminar) {
        int row = rand() % N;
        int col = rand() % N;
        if (board[row][col] != 0) {
            board[row][col] = 0;
            eliminados++;
        }
    }
}

bool isSafe(int **board, int row, int col, int num) {
    for (int i = 0; i < N; i++)
        if (board[row][i] == num || board[i][col] == num)
            return false;

    int boxRowStart = row - row % SQRT_N;
    int boxColStart = col - col % SQRT_N;

    for (int i = 0; i < SQRT_N; i++)
        for (int j = 0; j < SQRT_N; j++)
            if (board[i + boxRowStart][j + boxColStart] == num)
                return false;

    return true;
}

void printBoard(int **grid) {
    system("clear");
    cout<<  "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        ¡SUDOKU!                                               |" << endl;
    cout << "\t\t\t|       Rellena los números faltantes(Representados por 0) para Ganar           |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col % SQRT_N == 0 && col != 0)
                cout << " | ";
            cout << grid[row][col] << " ";
        }
        cout << endl;
        if ((row + 1) % SQRT_N == 0 && row != N - 1) {
            for (int i = 0; i < N; i++)
                cout << "---";
            cout << endl;
        }
    }
}

void MixNumer(int nums[]) {
    for (int i = 0; i < N; i++) {
        int j = rand() % N;
        swap(nums[i], nums[j]);
    }
}

bool solveSudoku(int **board, int row, int col) {
    if (row == N - 1 && col == N)
        return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    int nums[25];
    for (int i = 0; i < N; i++)
        nums[i] = i + 1;
    MixNumer(nums);

    for (int i = 0; i < N; i++) {
        int num = nums[i];
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void FillRandomBoard(int **board) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    solveSudoku(board, 0, 0);
    DeleteNumer(board, N * N / 2);
}

bool isSolvedCompletely(int **grid) {
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}

void playGame(int **board) {
    int row, col, num;
    while (true) {
        printBoard(board);
        cout << "Ingrese fila (0 para resolver): ";
        cin >> row;
        if (row == 0)
            solveSudoku(board,0,0);
            printBoard(board);
            return;
        cout << "Ingrese columna: ";
        cin >> col;
        cout << "Ingrese número: ";
        cin >> num;

        row--;
        col--;
        if (!isSafe(board, row, col, num)) {
            cout << "Movimiento inválido. Intenta de nuevo." << endl;
            continue;
        }
        board[row][col] = num;

        if (isSolvedCompletely(board)) {
            cout << "¡Felicidades! Ha Ganado." << endl;
            printBoard(board);
            return;
        }
    }
}

int main() {
    system("clear");
    srand(time(0));
    
    cout<<  "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        ¡SUDOKU!                                               |" << endl;
    cout << "\t\t\t|       Rellena los números faltantes(Representados por 0) para Ganar           |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    cout << "Ingrese el tamaño del tablero (por ejemplo, 4, 9, 16): ";
    cin >> N;
    SQRT_N = sqrt(N);

    if (SQRT_N * SQRT_N != N) {
        cout << "¡Tamaño inválido! El tamaño debe ser un cuadrado perfecto (por ejemplo, 4, 9, 16)." << endl;
        return 0;
    }
  
    int **board = new int*[N];
    for (int i = 0; i < N; i++)
        board[i] = new int[N];

    FillRandomBoard(board);
   
    while (true) {
        int choice;      
        cout << endl << endl;
        cout << "\t\t[1] Jugar al Sudoku" << endl;
        cout << "\t\t[2] ¿No puedes resolverlo? Ver el Sudoku resuelto" << endl;
        cout << "\t\t[3] Salir" << endl;
        cout << "\t\tIngrese su elección: ";
        cin  >> choice;

        switch (choice) {
            case 1:
                playGame(board);
                break;
            case 2:
                if (solveSudoku(board, 0, 0))
                {
                    cout << "El Sudoku resuelto es: "<< endl;
                    cout << endl << endl;
                    printBoard(board);
                    
                }
                else
                    cout << "No se encontró solución." << endl;
                break;
            case 3:
                system("clear");
                exit(0);
            default:
                cout << "Elección inválida" << endl;
        }
    }

    for (int i = 0; i < N; i++)
        delete[] board[i];
    delete[] board;

    return 0;
}
