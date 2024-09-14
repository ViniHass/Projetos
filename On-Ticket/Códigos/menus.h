#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "usuarios.h"
#include "reserva.h"
#include "Ordenacao.h"
#include "Busca.h"
//imprime na tela as opçoes de login
//1 faz login
//2 faz cadastro de usuarios
//encerra programa
void printLogin();
//processa o login conforme o comando dado pelo usuario
int login( ListaUsers *users, ListaUsers *admins, TipoUser *usuario );

//feito o login como usuario comum esta tela deverá aparecer
//mostrando as opçoes do usuario
//1 mostra shows
//2 consulta reservas
//3 altera dados cadastrais
//4 faz logoff do sistema
void printMenuUsuario();
//processa a escolha feito pelo usuario logado
int MenuUsuario( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos, ReservasUser reserva[]);

//caso o usuario tenha escolhido alterar os dados aparece este menu
//1 para alterar o nome
//2 para alerar senha
//3 para retornar ao Menu
void printMenuAlteraDados();
//processa a escolha de dados da alteração de dados
// é possivel alterar o nome e senhas cadastrados
void MenuAlteraDados( TipoUser *usuario );

//feito o login como usuario comum esta tela deverá aparecer
//mostrando as opçoes do usuario
//1 cadastra show
//2 disponibiliza ingressos
//3 deleta contas
//4 faz logoff do sistema
void printMenuAdmin();
//processa a escolha feito pelo usuario logado caso ele seja admin
int MenuAdmin( TipoUser *usuario, ListaUsers *users ,ListaShows *shows, ListaIngressos *ingressos, ReservasUser reserva[]);

void printMenuCadastraShow();

void MenuCadastraShow( TipoUser *usuario , ListaShows *shows, ListaIngressos *ingressos);

void printMenuOrdenacao();

void MenuOrdenacao( ListaUsers *users );

void printMenuBusca();

void MenuBusca( ListaUsers *users );

#endif