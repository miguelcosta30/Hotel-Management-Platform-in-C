#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DIAS_DESCONTO 7
/*Varaveis Globais*/
struct edificio *HeadEdificios;                                         //Cabeça da lista de edificios
struct historico *HeadHistorico;                                        //Cobeça da lista do historico
PORTOFLATS relacoes;                                                    //Estrutura global da PortoFlats(Politicas,Regras,etc)
RELATORIOS *relatorio;                                                  //Estrutura global para a geraçao de relatorios
int num_relatorios = 0;                                                 //Numero de relatorios

int main_projeto(int argc, char *argv)
{

    /*Inicia as estruturas*/
    init();
    reset_file("faturacao.txt");
    reset_file("ocupacao.txt");
    reset_file("historico.txt");

    /*Ler dados de ficheiros*/
    /*Requesito 4 e 5*/
    read_edificios_from_file("edificios.txt");
    read_estudios_from_file("estudios.txt");
    read_eventos_from_file("eventos.txt");
    read_regras_from_file("regras.txt");
    read_politicas_from_file("politicas.txt");
    read_estudio_politicas_from_file("estudio_politicas.txt");

    /*Requesito 2 e 3*/
    /*Inserções Manuais*/

    /*Inserção de Regras*/
    //insert_regra(10,"Frase",1);

    /*Inserção de Politica*/
    /*
        int arr[]={1,2,3};
        insert_politica("p4","airbnd",arr,sizeof(arr)/sizeof(arr[0]),1);
    */

    /*Inserção de Politica*/
    /*
        double arr[]={0.2,-0.3,0.1};
        insert_politica_estudio(4,"p1",arr,sizeof(arr)/sizeof(arr[0]),1);
    */

    /* Inserção de Edificios*/
    //insert_edificio(&HeadEdificios,HeadEdificios,5,"Centro de Baltar",12.02321,-12.00232,"Baltar centro do Mundo",1.5,1);

    /*Inserção de Estudio*/
    //insert_estudio(HeadEdificios, 100, 1, "T3", 100, 1);

    /*Inserção de Evento*/
    /*
        DATA days[]={{1,1,2020,12.30},{30,1,2020,14.00}};
        insert_evento(HeadEdificios, 7, days, 25, 30, "Bruno" , "estadia","AirBnA", 1);
    */

    /*Funções de Remover*/

    //remove_edificio(&HeadEdificios,2);
    //remove_estudio(20);
    //remove_hospede(&HeadHistorico,1);
    //remove_evento(5);
    //remove_regra(3);
    //remove_politica("p2");
    //remove_estudio_politica(2,"p1");

    /*Funções de Alterar*/

    /*alterar_edificio(2,"Edificio nao sei", "Rua nao sei",0.5,-12.32,-8.23);
    alterar_estudio(3,"T4",125);
    alterar_evento(5,"estadia");
    alterar_regra(1,"Vista para o rio");
    int regras[]={1,2,4};
    alterar_politica("p2","AirBnA",sizeof(regras)/sizeof(regras[0]),regras);
    double taxas[]={0.1,0.2,0.3};
    alterar_estudio_politica(2,"p1",3,"p2", sizeof(taxas)/sizeof(taxas[0]),taxas);*/

    /*Funções de print*/
    //printEdificios();
    //printEstudios();
    printEverything();
    //printHistorico();
    //printEventos();
    //printReservas();
    //printRegras();
    //printPoliticas();
    //printTaxas();

    /*Requesito 6*/ /*Ordem de ordenacao: 0->Menor taxa 1->Maior taxa 2->Ordem Estudio(se existir) 3->Ordem edificio(se existir)*/
    ocupacaoEstudio(34, 1, 1, 2020, 7, 1, 2021, 0);
    //ocupacaoEdificio(4, 1, 10, 2020, 7, 1, 2021, 1);
    //ocupacaoParqueEdificios(1, 10, 2020, 7, 1, 2021, 1);

    /*Requesito 7*/ /*Ordem de ordenacao: 0->Faturacao Decrescente 1->Faturacao Crescente 2->Ordem Estudio(se existir) 3->Ordem edificio(se existir)*/
    faturacaoEstudio(34, 1, 11, 2000, 7, 1, 2021, 0);
    //faturacaoEdificio(5, 1, 10, 2020, 7, 1, 2021, 0);
    //faturacaoParqueEdificios(1, 10, 2020, 7, 1, 2021, 0);

    /*Requesito 8*/
    //disponivel()->Função responsavel pela inserçao de eventos de forma a nao causar conflitos(função chamada na insert_evento)

    /*Requesito 9*/

    return 0;
}
/**
 * Função que inicia as estruturas
 */

void init()
{
    HeadEdificios = NULL;
    HeadHistorico = NULL;
    relacoes.num_regras = 0;
    relacoes.num_politicas = 0;
    relacoes.num_relacoes = 0;
    relacoes.regras = NULL;
    relacoes.estudio_politica = NULL;
    relacoes.politicas = NULL;
    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
}

/**
 * Função para alocar espaço para um array de inteiros
 * @param M - Tamanho do array
 * @return array alocado
 */

int *newIntArray(int M)
{
    return (int *)malloc(sizeof(int) * M);
}

/**
 * @param a - array vazio
 * @param string - string com inteiros
 * @return retorna um array de inteiros
 */

int *stringToarray(int *a, char *string)
{
    int i = 0;
    int num;
    char *token;
    token = strtok(string, ";");
    while (token != NULL)
    {
        num = atoi(token);
        a[i] = num;
        i++;
        token = strtok(NULL, ";");
    }
    return a;
}

/**
 * Converte uma string para um vetor doubles
 * @param a vetor vazio
 * @param string string de numeros
 * @return retorna o verto convertido
 */

double *stringToDoublearray(double *a, char *string)
{
    int i = 0;
    double num;
    char *token;
    token = strtok(string, ";");
    while (token != NULL)
    {

        num = atof(token);
        a[i] = num;

        i++;

        token = strtok(NULL, ";");
    }
    return a;
}

/**
 * Função para inserir uma regra
 * @param id_regra id da regra
 * @param regra designação da regra
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_regra(int id_regra, char *regra, int flag)
{
    REGRAS *vetor_regras = relacoes.regras;
    if (vetor_regras == NULL)
    {
        relacoes.num_regras = 1;
        vetor_regras = (REGRAS *)malloc(sizeof(REGRAS));
        vetor_regras[0].id = id_regra;
        vetor_regras[0].regra = (char *)malloc(30 * sizeof(char));
        strcpy(vetor_regras[0].regra, regra);
        relacoes.regras = vetor_regras;

        if (flag == 1)
        {
            insert_regras_to_file("regras.txt", id_regra, regra);
        }
    }
    else
    {
        int i = binarySearch_regras(vetor_regras, 0, relacoes.num_regras - 1, id_regra);
        {
            if (i < 0)
            {
                vetor_regras = (REGRAS *)realloc(vetor_regras, relacoes.num_regras + 1 * 100 * sizeof(REGRAS));
                REGRAS inserted_regra = {id_regra, regra};
                relacoes.num_regras = insert_regra_sorted(vetor_regras, inserted_regra, relacoes.num_regras);
                relacoes.regras = vetor_regras;
                if (flag == 1)
                {
                    insert_regras_to_file("regras.txt", id_regra, regra);
                }
            }
            else
            {
                printf("Regra nao foi adiciona por ja existir uma regra com o ID %d\n", id_regra);
            }
        }
    }
}

/**
 *
 * @param nome_politica nome da politica
 * @param plataforma nome da plataforma
 * @param vregras array de regras
 * @param num_regras numero de regras
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_politica(char *nome_politica, char *plataforma, int *vregras, int num_regras, int flag)
{
    POLITICA *vetor_politicas = relacoes.politicas;

    if (vetor_politicas == NULL)
    {
        relacoes.num_politicas = 1;
        vetor_politicas = (POLITICA *)malloc(sizeof(POLITICA));
        vetor_politicas[0].nome_politica = (char *)malloc(30 * sizeof(char));
        strcpy(vetor_politicas[0].nome_politica, nome_politica);
        vetor_politicas[0].plataforma = (char *)malloc(30 * sizeof(char));
        strcpy(vetor_politicas[0].plataforma, plataforma);
        vetor_politicas[0].num_regras = num_regras;
        vetor_politicas[0].regras = newIntArray(num_regras);

        for (int i = 0; i < num_regras; i++)
        {
            vetor_politicas[0].regras[i] = vregras[i];
        }
        relacoes.politicas = vetor_politicas;
        if (flag == 1)
        {
            insert_politicas_to_file("politicas.txt", nome_politica, plataforma, num_regras, vregras);
        }
        return;
    }
    else
    {
        int i = checkPolitica(vetor_politicas, 0, relacoes.num_politicas - 1, nome_politica);
        {
            if (i < 0)
            {
                vetor_politicas = (POLITICA *)realloc(vetor_politicas, relacoes.num_politicas + 1 * 10 * sizeof(POLITICA));
                POLITICA inserted_politica = {nome_politica, plataforma, num_regras, vregras};
                relacoes.num_politicas = insert_politica_sorted(vetor_politicas, inserted_politica, relacoes.num_politicas);
                relacoes.politicas = vetor_politicas;

                if (flag == 1)
                {
                    insert_politicas_to_file("politicas.txt", nome_politica, plataforma, num_regras, vregras);
                }
            }
            else
            {
                printf("Politica nao foi adiciona por ja existir uma politica com o nome %s\n", nome_politica);
                return;

            }
        }
    }
}

/**
 * Função para adicionar uma relação estudio-politica
 * @param estudio id do estudio
 * @param nome_politica id da politica
 * @param vtaxas array de taxas
 * @param num_taxas numero de taxas
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_politica_estudio(int estudio, char *nome_politica, double *vtaxas, int num_taxas, int flag)
{
    int *array;
    array = find_estudio(estudio);
    if (array[0] == 0 && array[1] == 0)
    {
        printf("Estudio nao existe em nenhum edificio\n");
        return;
    }
    int i = checkPolitica(relacoes.politicas, 0, relacoes.num_politicas, nome_politica);
    if (i < 0)
    {
        printf("Politica nao existe\n");
        return;
    }
    ESTUDIO_POLITICA *vetor_politica_estudio = relacoes.estudio_politica;
    if (vetor_politica_estudio == NULL)
    {
        relacoes.num_relacoes = 1;
        vetor_politica_estudio = (ESTUDIO_POLITICA *)malloc(sizeof(ESTUDIO_POLITICA));
        vetor_politica_estudio[0].id_estudio = estudio;
        vetor_politica_estudio[0].nome_politica = (char *)malloc(30 * sizeof(char));
        strcpy(vetor_politica_estudio[0].nome_politica, nome_politica);
        vetor_politica_estudio[0].num_taxas = num_taxas;
        vetor_politica_estudio[0].taxas = (double *)malloc(num_taxas * sizeof(double));

        for (i = 0; i < num_taxas; i++)
        {
            vetor_politica_estudio[0].taxas[i] = vtaxas[i];
        }
        relacoes.estudio_politica = vetor_politica_estudio;
        if (flag == 1)
        {

            insert_estudio_politicas_to_file("estudio_politicas.txt", estudio, nome_politica, num_taxas, vtaxas);
        }
        return;
    }
    else
    {
        int j = checkEstudioPolitica(vetor_politica_estudio, estudio, nome_politica);
        if (j < 0)
        {
            vetor_politica_estudio = (ESTUDIO_POLITICA *)realloc(vetor_politica_estudio, relacoes.num_relacoes + 1 * 100 * sizeof(ESTUDIO_POLITICA));
            ESTUDIO_POLITICA inserted_estudio_politica = {estudio, nome_politica, num_taxas, vtaxas};
            relacoes.num_relacoes = insert_estudio_politica_sorted(vetor_politica_estudio, inserted_estudio_politica, relacoes.num_relacoes);
            relacoes.estudio_politica = vetor_politica_estudio;

            if (flag == 1)
            {
                insert_estudio_politicas_to_file("estudio_politicas.txt", estudio, nome_politica, num_taxas, vtaxas);
            }
        }
        else
        {
            printf("Ja a configuracao do estudio %d com a politica %s\n", estudio, nome_politica);
        }

        return;
    }
}

/**
 * Função que adiciona um edificio à lista ligada de edificios
 * @param head cabeça da lista ligada
 * @param no no para percorrer
 * @param id id do edificio
 * @param nome_edificio nome do edificio
 * @param latitude latitude
 * @param longitude longitude
 * @param morada morada
 * @param precom2 preço por m2
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_edificio(struct edificio **head, struct edificio *no, int id, char *nome_edificio, double latitude, double longitude, char *morada, double precom2, int flag)
{

    struct edificio *node = no;
    if (node == NULL) //Se a cabeça for NULL significa que a lista está vazia
    {
        struct edificio *new_node = (struct edificio *)malloc(sizeof(struct edificio));
        new_node->id_edificio = id;
        new_node->num_estudios = 0;
        new_node->latitude = latitude;
        new_node->longitude = longitude;
        new_node->preco_m2 = precom2;
        new_node->nome = malloc(30 * sizeof(char));
        strcpy(new_node->nome, nome_edificio);
        new_node->morada = malloc(30 * sizeof(char));
        strcpy(new_node->morada, morada);
        new_node->vector_estudio = NULL;

        if (flag == 1)
        {
            insert_edificios_to_file("edificios.txt", id, nome_edificio, latitude, longitude, morada, precom2);
        }

        new_node->next = *head;
        *head = new_node;
    }
    else //Se nao tiver vazia
    {

        while (node != NULL)
        {

            if (node->id_edificio == id)
            {
                printf("Edificio nao foi adicionado pois ja existe um edificio com o ID %d\n", id);
                return;
            }
            node = node->next;
        }

        node = no;
        struct edificio *new_node = (struct edificio *)malloc(sizeof(struct edificio));
        new_node->id_edificio = id;
        new_node->num_estudios = 0;
        new_node->latitude = latitude;
        new_node->longitude = longitude;
        new_node->preco_m2 = precom2;
        new_node->nome = malloc(30 * sizeof(char));
        strcpy(new_node->nome, nome_edificio);
        new_node->morada = malloc(30 * sizeof(char));
        strcpy(new_node->morada, morada);
        new_node->vector_estudio = NULL;

        if (flag == 1)
        {
            insert_edificios_to_file("edificios.txt", id, nome_edificio, latitude, longitude, morada, precom2);
        }
        if (new_node->id_edificio > node->id_edificio)
        {
            while (node->next != NULL && new_node->id_edificio > node->id_edificio) //Anda pela lista ligada até encontrar o sitio correto do inserção
            {
                node = node->next;
            }
            new_node->next = node->next;
            node->next = new_node;
            return;
        }
        else
        { //Se o id que está a ser introduzido nao for maior que o que ja está na cabeça, entao adiciona se a cabeça
            new_node->next = *head;
            *head = new_node;
            return;
        }
    }
}

/**
 * Função para adicionar um estudio ao array de estudios de um edificio
 * @param no cabeça da lista de edificios
 * @param id_estudio id do estudio
 * @param id_edificio id do edificio onde se encontra o edificio
 * @param tipo desginaçao do estudio
 * @param m2 area do estudio
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_estudio(struct edificio *no, int id_estudio, int id_edificio, char *tipo, int m2, int flag)
{

    int *array;
    array = find_estudio(id_estudio); //Procura se existe algum edificio com aquele ID na estrutura inteira
    if (array[0] != 0 && array[1] != 0)
    {
        printf("Edificio com o ID %d já existe no edificio com o ID %d\n", array[1], array[0]);
        return;
    }
    struct edificio *node = no;
    if (node == NULL)
    {
        printf("Nao existe edificios para os qual pode ser adiciona um estudio\n");
    }
    else
    {
        while (node != NULL)
        {
            if (node->id_edificio == id_edificio)
            {
                if (node->vector_estudio == NULL) //Vetor de estudios nao existe
                {
                    node->num_estudios = 1;
                    ESTUDIO *vetor_estudios = (ESTUDIO *)malloc(1 * sizeof(ESTUDIO));
                    vetor_estudios[0].id_estudio = id_estudio;
                    vetor_estudios[0].area = m2;
                    vetor_estudios[0].tipo = malloc(30 * sizeof(char));
                    strcpy(vetor_estudios[0].tipo, tipo);
                    vetor_estudios[0].num_dias = 0;
                    vetor_estudios[0].num_plat = 0;
                    MASTERAGENDA *master = (MASTERAGENDA *)malloc(1 * sizeof(MASTERAGENDA));
                    BRANCHCALENDER *branch = (BRANCHCALENDER *)malloc(sizeof(BRANCHCALENDER));
                    master->vector_dias = NULL;
                    branch->vector_dias = NULL;
                    vetor_estudios[0].agendaMaster = master;
                    vetor_estudios[0].calender = branch;
                    node->vector_estudio = vetor_estudios;

                    if (flag == 1)
                    {
                        insert_estudios_to_file("estudios.txt", id_estudio, id_edificio, tipo, m2);
                    }
                    return;
                }
                else
                {
                    node->vector_estudio = (ESTUDIO *)realloc(node->vector_estudio, 100 * node->num_estudios * sizeof(DIAS));
                    ESTUDIO *vetor_estudios = node->vector_estudio;
                    ESTUDIO estudio = {id_estudio, tipo, m2, 0, 0, NULL, NULL};
                    node->num_estudios = insert_estudio_sorted(vetor_estudios, estudio, node->num_estudios);
                    int x = binarySearch_estudio(vetor_estudios, 0, node->num_estudios - 1, id_estudio);
                    vetor_estudios[x].id_estudio = id_estudio;
                    vetor_estudios[x].area = m2;
                    vetor_estudios[x].tipo = malloc(30 * sizeof(char));
                    strcpy(vetor_estudios[x].tipo, tipo);
                    vetor_estudios[x].num_dias = 0;
                    vetor_estudios[x].num_plat = 0;
                    MASTERAGENDA *master = (MASTERAGENDA *)malloc(1 * sizeof(MASTERAGENDA));
                    BRANCHCALENDER *branch = (BRANCHCALENDER *)malloc(sizeof(BRANCHCALENDER));
                    master->vector_dias = NULL;
                    branch->vector_dias = NULL;
                    vetor_estudios[x].agendaMaster = master;
                    vetor_estudios[x].calender = branch;
                    node->vector_estudio = vetor_estudios;

                    if (flag == 1)
                    {
                        insert_estudios_to_file("estudios.txt", id_estudio, id_edificio, tipo, m2);
                    }
                    return;
                }
            }
            node = node->next;
        }
    }
    printf("O edificio %d nao existe\n", id_edificio);
}

/**
 * Função que adiciona um evento a um estudio, nesta função está implementada o sistema de "colisoes" entre as agendas dos estudios
 * @param no no da cabeça da lista de edificios
 * @param id_estudio id do estudio onde quero inserir o evento
 * @param days dias do evento(Inicio e fim)
 * @param id_evento id do evento
 * @param id_cliente id do cliente
 * @param nome_cliente nome do cliente
 * @param nome_evento nome do evento
 * @param nome_plataforma nome da plataforma
 * @param flag (1->Escrever no ficheiro|0->Nao escrever no ficheiro)
 */

