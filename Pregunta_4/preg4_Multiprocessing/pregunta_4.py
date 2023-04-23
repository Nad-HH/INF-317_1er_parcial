# -*- coding: utf-8 -*-
"""
Created on Sun Apr 23 13:18:04 2023

@author: ASUS
"""

import multiprocessing


# funcion fibonacci con la tecnica de la memorizacion para mejorar el tiempo de ejecucion
def fibonacci(n, memo={}): 
    # Verificar si el resultado ya ha sido calculado anteriormente
    if n in memo:
        return memo[n]
    
    # Casos base
    if n == 0:
        memo[n] = 0
        return 0
    elif n == 1:
        memo[n] = 1
        return 1
    
    # Cálculo recursivo con ayuda de un diccionario
    memo[n] = fibonacci(n-1, memo) + fibonacci(n-2, memo)
    return memo[n]

if __name__ == '__main__':
    # usamos todos los procesos disponibles
    with multiprocessing.Pool() as pool:
        result = pool.map(fibonacci, range(1000))
    print(result)
