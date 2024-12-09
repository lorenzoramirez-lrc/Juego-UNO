Juego UNO
===============
**Autores:** Lorenzo Ramírez Calderón, Danna Valentina Cano, Juan Pablo Vanegas, Laura Lesmes Ocampo

## Descripcion General
Juego tradicional de UNO programado en el lenguaje de programacion C++.
## Manual del Usuario

**Compilación y Ejecución:** Ingrese el archivo en un entorno de desarrollo integrado de C + + ya
sea web o local y compile el código. El juego se desarrolla en la terminal.


**Controles:** Todos los controles son a teclado, todas las entradas de texto están diseñadas para ingresar números enteros con excepción de escoger el color e ingresar los nombres de los jugadores.


**Precaución:** Ingresar una entrada que no sea un número entero sin contar las excepciones llevará a la corrupción del programa y tendrá que volver a ser iniciado.

**Reglas:** Se siguen las reglas originales de UNO, en la variación de puntaje en la cual al finalizar cada ronda se le suman los puntos de sus cartas restantes a cada jugador. Al finalizar de jugar el jugador con menor puntaje es el ganador definitivo. 
Se sigue la siguiente tabla para los puntajes:
<div align="center">
Todas las cartas con número (0-9) ..................Valor del número

Roba dos......................................................................20 puntos 

Reversa........................................................................20 puntos

Salta.............................................................................20 puntos 

Comodín ......................................................................50 puntos 

Comodín Roba cuatro ..................................................50 puntos
</div>
 
**Código de cartas:** Las cartas siguen una estructura de dos caracteres, el primero indicando el número (0 a 9) y el segundo el color Azul (A), Dorado(D), Rojo(R), Verde(V), esta estructura se mantiene a excepción de las cartas de acción que siguen la siguiente estructura primer carácter (B) bloquear, (S) robar 2, (R) reversa, segundo carácter color respectivo, y para los comodines +4 (4S) y cambio de color (CC).
Ejemplo: 0A(Cero azul), RV (Reversa verde), 8R (Ocho rojo), SD(Robar 2 dorado)