void insert_evento(struct edificio *no, int id_estudio, DATA *days, int id_evento, int id_cliente, char *nome_cliente, char *nome_evento, char *nome_plataforma, int flag)
{
    if (checkEvento(id_evento) == 1)
    {
        printf("Evento nao foi adicionado.\n");
        return;
    }

    struct edificio *node = no;
    int *array = find_estudio(id_estudio);
    if (array[0] == 0)
    {
        printf("Estudio nao existe no programa\n");
        return;
    }
    while (node->id_edificio != array[0]) //Procura o edificio na lista ligada de edificios
    {
        node = node->next;
    }

    ESTUDIO *current = node->vector_estudio;
    int i = binarySearch_estudio(node->vector_estudio, 0, (node->num_estudios) - 1, id_estudio); //Encontra o estudio no vetor de estudios do node da lista ligada
    MASTERAGENDA *master = current[i].agendaMaster;
    BRANCHCALENDER *branch = current[i].calender;

    if (id_cliente != -1)
    {
        if (disponivel(id_estudio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano) != 0.00)
        {
            printf("O evento %d nao pode ser inserido pois existem outros eventos no intervalo de %d/%d/%d ate %d/%d/%d no estudio %d", id_evento, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano, id_estudio);
            return;
        }
        insert_historico(&HeadHistorico, HeadHistorico, id_cliente, nome_cliente, nome_evento, id_evento, days);

        if (current[i].num_plat == 0)
        {
            current[i].num_plat = 1;
            branch[0].num_dias = 1;
            branch[0].vector_dias = (DIAS *)malloc(branch[0].num_dias * 10 * sizeof(DIAS));
            branch[0].nome_plataforma = malloc(300 * sizeof(char));
            strcpy(branch[0].nome_plataforma, nome_plataforma);
            DIAS *diaY = branch[0].vector_dias;
            DIAS diaYaux = {days[0].dia, days[0].mes, days[0].ano, 0, NULL};
            diaY[0] = diaYaux;
            branch[0].vector_dias = diaY;
            current[i].calender = branch;
        }
        else
        {
            int m = checkPlataforma(branch, 0, current[i].num_plat - 1, nome_plataforma);    //Verifica se ja existe a plataforma no Array de plataformas daquele estudio

            if (m >= 0) //Ja existe a plataforma, atualizamos o array de dias
            {

                branch[m].vector_dias = (DIAS *)realloc(branch[m].vector_dias, branch[m].num_dias * 100 * sizeof(DIAS)); //Array de reservas daquela plataforma
                DIAS *diaX = branch[m].vector_dias;                                               //Declaramos o array dessa plataforma para esse estudio
                DIAS day = {days[0].dia, days[0].mes, days[0].ano, 0, NULL};                      //Estrutura auxilair
                branch[m].num_dias = insert_day_sorted(diaX, day, branch[m].num_dias);            //Insera no array de forma ordenada
                branch[m].vector_dias = diaX;
                current[i].calender = branch;
            }
            else
            {

                branch = (BRANCHCALENDER *)realloc(branch, 10 * sizeof(BRANCHCALENDER));                //Caso nao exista vamos adicionar uma plataforma com um unico dia
                BRANCHCALENDER plataforma = {nome_plataforma, 1, NULL};                                 //Estruta auxiliar plataforma
                current[i].num_plat = insert_plataform_sorted(branch, plataforma, current[i].num_plat); //Insera uma plataforma;
                int k = checkPlataforma(branch, 0, current[i].num_plat - 1, nome_plataforma);
                branch[k].vector_dias = (DIAS *)malloc(branch[0].num_dias * sizeof(DIAS));              //Aloca espaço para um dia (primeiro inserido)
                branch[k].nome_plataforma = malloc(300 * sizeof(char));
                strcpy(branch[k].nome_plataforma, nome_plataforma);
                branch[k].num_dias = 1; //Atualiza numero de dias
                branch[k].vector_dias = (DIAS *)malloc(branch[0].num_dias * sizeof(DIAS));
                DIAS *diaX = branch[k].vector_dias;
                diaX[0].dia = days[0].dia;
                diaX[0].mes = days[0].mes;
                diaX[0].ano = days[0].ano;
                diaX[0].vector_evento = NULL;
                branch[k].vector_dias = diaX;
                current[i].calender = branch;
            }
        }
    }
    if (master->vector_dias == NULL) //Se nao existir array vai criar
         {

        current[i].num_dias = 1; //Adiciona um dia aquele estudio
        master->vector_dias = (DIAS *)malloc(current[i].num_dias * sizeof(DIAS)); //Aloca espaço para um array de Dias
        DIAS *diaX = master->vector_dias;
        diaX[0].num_eventos = 1;
        diaX[0].dia = days[0].dia;
        diaX[0].mes = days[0].mes;
        diaX[0].ano = days[0].ano;
        diaX[0].vector_evento = NULL;

        struct evento *no_head = diaX[0].vector_evento; //Primeiro node da lista

        if (no_head == NULL) //Se a lista ligada de eventos daquele dia estiver vazia;
        {
            struct evento *node_evento = (EVENTO *)malloc(sizeof(EVENTO)); //Criaçao de um novo node

            /*Informações do node evento*/
            node_evento->id_cliente = id_cliente;
            node_evento->id_evento = id_evento;
            node_evento->nome_cliente = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_cliente, nome_cliente);
            node_evento->nome_plataforma = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_plataforma, nome_plataforma);
            node_evento->nome_evento = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_evento, nome_evento);

            DATA *datas = (DATA *)malloc(2 * sizeof(DATA));
            datas[0].dia = days[0].dia;
            datas[0].mes = days[0].mes;
            datas[0].ano = days[0].ano;
            datas[0].horas_minutos = days[0].horas_minutos;
            datas[1].dia = days[1].dia;
            datas[1].mes = days[1].mes;
            datas[1].ano = days[1].ano;
            datas[1].horas_minutos = days[1].horas_minutos;
            node_evento->datas = datas;

            /*Inserção à cabeça*/
            node_evento->nextEvento = no_head;
            diaX[0].vector_evento = node_evento;
            master->vector_dias = diaX;

            if (flag == 1)
            {
                insert_eventos_to_file("eventos.txt", id_evento, nome_evento, node_evento->datas, id_cliente,nome_cliente, id_estudio, nome_plataforma);
            }
        }
        return;
    }
    else
        {
        int j = checkDay(master->vector_dias, 0, (current[i].num_dias) - 1, days[0]); //BS no array de dias
        if (j >= 0){ //Se o dia ja existir naquele estudio

            DIAS *diaX = master->vector_dias;
            /*Atualiza o numero de eventos daquele dia*/
            diaX[j].num_eventos = (diaX[j].num_eventos) + 1;

            struct evento *current_node = diaX[j].vector_evento; //Cabeça da lista de eventos
            struct evento *node_evento = (EVENTO *)malloc(sizeof(EVENTO)); //Alocar espaço para um novo evento

            /*Coloca informações no novo no evento*/
            node_evento->id_cliente = id_cliente;
            node_evento->id_evento = id_evento;
            node_evento->nome_cliente = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_cliente, nome_cliente);
            node_evento->nome_plataforma = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_plataforma, nome_plataforma);
            node_evento->nome_evento = malloc(300 * sizeof(char));
            strcpy(node_evento->nome_evento, nome_evento);

            DATA *datas = (DATA *)malloc(2 * sizeof(DATA));
            datas[0].dia = days[0].dia;
            datas[0].mes = days[0].mes;
            datas[0].ano = days[0].ano;
            datas[0].horas_minutos = days[0].horas_minutos;
            datas[1].dia = days[1].dia;
            datas[1].mes = days[1].mes;
            datas[1].ano = days[1].ano;
            datas[1].horas_minutos = days[1].horas_minutos;
            node_evento->datas = datas;

            DATA *datas_head = current_node->datas;      //Datas do no cabeça
            DATA *data_novo_evento = node_evento->datas; //Datas do no a ser inserido

            if (data_novo_evento[0].horas_minutos >= datas_head[0].horas_minutos)
            {
                while (current_node->nextEvento != NULL && (current_node->nextEvento->datas->horas_minutos >data_novo_evento[0].horas_minutos)) //Anda pela lista ligada até encontrar o sitio correto do inserção
                {
                    current_node = current_node->nextEvento;
                }
                /*Insere na posição ordenada*/
                node_evento->nextEvento = current_node->nextEvento;
                current_node->nextEvento = node_evento;
                master->vector_dias = diaX;
            }
            else
            { //Faz inserção à cabeça

                /*Atualiza cabeça da lista*/
                node_evento->nextEvento = current_node;
                diaX[j].vector_evento = node_evento;
                master->vector_dias = diaX;
            }

            if (flag == 1)
            {
                insert_eventos_to_file("eventos.txt", id_evento, nome_evento, node_evento->datas, id_cliente,nome_cliente, id_estudio, nome_plataforma);
            }
            return;
        }
        else
        {
            master->vector_dias = (DIAS *)realloc(master->vector_dias,(current[i].num_dias+1*100) * sizeof(DIAS)); //Realocar
            DIAS *diaX = master->vector_dias;
            DIAS dia = {days[0].dia, days[0].mes, days[0].ano, 0, NULL};
            current[i].num_dias = insert_day_sorted(diaX, dia, current[i].num_dias); //Insera no array de forma ordenada
            int x = checkDay(diaX, 0, (current[i].num_dias) - 1, days[0]);
            struct evento *no_head = diaX[x].vector_evento;

            if (no_head == NULL) //Se a lista ligada de eventos daquele dia estiver vazia;
            {
                struct evento *node_evento = (EVENTO *)malloc(sizeof(EVENTO)); //Criaçao de um novo node
                node_evento->id_cliente = id_cliente;
                diaX[x].num_eventos = 1;
                node_evento->id_evento = id_evento;
                node_evento->nome_cliente = malloc(300 * sizeof(char));
                strcpy(node_evento->nome_cliente, nome_cliente);
                node_evento->nome_plataforma = malloc(300 * sizeof(char));
                strcpy(node_evento->nome_plataforma, nome_plataforma);
                node_evento->nome_evento = malloc(300 * sizeof(char));
                strcpy(node_evento->nome_evento, nome_evento);
                node_evento->nextEvento = no_head;
                DATA *datas = (DATA *)malloc(2 * sizeof(DATA));
                datas[0].dia = days[0].dia;
                datas[0].mes = days[0].mes;
                datas[0].ano = days[0].ano;
                datas[0].horas_minutos = days[0].horas_minutos;
                datas[1].dia = days[1].dia;
                datas[1].mes = days[1].mes;
                datas[1].ano = days[1].ano;
                datas[1].horas_minutos = days[1].horas_minutos;
                node_evento->datas = datas;

                diaX[x].vector_evento = node_evento;
                master->vector_dias = diaX;

                if (flag == 1)
                {
                    insert_eventos_to_file("eventos.txt", id_evento, nome_evento, node_evento->datas, id_cliente,nome_cliente, id_estudio, nome_plataforma);
                }
                return;
            }
        }
    }
}

