/* tox.c
 *
 * The Tox public API.
 *
 *  Copyright (C) 2013 Tox project All Rights Reserved.
 *
 *  This file is part of Tox.
 *
 *  Tox is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Tox is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Tox.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Messenger.h"

#define __TOX_DEFINED__
typedef struct Messenger Tox;

#include "tox.h"

/*
 * returns a FRIEND_ADDRESS_SIZE byte address to give to others.
 * Format: [client_id (32 bytes)][nospam number (4 bytes)][checksum (2 bytes)]
 *
 */
void tox_getaddress(Tox *tox, uint8_t *address)
{
    Messenger *m = tox;
    getaddress(m, address);
}

/*
 * Add a friend.
 * Set the data that will be sent along with friend request.
 * address is the address of the friend (returned by getaddress of the friend you wish to add) it must be FRIEND_ADDRESS_SIZE bytes. TODO: add checksum.
 * data is the data and length is the length.
 *
 *  return the friend number if success.
 *  return FA_TOOLONG if message length is too long.
 *  return FAERR_NOMESSAGE if no message (message length must be >= 1 byte).
 *  return FAERR_OWNKEY if user's own key.
 *  return FAERR_ALREADYSENT if friend request already sent or already a friend.
 *  return FAERR_UNKNOWN for unknown error.
 *  return FAERR_BADCHECKSUM if bad checksum in address.
 *  return FAERR_SETNEWNOSPAM if the friend was already there but the nospam was different.
 *  (the nospam for that friend was set to the new one).
 *  return FAERR_NOMEM if increasing the friend list size fails.
 */
int tox_addfriend(Tox *tox, uint8_t *address, uint8_t *data, uint16_t length)
{
    Messenger *m = tox;
    return m_addfriend(m, address, data, length);
}

/* Add a friend without sending a friendrequest.
 *
 *  return the friend number if success.
 *  return -1 if failure.
 */
int tox_addfriend_norequest(Tox *tox, uint8_t *client_id)
{
    Messenger *m = tox;
    return m_addfriend_norequest(m, client_id);
}

/*  return the friend id associated to that client id.
 *  return -1 if no such friend.
 */
int tox_getfriend_id(Tox *tox, uint8_t *client_id)
{
    Messenger *m = tox;
    return getfriend_id(m, client_id);
}

/* Copies the public key associated to that friend id into client_id buffer.
 * Make sure that client_id is of size CLIENT_ID_SIZE.
 *
 *  return 0 if success.
 *  return -1 if failure.
 */
int tox_getclient_id(Tox *tox, int friend_id, uint8_t *client_id)
{
    Messenger *m = tox;
    return getclient_id(m, friend_id, client_id);
}

/* Remove a friend. */
int tox_delfriend(Tox *tox, int friendnumber)
{
    Messenger *m = tox;
    return m_delfriend(m, friendnumber);
}

/* Checks friend's connecting status.
 *
 *  return 1 if friend is connected to us (Online).
 *  return 0 if friend is not connected to us (Offline).
 *  return -1 on failure.
 */
int tox_get_friend_connectionstatus(Tox *tox, int friendnumber)
{
    Messenger *m = tox;
    return m_get_friend_connectionstatus(m, friendnumber);
}

/* Checks if there exists a friend with given friendnumber.
 *
 *  return 1 if friend exists.
 *  return 0 if friend doesn't exist.
 */
int tox_friend_exists(Tox *tox, int friendnumber)
{
    Messenger *m = tox;
    return m_friend_exists(m, friendnumber);
}

/* Send a text chat message to an online friend.
 *  return the message id if packet was successfully put into the send queue.
 *  return 0 if it was not.
 *
 *  You will want to retain the return value, it will be passed to your read_receipt callback
 *  if one is received.
 *  m_sendmessage_withid will send a message with the id of your choosing,
 *  however we can generate an id for you by calling plain m_sendmessage.
 */
uint32_t tox_sendmessage(Tox *tox, int friendnumber, uint8_t *message, uint32_t length)
{
    Messenger *m = tox;
    return m_sendmessage(m, friendnumber, message, length);
}

uint32_t tox_sendmessage_withid(Tox *tox, int friendnumber, uint32_t theid, uint8_t *message, uint32_t length)
{
    Messenger *m = tox;
    return m_sendmessage_withid(m, friendnumber, theid, message, length);
}

