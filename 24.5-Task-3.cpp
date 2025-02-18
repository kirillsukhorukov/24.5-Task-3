#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// Функция вывода приветствия
void hello()
{
    std::cout << "----- Hello! Welcome to the 'TIMER' program. -----" << std::endl << std::endl;
    std::cout << "Enter the time interval to be recorded on the timer in the format MM:SS," << std::endl;
    std:: cout << "maximum interval 59 minutes 59 seconds." << std::endl;
}

// Функция проверки корректнеости ввода времени
bool valid_time (int& minute, int& second)
{
    std::string timerTime;
    std::cin >> timerTime; 
   
    // Проверка длины строки
    if (timerTime.length() != 5)
    {
        std::cout << "Error! Invalid time interval format. Please retry." << std::endl;
        return false;
    }
        
    // Проверка формата разделителя
    if (timerTime[2] != ':')
    {
        std::cout << "Error! Invalid time interval format. Please retry." << std::endl;
        return false;
    }

    // Извлечение компонентов времени таймера
    std::string minStr = timerTime.substr(0, 2);
    std::string secStr = timerTime.substr(3, 2);

    // Проверка, что все компоненты состоят из цифр
    for(char c : minStr) if(!isdigit(c)) 
    {
        std::cout << "Error! Invalid time interval format. Please retry." << std::endl;
        return false;
    }
    for(char c : secStr) if(!isdigit(c)) 
    {
        std::cout << "Error! Invalid time interval format. Please retry." << std::endl;
        return false;
    }
    
    // Преобразование в числа
    minute = std::stoi(minStr);
    second = std::stoi(secStr);

    // Проверка диапазона минут и секунд
    if (minute > 59 || second > 59)
    {
        std::cout << "Error! The time interval is incorrect. Please retry." << std::endl;
        return false;
    }

    return true;
}

// Функция ввода времени, которое нужно засеч
void input_time (int& interval)
{
    int minute;
    int second;

    do
    {
        std::cout << "Enter the time interval: ";
    }
    while (!valid_time(minute, second));

    interval = minute*60+second;
    
    return;
}

// Функция для реализации таймера обратного отсчета
void countdown_timer(const int& interval) 
{
    using namespace std::chrono;

    // Системное время начала отсчета
    auto startTime = steady_clock::now();
    // Системное время окончания отсчета 
    auto endTime = startTime+interval*1s;
    // Цикл отсчета времени
    while (steady_clock::now() < endTime) 
    {
        auto remaining = endTime - steady_clock::now();
        int remainingSec = duration_cast<seconds>(remaining).count();

        // Очистка текущей строку и вывод оставшегося времени
        std::cout << "\rLeft: " << remainingSec/60 << " min : " << remainingSec%60 << " sec"<< std::flush;

        // Пауза на 1 секунду
        std::this_thread::sleep_for(1s);
    }

    // Вывод сообщения о том, что время вышло
    std::cout << std::endl << "DING! DING! DING!" << std::endl;
}

int main ()
{
    // Приветствие
    hello();
    // Переменная заваемого интервала времени в секундах
    int interval = 0;
    // Ввод интервала
    input_time(interval);
    // Таймер обратного отсчета
    countdown_timer(interval);

    return 1;
}