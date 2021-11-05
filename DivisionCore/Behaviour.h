/**
  * @file Behaviour.h
  * @author Daniel Molinero Lucas (Papishushi)
  * @section Copyright © <2021+> <Daniel Molinero Lucas (Papishushi)> MIT LICENSE
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  * to deal in the Software without restriction, including without limitation the rights to use, copy,
  * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
  * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  **/
#ifndef DIVISIONCORE_BEHAVIOUR_H
#define DIVISIONCORE_BEHAVIOUR_H
#include "Component.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <thread>
#endif

#include <chrono>

namespace DivisionCore { namespace Core { namespace BehaviourSystem
{
    class Behaviour : public Component
    {
    public:
        bool enabled;
        bool isActiveAndEnabled;

        Behaviour(){
            enabled = true;
            isActiveAndEnabled = true;
        };

        static std::chrono::duration<double> GetUpdateRate()
        {
            // Using time point and system_clock
            std::chrono::time_point<std::chrono::system_clock> start, end;

            start = std::chrono::system_clock::now();
#if _WIN32
                Sleep(1000/60);
#elif __linux__
                using namespace std::literals;
            std::this_thread::sleep_for(1000ms/60);
#else __APPLE__
            sleep(1000/60);
#endif
            end = std::chrono::system_clock::now();

            return end - start;
        }
        static std::chrono::duration<double> GetAverageUpdateRate()
        {
            std::chrono::duration<double> temp[60];

            for(auto & i : temp)
            {
                i = GetUpdateRate();
            }

            std::chrono::duration<double> averageRate{};

            for(auto & i : temp)
            {
                averageRate += i;
            }

            return averageRate /= 60;

        }
    };
} } }
#endif //DIVISIONCORE_BEHAVIOUR_H

