#ifndef PROJETOLP1AED1_PROJETO_H
#define PROJETOLP1AED1_PROJETO_H

typedef struct data
{
    int dia;
    int mes;
    int ano;
    double horas_minutos;
}DATA;

typedef  struct evento
{
    int id_evento,id_cliente;               //Cliente que reservou o estudio para aquele evento
    char *nome_cliente;                     //Nome do cliente
    char *nome_evento;                      //Nome do evento
    char *nome_plataforma;                  //Nome da plataforma onde foi feito a reserva para o evento
    struct evento *nextEvento;              //Proximo evento daquele dia
    DATA *datas;                            //datas[0]->Data inicio | datas[1]->Data fim;
}EVENTO;

typedef  struct dias                         //Array de dias que possui a data inicial de cada evento
{
    int dia;
    int mes;
    int ano;
    int num_eventos;                         //Numero de evento de um dado dia
    struct evento *vector_evento;

}DIAS;

typedef struct masteragenda                   //Agenda que possui todas os eventos, limpezas, manutenção , tudo.
{
    DIAS *vector_dias;
}MASTERAGENDA;

typedef struct branchcalendar                  //Possui apenas os eventos relacionados a estadias assim como as plataformas onde foram feitas as reservas
{
    char *nome_plataforma;                     //Nome da plataforma
    int num_dias;                              //Numero de dias
    DIAS *vector_dias;
}BRANCHCALENDER;


typedef struct  estudio
{
    int id_estudio;                             //Id do estudio(unico)
    char *tipo;                                 //Configuração de cada estudio
    int area;                                   //Area do estudio
    int num_dias;                               //Numero de dias diferentes para os diversos eventos
    int num_plat;                               //Numero de plataformas onde esta estudio foi alugado
    MASTERAGENDA *agendaMaster;                 //Agenda Master
    BRANCHCALENDER *calender;                   //BranchCalender

}ESTUDIO;

typedef struct edificio
{
    int id_edificio;                            //Id do idificio (Unico)
    char *nome;                                 //Nome do edificio
   double latitude;
    double longitude;
    char *morada;
    double preco_m2;                            //Preço por metro quadrado
    int num_estudios;                           //Numero de edificios
    struct edificio *next;                      //Apontador para proximo edificio
    ESTUDIO *vector_estudio;                    //Vector com todos os estudios de um dado edificio.
}EDIFICIO;

typedef  struct estadias_historico
{
    int id_estadia;                             //Id do evento
    char * nome_evento;                         //Nome do evento
    DATA *data;                                 //Datas do evento
    struct  estadias_historico *pnext_estadia;  //Apontador para proxima estadia

}ESTADIAS_HISTORICO;

 typedef struct historico
 {
     int id_cliente;                            //id do cliente(unico)
     char *nome_cliente;                        //Nome do cliente
     int num_estadias;                          //Numero de estadias
     struct  estadias_historico *pfirst_estadia;//Apontadar por a lista ligada de estadias
     struct historico * pnext;                  //Apontador para proximo cliente no historico
 }HISTORICO;

typedef struct estudio_politica                 //Array de Relações Estudio-Politica
{
    int id_estudio;                             //Id do estudio
    char *nome_politica;                        //Nome da politica
    int num_taxas;                              //Numero de taxas
   double *taxas;                               //Taxas

}ESTUDIO_POLITICA;

typedef struct politicas                        //Array de Politicas
{
    char *nome_politica;                        //Nome da politica
    char *plataforma;                           //Nome da plataforma
    int num_regras;                             //Numero de Regras
    int *regras;                                //Array de regras
}POLITICA;

typedef struct regras                           //Array de Regras
{
    int id;                                     //Id da regras (Unico)
    char *regra;                                //Regra

}REGRAS;

typedef  struct PortoFlats                      //Estrutura que possui todas as relações sobre regras, estudios, politicas
{
    int num_regras;                             //Numero de regras global
    int num_politicas;                          //Numero de politicas global
    int num_relacoes;                           //Numero de relações Estudio-Politica global
    REGRAS *regras;                             //Array de regras
    POLITICA  *politicas;                       //Array de politicas
    ESTUDIO_POLITICA *estudio_politica;         //Array de relações

}PORTOFLATS;

typedef struct relatorios                       //Array para o auxilio da geração de relatorios de ocupação/faturamento
{
    int porto_flats;
    int edificio;                               //Id do edificio
    int estudio;                                //Id do estudio
    int evento;                                 //Id do evento
    int id_cliente;                             //Id do cliente
    double duracao_evento;                      //Duração do evento
    char *nome_cliente;                         //Nome do cliente
    char *nome_evento;                          //Nome do evento
    DATA *dias_contagem;                        //Dias para a geração do relatorio
    DATA *dias_eventos;                         //Dias do evento
    double dado;                                //Dado em conta (Faturação/ocupação)

}RELATORIOS;

