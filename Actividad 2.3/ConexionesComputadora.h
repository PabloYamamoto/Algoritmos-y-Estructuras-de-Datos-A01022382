/*
Clase de ConexionesComputadora para definir cada ip de la computadora y sus conexiones. 
Pablo Yamamoto - A01022382 
Santiago Kohn - A01029109
Fecha de creación - 12/10/2020
Fecha de última modificación - 13/10/2020
*/

#include <queue>
#include <stack>
#include "DataBase.h"

using namespace std;

template<class T>
#pragma once
class ConexionesComputadora
{
    string ip, nombre;
    stack<string> conexionesEntrantes;
    queue<string> conexionesSalientes;

public:
    ConexionesComputadora(){};
    ConexionesComputadora(string ip, string nombre, DataBase<T> *vector):ip{ip},nombre{nombre}
    {
        for (int i = 0; i < vector->All_Registrations.size(); i++)
        {
            if (vector->All_Registrations.at(i).getDestination_IP() == ip)
                conexionesEntrantes.push(vector->All_Registrations.at(i).getSource_IP());
            if (vector->All_Registrations.at(i).getSource_IP() == ip)
                conexionesSalientes.push(vector->All_Registrations.at(i).getDestination_IP());
        }
    }
    ~ConexionesComputadora(){}

    stack<string>* get_conexionesEntrantes(){return &conexionesEntrantes;}
    queue<string>* get_conexionesSalientes(){return &conexionesSalientes;}

    bool preguntaExtra(int n)
    {
        string ip;
        int i = 1;
        while(!conexionesSalientes.empty())
        {
            ip = conexionesSalientes.front();
            conexionesSalientes.pop();
            // Algoritmo que identifica exactamente 3 ip seguidas.
            /*
            if (!conexionesSalientes.empty() && ip == conexionesSalientes.front())
            {
                conexionesSalientes.pop();
                if (!conexionesSalientes.empty() && ip == conexionesSalientes.front())
                    return true;
            }
            */ 
            while(i<n){
                if (!conexionesSalientes.empty() && ip == conexionesSalientes.front())
                    conexionesSalientes.pop();
                else
                {
                    i = 1;
                    break;
                }
                i++;
            }
            if (i == n)
                return true;
        }
        return false;
    }
};