/* Send an action to an online friend.
 *
 *  return the message id if packet was successfully put into the send queue.
 *  return 0 if it was not.
 *
 *  You will want to retain the return value, it will be passed to your read_receipt callback
 *  if one is received.
 *  m_sendaction_withid will send an action message with the id of your choosing,
 *  however we can generate an id for you by calling plain m_sendaction.
 */
uint32_t tox_sendaction(Tox *tox, int friendnumber, uint8_t *action, uint32_t length)
{
    Messenger *m = tox;
    return m_sendaction(m, friendnumber, action, length);
}

uint32_t tox_sendaction_withid(Tox *tox, int friendnumber, uint32_t theid, uint8_t *action, uint32_t length)
{
    Messenger *m = tox;
    return m_sendaction_withid(m, friendnumber, theid, action, length);
}

/* Set our nickname.
 * name must be a string of maximum MAX_NAME_LENGTH length.
 * length must be at least 1 byte.
 * length is the length of name with the NULL terminator.
 *
 *  return 0 if success.
 *  return -1 if failure.
 */
int tox_setname(Tox *tox, uint8_t *name, uint16_t length)
{
    Messenger *m = tox;
    return setname(m, name, length);
}

/* Get your nickname.
 * m -  The messanger context to use.
 * name - Pointer to a string for the name.
 * nlen -  The length of the string buffer.
 *
 *  return length of the name.
 *  return 0 on error.
 */
uint16_t tox_getselfname(Tox *tox, uint8_t *name, uint16_t nlen)
{
    Messenger *m = tox;
    return getself_name(m, name, nlen);
}

/* Get name of friendnumber and put it in name.
 * name needs to be a valid memory location with a size of at least MAX_NAME_LENGTH (128) bytes.
 *
 *  return length of name (with the NULL terminator) if success.
 *  return -1 if failure.
 */
int tox_getname(Tox *tox, int friendnumber, uint8_t *name)
{
    Messenger *m = tox;
    return getname(m, friendnumber, name);
}

/* Set our user status;
 * you are responsible for freeing status after.
 *
 *  return 0 on success, -1 on failure.
 */
int tox_set_statusmessage(Tox *tox, uint8_t *status, uint16_t length)
{
    Messenger *m = tox;
    return m_set_statusmessage(m, status, length);
}

int tox_set_userstatus(Tox *tox, TOX_USERSTATUS status)
{
    Messenger *m = tox;
    return m_set_userstatus(m, (USERSTATUS)status);
}

/*  return the length of friendnumber's status message, including null.
 *  Pass it into malloc.
 */
int tox_get_statusmessage_size(Tox *tox, int friendnumber)
{
    Messenger *m = tox;
    return m_get_statusmessage_size(m, friendnumber);
}

/* Copy friendnumber's status message into buf, truncating if size is over maxlen.
 * Get the size you need to allocate from m_get_statusmessage_size.
 * The self variant will copy our own status message.
 */
int tox_copy_statusmessage(Tox *tox, int friendnumber, uint8_t *buf, uint32_t maxlen)
{
    Messenger *m = tox;
    return m_copy_statusmessage(m, friendnumber, buf, maxlen);
}

int tox_copy_self_statusmessage(Tox *tox, uint8_t *buf, uint32_t maxlen)
{
    Messenger *m = tox;
    return m_copy_self_statusmessage(m, buf, maxlen);
}

/* Return one of USERSTATUS values.
 * Values unknown to your application should be represented as USERSTATUS_NONE.
 * As above, the self variant will return our own USERSTATUS.
 * If friendnumber is invalid, this shall return USERSTATUS_INVALID.
 */
TOX_USERSTATUS tox_get_userstatus(Tox *tox, int friendnumber)
{
    Messenger *m = tox;
    return (TOX_USERSTATUS)m_get_userstatus(m, friendnumber);
}

TOX_USERSTATUS tox_get_selfuserstatus(Tox *tox)
{
    Messenger *m = tox;
    return (TOX_USERSTATUS)m_get_self_userstatus(m);
}


/* Sets whether we send read receipts for friendnumber.
 * This function is not lazy, and it will fail if yesno is not (0 or 1).
 */
void tox_set_sends_receipts(Tox *tox, int friendnumber, int yesno)
{
    Messenger *m = tox;
    m_set_sends_receipts(m, friendnumber, yesno);
}

/* Return the number of friends in the instance m.
 * You should use this to determine how much memory to allocate
 * for copy_friendlist. */
uint32_t tox_count_friendlist(Tox *tox)
{
    Messenger *m = tox;
    return count_friendlist(m);
}

