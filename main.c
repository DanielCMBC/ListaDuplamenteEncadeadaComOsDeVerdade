#include "ldec.h"

int main(){
    inserir_No_Inicio(24);
    inserir_final(26);
    inserir_final(39);
    inserir_No_Inicio(12);
    mostrar();

    deletar_Elemento_porTecla(24);
    mostrar();

    deletar_Elemento_porTecla(26);
    mostrar();

    deletar_Elemento_porTecla(39);
    mostrar();

    deletar_Elemento_porTecla(12);
    mostrar();
}