/**
 * BinarySearch no array de dias
 * @param dias Vetor dias
 * @param l low
 * @param r high
 * @param dia dia a ser procurado
 * @return caso existe retorna o index, caso nao exista retorna -1
 */

int checkDay(DIAS *dias, int l, int r, DATA dia)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (dias[mid].ano == dia.ano && dias[mid].mes == dia.mes && dias[mid].dia == dia.dia)
        {
            return mid;
        }

        if (dias[mid].ano > dia.ano || (dias[mid].ano == dia.ano && dias[mid].mes > dia.mes) ||
            (dias[mid].ano == dia.ano && dias[mid].mes == dia.mes && dias[mid].dia > dia.dia))
        {
            return checkDay(dias, l, mid - 1, dia);
        }

        return checkDay(dias, mid + 1, r, dia);
    }
    return -1;
}

/**
 * BinarySearh no vetor dias
 * @param vector_estudio vetor de estudios
 * @param l low
 * @param r high
 * @param id_estudio id do estudio a ser procurado
 * @return caso existe retorna o index, caso nao exista retorna -1
 */

int binarySearch_estudio(ESTUDIO *vector_estudio, int l, int r, int id_estudio)
{

    if (r >= l)
    {

        int mid = l + (r - l) / 2;

        if (vector_estudio[mid].id_estudio == id_estudio)
        {

            return mid;
        }

        if (vector_estudio[mid].id_estudio > id_estudio)
        {
            return binarySearch_estudio(vector_estudio, l, mid - 1, id_estudio);
        }

        return binarySearch_estudio(vector_estudio, mid + 1, r, id_estudio);
    }

    return -1;
}

/**
 * BinarySearch no vetor regras
 * @param vetor_regras vetor regras
 * @param l low
 * @param r high
 * @param id_regra id da regra a procurar
 * @return caso existe retorna o index, caso nao exista retorna -1
 */

int binarySearch_regras(REGRAS *vetor_regras, int l, int r, int id_regra)
{

    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (vetor_regras[mid].id == id_regra)
        {
            return mid;
        }

        if (vetor_regras[mid].id > id_regra)
        {
            return binarySearch_regras(vetor_regras, 0, mid - 1, id_regra);
        }
        return binarySearch_regras(vetor_regras, mid + 1, r, id_regra);
    }
    return -1;
}

/**
 * BinarySearch no BranchCalander do vetor Estudio
 * @param calendario Recebe o branchcalender do estudio
 * @param l low
 * @param r high
 * @param nome_plataforma nome da plataforma a ser procurada
 * @return caso existe retorna o index, caso nao exista retorna -1
 */

int checkPlataforma(BRANCHCALENDER *calendario, int l, int r, char *nome_plataforma)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (strcmp(calendario[mid].nome_plataforma, nome_plataforma) == 0)
        {
            return mid;
        }
        if (strcmp(calendario[mid].nome_plataforma, nome_plataforma) > 0)
        {
            return checkPlataforma(calendario, l, mid - 1, nome_plataforma);
        }
        return checkPlataforma(calendario, mid + 1, r, nome_plataforma);
    }
    return -1;
}

/**
 * BinarySearch no vetor politicas
 * @param vetor_politica array de politicas
 * @param l low
 * @param r high
 * @param nome_polica nome da politica a ser procurada
 * @return caso exista retorna o index, caso nao exista retorna -1
 */

int checkPolitica(POLITICA *vetor_politica, int l, int r, char *nome_polica)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (strcmp(vetor_politica[mid].nome_politica, nome_polica) == 0)
        {
            return mid;
        }
        if (strcmp(vetor_politica[mid].nome_politica, nome_polica) > 0)
        {
            return checkPolitica(vetor_politica, l, mid - 1, nome_polica);
        }
        return checkPolitica(vetor_politica, mid + 1, r, nome_polica);
    }
    return -1;
}

/**
 * Pesquisa Sequencial no vetor de relações estudio-politica
 * @param vetor_politica_estudio  vetor das relações
 * @param id_estudio id do estudio
 * @param politica nome da politica
 * @return  caso exista retorna o index, caso nao exista retorna -1
 */

int checkEstudioPolitica(ESTUDIO_POLITICA *vetor_politica_estudio, int id_estudio, char *politica)
{

    for (int i = 0; i < relacoes.num_relacoes; i++)
    {
        if (vetor_politica_estudio[i].id_estudio == id_estudio && strcmp(vetor_politica_estudio[i].nome_politica, politica) == 0)
        {
            return 1;
        }
    }
    return -1;
}

/**
 * Verifica se um dado evento ja existe.
 * @param id_evento id do evento
 * @return 1->encontrou|0->nao encontrou
 */

int checkEvento(int id_evento)
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        ESTUDIO *current = node->vector_estudio;
        for (int i = 0; i < node->num_estudios; i++)
        {
            MASTERAGENDA *master = current[i].agendaMaster;
            DIAS *current_dias = master->vector_dias;
            for (int j = 0; j < current[i].num_dias; j++)
            {
                struct evento *eventos = current_dias[j].vector_evento;
                while (eventos != NULL)
                {
                    if (eventos->id_evento == id_evento)
                    {
                        printf("Evento com o ID %d existe no estudio %d no edificio %d\n", eventos->id_evento, current[i].id_estudio, node->id_edificio);
                        return 1;
                    }
                    eventos = eventos->nextEvento;
                }
            }
        }
        node = node->next;
    }
    return 0;
}

/**
 * Inserção ordenada de dias
 * @param dias vetor_dias
 * @param dia dia a ser inserido
 * @param n tamanho do array
 * @return retorna tamanho+1
 */

int insert_day_sorted(DIAS *dias, DIAS dia, int n)
{

    int i;
    for (i = n - 1; (i >= 0 && (date_cmp(dias[i], dia) ==1));i--)
    {
        dias[i + 1] = dias[i];
    }
    dias[i + 1] = dia;
    return n + 1;
}

/**
 * Inserçao ordenada de plataformas
 * @param plataformas branchcalender de um estudio
 * @param plataforma nome da plataforma
 * @param n tamanho do array
 * @return retorna tamanho +1
 */

int insert_plataform_sorted(BRANCHCALENDER *plataformas, BRANCHCALENDER plataforma, int n)
{
    int i;
    for (i = n - 1; (i >= 0 && (strcmp(plataformas[i].nome_plataforma, plataforma.nome_plataforma) > 0)); i--)
    {
        plataformas[i + 1] = plataformas[i];
    }
    plataformas[i + 1] = plataforma;
    return n + 1;
}

/**
 * INserçao ordenada de politica
 * @param vetor_politica vetor politica
 * @param politica politica a ser inserida
 * @param n tamanho do array
 * @return retorna tamanho +1
 */

int insert_politica_sorted(POLITICA *vetor_politica, POLITICA politica, int n)
{

    int i;
    for (i = n - 1; (i >= 0 && (strcmp(vetor_politica[i].nome_politica, politica.nome_politica) > 0)); i--)
    {
        vetor_politica[i + 1] = vetor_politica[i];
    }
    vetor_politica[i + 1] = politica;
    return n + 1;
}

/**
 * Inserçao ordenada de estudio
 * @param vetor_estudios vetor estudio
 * @param estudio estudio a ser inserido
 * @param n tamanho do vetor
 * @return retorna tamanho+1
 */

int insert_estudio_sorted(ESTUDIO *vetor_estudios, ESTUDIO estudio, int n)
{
    int i;
    for (i = n - 1; (i >= 0 && vetor_estudios[i].id_estudio >
                               estudio.id_estudio);
         i--)
    {
        vetor_estudios[i + 1] = vetor_estudios[i];
    }
    vetor_estudios[i + 1] = estudio;
    return n + 1;
}

/**
 * Inserçao ordenada de regra
 * @param vetor_regra vetor regras
 * @param regra regra a ser inserida
 * @param n tamanho do vetor
 * @return retorna tamanho + 1
 */

int insert_regra_sorted(REGRAS *vetor_regra, REGRAS regra, int n)
{
    int i;
    for (i = n - 1; (i >= 0 && vetor_regra[i].id >regra.id);i--)
    {
        vetor_regra[i + 1] = vetor_regra[i];
    }
    vetor_regra[i + 1] = regra;
    return n + 1;
}

/**
 * Inserçao ordenada de uma relação estudio-politica
 * @param vetor_estudiopolitica vetor estudio politica
 * @param estudio_politica relação a ser inserida
 * @param n tamanho do array
 * @return retorna tamanho + 1
 */

int insert_estudio_politica_sorted(ESTUDIO_POLITICA *vetor_estudiopolitica, ESTUDIO_POLITICA estudio_politica, int n)
{
    int i;
    for (i = n - 1; (i >= 0 && vetor_estudiopolitica[i].id_estudio >= estudio_politica.id_estudio); i--)
    {
        vetor_estudiopolitica[i + 1] = vetor_estudiopolitica[i];
    }
    vetor_estudiopolitica[i + 1] = estudio_politica;
    return n + 1;
}

/**
 * Imprime os edificios
 */

void printEdificios()
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        printf("Edificio %d | Nome: %s \nMorada: %s | Lat:%0.2f|Lon:%0.2f\nPreco m2: %0.2f | Estudios: %d\n", node->id_edificio,
               node->nome, node->morada, node->latitude, node->longitude, node->preco_m2, node->num_estudios); //Imprime id e counter
        printf("-------------------------------------\n");
        node = node->next;
    }
}

/**
 * Imprime os edificios e os seus respetivos estudios
 */

void printEstudios()
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        printf("Edificio %d | Nome: %s | Estudios: %d\n", node->id_edificio,
               node->nome, node->num_estudios);
        ESTUDIO *current = node->vector_estudio;

        for (int i = 0; i < node->num_estudios; i++)
        {
            printf("Estudio[%d] | Tipo: %s | Area: %d\n", current[i].id_estudio, current[i].tipo, current[i].area);
        }
        printf("-------------------------------------\n");
        node = node->next;
    }
}

/**
 * Procura o estudio na lista de edificios
 * @param id_estudio id do edificio
 * @return retorna um array, array[0]->edificio|array[1]->estudio (retorna 0 em ambos caso n exista)
 */

int *find_estudio(int id_estudio)
{
    int i;
    int *array = newIntArray(5);
    struct edificio *node = HeadEdificios;

    while (node != NULL)
    {
        ESTUDIO *current = node->vector_estudio;
        i = binarySearch_estudio(node->vector_estudio, 0, (node->num_estudios) - 1, id_estudio);
        if (i != -1)
        {
            array[0] = node->id_edificio;
            array[1] = current[i].id_estudio;
            return array;
        }
        node = node->next;
    }
    array[0] = 0;
    array[1] = 0;
    return array;
}

/**
 * Funcao que lê os edificios  do ficheiro
 * @param filename nome do ficheiro
 */

void read_edificios_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int id_edificio = 0;
        char *nome = malloc(300 * sizeof(char)), *morada = malloc(300 * sizeof(char));
        double precom2 = 0.0, latitude = 0.0, longitude = 0.0;
        string = strtok(line, ",");
        while (string != NULL)
        {
            if (count == 0)
            {
                id_edificio = atoi(string);
            }
            if (count == 1)
            {
                strcpy(nome, string);
            }
            if (count == 2)
            {
                latitude = atof(string);
            }
            if (count == 3)
            {
                longitude = atof(string);
            }
            if (count == 4)
            {
                strcpy(morada, string);
            }
            if (count == 5)
            {
                precom2 = atof(string);
            }
            count++;
            string = strtok(NULL, ",");
        }
        insert_edificio(&HeadEdificios, HeadEdificios, id_edificio, nome, latitude, longitude, morada, precom2, 0);
        count = 0;
    }
    fclose(file);
}

/**
 * Funcao que lê os estudios do ficheiro
 * @param filename nome do ficheiro
 */

void read_estudios_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int id_estudio = 0, id_edificio = 0, m2 = 0;
        char *tipo = malloc(300 * sizeof(char));
        string = strtok(line, ",");
        while (string != NULL)
        {
            if (count == 0)
            {
                id_estudio = atoi(string);
            }
            if (count == 1)
            {
                id_edificio = atoi(string);
            }
            if (count == 2)
            {
                strcpy(tipo, string);
            }
            if (count == 3)
            {
                m2 = atoi(string);
            }
            count++;
            string = strtok(NULL, ",");
        }
        insert_estudio(HeadEdificios, id_estudio, id_edificio, tipo, m2, 0);
        count = 0;
    }
    fclose(file);
}

/**
 * Funcao que lê as relações eventos do ficheiro
 * @param filename nome do ficheiro
 */

void read_eventos_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int id_estudio = 0, id_cliente = 0, id_evento = 0, dia1 = 0, mes1 = 0, ano1 = 0, dia2 = 0, mes2 = 0, ano2 = 0;
        double hora_minuto1 = 0, hora_minuto2 = 0;
        char *nome_client = malloc(300 * sizeof(char)), *nome_evento = malloc(300 * sizeof(char)), *nome_plataforma = malloc(300 * sizeof(char));
        string = strtok(line, ",");
        while (string != NULL)
        {
            if (count == 0)
            {
                id_evento = atoi(string);
            }
            if (count == 1)
            {
                strcpy(nome_evento, string);
            }
            if (count == 2)
            {
                sscanf(string, "%d%*[^0123456789]%d%*[^0123456789]%d", &ano1, &mes1, &dia1);
            }
            if (count == 3)
            {
                hora_minuto1 = atof(string);
            }
            if (count == 4)
            {
                sscanf(string, "%d%*[^0123456789]%d%*[^0123456789]%d", &ano2, &mes2, &dia2);
            }
            if (count == 5)
            {
                hora_minuto2 = atof(string);
            }
            if (count == 6)
            {
                id_cliente = atoi(string);
            }
            if (count == 7)
            {
                strcpy(nome_client, string);
            }
            if (count == 8)
            {
                id_estudio = atoi(string);
            }
            if (count == 9)
            {
                strcpy(nome_plataforma, string);
            }
            count++;
            string = strtok(NULL, ",");
        }

        DATA *days = (DATA *)malloc(2 * sizeof(DATA));
        days[0].dia = dia1;
        days[0].mes = mes1;
        days[0].ano = ano1;
        days[0].horas_minutos = hora_minuto1;
        days[1].dia = dia2;
        days[1].mes = mes2;
        days[1].ano = ano2;
        days[1].horas_minutos = hora_minuto2;
        insert_evento(HeadEdificios, id_estudio, days, id_evento, id_cliente, nome_client, nome_evento, nome_plataforma,0);
        count = 0;
    }
    fclose(file);
}

/**
 * Funcao que lê regras do ficheiro
 * @param filename nome do ficheiro
 */

void read_regras_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int id_regra = 0;
        char *regra = malloc(300 * sizeof(char));
        string = strtok(line, ",");
        while (string != NULL)
        {
            if (count == 0)
            {
                id_regra = atoi(string);
            }
            if (count == 1)
            {
                strcpy(regra, string);
            }
            count++;
            string = strtok(NULL, ",");
        }
        insert_regra(id_regra, regra, 0);
        count = 0;
    }
    fclose(file);
}

