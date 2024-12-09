/*
Codigo Fuente Juego UNO
Autores:Lorenzo Ramirez Calderon, Juan Pablo Vanegas, Danna Valentina Cano, Laura Lesmes Ocampoo
Profesor: Andres Felipe Pedraza Infante
Universidad: Pontificia Universidad Javeriana
Fecha: 13 de noviembre, 2024

Descripcion: Juego Uno de 2 a 4 jugadores, utilizando el  modo de juego de multiples rondas en base a puntaje
*/

#include <iostream>
#include <ctime>

using namespace std;

//Creacion estructura jugador
struct jugador{
    string nombre;
    int numero_cartas;
    int puntaje;
};

//Firma de funciones
void mezclar_cartas(string lista[],int numero_cartas);
int calcular_puntaje(string baraja_jugadores[][54],jugador jugadores[],int jugador);
void reversa(int turnos_jugadores[], int posicionActual, int cantidad_jugadores);

int main(){

int iniciar=0;

//Inicilizacion del menu
while(iniciar!=2){
    cout<<"Bienvenido al Clasico Juego UNO!"<<endl;
    cout<<"1.Iniciar Juego"<<endl;
    cout<<"2.Salir del Juego"<<endl;
    cout<<"Selecione alguna de las opciones para continuar: ";
    cin>>iniciar;
    
    //Se crea error para opcion incorrecta
    while((iniciar!=1) && (iniciar!=2)){
        cout<<"Opcion incorrecta intente nuevamente"<<endl;
        cout<<"1.Iniciar Juego"<<endl;
        cout<<"2.Salir del Juego"<<endl;
        cout<<"Selecione alguna de las opciones para continuar: ";
        cin>>iniciar;
    }
    
    //Inicialicion del Juego
    if(iniciar==1){

        //Numero de jugadores y se crea error para opcion incorrecta de jugadores
        int numero_de_jugadores;
        cout<<"Ingrese el numero de jugadores (2 a 4): ";
        cin>>numero_de_jugadores;
        
        while(numero_de_jugadores<2||numero_de_jugadores>4){
            cout<<"Numero de jugadores no permitido intente nuevamente"<<endl;
            cout<<"Ingrese el numero de jugadores (2 a 4): ";
            cin>>numero_de_jugadores;
        }
        //Inicializa arreglo de estructuras con el numero de jugadores(nombre, numero de cartas, y puntaje)
        jugador jugadores[numero_de_jugadores];

        for(int i=0;i<numero_de_jugadores;i++){
            cout<< "Inserte el nombre del Jugador "<<i+1<<": ";
            cin>> jugadores[i].nombre;
            jugadores[i].numero_cartas=7;
            jugadores[i].puntaje=0;
        }
        cout<<endl;
        //Se crea matriz de baraja de jugadores y arreglo de la baraja de descarte
        string baraja_jugadores[numero_de_jugadores][54];
        string descarte[108];
        
        //Se inicializa la ronda
        int otra_ronda=-1;
        int numero_de_rondas=0;
        do{

            //Se inicializa baraja de juego
            string baraja[108] = {"0A", "1A", "2A", "3A", "4A", "5A", "6A", "7A", "8A", "9A", "1A", "2A", "3A", "4A", "5A", "6A", "7A", "8A", "9A", "0V", "1V", "2V", "3V", "4V", "5V",
            "6V", "7V", "8V", "9V", "1V", "2V", "3V", "4V", "5V", "6V", "7V", "8V", "9V", "0R", "1R", "2R", "3R", "4R", "5R", "6R", "7R", "8R", "9R", "1R", "2R", "3R", "4R", "5R", 
            "6R", "7R", "8R", "9R", "0D", "1D", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "1D", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "SA", "SA", "SR", "SR", "SV", "SV",
            "SD", "SD", "RA", "RA", "RV", "RV", "RR","RR", "RD", "RD", "BA","BA", "BV", "BV", "BR", "BR", "BD","BD", "4S", "4S", "4S", "4S", "CC", "CC", "CC", "CC"};
            int tamaño_baraja=108;
            
            //Se mezclan las cartas
            mezclar_cartas(baraja,108);

            //Asignacion nuevamente de 7 cartas a cada jugador en caso tal de haber una segunda ronda
            for(int i=0;i<numero_de_jugadores;i++){
                jugadores[i].numero_cartas=7;
            }

            //Se inicializa matriz descarte en blanco
            for(int i=0;i<108;i++){
                descarte[i]="";
            }
            int tamaño_descarte=0;

            //Se crea arreglo de control de turnos
            int turnos_jugadores[numero_de_jugadores];

            //Se inicializa arreglo de control de turnos desdeee 0 hasta numero de jugadores-1
            for(int i=0;i<numero_de_jugadores;i++){
                turnos_jugadores[i]=i;
            }
            //Se inicializa la baraja de cada jugador vacia
            for(int i=0;i<numero_de_jugadores;i++){
                for(int k=0;k<7;k++){
                    baraja_jugadores[i][k]="";
                }
            }
            
            //Se asignan 7 cartas a cada jugador
            int contadorbaraja=0;
            for(int i=0;i<numero_de_jugadores;i++){
                for(int k=0;k<7;k++){
                    baraja_jugadores[i][k]=baraja[contadorbaraja];
                    contadorbaraja+=1;
                }
            }

            //Se inicializa booleano que establece si hay cambio de color presente
            bool cambio_color=false;

            //Se asigna la carta de inicio de juego como primera carta de descarta
            descarte[0]= baraja[contadorbaraja];
            tamaño_descarte+=1;
            //Se inicializa la carta_actual
            string carta_actual;
            cout<<"Inicia el Juego"<<endl<<endl;

            //Pide al jugador anterior al que inicia que escoja un color en caso tal de que la carta inicial sea un +4 o un Cambio de color
            if(descarte[0][1]=='S'||descarte[0][1]=='C'){
                cout<<"El juego ha iniciado con una carta +4 o de cambio de color"<<endl;
                cout<<jugadores[numero_de_jugadores-1].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color con el que iniciara el juego: ";
                cout<<"para elegir el color con el que iniciara el juego: ";
                cin>>carta_actual;

                while(carta_actual.size()>2||carta_actual.size()<2||(carta_actual[1]!='A'&&carta_actual[1]!='D'&&carta_actual[1]!='V'&&carta_actual[1]!='R')){
                    cout<<"Color o tamaño del texto ingresado no es valido intente nuevamente"<<endl;
                    cout<<jugadores[numero_de_jugadores-1].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color con el que iniciara el juego: ";
                    cin>>carta_actual;
                }

                cambio_color=true;
            }
           
            //Se mueve el arreglo de la baraja teniendo en cuenta las cartas extraidas de esta y se modifica el tamaño
            for(int i=contadorbaraja;i<108; i++){
                baraja[i-contadorbaraja]=baraja[i];
            }
            tamaño_baraja-=contadorbaraja;

            //Se inicializa booleanos de control de juego
            bool jugador_con_0_cartas=false;
            bool salta=false;
            bool reversas=false;

            //Ciclo que revisa si algun jugador gano
            while(jugador_con_0_cartas==false){
                //Ciclo de los turnos de juego
                for(int turno=0;turno<numero_de_jugadores;turno++){
                    //Se revisa que el jugador anterior no haya puesto una carta de bloqueo
                    if(salta==false){
                        //Si la anterior carta fue de reversa se regresa a falso
                        if(reversas==true){
                            reversas=false;
                        }

                        //Se calcula el proximo jugador teniendo en cuenta si este es el ultimo del arreglo o no
                        int proximo_jugador;
                        if(turno==numero_de_jugadores-1){
                            proximo_jugador=0;
                        }else{
                            proximo_jugador=turno+1;
                        }

                        //Se menciona de quien es el turno y se muestran sus cartas cada una asignada a un numero
                        cout<< "Turno de "<<jugadores[turnos_jugadores[turno]].nombre<<endl;
                        cout<<"Codigo de Cartas: Azul(#A), Amarillo(#D), Verde(#V), Rojo(#R), Bloquear(B(C)), Reversa(R(C)), +2(S(C)), +4 (4S), Cambiar Color(CC)"<<endl;
                        cout<<"#=Numero, (C)=Color"<<endl;
                        cout<<"Tus cartas son:";
                        for(int k=0;k<jugadores[turnos_jugadores[turno]].numero_cartas;k++){
                            cout<<k+1<<"."<<baraja_jugadores[turnos_jugadores[turno]][k]<<", ";
                        }
                        
                        cout<<endl;
                        //Se selecciona y muestra la carta actual de la primera posicion de descarte siempre y cuando la anterior no haya sido de cambio de color
                        if(cambio_color==false){
                            carta_actual=descarte[0];
                        }
                        cout<<"La carta actual es: "<<carta_actual<<endl;

                        //Se inicializa el color y numero actual de la carta
                        char numero_actual=carta_actual[0];
                        char color_actual=carta_actual[1];
                        
                        //Se le pide al jugador que ingrese el numero de la carta a jugar
                        int numero_carta_a_jugar;
                        cout<<"Ingrese el numero de la carta que quiere jugar o si quiere robar una carta presione (0): ";
                        cin>>numero_carta_a_jugar;

                        //Se inicializa booleano de si se va a robar carta si el numero es igual a cero se vuelve verdadera
                        bool robar_carta=false;
                        
                        if(numero_carta_a_jugar==0){
                            robar_carta=true;
                        }
                        
                        //ciclo para revisar que la carta ingresada pueda ser jugada
                        if(robar_carta==false){
                            do{
                                while((numero_carta_a_jugar<0)||(numero_carta_a_jugar>jugadores[turnos_jugadores[turno]].numero_cartas)){
                                    cout<<"Carta no existente intente nuevamente con el numero de una carta en su baraja";
                                    cout<<"Ingrese el numero de la carta que quiere jugar o si quiere robar una carta presione (0):";
                                    cin>>numero_carta_a_jugar;
                                }
                                while((baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]!=numero_actual)&&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!=color_actual)
                                &&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!='S')&&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!='C')&&numero_carta_a_jugar!=0){
                                    cout<<"Esta carta no puede ser jugada recuerde que debe coincidir el color o el numero o la accion o ser un comodin"<<endl;
                                    cout<<"Ingrese el numero de la carta que quiere jugar o si quiere robar una carta presione (0):  ";
                                    cin>>numero_carta_a_jugar;
                                }

                                if(numero_carta_a_jugar==0){
                                    robar_carta=true;
                                }

                            }while(((baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]!=numero_actual)&&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!=color_actual)
                                &&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!='S')&&(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]!='C'))&&numero_carta_a_jugar!=0);
                        }
                        
                        //En caso de que no se robe una carta el cambio de color se vuelve falso de resto se mantiene verdadero hasta que alguien juegue una carta
                        if(cambio_color==true&&robar_carta==false){
                            cambio_color=false;
                        }

                        //Jugar carta de manera normal
                        if(robar_carta==false){
                            //Se traslada el arreglo descarte una pocision a la derecha y se inserta la carta jugada en la primera pocision
                            for(int i=0;i<tamaño_descarte;i++){
                                descarte[i+1]=descarte[i];
                            }
                            descarte[0]=baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1];
                            tamaño_descarte+=1;

                            
                            //Se revisa si la carta es de accion
                            if((baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='B')||(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='R')||(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='S')
                            ||(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]=='S')||(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]=='C')){

                                if(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='B'){
                                    salta=true;  //Si es de bloquear se activa el booleano salta para bloquear al siguiente jugador
                                }else if(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='R'){
                                    reversa(turnos_jugadores,turno,numero_de_jugadores); //funcion de reversa y se activa booleano indicando que se hizo una reversa
                                    reversas=true;
                                }else if(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][0]=='S'){
                                    //Se añaden dos cartas al siguiente jugador, se actualiza la baraja de cartas y se salta su turno activando el booleano de salta
                                    cout<<"+2 ha sido jugado se le añadira dos cartas a "<<jugadores[turnos_jugadores[proximo_jugador]].nombre<<" y su turno sera saltado"<<endl;
                                    for(int i=0;i<2;i++){
                                        baraja_jugadores[turnos_jugadores[proximo_jugador]][jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+i]=baraja[i];
                                    }
                                    jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+=2;
                                    for(int i=2;i<108; i++){
                                        baraja[i-2]=baraja[i];
                                    }
                                    tamaño_baraja-=2;
                                    salta=true;
                                }else if(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]=='S'){
                                    //Se añaden dos cartas al siguiente jugador, se actualiza la baraja de cartas y se salta su turno activando el booleano de salta y le pide al usuario escoger un color activando el booleano
                                    cout<<"+4 ha sido jugado se le añadiran cuatro cartas a "<<jugadores[turnos_jugadores[proximo_jugador]].nombre<<" y su turno sera saltado"<<endl<<endl;
                                    for(int i=0;i<4;i++){
                                        baraja_jugadores[turnos_jugadores[proximo_jugador]][jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+i]=baraja[i];
                                    }
                                    jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+=4;
                                    for(int i=4;i<108; i++){
                                        baraja[i-4]=baraja[i];
                                    }
                                    tamaño_baraja-=4;
                                    salta=true;
                                    cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                    cin>>carta_actual;

                                    while(carta_actual.size()>2||carta_actual.size()<2||(carta_actual[1]!='A'&&carta_actual[1]!='D'&&carta_actual[1]!='V'&&carta_actual[1]!='R')){
                                        cout<<"Color o tamaño del texto ingresado no es valido intente nuevamente"<<endl;
                                        cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                        cin>>carta_actual;
                                    }

                                    cambio_color=true;

                                }else if(baraja_jugadores[turnos_jugadores[turno]][numero_carta_a_jugar-1][1]=='C'){
                                    //le pide al usuario escoger un color activando el booleano respectivo
                                    cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                    cin>>carta_actual;

                                    while(carta_actual.size()>2||carta_actual.size()<2||(carta_actual[1]!='A'&&carta_actual[1]!='D'&&carta_actual[1]!='V'&&carta_actual[1]!='R')){
                                        cout<<"Color o tamaño del texto ingresado no es valido intente nuevamente"<<endl;
                                        cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                        cin>>carta_actual;
                                    }
                                    cambio_color=true;
                                }

                            }
                            if((numero_de_jugadores==2)&&(reversas==true)){
                                //Caso especial donde se retira la carta de un jugador de su baraja despues de haberse jugado una reversa y solo hay dos jugadores
                                for(int i=numero_carta_a_jugar-1;i<jugadores[turnos_jugadores[proximo_jugador]].numero_cartas;i++){
                                    baraja_jugadores[turnos_jugadores[proximo_jugador]][i]=baraja_jugadores[turnos_jugadores[proximo_jugador]][i+1];
                                }
                                jugadores[turnos_jugadores[proximo_jugador]].numero_cartas-=1;
                            }else{
                                //Se retira la carta jugada de la baraja del jugador
                                for(int i=numero_carta_a_jugar-1;i<jugadores[turnos_jugadores[turno]].numero_cartas;i++){
                                    baraja_jugadores[turnos_jugadores[turno]][i]=baraja_jugadores[turnos_jugadores[turno]][i+1];
                                }
                                jugadores[turnos_jugadores[turno]].numero_cartas-=1;
                            }
                        
                        }
                        //Robar carta
                        if(robar_carta==true){
                            string carta_robada=baraja[0];//Se asigna la primera carta de la baraja como la carta robada
                            if(carta_robada[0]==numero_actual||carta_robada[1]==color_actual||carta_robada[1]=='C'||carta_robada[1]=='S'){//Se revisa si la carta robada puede ser jugada inmediatamente
                                cout<<"Su carta robada fue "<<carta_robada<<" y pudo ser jugada"<<endl;
                                //Se desplazan y modifican los tamaños de los arreglos de baraj y descarte
                                for(int i=1;i<108; i++){
                                    baraja[i-1]=baraja[i];
                                }
                                tamaño_baraja-=1;
                                for(int i=0;i<tamaño_descarte;i++){
                                descarte[i+1]=descarte[i];
                                }
                                descarte[0]=carta_robada;
                                tamaño_descarte+=1;
                                cambio_color=false;
                                
                                //Mismo funcionamiento de cartas accion
                                if((carta_robada[0]=='B')||(carta_robada[0]=='R')||(carta_robada[0]=='S')||(carta_robada[1]=='S')||(carta_robada[1]=='C')){

                                    if(carta_robada[0]=='B'){
                                        salta=true;
                                    }else if(carta_robada[0]=='R'){
                                        reversa(turnos_jugadores,turno,numero_de_jugadores);
                                        reversas=true;
                                    }else if(carta_robada[0]=='S'){
                                        cout<<"+2 ha sido jugado se le añadira dos cartas a "<<jugadores[turnos_jugadores[proximo_jugador]].nombre<<" y su turno sera saltado"<<endl;
                                        for(int i=0;i<2;i++){
                                            baraja_jugadores[turnos_jugadores[proximo_jugador]][jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+i]=baraja[i];
                                        }
                                        jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+=2;
                                        for(int i=2;i<108; i++){
                                            baraja[i-2]=baraja[i];
                                        }
                                        tamaño_baraja-=2;
                                        salta=true;
                                    }else if(carta_robada[1]=='S'){
                                        cout<<"+4 ha sido jugado se le añadiran cuatro cartas a "<<jugadores[turnos_jugadores[proximo_jugador]].nombre<<" y su turno sera saltado"<<endl<<endl;
                                        for(int i=0;i<4;i++){
                                            baraja_jugadores[turnos_jugadores[proximo_jugador]][jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+i]=baraja[i];
                                        }
                                        jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+=4;
                                        for(int i=4;i<108; i++){
                                            baraja[i-4]=baraja[i];
                                        }
                                        tamaño_baraja-=4;
                                        salta=true;
                                        cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                        cin>>carta_actual;

                                        while(carta_actual.size()>2||carta_actual.size()<2||(carta_actual[1]!='A'&&carta_actual[1]!='D'&&carta_actual[1]!='V'&&carta_actual[1]!='R')){
                                            cout<<"Color o tamaño del texto ingresado no es valido intente nuevamente"<<endl;
                                            cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                            cin>>carta_actual;
                                        }

                                        cambio_color=true;

                                    }else if(carta_robada[1]=='C'){
                                        cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                        cin>>carta_actual;

                                        while(carta_actual.size()>2||carta_actual.size()<2||(carta_actual[1]!='A'&&carta_actual[1]!='D'&&carta_actual[1]!='V'&&carta_actual[1]!='R')){
                                            cout<<"Color o tamaño del texto ingresado no es valido intente nuevamente"<<endl;
                                            cout<<jugadores[turnos_jugadores[turno]].nombre<<" digite (XD) para dorado, (XA) para azul, (XV) para verde, (XR) para rojo para elegir el color al que quiere cambiar: ";
                                            cin>>carta_actual;
                                        }
                                        cambio_color=true;
                                    }
                                }
                            }else{
                                //Si la carta no puede ser jugada se añade la carta a la baraj del jugador y se modifica la baraja
                                cout<<"Su carta robada fue "<<carta_robada<<" y no pudo ser jugada inmediatamente"<<endl;
                                cout<<"La carta ha sido insertada en su baraja"<<endl;
                                for(int i=1;i<108; i++){
                                    baraja[i-1]=baraja[i];
                                }
                                tamaño_baraja-=1;
                                baraja_jugadores[turnos_jugadores[turno]][jugadores[turnos_jugadores[turno]].numero_cartas]=carta_robada;
                                jugadores[turnos_jugadores[turno]].numero_cartas+=1;   
                            }   
                        }
                        
                        //Proceso de revision si el jugador dijo uno
                        if((numero_de_jugadores==2)&&(reversas==true)){
                            //Caso especial donde se revisa las cartas es del proximo jugador(que es el actual) debido a que hubo una reversa
                            if(jugadores[turnos_jugadores[proximo_jugador]].numero_cartas==1){
                                int grito_uno=0;
                                cout<< "¿El jugador dijo uno? Presione (1) para si (2) para no:";
                                cin>>grito_uno;
                                while(grito_uno>2||grito_uno<1){
                                    cout<<"Opcion no valida intente nuevamente"<<endl;
                                    cout<< "¿El jugador dijo uno? Presione (1) para si (2) para no:"<<endl;
                                    cin>>grito_uno;
                                }
                                if(grito_uno==2){//Si no se dijo uno se añaden dos cartas a su baraja y se modifica la baraja de juego
                                    for(int i=0;i<2;i++){
                                        baraja_jugadores[turnos_jugadores[proximo_jugador]][jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+i]=baraja[i];
                                    }
                                    jugadores[turnos_jugadores[proximo_jugador]].numero_cartas+=2;
                                    for(int i=2;i<108; i++){
                                        baraja[i-2]=baraja[i];
                                    }
                                    tamaño_baraja-=2;
                                }
                            }
                        }else{
                            if(jugadores[turnos_jugadores[turno]].numero_cartas==1){
                                int grito_uno=0;
                                cout<< "¿El jugador dijo uno? Presione (1) para si (2) para no:";
                                cin>>grito_uno;
                                while(grito_uno>2||grito_uno<1){
                                    cout<<"Opcion no valida intente nuevamente"<<endl;
                                    cout<< "¿El jugador dijo uno? Presione (1) para si (2) para no:"<<endl;
                                    cin>>grito_uno;
                                }
                                if(grito_uno==2){//Si no se dijo uno se añaden dos cartas a su baraja y se modifica la baraja de juego
                                    for(int i=0;i<2;i++){
                                        baraja_jugadores[turnos_jugadores[turno]][jugadores[turnos_jugadores[turno]].numero_cartas+i]=baraja[i];
                                    }
                                    jugadores[turnos_jugadores[turno]].numero_cartas+=2;
                                    for(int i=2;i<108; i++){
                                        baraja[i-2]=baraja[i];
                                    }
                                    tamaño_baraja-=2;
                                }
                            }
                        }
                          


                        //Revisa si el jugador se quedo sin cartas
                        if((numero_de_jugadores==2)&&(reversas==true)){
                            //Caso especial donde se revisa las cartas es del proximo jugador(que es el actual) debido a que hubo una reversa
                            if(jugadores[turnos_jugadores[proximo_jugador]].numero_cartas==0){
                                jugador_con_0_cartas=true;
                                break;
                            }
                        }else{
                            //caso normal
                            if(jugadores[turnos_jugadores[turno]].numero_cartas==0){
                                jugador_con_0_cartas=true;
                                break;
                            }
                        }
                        
                        
                        //En caso de que la baraja se quede sin cartas, se mescla la baraja de descarte y se añaden nuevamente a la baraja dejando vacio el arreglo descarte excepto por la primera carta
                        if(tamaño_baraja==0){
                           
                            for(int i=1;i<tamaño_descarte;i++){
                                baraja[i-1]=descarte[i];
                                descarte[i]="";
                            }
                            tamaño_baraja=tamaño_descarte-1;
                            tamaño_descarte=1;
                            mezclar_cartas(baraja,tamaño_baraja);
                        }
                    }else if(salta==true){
                        //En caso de que se haya jugado una carta de bloqueo se muestra un mensaje y se vuelve el booleano falso para que el proximo jugador ya pueda jugar
                        cout<<jugadores[turnos_jugadores[turno]].nombre<<" su turno ha sido saltado"<<endl;
                        salta=false;    
                    }
                    cout<<endl;
                }
            }
            //Se muestra el ganador de la ronda
            for(int i=0;i<numero_de_jugadores;i++){
                if(jugadores[i].numero_cartas==0){
                    cout<<"El ganador de la ronda ha sido: "<<jugadores[i].nombre<<endl;
                    break;
                }
            }
            //Se calculan y muestran los puntajes de la ronda
            cout<<"Los puntajes de la ronda son:"<<endl;
            for(int i=0;i<numero_de_jugadores;i++){
                int puntaje_ronda=calcular_puntaje(baraja_jugadores,jugadores,i);
                cout<<jugadores[i].nombre<<": "<<puntaje_ronda<<endl;

            }
            cout<<endl<<endl;
            //Se muestran los puntajes globales
            cout<<"Los puntajes globales son:"<<endl;
            for(int i=0;i<numero_de_jugadores;i++){
                cout<<jugadores[i].nombre<<": "<<jugadores[i].puntaje<<endl;
            }
            //Se pregunta si se desea jugar otra ronda se genera error en caso tal de no escoger opcion valida
            cout<<"¿Desea jugar otra ronda? Presione (1) para si (2) para no (Recuerde que la ronda se iniciara con los mismos jugadores, para jugar con otros jugadores regrese al menu principal presionando(2)): ";
            cin>>otra_ronda;
            while(otra_ronda<1||otra_ronda>2){
                cout<<"Opcion no valida, intente nuevamente"<<endl;
                cout<<"¿Desea jugar otra ronda? Presione (1) para si (2) para no: ";
                cin>>otra_ronda;
            }
            numero_de_rondas+=1;
        }while(otra_ronda!=2);
        //Se calcula el ganador o ganadores
        int numero_ganadores=0;
        string nombre_ganadores[numero_de_jugadores];
        int puntajeganador=jugadores[0].puntaje;
        for(int i=0;i<numero_de_jugadores;i++){
            if(jugadores[i].puntaje<puntajeganador){
                puntajeganador=jugadores[i].puntaje;
            }
        }
        for(int i=0;i<numero_de_jugadores;i++){
            if(jugadores[i].puntaje==puntajeganador){
                nombre_ganadores[numero_ganadores]=jugadores[i].nombre;
                numero_ganadores+=1;
            }
        }
        if(numero_ganadores==1){ //Se muestra al ganador y se regresa al menu principal
            cout<<"El ganador definitvo de la partida despues de "<<numero_de_rondas<<" rondas fue "<<nombre_ganadores[0]<<" con un puntaje de "<<puntajeganador<<endl;
            cout<<"Regresando al menu principal"<<endl<<endl;
        }else{//Se muestra el empate entre los diferentes jugadores en caso tal de que exista
            cout<<"Ha habido un empate definitivo en los puntajes globales despues de "<<numero_de_rondas<< " rondas entre los jugadores ";
            for(int i=0;i<numero_de_jugadores;i++){
                cout<<", "<<nombre_ganadores[i];
            }
            cout<<" con un puntaje de "<<puntajeganador<<endl;
            cout<<"Regresando al menu principal"<<endl<<endl;
        }
    }else if(iniciar==2){ //Segunda opcion del menu y finaliza el programa
        cout<<"Gracias por jugar vuelva pronto!"<<endl;
    }
}
return 0;
}


