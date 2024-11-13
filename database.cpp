#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <string>
#include <vector>

// Функция для создания таблиц
void create_tables(sqlite3* db) {
    const char* create_user_data = "CREATE TABLE IF NOT EXISTS User_Data ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "login TEXT NOT NULL,"
        "nickname TEXT NOT NULL,"
        "password TEXT NOT NULL);";

    const char* create_playing_stats = "CREATE TABLE IF NOT EXISTS Playing_Stats ("
        "user_id INTEGER,"
        "gameplay_time INTEGER,"
        "FOREIGN KEY (user_id) REFERENCES User_Data (user_id));";

    char* errMsg = 0;
    sqlite3_exec(db, create_user_data, 0, 0, &errMsg);
    sqlite3_exec(db, create_playing_stats, 0, 0, &errMsg);
}

// Функция для создания пользователя
void create_user(sqlite3* db, const std::string& login, const std::string& nickname, const std::string& password) {
    std::string sql = "INSERT INTO User_Data (login, nickname, password) VALUES ('" + login + "', '" + nickname + "', '" + password + "');";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для создания статистики
void create_stats(sqlite3* db, int user_id, int gameplay_time) {
    std::string sql = "INSERT INTO Playing_Stats (user_id, gameplay_time) VALUES (" + std::to_string(user_id) + ", " + std::to_string(gameplay_time) + ");";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для чтения данных пользователя
void read_user(sqlite3* db, int user_id) {
    std::string sql = "SELECT * FROM User_Data WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "User Data: "
            << sqlite3_column_int(stmt, 0) << " "
            << sqlite3_column_text(stmt, 1) << " "
            << sqlite3_column_text(stmt, 2) << " "
            << sqlite3_column_text(stmt, 3) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Функция для чтения статистики игры
void read_stats(sqlite3* db, int user_id) {
    std::string sql = "SELECT * FROM Playing_Stats WHERE user_id = " + std::to_string(user_id) + ";";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "Stats Data: "
            << sqlite3_column_int(stmt, 0) << " "
            << sqlite3_column_int(stmt, 1) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Функция для обновления данных пользователя
void update_user(sqlite3* db, int user_id, const std::string& login, const std::string& nickname, const std::string& password) {
    std::string sql = "UPDATE User_Data SET login = '" + login + "', nickname = '" + nickname + "', password = '" + password + "' WHERE user_id = " + std::to_string(user_id) + ";";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для обновления статистики игры
void update_stats(sqlite3* db, int user_id, int gameplay_time) {
    std::string sql = "UPDATE Playing_Stats SET gameplay_time = " + std::to_string(gameplay_time) + " WHERE user_id = " + std::to_string(user_id) + ";";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для удаления пользователя
void delete_user(sqlite3* db, int user_id) {
    std::string sql = "DELETE FROM User_Data WHERE user_id = " + std::to_string(user_id) + ";";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для удаления статистики
void delete_stats(sqlite3* db, int user_id) {
    std::string sql = "DELETE FROM Playing_Stats WHERE user_id = " + std::to_string(user_id) + ";";
    char* errMsg = 0;
    sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
}

// Функция для экспорта данных в CSV
void export_to_csv(sqlite3* db, const std::string& table_name, const std::string& file_name) {
    std::ofstream file(file_name);
    std::string sql = "SELECT * FROM " + table_name + ";";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int col = 0; col < sqlite3_column_count(stmt); ++col) {
            if (col > 0) {
                file << ",";
            }
            const char* text = (const char*)sqlite3_column_text(stmt, col);
            file << (text ? text : "");
        }
        file << "\n";
    }

    sqlite3_finalize(stmt);
    file.close();
}

int main() {
    sqlite3* db;
    sqlite3_open("game_stats.db", &db);
    create_tables(db);

    int code;
    std::cin >> code;

    switch (code) {
    case 0: {
        std::string login, nickname, password;
        std::cin >> login >> nickname >> password;
        create_user(db, login, nickname, password);
        int user_id = sqlite3_last_insert_rowid(db);
        create_stats(db, user_id, 0);
        break;
    }
    case 1: {
        int user_id;
        std::cin >> user_id;
        read_user(db, user_id);
        break;
    }
    case 2: {
        int user_id;
        std::cin >> user_id;
        read_stats(db, user_id);
        break;
    }
    case 3: {
        int user_id;
        std::string new_login, new_nickname, new_password;
        std::cin >> user_id >> new_login >> new_nickname >> new_password;
        update_user(db, user_id, new_login, new_nickname, new_password);
        break;
    }
    case 4: {
        int user_id, new_gameplay_time;
        std::cin >> user_id >> new_gameplay_time;
        update_stats(db, user_id, new_gameplay_time);
        break;
    }
    case 5: {
        int user_id;
        std::cin >> user_id;
        delete_user(db, user_id);
        delete_stats(db, user_id);
        break;
    }
    case 6: {
        export_to_csv(db, "User_Data", "user_data.csv");
        export_to_csv(db, "Playing_Stats", "playing_stats.csv");
        break;
    }
    }

    sqlite3_close(db);
    return 0;
}