/**
 * Funcao que lê as relações politicas do ficheiro
 * @param filename nome do ficheiro
 */

void read_politicas_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string, *string_save;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int count_regras = 0, *array_regras = newIntArray(0);
        char *politica = malloc(300 * sizeof(char)), *plataforma = malloc(300 * sizeof(char));
        string = strtok_r(line, ",", &string_save);
        while (string != NULL)
        {
            if (count == 0)
            {
                strcpy(politica, string);
            }
            if (count == 1)
            {
                strcpy(plataforma, string);
            }
            if (count == 2)
            {
                char *string_aux = malloc(30 * sizeof(char));
                strcpy(string_aux, string); //Guarda o array em formato string
                char *string2, *string2_save;
                string2 = strtok_r(string, ";", &string2_save);
                while (string2 != NULL)
                {
                    count_regras++;
                    string2 = strtok_r(NULL, ";", &string2_save);
                }
                array_regras = newIntArray(count_regras);
                array_regras = stringToarray(array_regras, string_aux);
            }
            count++;
            string = strtok_r(NULL, ",", &string_save);
        }

        insert_politica(politica, plataforma, array_regras, count_regras, 0);
        count = 0;
    }
    printf("\n");
    fclose(file);
}

/**
 * Funcao que lê as relações politica-estudio do ficheiro
 * @param filename nome do ficheiro
 */

void read_estudio_politicas_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *string, *string_save;
    int count = 0;
    while (fgets(line, sizeof(line), file))
    {
        size_t last_idx = strlen(line) - 1;
        if (line[last_idx] == '\n')
        {
            line[last_idx] = '\0';
        }
        int count_taxas = 0, id_estudio = 0;
        double *array_taxas = (double *)malloc(sizeof(double));
        char *politica = malloc(300 * sizeof(char));
        string = strtok_r(line, ",", &string_save);
        while (string != NULL)
        {
            if (count == 0)
            {
                id_estudio = atoi(string);
            }
            if (count == 1)
            {
                strcpy(politica, string);
            }
            if (count == 2)
            {
                char *string_aux = malloc(30 * sizeof(char));
                strcpy(string_aux, string); //Guarda o array em formato string
                char *string2, *string2_save;
                string2 = strtok_r(string, ";", &string2_save);

                while (string2 != NULL)
                {
                    count_taxas++;
                    string2 = strtok_r(NULL, ";", &string2_save);
                }
                array_taxas = (double *)malloc(count_taxas * sizeof(double));
                array_taxas = stringToDoublearray(array_taxas, string_aux);
            }
            count++;
            string = strtok_r(NULL, ",", &string_save);
        }
        insert_politica_estudio(id_estudio, politica, array_taxas, count_taxas, 0);
        count = 0;
    }
    fclose(file);
}

/**
 * Funcao para inserir edificios no ficheiro
 * @param filename nome do ficheiro
 * @param id id do edificio
 * @param nome_edificio nome do edificio
 * @param latitude latitude
 * @param longitude longitude
 * @param morada morada
 * @param precom2 preco por metro quadrado do edificio
 */

void insert_edificios_to_file(char *filename, int id, char *nome_edificio, double latitude, double longitude, char *morada, double precom2)
{

    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,%s,%0.2f,%0.2f,%s,%0.2f\n", id, nome_edificio, latitude, longitude, morada, precom2);
    fclose(file);
}

/**
 * Funcao para inserir estudio no ficheiro
 * @param filename nome do ficheiro
 * @param id_estudio id do estudio
 * @param id_edificio id do edificio onde o estudio se encontra
 * @param tipo designaçao do estudio
 * @param m2 area do estudio
 */

void insert_estudios_to_file(char *filename, int id_estudio, int id_edificio, char *tipo, int m2)
{
    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,%d,%s,%d\n", id_estudio, id_edificio, tipo, m2);
    fclose(file);
}

/**
 * Inserir uma regra para o ficheiro
 * @param filename nome do ficheiro
 * @param id_regra id da regra
 * @param nome desginação da regra
 */

void insert_regras_to_file(char *filename, int id_regra, char *nome)
{
    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,%s\n", id_regra, nome);
    fclose(file);
}

/**
 * Função para inserir politicas
 * @param filename nome do ficheiro
 * @param nome nome da politica
 * @param nome_plataforma nome da plataforma
 * @param num_regras numero de regras
 * @param regras array de regras
 */

void insert_politicas_to_file(char *filename, char *nome, char *nome_plataforma, int num_regras, int *regras)
{
    FILE *file = fopen(filename, "a");
    fprintf(file, "%s,%s,", nome, nome_plataforma);
    for (int i = 0; i < num_regras; i++)
    {
        if (i == num_regras - 1)
        {
            fprintf(file, "%d\n", regras[i]);
        }
        else
        {
            fprintf(file, "%d;", regras[i]);
        }
    }
    fclose(file);
}

/**
 * Funçao para inserir taxas no ficheiro
 * @param filename nome do ficheiro
 * @param id_estudio id do estudio
 * @param nome_politica nome da politica
 * @param num_taxas numero de taxas
 * @param taxas array de taxas
 */

void insert_estudio_politicas_to_file(char *filename, int id_estudio, char *nome_politica, int num_taxas, double *taxas)
{
    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,%s,", id_estudio, nome_politica);
    for (int i = 0; i < num_taxas; i++)
    {
        if (i == num_taxas - 1)
        {
            fprintf(file, "%0.2f\n", taxas[i]);
        }
        else
        {
            fprintf(file, "%0.2f;", taxas[i]);
        }
    }
    fclose(file);
}

 /**
  * Função para inserir eventos no ficheiro
  * @param filename nome do ficheiro
  * @param id_evento id evento
  * @param nome nome evento
  * @param day dias do evento (inicio e fim)
  * @param id_cliente id do cliente
  * @param nome_cliente nome do cliente
  * @param estudio_id id do estudio
  * @param plataforma plataforma do evento
  */

void insert_eventos_to_file(char *filename, int id_evento, char *nome, DATA *day, int id_cliente, char *nome_cliente,
                            int estudio_id, char *plataforma)
{
    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,%s,%d-%d-%d,%0.2f,%d-%d-%d,%0.2f,%d,%s,%d,%s\n", id_evento, nome, day[0].ano, day[0].mes,
            day[0].dia, day[0].horas_minutos, day[1].ano, day[1].mes, day[1].dia, day[1].horas_minutos, id_cliente,
            nome_cliente, estudio_id, plataforma);
    fclose(file);
}

/**
 *Print das regras
 */

void printRegras()
{
    printf("Regras:\n");
    REGRAS *vetor_regras = relacoes.regras;
    for (int i = 0; i < relacoes.num_regras; i++)
    {
        printf("%d-%s\n", vetor_regras[i].id, vetor_regras[i].regra);
    }
}

/**
 * Print das politicas
 */

void printPoliticas()
{
    printf("Politicas:\n");
    POLITICA *vetor_politicas = relacoes.politicas;
    for (int i = 0; i < relacoes.num_politicas; i++)
    {
        printf("Politica: %s | Plataforma: %s | Regras: ", vetor_politicas[i].nome_politica, vetor_politicas[i].plataforma);
        for (int j = 0; j < vetor_politicas[i].num_regras; j++)
        {
            printf("%d ", vetor_politicas[i].regras[j]);
        }
        printf("\n");
    }
}

/**
 * Print das taxas
 */

void printTaxas()
{
    printf("Taxas:\n");
    ESTUDIO_POLITICA *vetor_estudio_politicas = relacoes.estudio_politica;
    for (int i = 0; i < relacoes.num_relacoes; i++)
    {
        printf("Estudio: %d | Politica: %s | Taxas: ", vetor_estudio_politicas[i].id_estudio, vetor_estudio_politicas[i].nome_politica);
        for (int j = 0; j < vetor_estudio_politicas[i].num_taxas; j++)
        {
            printf("%0.2f ", vetor_estudio_politicas[i].taxas[j]);
        }
        printf("\n");
    }
}

/**
 * Função que imprime tudo
 */

void printEverything()
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        printf("Edificio %d:\nNumero de estudios: %d\n", node->id_edificio,node->num_estudios); //Imprime id e counter
        ESTUDIO *current = node->vector_estudio;

        for (int i = 0; i < node->num_estudios; i++)
        {
            printf("Estudio[%d] | Tipo: %s | Area: %d \n", current[i].id_estudio, current[i].tipo, current[i].area);
            MASTERAGENDA *master = current[i].agendaMaster;
            DIAS *current_dias = master->vector_dias;

            if (current_dias == NULL)
            {
                printf("   Este estudio nao possui eventos\n");
            }
            else
            {
                for (int j = 0; j < current[i].num_dias; j++)
                {
                    printf("   Dia=%d,Mes=%d,Ano=%d\n\n", current_dias[j].dia, current_dias[j].mes,current_dias[j].ano);
                    struct evento *eventos = current_dias[j].vector_evento;
                    while (eventos != NULL)
                    {
                        DATA *dias = eventos->datas;
                        if (eventos->id_cliente != -1)
                        {
                            printf("      ID Evento: %d | ID Client: %d | Nome cliente: %s | Nome evento: %s | Plataforma: %s\n      Inicio:%d/%d/%d(%0.2f) Fim:%d/%d/%d(%0.2f)\n",
                                   eventos->id_evento, eventos->id_cliente, eventos->nome_cliente, eventos->nome_evento, eventos->nome_plataforma,
                                   dias[0].dia, dias[0].mes, dias[0].ano, dias[0].horas_minutos, dias[1].dia,
                                   dias[1].mes, dias[1].ano, dias[1].horas_minutos);
                        }
                        else
                        {
                            printf("      ID Evento: %d | Nome evento: %s | Inicio:%d/%d/%d (%0.2f)Fim:%d/%d/%d (%0.2f)\n",
                                   eventos->id_evento, eventos->nome_evento, dias[0].dia, dias[0].mes, dias[0].ano,
                                   dias[0].horas_minutos, dias[1].dia, dias[1].mes, dias[1].ano, dias[1].horas_minutos);
                        }
                        printf("\n");
                        eventos = eventos->nextEvento;
                    }
                    printf("\n");
                }
            }
            printf("\n\n");
        }
        printf("-------------------------------------\n");
        node = node->next;
    }
}

/**
 * Função que imprime todos os eventos
 */

void printEventos()
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        ESTUDIO *current = node->vector_estudio;
        for (int i = 0; i < node->num_estudios; i++)
        {
            MASTERAGENDA *master = current[i].agendaMaster;
            DIAS *current_dias = master->vector_dias;
            for (int j = 0; j < current[i].num_dias; j++)
            {
                struct evento *eventos = current_dias[j].vector_evento;
                while (eventos != NULL)
                {
                    DATA *dias = eventos->datas;
                    if (eventos->id_cliente != -1)
                    {
                        printf("      ID Evento: %d | ID Client: %d | Nome cliente: %s | Nome evento: %s |\n      Inicio:%d/%d/%d(%0.2f) Fim:%d/%d/%d(%0.2f)\n",
                               eventos->id_evento, eventos->id_cliente, eventos->nome_cliente, eventos->nome_evento,
                               dias[0].dia, dias[0].mes, dias[0].ano, dias[0].horas_minutos, dias[1].dia,
                               dias[1].mes, dias[1].ano, dias[1].horas_minutos);
                    }
                    else
                    {
                        printf("      ID Evento: %d | Nome evento: %s | Inicio:%d/%d/%d (%0.2f)Fim:%d/%d/%d (%0.2f)\n",
                               eventos->id_evento, eventos->nome_evento, dias[0].dia, dias[0].mes, dias[0].ano,
                               dias[0].horas_minutos, dias[1].dia, dias[1].mes, dias[1].ano, dias[1].horas_minutos);
                    }
                    printf("\n");
                    eventos = eventos->nextEvento;
                }
            }
        }
        node = node->next;
    }
}

/**
 * Função que imprime o branch calender de todos os estudios
 */

void printReservas()
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        printf("Edificio %d:\n", node->id_edificio); //Imprime id e counter
        ESTUDIO *current = node->vector_estudio;
        for (int i = 0; i < node->num_estudios; i++)
        {
            BRANCHCALENDER *branch = current[i].calender;
            if (current[i].num_plat != 0)
            {
                printf("Estudio[%d]\n", current[i].id_estudio);
                for (int j = 0; j < current[i].num_plat; j++)
                {
                    DIAS *reservas = branch[j].vector_dias;
                    printf("Plataforma: %s\n", branch[j].nome_plataforma);
                    if (reservas == NULL)
                    {
                        printf("Nao possui dias \n");
                        return;
                    }
                    for (int k = 0; k < branch[j].num_dias; k++)
                    {
                        printf("   Dia=%d,Mes=%d,Ano=%d\n\n", reservas[k].dia, reservas[k].mes, reservas[k].ano);
                    }
                    printf("\n");
                }
            }
        }
        printf("-------------------------------------\n");
        node = node->next;
    }
}

/**
 * Função que inserede um cliente no historico de clientes, sempre que é adiciona um evento do tipo estadia
 * @param head cabeça da lista do historico (apontador duplo caso seja necessario alterar)
 * @param no no para percorrer
 * @param id_cliente cliente a ser adicionado à lista
 * @param nome_cliente nome do cliente
 * @param nome_evento nome do evento
 * @param id_estadia id do evento
 * @param reserva datas da reserva (Inicio-Fim)
 */

void insert_historico(struct historico **head, struct historico *no, long int id_cliente, char *nome_cliente, char *nome_evento, int id_estadia, DATA *reserva)
{
    struct historico *node = no;
    if (node == NULL) //Se a lista tiver vazio, coloca a primeira pessoa
    {
        struct historico *new_node = (struct historico *)malloc(sizeof(struct historico));     //Cria um novo no
        new_node->id_cliente = id_cliente; //Preenche com informação
        new_node->num_estadias = 1;
        new_node->nome_cliente = malloc(300 * sizeof(char));
        strcpy(new_node->nome_cliente, nome_cliente);
        new_node->pfirst_estadia = NULL; //Apontador para a segunda lista fica a NULL
        new_node->pfirst_estadia = insert_eventos_historico(new_node, id_estadia, nome_evento,reserva); //Atualiza o apontador
        new_node->pnext = *head;                                      //Atualiza a cabeça
        *head = new_node;
        return;
    }
    else //Se nao tiver vazia
    {
        while (node != NULL)
        {
            if (node->id_cliente == id_cliente) //Percorre a lista para ver se aquela pessoa ja existe lá
            {
                node->num_estadias = node->num_estadias +1; //Adiciona mais uma estadia
                node->pfirst_estadia = insert_eventos_historico(node, id_estadia, nome_evento,reserva); //Atualiza o apontador
                return;
            }
            node = node->pnext;
        }
        //Se não existe é adiciona um novo cliente na lista
        //Volta para a cabeça
        struct historico *new_node = (struct historico *)malloc(sizeof(struct historico));     //Aloca espaço para um novo no
        struct historico *current = *head; //No auxiliar
        new_node->id_cliente = id_cliente; //Coloca informação
        new_node->num_estadias = 1;
        new_node->nome_cliente = malloc(300 * sizeof(char));
        strcpy(new_node->nome_cliente, nome_cliente);
        new_node->pfirst_estadia = NULL;
        new_node->pfirst_estadia = insert_eventos_historico(new_node, id_estadia, nome_evento,reserva); //Atualiza o apontador

        if (new_node->id_cliente > current->id_cliente)
        {

            while (current->pnext != NULL && (current->pnext->id_cliente <
                                              new_node->id_cliente))
            { //Encontra a posição para a inserção do no (current,new_node,current->next)
                current = current->pnext;
            }

            new_node->pnext = current->pnext;
            current->pnext = new_node;
            return;
        }
        else //Se o nó que eu for add for menor que o no presenta na cabeça ent este no será a cabeça
        {
            new_node->pnext = *head;
            *head = new_node;
            return;
        }
    }
}