/*Funcion mezclar cartas
Entrada: arreglo con cartas, cantidad de cartas en el arreglo
*/
void mezclar_cartas(string lista[],int numero_cartas){
    srand((unsigned) time(NULL));
    for(int i=0;i<numero_cartas;i++){
        int j= (numero_cartas + (rand() % (numero_cartas+1)))%numero_cartas;//Se crea un numero alatorio y se obtiene su modulo dependiendo del numero de cartas
        //Se intercambian las cartas entre el la pocision resultado del modulo y la pocision actual del ciclo
        string temp= lista[i];
        lista[i]=lista[j];
        lista[j]=temp;
        
    }
}

/*
Funcion Calcular Puntaje
Entrada: matriz con las cartas de cada jugador, arreglo de la estructura jugador, numero del turno del jugador
Salida: puntaje de la ronda
*/

int calcular_puntaje(string baraja_jugadores[][54],jugador jugadores[],int jugador){
    //Se inicializa el puntaje actual a calcular
    int puntaje_actual=0;
    //Se recorre la baraja del jugador
    for(int i=0;i<jugadores[jugador].numero_cartas;i++){
        string carta_actual=baraja_jugadores[jugador][i];
        if((carta_actual[1]=='A')||(carta_actual[1]=='D')||(carta_actual[1]=='R')||(carta_actual[1]=='V')){
            if((carta_actual[0]=='0')||(carta_actual[0]=='1')||(carta_actual[0]=='2')||(carta_actual[0]=='3')||(carta_actual[0]=='4')||(carta_actual[0]=='5')||(carta_actual[0]=='6')||(carta_actual[0]=='7')||(carta_actual[0]=='8')||(carta_actual[0]=='9')){
                //Si es una carta de numero se añade el numero de la carta
                char numero_char=carta_actual[0];
                int numero_int=numero_char-'0';
                puntaje_actual+=numero_int;
            }else if((carta_actual[0]=='B')||(carta_actual[0]=='R')||(carta_actual[0]=='S')){
                //Si es de +2, reversa o bloquear se añade +20
                puntaje_actual+=20;
            }
        }else if((carta_actual[1]=='S')||(carta_actual[1]=='C')){
            //Si es +4 o cambio de color se añade +50
            puntaje_actual+=50;
        }
    }

    //Se suma el puntaje de la ronda al puntaje global del jugador
    jugadores[jugador].puntaje +=puntaje_actual;
    //Se retorna el puntaje de la ronda de ese jugador
    return puntaje_actual;
}