/* Copy a list of valid friend IDs into the array out_list.
 * If out_list is NULL, returns 0.
 * Otherwise, returns the number of elements copied.
 * If the array was too small, the contents
 * of out_list will be truncated to list_size. */
uint32_t tox_copy_friendlist(Tox *tox, int *out_list, uint32_t list_size)
{
    Messenger *m = tox;
    return copy_friendlist(m, out_list, list_size);
}

/* Set the function that will be executed when a friend request is received.
 *  Function format is function(uint8_t * public_key, uint8_t * data, uint16_t length)
 */
void tox_callback_friendrequest(Tox *tox, void (*function)(uint8_t *, uint8_t *, uint16_t, void *), void *userdata)
{
    Messenger *m = tox;
    m_callback_friendrequest(m, function, userdata);
}


/* Set the function that will be executed when a message from a friend is received.
 *  Function format is: function(int friendnumber, uint8_t * message, uint32_t length)
 */
void tox_callback_friendmessage(Tox *tox, void (*function)(Messenger *tox, int, uint8_t *, uint16_t, void *),
                                void *userdata)
{
    Messenger *m = tox;
    m_callback_friendmessage(m, function, userdata);
}

/* Set the function that will be executed when an action from a friend is received.
 *  function format is: function(int friendnumber, uint8_t * action, uint32_t length)
 */
void tox_callback_action(Tox *tox, void (*function)(Messenger *tox, int, uint8_t *, uint16_t, void *), void *userdata)
{
    Messenger *m = tox;
    m_callback_action(m, function, userdata);
}

/* Set the callback for name changes.
 *  function(int friendnumber, uint8_t *newname, uint16_t length)
 *  You are not responsible for freeing newname.
 */
void tox_callback_namechange(Tox *tox, void (*function)(Messenger *tox, int, uint8_t *, uint16_t, void *),
                             void *userdata)
{
    Messenger *m = tox;
    m_callback_namechange(m, function, userdata);
}

/* Set the callback for status message changes.
 *  function(int friendnumber, uint8_t *newstatus, uint16_t length)
 *  You are not responsible for freeing newstatus.
 */
void tox_callback_statusmessage(Tox *tox, void (*function)(Messenger *tox, int, uint8_t *, uint16_t, void *),
                                void *userdata)
{
    Messenger *m = tox;
    m_callback_statusmessage(m, function, userdata);
}

/* Set the callback for status type changes.
 *  function(int friendnumber, USERSTATUS kind)
 */
void tox_callback_userstatus(Tox *tox, void (*_function)(Tox *tox, int, TOX_USERSTATUS, void *), void *userdata)
{
    Messenger *m = tox;
    typedef void (*function_type)(Messenger *, int, USERSTATUS, void *);
    function_type function = (function_type)_function;
    m_callback_userstatus(m, function, userdata);
}

/* Set the callback for read receipts.
 *  function(int friendnumber, uint32_t receipt)
 *
 *  If you are keeping a record of returns from m_sendmessage;
 *  receipt might be one of those values, meaning the message
 *  has been received on the other side.
 *  Since core doesn't track ids for you, receipt may not correspond to any message.
 *  in that case, you should discard it.
 */
void tox_callback_read_receipt(Tox *tox, void (*function)(Messenger *tox, int, uint32_t, void *), void *userdata)
{
    Messenger *m = tox;
    m_callback_read_receipt(m, function, userdata);
}

/* Set the callback for connection status changes.
 *  function(int friendnumber, uint8_t status)
 *
 *  Status:
 *    0 -- friend went offline after being previously online
 *    1 -- friend went online
 *
 *  NOTE: this callback is not called when adding friends, thus the "after
 *  being previously online" part. It's assumed that when adding friends,
 *  their connection status is offline.
 */
void tox_callback_connectionstatus(Tox *tox, void (*function)(Messenger *tox, int, uint8_t, void *), void *userdata)
{
    Messenger *m = tox;
    m_callback_connectionstatus(m, function, userdata);
}

/**********GROUP CHAT FUNCTIONS: WARNING WILL BREAK A LOT************/

/* Set the callback for group invites.
 *
 *  Function(Tox *tox, int friendnumber, uint8_t *group_public_key, void *userdata)
 */
void tox_callback_group_invite(Tox *tox, void (*function)(Messenger *tox, int, uint8_t *, void *), void *userdata)
{
    Messenger *m = tox;
    m_callback_group_invite(m, function, userdata);
}
/* Set the callback for group messages.
 *
 *  Function(Tox *tox, int groupnumber, int friendgroupnumber, uint8_t * message, uint16_t length, void *userdata)
 */