ESTADIAS_HISTORICO *insert_eventos_historico(struct historico *no, int id_estadia, char *nome_evento, DATA *reserva)
{

    struct estadias_historico *nova_estadia = (struct estadias_historico *)malloc(sizeof(struct estadias_historico));
    struct estadias_historico *current = no->pfirst_estadia;
    nova_estadia->id_estadia = id_estadia;
    nova_estadia->nome_evento = malloc(300 * sizeof(char));
    strcpy(nova_estadia->nome_evento, nome_evento);
    DATA *datas = (DATA *)malloc(1 * sizeof(DATA));
    datas[0].dia = reserva[0].dia;
    datas[0].mes = reserva[0].mes;
    datas[0].ano = reserva[0].ano;
    nova_estadia->data = datas;

    if (current == NULL)
    {
        nova_estadia->pnext_estadia = no->pfirst_estadia;
        no->pfirst_estadia = nova_estadia;
        return nova_estadia;
    }
    else
    {
        if (nova_estadia->id_estadia > current->id_estadia)
        {
            while (current->pnext_estadia != NULL && (current->pnext_estadia->id_estadia <nova_estadia->id_estadia))
            { //Encontra a posição para a inserção do no (current,new_node,current->next)
                current = current->pnext_estadia;
            }
            nova_estadia->pnext_estadia = current->pnext_estadia;
            current->pnext_estadia = nova_estadia;
            return no->pfirst_estadia;
        }
        else //Se o nó que eu for add for menor que o no presenta na cabeça ent este no será a cabeça
        {
            nova_estadia->pnext_estadia = no->pfirst_estadia;
            no->pfirst_estadia = nova_estadia;
            return nova_estadia;
        }
    }
}

/**
 * Imprime o historico de clientes
 */

void printHistorico()
{
    FILE *file;
    file=fopen("historico.txt","a");

    printf("Historico de todos os clientes:\n\n");
    fprintf(file,"Historico de todos os clientes:\n\n");
    struct historico *node = HeadHistorico;
    while (node != NULL)
    {
        printf("Nome: %s |ID do Cliente: %d|Estadias: %d\n", node->nome_cliente, node->id_cliente, node->num_estadias);
        fprintf(file,"Nome: %s |ID do Cliente: %d|Estadias: %d\n", node->nome_cliente, node->id_cliente, node->num_estadias);
        struct estadias_historico *estadia = node->pfirst_estadia;
        while (estadia != NULL)
        {
            DATA *reserva = estadia->data;
            printf("ID da Estadia: %d | Nome: %s | Reserva:%d/%d/%d\n", estadia->id_estadia, estadia->nome_evento,reserva[0].dia, reserva[0].mes, reserva[0].ano);
            fprintf(file,"ID da Estadia: %d | Nome: %s | Reserva:%d/%d/%d\n", estadia->id_estadia, estadia->nome_evento,reserva[0].dia, reserva[0].mes, reserva[0].ano);

            estadia = estadia->pnext_estadia;
        }
        printf("\n");
        fprintf(file,"\n");
        node = node->pnext;
    }
}

/**
 * Encontra o estudio na lista de edificios
 * @param id_estudio estudio a ser encontrado
 */

void find_estudio_by_id(int id_estudio)
{
    int *array;
    array = find_estudio(id_estudio);
    if (array[0] != 0 && array[1] != 0)
    {
        printf("Encontrei estudio [%d] no edificio [%d]\n", array[1], array[0]);
    }
    else
    {
        printf("Estudio nao existe em lado nenhum\n");
    }
}

/**
 * Função que comparar duas datas do tipo DIAS
 * @param d1
 * @param d2
 * @return 1-d1>d2 | -1->d1<d2 | 0->d1=d2
 */

int date_cmp(DIAS d1, DIAS d2)
{
    if (d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano)
        return 0; //d1 e d2 sao iguais
    else if (d1.ano > d2.ano || (d1.ano == d2.ano && d1.mes > d2.mes) ||
             (d1.ano == d2.ano && d1.mes == d2.mes && d1.dia > d2.dia))
        return 1; //d1 é maior
    else
        return -1; //d2 é maior
}


/**
 * Funçao para remover edificio da lista ligada de edificios
 * @param head cabeça da lista
 * @param id_edificio edificio a ser removido
 */

void remove_edificio(struct edificio **head, int id_edificio)
{
    struct edificio *no = *head;
    struct edificio *previous = NULL;
    if (no->id_edificio == id_edificio)
    {
        HeadEdificios = no->next;
    }
    else
    {
        while (no != NULL)
        {
            if (no->id_edificio == id_edificio)
            {
                previous->next = no->next;
                free(no);
                printf("Edificio %d removido\n",id_edificio);
                return;
            }
            previous = no;
            no = no->next;
        }
        if(no==NULL)
        {
            printf("Edificio %d nao existe\n",id_edificio);
        }
    }
}

/**
 * Remove um evento da lista ligada de eventos de um dia
 * @param id_evento id do evento a ser removido
 */

void remove_evento(int id_evento)
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        ESTUDIO *current = node->vector_estudio;
        for (int i = 0; i < node->num_estudios; i++)
        {
            MASTERAGENDA *master = current[i].agendaMaster;
            DIAS *current_dias = master->vector_dias;
            for (int j = 0; j < current[i].num_dias; j++)
            {
                struct evento *eventos = current_dias[j].vector_evento;
                struct evento *previous = NULL;

                if (eventos->id_evento == id_evento)
                {
                    current_dias[j].vector_evento = eventos->nextEvento;
                }
                else
                {
                    while (eventos != NULL)
                    {

                        if (eventos->id_evento == id_evento)
                        {
                            previous->nextEvento = eventos->nextEvento;
                            free(eventos);
                            return;
                        }
                        previous = eventos;
                        eventos = eventos->nextEvento;
                    }
                }
            }
        }
        node = node->next;
    }
    printf("Evento %d nao existe para ser removido\n", id_evento);
}

/**
 * Remove da lista ligada de hospedes
 * @param head começa
 * @param id_cliente
 */

void remove_hospede(struct historico **head, int id_cliente)
{
    struct historico *no = *head;
    struct historico *previous = NULL;
    if (no->id_cliente == id_cliente)
    {
        HeadHistorico = no->pnext;
    }
    else
    {
        while (no != NULL)
        {
            if (no->id_cliente == id_cliente)
            {
                printf("Cliente Removido: ID[%d] Nome:%s\n", no->id_cliente, no->nome_cliente);
                previous->pnext = no->pnext;
                free(no);
                return;
            }
            previous = no;
            no = no->pnext;
        }
        printf("Cliente com ID %d nao existe\n",id_cliente);
    }
}

void remove_estudio(int id_estudio)
{
    int *array;
    array = find_estudio(id_estudio);
    if (array[0] == 0 || array[1] == 0)
    {
        printf("Estudio nao existe\n");
        return;
    }
    struct edificio *no = HeadEdificios;
    while (no != NULL && no->id_edificio != array[0])
    {
        no = no->next;
    }
    ESTUDIO *current = no->vector_estudio;
    int pos = binarySearch_estudio(current, 0, no->num_estudios - 1, id_estudio);
    for (int i = pos; i < no->num_estudios - 1; i++)
    {
        current[i] = current[i + 1];
    }
    no->num_estudios = no->num_estudios - 1;
    printf("Estudio %d removido do edificio %d.\n", id_estudio, no->id_edificio);
}

/**
 * Funçao que remove do array global de regras
 * @param id_regra regra a ser removida
 */

void remove_regra(int id_regra)
{
    REGRAS *vetor_regras = relacoes.regras;
    int pos = binarySearch_regras(vetor_regras, 0, relacoes.num_regras - 1, id_regra);
    if (pos < 0)
    {
        printf("Regra nao existe\n");
        return;
    }

    for (int i = pos; i < relacoes.num_regras - 1; i++)
    {
        vetor_regras[i] = vetor_regras[i + 1];
    }
    relacoes.num_regras -= 1;
    relacoes.regras = vetor_regras;
    printf("Regra %d removida\n", id_regra);
}

/**
 * Função que remove politica do array global de politicas
 * @param nome politica a ser removida
 */

void remove_politica(char *nome)
{
    POLITICA *vetor_politicas = relacoes.politicas;

    int pos = checkPolitica(vetor_politicas, 0, relacoes.num_politicas - 1, nome);

    if (pos < 0)
    {
        printf("Politica  %s nao existe\n", nome);
        return;
    }

    for (int i = pos; i < relacoes.num_politicas - 1; i++)
    {
        vetor_politicas[i] = vetor_politicas[i + 1];
    }
    relacoes.num_politicas -= 1;
    relacoes.politicas = vetor_politicas;
    printf("Politica %s removida\n", nome);
}

/**
 * Função que remove estudio do vetor de estudios de um edificio
 * @param estudio
 * @param nome
 */

void remove_estudio_politica(int estudio, char *nome)
{
    ESTUDIO_POLITICA *vetor_politica_estudios = relacoes.estudio_politica;

    int pos = checkEstudioPolitica(vetor_politica_estudios, estudio, nome);
    int i, j = 0;
    if (pos < 0)
    {
        printf("A configuracao do estudo %d com a politica %s nao existe\n", estudio, nome);
        return;
    }
    for (i = 0; i < relacoes.num_relacoes; i++)
    {
        if (vetor_politica_estudios[i].id_estudio == estudio && strcmp(vetor_politica_estudios[i].nome_politica, nome) == 0)
        {
            vetor_politica_estudios[i] = vetor_politica_estudios[i + 1];
            break;
        }
    }
    for (j = i; j < relacoes.num_relacoes; j++)
    {
        vetor_politica_estudios[j] = vetor_politica_estudios[j + 1];
    }

    relacoes.num_relacoes -= 1;
    relacoes.estudio_politica = vetor_politica_estudios;
    printf("A configuracao do estudo %d com a politica %s foi removida\n", estudio, nome);
}

/**
 * Função que altera os atributos do edificio
 * @param id_edificio edificio a alterar
 * @param new_nome novo nome
 * @param new_morada nova morada
 * @param new_preco_m2 novo preço
 * @param new_latitude nova latitude
 * @param new_longitude nova longitude
 */

void alterar_edificio(int id_edificio, char *new_nome, char *new_morada, double new_preco_m2, double new_latitude, double new_longitude)
{
    struct edificio *no = HeadEdificios;
    while (no != NULL)
    {
        if (no->id_edificio == id_edificio)
        {
            no->preco_m2 = new_preco_m2;
            strcpy(no->nome, new_nome);
            strcpy(no->morada, new_morada);
            no->longitude = new_longitude;
            no->latitude = new_latitude;
            printf("Edificio %d foi alterado\n", no->id_edificio);
            return;
        }
        no = no->next;
    }
}

/**
 * Função que apenas altera o nome do evento
 * @param id_evento id do evento a alterar
 * @param new_nome_evento novo nome
 */

void alterar_evento(int id_evento, char *new_nome_evento)
{
    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        ESTUDIO *current = node->vector_estudio;
        for (int i = 0; i < node->num_estudios; i++)
        {
            MASTERAGENDA *master = current[i].agendaMaster;
            DIAS *current_dias = master->vector_dias;
            for (int j = 0; j < current[i].num_dias; j++)
            {
                struct evento *eventos = current_dias[j].vector_evento;

                if (eventos->id_evento == id_evento)
                {
                    current_dias[j].vector_evento = eventos->nextEvento;
                }
                else
                {
                    while (eventos != NULL)
                    {
                        if (eventos->id_evento == id_evento)
                        {
                            strcpy(eventos->nome_evento, new_nome_evento);
                            printf("Evento %d foi alterado\n", id_evento);
                            return;
                        }
                        eventos = eventos->nextEvento;
                    }
                }
            }
        }
        node = node->next;
    }
    printf("Evento %d nao existe para ser alterado\n", id_evento);
}

/**
 * Função para alterar o tipo do estudio e a area
 * @param id_estudio id do estudio a alterar
 * @param new_tipo nova designação
 * @param area nova area
 */

void alterar_estudio(int id_estudio, char *new_tipo, int area)
{
    int *array;
    array = find_estudio(id_estudio);
    if (array[0] == 0 || array[1] == 0)
    {
        printf("Estudio nao existe\n");
        return;
    }
    struct edificio *no = HeadEdificios;
    while (no->id_edificio != array[0])
    {
        no = no->next;
    }

    ESTUDIO *current = no->vector_estudio;
    int pos = binarySearch_estudio(current, 0, no->num_estudios - 1, id_estudio);
    current[pos].area = area;
    strcpy(current[pos].tipo, new_tipo);
    printf("Estudio %d foi alterado.\n", id_estudio);
}

/**
 * Função que apenas altera a designação de uma regra
 * @param id_regra  id da regra a alterar
 * @param new_regra nova designação
 */

void alterar_regra(int id_regra, char *new_regra)
{
    REGRAS *vetor_regras = relacoes.regras;
    int pos = binarySearch_regras(vetor_regras, 0, relacoes.num_regras - 1, id_regra);
    if (pos < 0)
    {
        printf("Regra nao existe\n");
        return;
    }
    strcpy(vetor_regras[pos].regra, new_regra);
    printf("Regra %d foi alterada\n", id_regra);
}

/**
 * Função para alterar as politicas (Alterando a plataforma e as regras)
 * @param nome nome da politica a alterar
 * @param new_plataforma  nova plataforma para aquela politica
 * @param num_regras numero de novas regras
 * @param array novas regras
 */

void alterar_politica(char *nome, char *new_plataforma, int num_regras, int *array)
{
    POLITICA *vetor_politicas = relacoes.politicas;
    int pos = checkPolitica(vetor_politicas, 0, relacoes.num_politicas - 1, nome);
    if (pos < 0)
    {
        printf("Politica  %s nao existe\n", nome);
        return;
    }
    vetor_politicas[pos].num_regras = num_regras;
    strcpy(vetor_politicas[pos].plataforma, new_plataforma);
    vetor_politicas[pos].regras = array;
    printf("Politica %s foi alterada\n", nome);
}

/**
 * Função que altera as relações estudio-politica
 * @param estudio id do estudio a alterar
 * @param nome nome da politica a alterar
 * @param new_estudio novo estudio
 * @param new_politica nova politica
 * @param num_taxas novas taxas
 * @param taxas numero de taxas
 */

