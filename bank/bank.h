/*
 * The Bank takes commands from stdin as well as from the ATM.  
 *
 * Commands from stdin be handled by bank_process_local_command.
 *
 * Remote commands from the ATM should be handled by
 * bank_process_remote_command.
 *
 * The Bank can read both .card files AND .pin files.
 *
 * Feel free to update the struct and the processing as you desire
 * (though you probably won't need/want to change send/recv).
 */

#ifndef __BANK_H__
#define __BANK_H__

#include "util/list.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


typedef struct _Bank
{
    // Networking state
    int sockfd;
    struct sockaddr_in rtr_addr;
    struct sockaddr_in bank_addr;

    // Protocol state
    // TODO add more, as needed
    List *pin_bal;
    List *usr_pin;
	List *pin_usr;
    FILE *init;
} Bank;

Bank* bank_create();
void bank_free(Bank *bank);
ssize_t bank_send(Bank *bank, char *data, size_t data_len);
ssize_t bank_recv(Bank *bank, char *data, size_t max_data_len);
void bank_process_local_command(Bank *bank, char *command, size_t len);
void bank_process_remote_command(Bank *bank, char *command, size_t len);
int username_is_valid(char *username);
int user_exists(char *username);
int valid_pin(char *pin);
int valid_balanceamt_input(char *balance);
int contains_nondigit(char *str);
void send_invalid(Bank *bank);
void send_s(Bank *bank);
void send_ng(Bank *bank);
void send_une(Bank *bank);
void send_ce(Bank *bank);
void send_bal(Bank *bank, char *bal);
int get_bal(Bank *bank, char *username);
int decrypt_and_verify(char* msg, char  *enc);
int encrypt_and_sign(char *enc, char *dec);
void get_salt(char *salt);

#endif