int main_projeto(int argc, char * argv);
void init();
/*Funções de inserção*/
void insert_regra(int id_regra,char *regra,int flag);
void insert_politica(char *nome_politica,char *plataforma, int *vregras,int num_regras,int flag);
void insert_edificio(struct edificio **head, struct edificio *no, int id, char *nome_edificio, double latitude, double longitude,char *morada, double precom2,int flag);
void insert_estudio(struct edificio *no, int id_estudio, int id_edificio,char *tipo, int m2, int flag);
void insert_evento(struct edificio *no, int id_estudio, DATA *days, int id_evento, int id_cliente, char *nome_cliente , char *nome_evento, char *nome_plataforma, int flag);
void insert_historico(struct historico **head, struct historico *no,long int id_cliente, char* nome_cliente,char* nome_evento, int id_estadia, DATA *reserva);
void insert_politica_estudio(int estudio,char *nome_politica, double *vtaxas,int num_taxas,int flag);
ESTADIAS_HISTORICO* insert_eventos_historico(struct historico *no, int id_estadia, char *nome_evento, DATA *reserva);
/*Funções de leitura de ficheiro*/
void read_edificios_from_file(char *filename);
void read_estudios_from_file(char *filename);
void read_eventos_from_file(char *filename);
void read_regras_from_file(char *filename);
void read_politicas_from_file(char *filename);
void read_estudio_politicas_from_file(char *filename);
/*Funções de Inserir em ficheiro*/
void insert_edificios_to_file(char *filename, int id, char *nome_edificio, double latitude, double longitude,char *morada, double precom2);
void insert_estudios_to_file(char*filename,int id_estudio, int id_edificio,char *tipo, int m2);
void insert_regras_to_file(char*filename,int id_regra,char *nome);
void insert_eventos_to_file(char *filename, int id_evento,char *nome , DATA *day,int id_cliente, char *nome_cliente, int estudio_id, char *plataforma);
void insert_politicas_to_file(char*filename,char *nome,char *nome_plataforma,int num_regras, int *regras);
void insert_estudio_politicas_to_file(char*filename,int id_estudio,char *nome_politica,int num_taxas, double *taxas);
/*Funções de Pesquisa*/
int checkDay(DIAS *dias, int l, int r, DATA dia);
int checkEvento(int id_evento);
int checkPolitica(POLITICA *vetor_politica, int l, int r, char *nome_polica);//
int checkPlataforma(BRANCHCALENDER *calendario, int l, int r, char *nome_plataforma);//
int *find_estudio(int id_estudio);//
int binarySearch_estudio(ESTUDIO *vector_estudio, int l, int r, int id_estudio);//
int binarySearch_regras(REGRAS *vetor_regras, int l, int r, int id_regra);//
int checkEstudioPolitica(ESTUDIO_POLITICA *vetor_politica_estudio, int  id_estudio,char *politica);//sequencial
void find_estudio_by_id(int id_estudio);
/*Funções de remoção*/
void remove_edificio(struct edificio **head,int id_edificio);
void remove_evento(int id_evento);
void remove_estudio(int id_estudio);
void remove_hospede(struct historico **head,int id_cliente);
void remove_regra(int id_regra);
void remove_politica(char *nome);
void remove_estudio_politica(int estudio, char *nome);
/*Funções de Alteração*/
void alterar_edificio(int id_edificio, char *new_nome, char *new_morada,double new_preco_m2, double new_latitude, double new_longitude);
void alterar_regra(int id_regra,char *new_regra);
void alterar_politica(char *nome,char *new_plataforma, int num_regras, int *array);
void alterar_estudio_politica(int estudio, char *nome, int new_estudio, char *new_politica, int num_taxas, double *taxas);
void alterar_estudio(int id_estudio, char *new_tipo, int area);
void alterar_evento(int id_evento, char *new_nome_evento);
/*Funções de inserção ordenada*/
int insert_day_sorted(DIAS *dias,DIAS dia,int n);
int insert_plataform_sorted(BRANCHCALENDER *plataformas,BRANCHCALENDER plataforma,int n);
int insert_estudio_sorted(ESTUDIO *vetor_estudios,ESTUDIO estudio,int n);
int insert_regra_sorted(REGRAS *vetor_regra, REGRAS regra, int n);
int insert_estudio_politica_sorted(ESTUDIO_POLITICA *vetor_estudiopolitica, ESTUDIO_POLITICA estudio_politica, int n);
int insert_politica_sorted(POLITICA *vetor_politica, POLITICA politica, int n);
int insert_sorted_relatorios(RELATORIOS *relatorios, RELATORIOS inserted_relatorio, int n, int order);
/*Funções de print*/
void printEverything();
void printEdificios();
void printEventos();
void printReservas();
void printEstudios();
void printHistorico();
void printRegras();
void printPoliticas();
void printTaxas();
void printRelatoriosEstudio(char *filename,double estatistica,DIAS *days,int dado);
void printRelatoriosEdificio(char *filename,double estatistica, DIAS *days,int dado);
void printRelatoriosParqueEdificios(char *filename,double estatistica, DIAS *days,int dado);
/*Funções de ocupação*/
void ocupacaoEstudio(int estudio,int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int ordem);
void ocupacaoEdificio(int estudio,int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int ordem);
void ocupacaoParqueEdificios(int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int ordem);
/*Funções de Faturação*/
void faturacaoEstudio(int estudio,int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int ordem);
void faturacaoEdificio(int estudio,int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int odem);
void faturacaoParqueEdificios(int dia1,int mes1, int ano1,int dia2,int mes2, int ano2,int ordem);
/*Função de resolverColisões*/
double disponivel(int id_estudio,int dia1,int mes1, int ano1,int dia2,int mes2, int ano2);
/*Funções Auxiliares*/
int date_cmp(DIAS d1, DIAS d2);
double diferenca_de_dias(int dia1,int mes1, int ano1, int dia2, int mes2,int ano2);
double taxas(double preco_base,DIAS *AllDays,int id_estudio,int id_evento,char *nome_plataforma,int num_dias);
DIAS *fillAllDays(DIAS *AllDays,DIAS d1,DIAS d2, int num_dias);
double aplicar_taxas(double preco, int *array_regras,int num_regras, double *array_taxas,DIAS *AllDays,int num_dias);
DIAS next_day(DIAS Dia);
int dayofweek(int d, int m, int y);
int dayOfyear(int day,int mon, int year);
int *newIntArray(int M);
int *stringToarray(int *a, char *string);
double *stringToDoublearray(double *a, char *string);
void reset_file(char *filename);

#endif //PROJETOLP1AED1_PROJETO_H