void alterar_estudio_politica(int estudio, char *nome, int new_estudio, char *new_politica, int num_taxas, double *taxas)
{
    ESTUDIO_POLITICA *vetor_politica_estudios = relacoes.estudio_politica;
    int pos = checkEstudioPolitica(vetor_politica_estudios, estudio, nome);
    int i, j = 0;
    if (pos < 0)
    {
        printf("A configuracao do estudo %d com a politica %s nao existe\n", estudio, nome);
        return;
    }
    for (i = 0; i < relacoes.num_relacoes; i++)
    {
        if (vetor_politica_estudios[i].id_estudio == estudio && strcmp(vetor_politica_estudios[i].nome_politica, nome) == 0)
        {
            vetor_politica_estudios[i].id_estudio = new_estudio;
            vetor_politica_estudios[i].taxas = taxas;
            strcpy(vetor_politica_estudios[i].nome_politica, new_politica);
            vetor_politica_estudios[i].num_taxas = num_taxas;
            printf("A configuracao do estudo %d com a politica %s foi alterada\n", estudio, nome);
            break;
        }
    }
}

/**
 * Função que faz o relatorio de um estudio, por % de ocupação.
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */

void ocupacaoEstudio(int estudio, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    if (ordem == 2 || ordem == 3)
    {
        printf("Ordem de ordenacao invalida\n");
        return;
    }
    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    num_relatorios = 0;
    int *array;
    array = find_estudio(estudio);
    if (array[0] == 0 && array[1] == 0)
    {
        printf("Edificio com o id %d nao existe\n", estudio);
        return;
    }
    double num_dias;
    double ocupado = 0;
    num_dias = diferenca_de_dias(dia1, mes1, ano1, dia2, mes2, ano2);
    struct edificio *node = HeadEdificios;
    while (node->id_edificio != array[0])
    {
        node = node->next;
    }

    ESTUDIO *vetor_estudio = node->vector_estudio;
    int i = binarySearch_estudio(vetor_estudio, 0, node->num_estudios - 1, estudio);
    MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
    DIAS *vetor_dias = agenda->vector_dias;
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL}, {dia2, mes2, ano2, 0, NULL}};

    for (int j = 0; j < vetor_estudio[i].num_dias; j++)
    {
        struct evento *eventos = vetor_dias[j].vector_evento;
        while (eventos != NULL)
        {
            DATA *dias = eventos->datas;
            if (eventos->id_cliente != -1)
            {
                double duracao = 0;
                DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL}, {dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                {
                    duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);

                    DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));

                    contagem[0]=dias[0];
                    contagem[1]=dias[1];
                    RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, duracao};
                    relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                    num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                }
                else
                {
                    if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                    {
                        duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);

                        DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                        contagem[0].dia = days[0].dia;
                        contagem[0].mes = days[0].mes;
                        contagem[0].ano = days[0].ano;
                        contagem[1].dia = days[1].dia;
                        contagem[1].mes = days[1].mes;
                        contagem[1].ano = days[1].ano;

                        RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, duracao};
                        relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                        num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                    }
                    else
                    {
                        if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                        {
                            duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);

                            DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                            contagem[0].dia = dias[0].dia;
                            contagem[0].mes = dias[0].mes;
                            contagem[0].ano = dias[0].ano;
                            contagem[1].dia = days[1].dia;
                            contagem[1].mes = days[1].mes;
                            contagem[1].ano = days[1].ano;

                            RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, duracao};
                            relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                            num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                        }
                        else
                        {
                            if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                            {
                                duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);

                                DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                                contagem[0].dia = days[0].dia;
                                contagem[0].mes = days[0].mes;
                                contagem[0].ano = days[0].ano;
                                contagem[1].dia = dias[1].dia;
                                contagem[1].mes = dias[1].mes;
                                contagem[1].ano = dias[1].ano;

                                RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, duracao};
                                relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                                num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                            }
                        }
                    }
                }
                ocupado += duracao;
            }
            eventos = eventos->nextEvento;
        }
    }
    double percentagem_ocupado = (ocupado / num_dias) * 100;
    printRelatoriosEstudio("ocupacao.txt", percentagem_ocupado, days, 1);
}

/**
 * Função que faz o relatorio de um Edificio, por % de ocupaçao
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */

void ocupacaoEdificio(int edificio, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    if (ordem == 3)
    {
        printf("Ordem de ordenacao invalida\n");
        return;
    }

    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    num_relatorios = 0;
    double num_dias;
    double ocupado_edificio = 0;
    int i = 0;
    num_dias = diferenca_de_dias(dia1, mes1, ano1, dia2, mes2, ano2);

    struct edificio *node = HeadEdificios;
    while (node!=NULL && node->id_edificio != edificio)
    {
        node = node->next;
    }
    if(node==NULL)
    {
        printf("Edificio %d nao existe\n",edificio);
        return;
    }
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL},{dia2, mes2, ano2, 0, NULL}};
    ESTUDIO *vetor_estudio = node->vector_estudio;
    if(vetor_estudio!=NULL)
    {
        for (i = 0; i < node->num_estudios; i++)
        {
            double ocupado = 0;
            double percentagem_ocupado = 0;
            MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
            DIAS *vetor_dias = agenda->vector_dias;

            for (int j = 0; j < vetor_estudio[i].num_dias; j++)
            {
                struct evento *eventos = vetor_dias[j].vector_evento;
                while (eventos != NULL)
                {
                    DATA *dias = eventos->datas;
                    if (eventos->id_cliente != -1)
                    {
                        double duracao = 0;
                        DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL}, {dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                        if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                        {
                            duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                        }
                        else
                        {
                            if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                            {
                                duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                            }
                            else
                            {
                                if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                                {
                                    duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                }
                                else
                                {
                                    if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                                    {
                                        duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                    }
                                }
                            }
                        }
                        ocupado += duracao;
                    }
                    eventos = eventos->nextEvento;
                }
            }
            DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
            contagem[0].dia = days[0].dia;
            contagem[0].mes = days[0].mes;
            contagem[0].ano = days[0].ano;
            contagem[1].dia = days[1].dia;
            contagem[1].mes = days[1].mes;
            contagem[1].ano = days[1].ano;

            percentagem_ocupado = (ocupado / num_dias) * 100;
            ocupado_edificio += percentagem_ocupado;

            RELATORIOS insert_relatorio = {0, node->id_edificio, vetor_estudio[i].id_estudio, 0, 0, num_dias, NULL, NULL, NULL, contagem, percentagem_ocupado};
            relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
            num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
        }

    }
    else
    {
       printf("Edificio %d nao possui estudios\n",node->id_edificio);
       return;
    }

    ocupado_edificio = ocupado_edificio / i;
    printRelatoriosEdificio("ocupacao.txt", ocupado_edificio, days, 1);
}

/**
 * Função que faz o relatorio do parque de edificios da portoFlats (todos os edificios), por % de ocupação.
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */

void ocupacaoParqueEdificios(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    if (ordem == 2)
    {
        printf("Ordenacao invalida\n");
        return;
    }

    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    num_relatorios = 0;
    double num_dias;
    int num_edificios = 0;
    double ocupado_edificio = 0, ocupado_parque = 0;
    int i = 0;
    num_dias = diferenca_de_dias(dia1, mes1, ano1, dia2, mes2, ano2);
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL}, {dia2, mes2, ano2, 0, NULL}};

    struct edificio *node = HeadEdificios;
    while (node != NULL)
    {
        num_edificios++;
        ESTUDIO *vetor_estudio = node->vector_estudio;
        if(vetor_estudio==NULL)
        {
            ocupado_edificio=0;
        } else
        {
            for (i = 0; i < node->num_estudios; i++)
            {
                double ocupado = 0;
                double percentagem_ocupado = 0;

                MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
                DIAS *vetor_dias = agenda->vector_dias;

                for (int j = 0; j < vetor_estudio[i].num_dias; j++)
                {

                    struct evento *eventos = vetor_dias[j].vector_evento;
                    while (eventos != NULL)
                    {
                        DATA *dias = eventos->datas;
                        if (eventos->id_cliente != -1)
                        {
                            double duracao = 0;
                            DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL}, {dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                            if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                            {

                                duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                            }
                            else
                            {

                                if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                                {
                                    duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                }
                                else
                                {
                                    if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                                    {

                                        duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                    }
                                    else
                                    {
                                        if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                                        {
                                            duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                        }
                                    }
                                }
                            }
                            ocupado += duracao;
                        }
                        eventos = eventos->nextEvento;
                    }
                }
                percentagem_ocupado = (ocupado / num_dias) * 100;
                ocupado_edificio += percentagem_ocupado;
            }
        }
        ocupado_edificio = ocupado_edificio / i;
        ocupado_parque += ocupado_edificio;

        DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
        contagem[0].dia = days[0].dia;
        contagem[0].mes = days[0].mes;
        contagem[0].ano = days[0].ano;
        contagem[1].dia = days[1].dia;
        contagem[1].mes = days[1].mes;
        contagem[1].ano = days[1].ano;

        RELATORIOS insert_relatorio = {0, node->id_edificio, 0, 0, 0, num_dias, NULL, NULL, NULL, contagem, ocupado_edificio};
        relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
        num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);

        node = node->next;
    }
    ocupado_parque = ocupado_parque / num_edificios;
    printRelatoriosParqueEdificios("ocupacao.txt", ocupado_parque, days, 1);
}

/**
 *
 * @param id_estudio estudio para o qual vai ser gerado um relatorio
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @return Irá retornar o numero de dias em que um estudio está ocupado (Se retornar 0 significa que o estudio está completamente livre para esse intervalo de tempo)
 */

double disponivel(int id_estudio, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2) //Verifica se num detemrinado intervalo de tempo existe alguma ocupaçao, caso existe n pode ser adiciona o novo evento
{
    int *array;
    array = find_estudio(id_estudio);
    double ocupado = 0;
    struct edificio *node = HeadEdificios;

    while (node->id_edificio != array[0])
    {
        node = node->next;
    }

    ESTUDIO *vetor_estudio = node->vector_estudio;
    int i = binarySearch_estudio(vetor_estudio, 0, node->num_estudios - 1, id_estudio);
    MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;

    DIAS *vetor_dias = agenda->vector_dias;
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL},{dia2, mes2, ano2, 0, NULL}};
    for (int j = 0; j < vetor_estudio[i].num_dias; j++)
    {
        struct evento *eventos = vetor_dias[j].vector_evento;
        while (eventos != NULL)
        {
            DATA *dias = eventos->datas;
            if (eventos->id_cliente != -1)
            {
                double duracao = 0;
                DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL}, {dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                if (date_cmp(aux_dias[0], days[0]) >= 0 && date_cmp(days[1], aux_dias[1]) >= 0) //Dentro do limite(d2,d1)
                {
                    duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                }
                else
                {

                    if (date_cmp(days[0], aux_dias[0]) >= 0 && date_cmp(aux_dias[1], days[1]) >= 0) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                    {
                        duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                    }
                    else
                    {
                        if (date_cmp(aux_dias[0], days[0]) >= 0 && date_cmp(days[1], aux_dias[0]) >= 0) //Limite direito
                        {
                            duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                        }
                        else
                        {
                            if (date_cmp(days[0], aux_dias[0]) >= 0 && date_cmp(aux_dias[1], days[0]) >= 0) //Limite esquerdo
                            {
                                duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                            }
                        }
                    }
                }
                ocupado += duracao;
            }
            eventos = eventos->nextEvento;
        }
    }
    return ocupado;
}

/**
 * Função que faz a diferença de dias entre 2 dias
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @return returna a diferença de dias
 */

double diferenca_de_dias(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2)
{
    int sdia1, smes1, sano1;
    struct tm date1 = {0};
    char sdata1[15];
    sprintf(sdata1, "%d/%d/%d", dia1, mes1, ano1);
    sscanf(sdata1, "%d%*[^0123456789]%d%*[^0123456789]%d", &sdia1, &smes1, &sano1);
    //printf("%s\n",sdata1);
    // printf("%d %d %d\n",sdia1,smes1,sano1);
    date1.tm_mday = sdia1;
    date1.tm_mon = smes1;
    date1.tm_year = sano1 - 1900;
    time_t d1;
    d1 = mktime(&date1);

    int sdia2, smes2, sano2;
    struct tm date2 = {0};
    char sdata2[15];
    sprintf(sdata2, "%d/%d/%d", dia2, mes2, ano2);
    sscanf(sdata2, "%d%*[^0123456789]%d%*[^0123456789]%d", &sdia2, &smes2, &sano2);
    //printf("%s\n",sdata2);
    //printf("%d %d %d\n",sdia2,smes2,sano2);
    date2.tm_mday = sdia2;
    date2.tm_mon = smes2;
    date2.tm_year = sano2 - 1900;
    time_t d2;
    d2 = mktime(&date2);
    double seconds = difftime(d2, d1);
    double minutes = seconds / 60.0;
    double horas = minutes / 60.0;
    double dias = horas / 24;
    return dias;
}

/**
 * Função que faz o relatorio de um estudio
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */

void faturacaoEstudio(int estudio, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    if (ordem == 2 || ordem == 3)
    {
        printf("Ordem de ordenaçao invalida\n");
        return;
    }
    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    num_relatorios = 0;
    int *array;
    array = find_estudio(estudio);                      //Procura se existe algum edificio com aquele ID na estrutura inteira
    if (array[0] == 0 && array[1] == 0)
    {
        printf("Estudio com o id %d nao existe\n", estudio);
        return;
    }
    double faturacao_estudio = 0.0;
    struct edificio *node = HeadEdificios;

    while (node->id_edificio != array[0])
    {
        node = node->next;
    }
    double preco_base;
    ESTUDIO *vetor_estudio = node->vector_estudio;
    int i = binarySearch_estudio(vetor_estudio, 0, node->num_estudios - 1, estudio);
    preco_base = node->preco_m2 * vetor_estudio[i].area;
    MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
    DIAS *vetor_dias = agenda->vector_dias;
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL},{dia2, mes2, ano2, 0, NULL}};
    for (int j = 0; j < vetor_estudio[i].num_dias; j++)
    {
        struct evento *eventos = vetor_dias[j].vector_evento;
        while (eventos != NULL)
        {
            DATA *dias = eventos->datas;
            if (eventos->id_cliente != -1)
            {
                double duracao = 0;
                double preco_evento = 0.0;

                DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL},{dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}}; //Converte para poder fazer comparações

                if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                {
                    duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                    DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                    allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao);
                    preco_evento = taxas(preco_base, allDays, estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);

                    DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                    contagem[0].dia = dias[0].dia;
                    contagem[0].mes = dias[0].mes;
                    contagem[0].ano = dias[0].ano;
                    contagem[1].dia = dias[1].dia;
                    contagem[1].mes = dias[1].mes;
                    contagem[1].ano = dias[1].ano;

                    RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, preco_evento};
                    relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                    num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                }
                else
                {
                    if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                    {
                        duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                        DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                        allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao + 2);
                        preco_evento = taxas(preco_base, allDays, estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 2);

                        DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                        contagem[0].dia = days[0].dia;
                        contagem[0].mes = days[0].mes;
                        contagem[0].ano = days[0].ano;
                        contagem[1].dia = days[1].dia;
                        contagem[1].mes = days[1].mes;
                        contagem[1].ano = days[1].ano;

                        RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, preco_evento};
                        relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                        num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                    }
                    else
                    {
                        if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                        {
                            duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                            DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                            allDays = fillAllDays(allDays, aux_dias[0], days[1], (int)duracao + 1);
                            preco_evento = taxas(preco_base, allDays, estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);

                            DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                            contagem[0].dia = dias[0].dia;
                            contagem[0].mes = dias[0].mes;
                            contagem[0].ano = dias[0].ano;
                            contagem[1].dia = days[1].dia;
                            contagem[1].mes = days[1].mes;
                            contagem[1].ano = days[1].ano;

                            RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, preco_evento};
                            relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                            num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                        }
                        else
                        {
                            if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                            {
                                duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                allDays = fillAllDays(allDays, days[0], aux_dias[1], (int)duracao + 1);
                                preco_evento = taxas(preco_base, allDays, estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);

                                DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
                                contagem[0].dia = days[0].dia;
                                contagem[0].mes = days[0].mes;
                                contagem[0].ano = days[0].ano;
                                contagem[1].dia = dias[1].dia;
                                contagem[1].mes = dias[1].mes;
                                contagem[1].ano = dias[1].ano;

                                RELATORIOS insert_relatorio = {0, 0, estudio, eventos->id_evento, eventos->id_cliente, duracao, eventos->nome_cliente, eventos->nome_evento, contagem, eventos->datas, preco_evento};
                                relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
                                num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
                            }
                        }
                    }
                }
                faturacao_estudio += preco_evento;
            }
            eventos = eventos->nextEvento;
        }
    }
    printRelatoriosEstudio("faturacao.txt", faturacao_estudio, days, 2);
    num_relatorios--;
}