void tox_callback_group_message(Tox *tox, void (*function)(Messenger *tox, int, int, uint8_t *, uint16_t, void *),
                                void *userdata)
{
    Messenger *m = tox;
    m_callback_group_message(m, function, userdata);
}
/* Creates a new groupchat and puts it in the chats array.
 *
 * return group number on success.
 * return -1 on failure.
 */
int tox_add_groupchat(Tox *tox)
{
    Messenger *m = tox;
    return add_groupchat(m);
}
/* Delete a groupchat from the chats array.
 *
 * return 0 on success.
 * return -1 if failure.
 */
int tox_del_groupchat(Tox *tox, int groupnumber)
{
    Messenger *m = tox;
    return del_groupchat(m, groupnumber);
}

/* Copy the name of peernumber who is in groupnumber to name.
 * name must be at least MAX_NICK_BYTES long.
 *
 * return length of name if success
 * return -1 if failure
 */
int tox_group_peername(Tox *tox, int groupnumber, int peernumber, uint8_t *name)
{
    Messenger *m = tox;
    return m_group_peername(m, groupnumber, peernumber, name);
}
/* invite friendnumber to groupnumber
 * return 0 on success
 * return -1 on failure
 */
int tox_invite_friend(Tox *tox, int friendnumber, int groupnumber)
{
    Messenger *m = tox;
    return invite_friend(m, friendnumber, groupnumber);
}
/* Join a group (you need to have been invited first.)
 *
 * returns group number on success
 * returns -1 on failure.
 */
int tox_join_groupchat(Tox *tox, int friendnumber, uint8_t *friend_group_public_key)
{
    Messenger *m = tox;
    return join_groupchat(m, friendnumber, friend_group_public_key);
}

/* send a group message
 * return 0 on success
 * return -1 on failure
 */
int tox_group_message_send(Tox *tox, int groupnumber, uint8_t *message, uint32_t length)
{
    Messenger *m = tox;
    return group_message_send(m, groupnumber, message, length);
}

/* Return the number of chats in the instance m.
 * You should use this to determine how much memory to allocate
 * for copy_chatlist. */
uint32_t tox_count_chatlist(Tox *tox)
{
    Messenger *m = tox;
    return count_chatlist(m);
}

/* Copy a list of valid chat IDs into the array out_list.
 * If out_list is NULL, returns 0.
 * Otherwise, returns the number of elements copied.
 * If the array was too small, the contents
 * of out_list will be truncated to list_size. */
uint32_t tox_copy_chatlist(Tox *tox, int *out_list, uint32_t list_size)
{
    Messenger *m = tox;
    return copy_chatlist(m, out_list, list_size);
}


/****************FILE SENDING FUNCTIONS*****************/


/* Set the callback for file send requests.
 *
 *  Function(Tox *tox, int friendnumber, uint8_t filenumber, uint64_t filesize, uint8_t *filename, uint16_t filename_length, void *userdata)
 */
void tox_callback_file_sendrequest(Tox *tox, void (*function)(Messenger *tox, int, uint8_t, uint64_t, uint8_t *,
                                   uint16_t,
                                   void *), void *userdata)
{
    Messenger *m = tox;
    callback_file_sendrequest(m, function, userdata);
}
/* Set the callback for file control requests.
 *
 *  Function(Tox *tox, int friendnumber, uint8_t send_receive, uint8_t filenumber, uint8_t control_type, uint8_t *data, uint16_t length, void *userdata)
 *
 */
void tox_callback_file_control(Tox *tox, void (*function)(Messenger *tox, int, uint8_t, uint8_t, uint8_t, uint8_t *,
                               uint16_t, void *), void *userdata)
{
    Messenger *m = tox;
    callback_file_control(m, function, userdata);
}
/* Set the callback for file data.
 *
 *  Function(Tox *tox, int friendnumber, uint8_t filenumber, uint8_t *data, uint16_t length, void *userdata)
 *
 */
void tox_callback_file_data(Tox *tox, void (*function)(Messenger *tox, int, uint8_t, uint8_t *, uint16_t length,
                            void *),
                            void *userdata)

{
    Messenger *m = tox;
    callback_file_data(m, function, userdata);
}
/* Send a file send request.
 * Maximum filename length is 255 bytes.
 *  return file number on success
 *  return -1 on failure
 */
