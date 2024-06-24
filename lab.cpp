#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <tuple>

using namespace std;

// Movimientos posibles
vector<tuple<int, int, char>> directions = {{1, 0, 'D'}, {-1, 0, 'U'}, {0, 1, 'R'}, {0, -1, 'L'}};

// Verificar si una celda está dentro de los límites del laberinto
bool isValid(int i, int j, vector<vector<int>>& maze) {
    return 0 <= i && i < maze.size() && 0 <= j && j < maze[0].size();
}

// Búsqueda en profundidad (DFS) para encontrar todos los caminos posibles
void dfs(int i, int j, vector<vector<int>>& maze, set<pair<int, int>>& visited, vector<string>& ans, string path, int limit) {
    if (i == maze.size() - 1 && j == maze[0].size() - 1) {  // Si llegamos a la celda de destino
        ans.push_back(path);
        return;
    }
    if (ans.size() >= limit) {
        return;
    }
    visited.insert({i, j});  // Marcar la celda actual como visitada

    for (const auto& dir : directions) {
        int di = get<0>(dir);
        int dj = get<1>(dir);
        char direction = get<2>(dir);
        int ni = i + di, nj = j + dj;
        if (isValid(ni, nj, maze) && visited.find({ni, nj}) == visited.end() && maze[ni][nj] == 1) {
            dfs(ni, nj, maze, visited, ans, path + direction, limit);
        }
    }
    visited.erase({i, j});
}

// Encontrar caminos posibles en el laberinto generado
vector<string> find_Path(vector<vector<int>>& maze, int n, int limit = 1) {  // Por defecto, limitar a 1 camino
    vector<string> ans;
    if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
        return ans;
    }
    string path = "";
    set<pair<int, int>> visited;
    dfs(0, 0, maze, visited, ans, path, limit);
    return ans;
}

// Generar un laberinto con un camino garantizado
vector<vector<int>> generate_maze_with_path(int n) {
    vector<vector<int>> maze(n, vector<int>(n, 0));
    
    // Crear un camino directo desde la entrada hasta la salida
    int x = 0, y = 0;
    while (x < n - 1 || y < n - 1) {
        maze[x][y] = 1;
        if (x < n - 1 && (y == n - 1 || rand() % 2 == 0)) {
            x++;
        } else {
            y++;
        }
    }
    maze[x][y] = 1;  // Asegurarse de que la última celda (n-1, n-1) esté marcada como camino

    // Añadir obstáculos aleatorios sin bloquear el camino
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == 0 && rand() % 2 == 0) {
                maze[i][j] = 0;
            } else {
                maze[i][j] = 1;
            }
        }
    }

    return maze;
}

int main() {
    srand(time(0));

    // Tamaño del laberinto
    int n;
    cout << "Ingrese el tamaño del laberinto: ";
    cin >> n;
    vector<vector<int>> maze = generate_maze_with_path(n);

    // Imprimir el laberinto generado
    cout << "Laberinto generado:" << endl;
    for (const auto& row : maze) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    // Encontrar todos los caminos posibles en el laberinto generado usando DFS
    vector<string> paths = find_Path(maze, n, 1);

    // Imprimir los caminos encontrados
    cout << "\nCaminos encontrados:" << endl;
    for (const auto& path : paths) {
        cout << path << endl;
    }

    return 0;
}