/**
 *Função que faz a faturação de um Edificio
 * @param edificio id do edificio onde vai ser gerado o relatorio
 * @param dia1  dia inicial
 * @param mes1  mes inicial
 * @param ano1  ano inicial
 * @param dia2  dia final
 * @param mes2  mes final
 * @param ano2  ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */
void faturacaoEdificio(int edificio, int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    if (ordem == 3)
    {
        printf("Ordem de ordenaçao invalida\n");
        return;
    }

    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    num_relatorios = 0;
    double faturacao_edificio = 0.0;
    double num_dias;
    num_dias = diferenca_de_dias(dia1, mes1, ano1, dia2, mes2, ano2);
    struct edificio *node = HeadEdificios;
    while (node !=NULL && node->id_edificio != edificio)
    {
        node = node->next;
    }
    if(node==NULL)
    {
        printf("Edificio %d nao existe\n",edificio);
        return;
    }
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL}, {dia2, mes2, ano2, 0, NULL}};          //Converter dias da função para estrutura DIAS
    double preco_base;
    ESTUDIO *vetor_estudio = node->vector_estudio;
    if(vetor_estudio!=NULL)
    {
        for (int i = 0; i < node->num_estudios; i++)
        {
            double faturacao_estudio = 0.0;
            preco_base = node->preco_m2 * vetor_estudio[i].area;
            MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
            DIAS *vetor_dias = agenda->vector_dias;

            for (int j = 0; j < vetor_estudio[i].num_dias; j++)
            {
                struct evento *eventos = vetor_dias[j].vector_evento;
                while (eventos != NULL)
                {
                    DATA *dias = eventos->datas;
                    if (eventos->id_cliente != -1)
                    {
                        double duracao = 0;
                        double preco_evento = 0.0;
                        DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL}, {dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                        if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                        {
                            duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                            DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                            allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao);
                            preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);
                        }
                        else
                        {

                            if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                            {
                                duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao + 2);
                                preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 2);
                            }
                            else
                            {
                                if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                                {
                                    duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                    DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                    allDays = fillAllDays(allDays, aux_dias[0], days[1], (int)duracao + 1);
                                    preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento,eventos->nome_plataforma, (int)duracao + 1);
                                }
                                else
                                {
                                    if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                                    {
                                        duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                        DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                        allDays = fillAllDays(allDays, days[0], aux_dias[1], (int)duracao + 1);
                                        preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);
                                    }
                                }
                            }
                        }
                        faturacao_estudio += preco_evento;              //Soma faturação de todos os eventos
                    }

                    eventos = eventos->nextEvento;
                }
            }

            DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
            contagem[0].dia = days[0].dia;
            contagem[0].mes = days[0].mes;
            contagem[0].ano = days[0].ano;
            contagem[1].dia = days[1].dia;
            contagem[1].mes = days[1].mes;
            contagem[1].ano = days[1].ano;

            faturacao_edificio += faturacao_estudio;                //soma faturação de todos os estudios
            RELATORIOS insert_relatorio = {0, node->id_edificio, vetor_estudio[i].id_estudio, 0, 0, num_dias, NULL, NULL, NULL, contagem, faturacao_estudio};
            relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
            num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);
        }
    } else{
        printf("Edificio %d nao possui estudios\n",node->id_edificio);
        return;

    }

    printRelatoriosEdificio("faturacao.txt", faturacao_edificio, days, 2);
}
/**
 * @param dia1 dia inicial
 * @param mes1 mes inicial
 * @param ano1 ano inicial
 * @param dia2 dia final
 * @param mes2 mes final
 * @param ano2 ano final
 * @param ordem tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 */

void faturacaoParqueEdificios(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, int ordem)
{
    relatorio = (RELATORIOS *)malloc(sizeof(RELATORIOS));
    if (ordem == 2)
    {
        printf("Ordenacao invalida\n");
        return;
    }

    num_relatorios = 0;
    double num_dias;
    double faturacao_parque = 0.0;
    num_dias = diferenca_de_dias(dia1, mes1, ano1, dia2, mes2, ano2);
    DIAS days[2] = {{dia1, mes1, ano1, 0, NULL}, {dia2, mes2, ano2, 0, NULL}};
    struct edificio *node = HeadEdificios;
    int i;
    while (node != NULL)
    {
        double faturacao_edificio = 0.0;
        double preco_base;
        ESTUDIO *vetor_estudio = node->vector_estudio;

        if (vetor_estudio != NULL)                                      //Se possuir estudios
        {
            for (i = 0; i < node->num_estudios; i++)
            {
                double faturacao_estudio = 0.0;
                preco_base = node->preco_m2 * vetor_estudio[i].area;
                MASTERAGENDA *agenda = vetor_estudio[i].agendaMaster;
                DIAS *vetor_dias = agenda->vector_dias;

                for (int j = 0; j < vetor_estudio[i].num_dias; j++)
                {
                    struct evento *eventos = vetor_dias[j].vector_evento;
                    while (eventos != NULL)
                    {
                        DATA *dias = eventos->datas;
                        if (eventos->id_cliente != -1)
                        {
                            double duracao = 0;
                            double preco_evento = 0.0;
                            DIAS aux_dias[2] = {{dias[0].dia, dias[0].mes, dias[0].ano, 0, NULL},{dias[1].dia, dias[1].mes, dias[1].ano, 0, NULL}};

                            if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[1]) == 1) //Dentro do limite(d2,d1)
                            {
                                duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao);
                                preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);
                            }
                            else
                            {

                                if (date_cmp(days[0], aux_dias[0]) == 1 && date_cmp(aux_dias[1], days[1]) == 1) //(f2,f1) Fora do limite (Estudio completamente ocupado durante este periodo de tempo) ocupacao=100%
                                {
                                    duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                    DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                    allDays = fillAllDays(allDays, aux_dias[0], aux_dias[1], (int)duracao + 2);
                                    preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 2);
                                }
                                else
                                {
                                    if (date_cmp(aux_dias[0], days[0]) == 1 && date_cmp(days[1], aux_dias[0]) == 1) //Limite direito
                                    {
                                        duracao = diferenca_de_dias(dias[0].dia, dias[0].mes, dias[0].ano, days[1].dia, days[1].mes, days[1].ano);
                                        DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                        allDays = fillAllDays(allDays, aux_dias[0], days[1], (int)duracao + 1);
                                        preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);
                                    }
                                    else
                                    {

                                        if (date_cmp(days[0], aux_dias[0]) == 1 &&date_cmp(aux_dias[1], days[0]) == 1) //Limite esquerdo
                                        {
                                            duracao = diferenca_de_dias(days[0].dia, days[0].mes, days[0].ano, dias[1].dia, dias[1].mes, dias[1].ano);
                                            DIAS *allDays = (DIAS *)malloc((int)duracao * 2 * sizeof(DIAS));
                                            allDays = fillAllDays(allDays, days[0], aux_dias[1], (int)duracao + 1);
                                            preco_evento = taxas(preco_base, allDays, vetor_estudio[i].id_estudio, eventos->id_evento, eventos->nome_plataforma, (int)duracao + 1);
                                        }
                                    }
                                }
                            }
                            faturacao_estudio += preco_evento;
                        }
                        eventos = eventos->nextEvento;
                    }
                }
                faturacao_edificio += faturacao_estudio;
            }
        }
        else{                                               //Caso não possua estudios
            faturacao_edificio = 0;
        }

        faturacao_parque += faturacao_edificio;

        DATA *contagem = (DATA *)malloc(2 * sizeof(DATA));
        contagem[0].dia = days[0].dia;
        contagem[0].mes = days[0].mes;
        contagem[0].ano = days[0].ano;
        contagem[1].dia = days[1].dia;
        contagem[1].mes = days[1].mes;
        contagem[1].ano = days[1].ano;

        RELATORIOS insert_relatorio = {0, node->id_edificio, 0, 0, 0, num_dias, NULL, NULL, NULL, contagem, faturacao_edificio};
        relatorio = (RELATORIOS *)realloc(relatorio, (num_relatorios + 1) * 100 + sizeof(RELATORIOS));
        num_relatorios = insert_sorted_relatorios(relatorio, insert_relatorio, num_relatorios, ordem);

        node = node->next;
    }
    printRelatoriosParqueEdificios("faturacao.txt", faturacao_parque, days, 2);                                             //Imprime o relatorio final
}

/**
 * Dado um intervalo de dia a função irá retornar um array preenchido com todos os dias entre esse intervalo
 * @param AllDays array vazio
 * @param d1 dia inicial
 * @param d2 dia final
 * @param num_dias intervalo de dias
 * @return array preenchido com o intervalo de dias
 */

DIAS *fillAllDays(DIAS *AllDays, DIAS d1, DIAS d2, int num_dias)
{

    int i = 0;
    DIAS NextDay = {d1.dia, d1.mes, d1.ano, 0, NULL};
    AllDays[0] = d1;
    for (i = 1; i <= num_dias; i++)
    {
        NextDay = next_day(NextDay);
        if (date_cmp(NextDay, d2) == 0) //Para nao ultrapassar o limite
        {
            break;
        }
        AllDays[i] = NextDay;
    }
    AllDays[i] = d2;
    return AllDays;
}
/**
 * Função que irá verificar se as politicas estão a ser respeitadas ou não
 * @param preco_base        preço base de cada estudio (preço por dia)
 * @param AllDays           array com todos os dias da estadia
 * @param id_estudio        id do estudio
 * @param id_evento         id do evento
 * @param nome_plataforma   nome da plataforma
 * @param num_dias          numero de dias
 * @return
 */
double taxas(double preco_base, DIAS *AllDays, int id_estudio, int id_evento, char *nome_plataforma, int num_dias)
{
    double preco_final = 1.0;
    ESTUDIO_POLITICA *vetor_estudio_politica = relacoes.estudio_politica;
    POLITICA *vetor_politica = relacoes.politicas;

    for (int i = 0; i < relacoes.num_relacoes - 1; i++)
    {
        if (vetor_estudio_politica[i].id_estudio == id_estudio) //Localiza estudio
        {
            for (int j = 0; j < relacoes.num_politicas - 1; j++)
            {
                if (strcmp(vetor_estudio_politica[i].nome_politica, vetor_politica[j].nome_politica) == 0 && strcmp(vetor_politica[j].plataforma, nome_plataforma) == 0) //Ve a politica do estudio e compara com a plataforma do evento
                {
                    printf("\nEvento %d respeita politica %s pois foi reservado na plataforma %s\n", id_evento, vetor_politica[j].nome_politica, nome_plataforma);
                    preco_final = aplicar_taxas(preco_base, vetor_politica[j].regras, vetor_politica[j].num_regras, vetor_estudio_politica[i].taxas, AllDays, num_dias);
                    return preco_final;
                }
            }
        }
    }
    return preco_base * num_dias; //Caso n lhe seja aplicada nenhuma politica irá retornar o preco pelo n de dias (preco_base*m2);
}

/**
 * Função que irá aplicar taxas no preço base/dia do estudio e irá retornar o valor final da estadia
 * @param preco preço   base de um dado estudio (preço por dia)
 * @param array_regras  array de regras da politica
 * @param num_regras    numero de regras da politica
 * @param array_taxas   array de taxas do estudio
 * @param AllDays       array com todos os dias da estadia
 * @param num_dias      numero de dias da estadia
 * @return              valor com descontos/taxas
 */

double aplicar_taxas(double preco, int *array_regras, int num_regras, double *array_taxas, DIAS *AllDays, int num_dias)
{
    double preco_base_dia = preco, preco_base_dia_taxa = preco, preco_por_dia_especial=0;
    double preco_com_taxas = 0;
    int j = 0, d = 0;
    for (int i = 0; i < num_regras; i++) //um if para cada regra
    {
        int dia_especial=0,dia_fds=0;
        for (d = 0; d < num_dias; d++) //Primeriamente irá colocar preços nos dias "especiais"
        {
            if (array_regras[i] == 1) //Se for ao fim de semana
            {
                int dia_semana;
                dia_semana = dayofweek(AllDays[d].dia, AllDays[d].mes, AllDays[d].ano);
                if (dia_semana == 0 || dia_semana == 6)
                {
                    dia_fds++;
                    preco_com_taxas += (preco_base_dia + preco_base_dia * array_taxas[j]); // Preço do dia ao fds 12
                   /* printf("%0.2f- %0.2f\n",preco_com_taxas,preco_base_dia*dia_fds);
                    printf("%d\n",dia_fds);*/
                }
                preco_por_dia_especial=preco_com_taxas-preco_base_dia*dia_fds;             //Valor a mais pelo dia ser ao fds 2
            }
         /* if (array_regras[i] == 4)       //Se for em epoca especial (Ferias de verão por exemplo)
            {
                int dia_do_ano;
                dia_do_ano = dayOfyear(AllDays[d].dia, AllDays[d].mes, AllDays[d].ano);
                printf("%d\n",dia_do_ano);
                if (dia_do_ano > 153 && dia_do_ano < 244) //Periodo de ferias (Junho/Julho/Agosto
                {
                    dia_especial++;
                   // preco_com_taxas += (preco_base_dia + preco_base_dia * array_taxas[j]); // Preço do dia ao fds 12
                    printf("|%0.2f- %0.2f\n",preco_com_taxas,preco_base_dia);
                    printf("|%d\n",dia_especial);
                  //  preco_por_dia_especial=preco_com_taxas-preco_base_dia*dia_especial;             //Valor a mais pelo dia ser ao fds 2
                }
            }*/
        }
        j++;
    }
    j = 0;
    for (int i = 0; i < num_regras; i++)                    //preço de um dia aplicando TODAS as taxas
    {
        if (array_regras[i] == 2)
        {
            preco_base_dia_taxa += preco_base_dia * array_taxas[j];
        }
        if (array_regras[i] == 3)
        {
            preco_base_dia_taxa += preco_base_dia * array_taxas[j];
        }
        if (array_regras[i] == 4)
        {
            if (d > DIAS_DESCONTO)
            {
                preco_base_dia_taxa += preco_base_dia * array_taxas[j];
            }
        }
        if (array_regras[i] == 5)
        {
            preco_base_dia_taxa += preco_base_dia * array_taxas[j];
        }
        if (array_regras[i] == 7)
        {
            preco_base_dia_taxa += preco_base_dia * array_taxas[j];
        }
        j++;
    }

    preco_com_taxas = (preco_base_dia_taxa * num_dias)+preco_por_dia_especial;
    //printf("%0.2f= (%0.2f x %d) + %0.2f\n",preco_com_taxas,preco_base_dia_taxa,num_dias,preco_por_dia_especial);
    return preco_com_taxas;
}

