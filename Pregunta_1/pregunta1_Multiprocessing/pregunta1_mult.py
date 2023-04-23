# -*- coding: utf-8 -*-
"""
Created on Sat Apr 22 20:23:59 2023

@author: ASUS
"""

import multiprocessing
from funciones import es_palindromo

def main():
    pal = input("Ingresa una palabra: ") 
    # usamos dos procesos 
    with multiprocessing.Pool(processes=2) as pool:
        resultado = pool.map(es_palindromo, [pal])[0]
    if resultado:
        print("VERDADERO")
    else:
        print("FALSO")

if __name__ == '__main__':
    main()