/*Funcion de reversa
Entrada: arreglo de los turnos de los jugadores, turno_actual, cantidad de jugadores en la ronda */
void reversa(int turnos_jugadores[], int posicionActual, int cantidad_jugadores){
  
    if (cantidad_jugadores == 2){//Si son dos jugadores intercambia ambos
        int temp = turnos_jugadores [0];
        turnos_jugadores [0] = turnos_jugadores [1];
        turnos_jugadores [1] = temp;
    }else if (cantidad_jugadores == 3){//Si son tres jugadores mantiene uno fijo e intercambia dos volteando el orden
      if (posicionActual == 0){
        int temp = turnos_jugadores [1];
        turnos_jugadores [1] = turnos_jugadores [2];
        turnos_jugadores [2] = temp;
      } else if (posicionActual == 1){
        int temp = turnos_jugadores [0];
        turnos_jugadores [0] = turnos_jugadores [2];
        turnos_jugadores [2] = temp;
      } else {
        int temp = turnos_jugadores [0];
        turnos_jugadores [0] = turnos_jugadores [1];
        turnos_jugadores [1] = temp;
      }
    }else{//Si son tres jugadores se mantiene dos fijo y se intercambian dos para asi lograr la reversa
        if (posicionActual == 0){
            int temp = turnos_jugadores [1];
            turnos_jugadores [1] = turnos_jugadores [3];
            turnos_jugadores [3] = temp;
        } else if (posicionActual == 1){
            int temp = turnos_jugadores [0];
            turnos_jugadores [0] = turnos_jugadores [2];
            turnos_jugadores [2] = temp;
        } else if (posicionActual == 2){
            int temp = turnos_jugadores [1];
            turnos_jugadores [1] = turnos_jugadores [3];
            turnos_jugadores [3] = temp;
            }else {
        int temp = turnos_jugadores [0];
            turnos_jugadores [0] = turnos_jugadores [2];
            turnos_jugadores [2] = temp;
        }
    }          
}