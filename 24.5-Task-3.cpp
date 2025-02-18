#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>

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
void input_time (std::tm& interval)
{
    int minute;
    int second;

    do
    {
        std::cout << "Enter the time interval: ";
    }
    while (!valid_time(minute, second));

    interval.tm_min = minute;
    interval.tm_sec = second;
    
    return;
}

int main ()
{
    hello();

    std::tm interval = {0};
    input_time(interval);
    
    std::cout << "Time interval->  " << std::put_time(&interval, "%M:%S") << std::endl;
    
    
    return 1;
}