int tox_new_filesender(Tox *tox, int friendnumber, uint64_t filesize, uint8_t *filename, uint16_t filename_length)
{
    Messenger *m = tox;
    return new_filesender(m, friendnumber, filesize, filename, filename_length);
}
/* Send a file control request.
 * send_receive is 0 if we want the control packet to target a sending file, 1 if it targets a receiving file.
 *
 *  return 1 on success
 *  return 0 on failure
 */
int tox_file_sendcontrol(Tox *tox, int friendnumber, uint8_t send_receive, uint8_t filenumber, uint8_t message_id,
                         uint8_t *data, uint16_t length)
{
    Messenger *m = tox;
    return file_control(m, friendnumber, send_receive, filenumber, message_id, data, length);
}
/* Send file data.
 *
 *  return 1 on success
 *  return 0 on failure
 */
int tox_file_senddata(Tox *tox, int friendnumber, uint8_t filenumber, uint8_t *data, uint16_t length)
{
    Messenger *m = tox;
    return file_data(m, friendnumber, filenumber, data, length);
}

/* Returns the recommended/maximum size of the filedata you send with tox_file_senddata()
 *
 *  return size on success
 *  return 0 on failure (currently will never return 0)
 */
int tox_filedata_size(Tox *tox, int friendnumber)
{
    return MAX_DATA_SIZE - crypto_box_MACBYTES - 3;
}

/* Give the number of bytes left to be sent/received.
 *
 *  send_receive is 0 if we want the sending files, 1 if we want the receiving.
 *
 *  return number of bytes remaining to be sent/received on success
 *  return 0 on failure
 */
uint64_t tox_file_dataremaining(Tox *tox, int friendnumber, uint8_t filenumber, uint8_t send_receive)
{
    Messenger *m = tox;
    return file_dataremaining(m, friendnumber, filenumber, send_receive);
}

/***************END OF FILE SENDING FUNCTIONS******************/

/* Use these functions to bootstrap the client.
 * Sends a get nodes request to the given node with ip port and public_key.
 */
void tox_bootstrap_from_ip(Tox *tox, tox_IP_Port _ip_port, uint8_t *public_key)
{
    Messenger *m = tox;
    IP_Port ip_port;
    memcpy(&ip_port, &_ip_port, sizeof(IP_Port));
    DHT_bootstrap(m->dht, ip_port, public_key);
}

int tox_bootstrap_from_address(Tox *tox, const char *address,
                               uint8_t ipv6enabled, uint16_t port, uint8_t *public_key)
{
    Messenger *m = tox;
    return DHT_bootstrap_from_address(m->dht, address, ipv6enabled, port, public_key);
};

/*  return 0 if we are not connected to the DHT.
 *  return 1 if we are.
 */
int tox_isconnected(Tox *tox)
{
    Messenger *m = tox;
    return DHT_isconnected(m->dht);
}

/* Run this at startup.
 *
 *  return allocated instance of tox on success.
 *  return 0 if there are problems.
 */
Tox *tox_new(uint8_t ipv6enabled)
{
    return new_messenger(ipv6enabled);
}

/* Run this before closing shop.
 * Free all datastructures.
 */
void tox_kill(Tox *tox)
{
    Messenger *m = tox;
    kill_messenger(m);
}

/* The main loop that needs to be run at least 20 times per second. */
void tox_do(Tox *tox)
{
    Messenger *m = tox;
    do_messenger(m);
}

/*
 * functions to avoid excessive polling
 */
int tox_wait_prepare(Tox *tox, uint8_t *data, uint16_t *lenptr)
{
    Messenger *m = tox;
    return wait_prepare_messenger(m, data, lenptr);
}

int tox_wait_execute(Tox *tox, uint8_t *data, uint16_t len, uint16_t milliseconds)
{
    Messenger *m = tox;
    return wait_execute_messenger(m, data, len, milliseconds);
}

void tox_wait_cleanup(Tox *tox, uint8_t *data, uint16_t len)
{
    Messenger *m = tox;
    wait_cleanup_messenger(m, data, len);
}

/* SAVING AND LOADING FUNCTIONS: */

/*  return size of the messenger data (for saving). */
uint32_t tox_size(Tox *tox)
{
    Messenger *m = tox;
    return messenger_size(m);
}

/* Save the messenger in data (must be allocated memory of size Messenger_size()). */
void tox_save(Tox *tox, uint8_t *data)
{
    Messenger *m = tox;
    messenger_save(m, data);
}

/* Load the messenger from data of size length. */
int tox_load(Tox *tox, uint8_t *data, uint32_t length)
{
    Messenger *m = tox;
    return messenger_load(m, data, length);
}