/**
 * Função que retorna o proximo de dia de um dia inserido
 * @param Dia dia inserido
 * @return Proximo dia do dia inserido
 */

DIAS next_day(DIAS Dia)
{
    int dia = Dia.dia;
    int mes = Dia.mes;
    int ano = Dia.ano;
    DIAS NextDay = {0, 0, 0, 0, NULL};

    if (mes == 2)       //Caso especial de fevereiro
    {
        if (dia == 28)
        {
            if (((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) //Ano bisexto
            {
                dia = 29;
                mes = 2;
            }
            else
            {
                dia = 1;
                mes = mes + 1;
            }
            NextDay.dia = dia;
            NextDay.mes = mes;
            NextDay.ano = ano;
            return NextDay;
        }
        if (dia == 29)
        {
            dia = 1;
            mes = mes + 1;
            NextDay.dia = dia;
            NextDay.mes = mes;
            NextDay.ano = ano;
            return NextDay;
        }
    }

    if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10) && //Meses com 31 dias
        dia == 31)
    {
        dia = 1;
        mes = mes + 1;
        NextDay.dia = dia;
        NextDay.mes = mes;
        NextDay.ano = ano;
        return NextDay;
    }
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 10 || mes == 11) && dia == 30) //Meses com 30 dias
    {
        dia = 1;
        mes = mes + 1;
        NextDay.dia = dia;
        NextDay.mes = mes;
        NextDay.ano = ano;
        return NextDay;
    }
    if (mes == 12 && dia == 31)                 //Caso especial do ultimo dia do ano
    {

        ano = ano + 1;
        dia = 1;
        mes = 1;
        NextDay.dia = dia;
        NextDay.mes = mes;
        NextDay.ano = ano;
        return NextDay;
    }
                                                //Caso nao seja nenhuma caso especial, apenas soma um dia
    dia = dia + 1;
    NextDay.dia = dia;
    NextDay.mes = mes;
    NextDay.ano = ano;
    return NextDay;
}

/**
 * Função para ver qual é o dia do ano (auxilia nas regras)
 * @param d dia
 * @param m mes
 * @param y ano
 * @return retorna o dia da semana (0-domingo até 6-sabado)
 */

int dayofweek(int d, int m, int y)
{
    int t[] = {0, 3, 2, 5, 0, 3,
               5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 +
            y / 400 + t[m - 1] + d) %
           7;
}

/**
 * Função responsavel para ver qual o dia do ano (auxilia nas regras)
 * @param day - dia
 * @param mon - mes
 * @param year - ano
 * @return retorna o dia do ano (0 até 365/366)
 */

int dayOfyear(int day, int mon, int year)
{
    int  days_in_feb = 28, doy;    // day of year
    doy = day;

    if( (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0) )
    {
        days_in_feb = 29;
    }
    switch(mon)
    {
        case 2:
            doy += 31;
            break;
        case 3:
            doy += 31+days_in_feb;
            break;
        case 4:
            doy += 31+days_in_feb+31;
            break;
        case 5:
            doy += 31+days_in_feb+31+30;
            break;
        case 6:
            doy += 31+days_in_feb+31+30+31;
            break;
        case 7:
            doy += 31+days_in_feb+31+30+31+30;
            break;
        case 8:
            doy += 31+days_in_feb+31+30+31+30+31;
            break;
        case 9:
            doy += 31+days_in_feb+31+30+31+30+31+31;
            break;
        case 10:
            doy += 31+days_in_feb+31+30+31+30+31+31+30;
            break;
        case 11:
            doy += 31+days_in_feb+31+30+31+30+31+31+30+31;
            break;
        case 12:
            doy += 31+days_in_feb+31+30+31+30+31+31+30+31+30;
            break;
    }
    return doy;
}

/**
 * Função responsavel pela ordenação dos relatorios
 * @param relatorios - array de relatorios
 * @param inserted_relatorio - relatorio inserido
 * @param n - tamannho do array de relatorios inicial
 * @param order - tipo de ordenação (0->ordem crescete do dado|1->ordem decrescente do dado|2->ordem de estudio|3->ordem de edificio)
 * @return
 */

int insert_sorted_relatorios(RELATORIOS *relatorios, RELATORIOS inserted_relatorio, int n, int order)
{
    int i;
    if (order == 0)
    {
        for (i = n - 1; (i >= 0 && relatorios[i].dado >= inserted_relatorio.dado); i--)
        {
            relatorios[i + 1] = relatorios[i];
        }
        relatorios[i + 1] = inserted_relatorio;
    }
    if (order == 1)
    {
        for (i = n - 1; (i >= 0 && relatorios[i].dado <= inserted_relatorio.dado); i--)
        {
            relatorios[i + 1] = relatorios[i];
        }
        relatorios[i + 1] = inserted_relatorio;
    }
    if (order == 2)
    {
        for (i = n - 1; (i >= 0 && relatorios[i].estudio >= inserted_relatorio.estudio); i--)
        {
            relatorios[i + 1] = relatorios[i];
        }
        relatorios[i + 1] = inserted_relatorio;
    }
    if (order == 3)
    {
        for (i = n - 1; (i >= 0 && relatorios[i].edificio >= inserted_relatorio.edificio); i--)
        {
            relatorios[i + 1] = relatorios[i];
        }
        relatorios[i + 1] = inserted_relatorio;
    }
    return (n + 1);
}

/**
 * @param filename - nome do ficheiro
 * @param estatistica - estatistica final do estudio
 * @param days - intervalo de dias do relatorio
 * @param dado - tipo de dado (dado=1->opucaçao|dado=2->faturacao)
 */

void printRelatoriosEstudio(char *filename, double estatistica, DIAS *days, int dado)
{
    FILE *file = fopen(filename, "a");
    int i = 0;
    RELATORIOS *vetor_relatorio = relatorio;
    if (dado == 1)
    {
        printf("Relatorio de Ocupacao do Estudio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n", vetor_relatorio[i].estudio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de Ocupacao do Estudio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n", vetor_relatorio[i].estudio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    else
    {
        printf("Relatorio de faturacao do Estudio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n", vetor_relatorio[i].estudio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de faturacao do Estudio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n", vetor_relatorio[i].estudio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    for (i = 0; i < num_relatorios; i++)
    {

        DATA *datas_evento = vetor_relatorio[i].dias_eventos, *datas_contagem = vetor_relatorio[i].dias_contagem;
        printf("\nID Evento: %d | ID Client: %d | Nome cliente: %s | Nome evento: %s |\nPeriodo do evento: %d/%d/%d(%0.2f)-%d/%d/%d(%0.2f) | Periodo analisado: %d/%d/%d-%d/%d/%d \n",
               vetor_relatorio[i].evento, vetor_relatorio[i].id_cliente, vetor_relatorio[i].nome_cliente,
               vetor_relatorio[i].nome_evento, datas_evento[0].dia, datas_evento[0].mes, datas_evento[0].ano,
               datas_evento[0].horas_minutos, datas_evento[1].dia, datas_evento[1].mes, datas_evento[1].ano,
               datas_evento[1].horas_minutos, datas_contagem[0].dia, datas_contagem[0].mes, datas_contagem[0].ano,
               datas_contagem[1].dia, datas_contagem[1].mes, datas_contagem[1].ano);
        fprintf(file, "\nID Evento: %d | ID Client: %d | Nome cliente: %s | Nome evento: %s |\nPeriodo do evento: %d/%d/%d(%0.2f)-%d/%d/%d(%0.2f) | Periodo de analisado: %d/%d/%d-%d/%d/%d \n",
                vetor_relatorio[i].evento, vetor_relatorio[i].id_cliente, vetor_relatorio[i].nome_cliente,
                vetor_relatorio[i].nome_evento, datas_evento[0].dia, datas_evento[0].mes, datas_evento[0].ano,
                datas_evento[0].horas_minutos, datas_evento[1].dia, datas_evento[1].mes, datas_evento[1].ano,
                datas_evento[1].horas_minutos, datas_contagem[0].dia, datas_contagem[0].mes, datas_contagem[0].ano,
                datas_contagem[1].dia, datas_contagem[1].mes, datas_contagem[1].ano);

        if (dado == 1)
        {
            printf("Ocupacao: %0.0f dias\n", vetor_relatorio[i].dado);
            fprintf(file, "Ocupacao: %0.0f dias\n", vetor_relatorio[i].dado);
        }
        else
        {
            printf("Faturacao: %0.2f euros\n", vetor_relatorio[i].dado);
            fprintf(file, "Faturacao: %0.2f euros\n", vetor_relatorio[i].dado);
        }
    }
    i = 0;
    if (dado == 1)
    {
        printf("\nO Estudio %d possui uma taxa de ocupacao de %0.2f %%\n\n", vetor_relatorio[i].estudio, estatistica);
        fprintf(file, "\nO Estudio %d possui uma taxa de ocupacao de %0.2f %%\n", vetor_relatorio[i].estudio, estatistica);
    }
    else
    {
        printf("\nO Estudio %d possui uma faturacao de %0.2f euros\n\n", vetor_relatorio[i].estudio, estatistica);
        fprintf(file, "\nO Estudio %d possui uma faturacao de %0.2f euros\n", vetor_relatorio[i].estudio, estatistica);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

/**
 * Função responsavel pelo print no ecra e no ficheiro dos relatorios de ocupação e faturação de um dado edificio
 * @param filename - nome do ficheiro
 * @param estatistica - estatitica final da função
 * @param days - dias da pesquisa do relatorio
 * @param dado - tipo de dado (1->ocupação/2->faturação)
 */

void printRelatoriosEdificio(char *filename, double estatistica, DIAS *days, int dado) //dado=1->opucaçao|dado=2->faturacao
{
    FILE *file = fopen(filename, "a");
    int i = 0;
    RELATORIOS *vetor_relatorio = relatorio;
    if (dado == 1)
    {
        printf("Relatorio de Ocupacao do Edificio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", vetor_relatorio[i].edificio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de Ocupacao do Edificio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", vetor_relatorio[i].edificio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    else
    {

        printf("Relatorio de faturacao do Edificio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", vetor_relatorio[i].edificio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de faturacao do Edificio %d\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", vetor_relatorio[i].edificio, days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    for (i = 0; i < num_relatorios; i++)
    {
        printf("Estudio %d: ", vetor_relatorio[i].estudio);
        fprintf(file, "Estudio %d: ", vetor_relatorio[i].estudio);

        if (dado == 1)
        {
            printf(" %0.2f %%\n", vetor_relatorio[i].dado);
            fprintf(file, " %0.2f %%\n", vetor_relatorio[i].dado);
        }
        else
        {
            printf("%0.2f euros\n", vetor_relatorio[i].dado);
            fprintf(file, "%0.2f euros\n", vetor_relatorio[i].dado);
        }
    }
    i = 0;
    if (dado == 1)
    {
        printf("\nO Edificio %d possui uma taxa de ocupacao de %0.2f %%\n\n", vetor_relatorio[i].edificio, estatistica);
        fprintf(file, "\nO Edificio %d possui uma taxa de ocupacao de %0.2f %%\n", vetor_relatorio[i].edificio, estatistica);
    }
    else
    {
        printf("\nO Edificio %d possui uma faturacao de %0.2f euros\n\n", vetor_relatorio[i].edificio, estatistica);
        fprintf(file, "\nO Edifico %d possui uma faturacao de %0.2f euros\n", vetor_relatorio[i].edificio, estatistica);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

/**
 * Função responsavel pelo print no ecra e no ficheiro dos relatorios de ocupação e faturação do parque de edificios
 * @param filename - nome do ficheiro
 * @param estatistica - estatitica final da função
 * @param days - dias da pesquisa do relatorio
 * @param dado - tipo de dado (1->ocupação/2->faturação)
 */

void printRelatoriosParqueEdificios(char *filename, double estatistica, DIAS *days, int dado) //dado=1->opucaçao|dado=2->faturacao
{
    FILE *file = fopen(filename, "a");
    int i = 0;
    RELATORIOS *vetor_relatorio = relatorio;
    if (dado == 1)
    {
        printf("Relatorio de Ocupacao do Parque de Edificios:\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de Ocupacao do Parque de  Edificios:\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    else
    {
        printf("Relatorio de faturacao do Parque de edificios Edificio:\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
        fprintf(file, "Relatorio de faturacao do Parque de edificios:\nPeriodo do relatorio: %d/%d/%d - %d/%d/%d\n\n", days[0].dia, days[0].mes, days[0].ano, days[1].dia, days[1].mes, days[1].ano);
    }
    for (i = 0; i < num_relatorios; i++)
    {
        printf("Edificio %d: ",vetor_relatorio[i].edificio);
        fprintf(file, "Edificio %d: ",vetor_relatorio[i].edificio);

        if (dado == 1)
        {
            printf(" %0.2f %%\n", vetor_relatorio[i].dado);
            fprintf(file, " %0.2f %%\n", vetor_relatorio[i].dado);
        }
        else
        {
            printf("%0.2f euros\n", vetor_relatorio[i].dado);
            fprintf(file, "%0.2f euros\n", vetor_relatorio[i].dado);
        }
    }
    if (dado == 1)
    {
        printf("\nO Parque de Edificios possui uma taxa de ocupacao de %0.2f %%\n\n", estatistica);
        fprintf(file, "\nO Parque de Edificios possui uma taxa de ocupacao de %0.2f %%\n", estatistica);
    }
    else
    {
        printf("\nO Parque de Edificios possui uma faturacao de %0.2f euros\n\n", estatistica);
        fprintf(file, "\nO Parque de Edificios possui uma faturacao de %0.2f euros\n", estatistica);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}


 /**
  * Função que limpa um ficheiro (deixa o em branco)
  * @param filename - nome do ficheiro a ser limpado
  */
void reset_file(char *filename)
{
    fclose(fopen(filename, "w"));
}
