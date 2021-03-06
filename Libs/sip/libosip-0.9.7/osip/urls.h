/*
  The oSIP library implements the Session Initiation Protocol (SIP -rfc3261-)
  Copyright (C) 2001,2002,2003  Aymeric MOIZARD jack@atosc.org
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _URLS_H_
#define _URLS_H_

#include <osip/const.h>


/**
 * @file urls.h
 * @brief oSIP url parser Routines
 *
 * This is the implementation of sip url scheme. It also partially support
 * any unrecognised scheme (not starting with 'sip:' or 'sips:'). Unrecognised
 * scheme are stored in url->string.
 */

/**
 * @defgroup oSIP_URLS oSIP url parser Handling
 * @ingroup oSIP
 * @{
 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Structure for referencing url parameters.
 * @defvar url_param_t
 */
  typedef struct url_param_t url_param_t;

  struct url_param_t
  {
    char *gname;
    char *gvalue;
  };

/**
 * Structure for referencing url headers.
 * @defvar url_header_t
 */
  typedef url_param_t url_header_t;

/**
 * Allocate a url parameter element.
 * @param url_param The element to work on.
 */
  int url_param_init (url_param_t ** url_param);
/**
 * Free a url parameter element.
 * @param url_param The element to work on.
 */
  void url_param_free (url_param_t * url_param);
/**
 * Set values of a url parameter element.
 * @param url_param The element to work on.
 * @param name The token name.
 * @param value The token value.
 */
  int url_param_set (url_param_t * url_param, char *name, char *value);
/**
 * Clone a url parameter element.
 * @param url_param The element to work on.
 * @param dest The resulting new allocated element.
 */
  int url_param_clone (url_param_t * url_param, url_param_t ** dest);
#ifndef DOXYGEN
/*
 * Free a list of a url parameter element.
 * @param url_params The list of url parameter element to free.
 */
  void url_param_freelist (list_t * url_params);
#endif
/**
 * Allocate and add a url parameter element in a list.
 * @param url_params The list of url parameter element to work on.
 * @param name The token name.
 * @param value The token value.
 */
  int url_param_add (list_t * url_params, char *name, char *value);
/**
 * Find in a url parameter element in a list.
 * @param url_params The list of url parameter element to work on.
 * @param name The name of the parameter element to find.
 * @param dest A pointer on the element found.
 */
  int url_param_getbyname (list_t * url_params, char *name,
			   url_param_t ** dest);

/**
 * Allocate a generic parameter element.
 * @param url_header The element to work on.
 */
#define url_header_init(url_header) url_param_init(url_header)
/**
 * Free a generic parameter element.
 * @param url_header The element to work on.
 */
#define url_header_free(url_header) url_param_free(url_header)
/**
 * Set values of a generic parameter element.
 * @param url_header The element to work on.
 * @param name The token name.
 * @param value The token value.
 */
#define url_header_set(url_header, name, value)  url_param_set(url_header, name, value)
/**
 * Clone a generic parameter element.
 * @param url_header The element to work on.
 * @param dest The resulting new allocated element.
 */
#define url_header_clone(url_header,dest)    url_param_clone(url_header,dest)
#ifndef DOXYGEN
/*
 * Free a list of a generic parameter element.
 * @param LIST The list of generic parameter element to free.
 */
#define url_header_freelist(LIST)       url_param_freelist(LIST)
#endif
/**
 * Allocate and add a generic parameter element in a list.
 * @param url_headers The list of generic parameter element to work on.
 * @param name The token name.
 * @param value The token value.
 */
#define url_header_add(url_headers,name,value)        url_param_add(url_headers,name,value)
/**
 * Find in a generic parameter element in a list.
 * @param url_headers The list of generic parameter element to work on.
 * @param name The name of the parameter element to find.
 * @param dest A pointer on the element found.
 */
#define url_header_getbyname(url_headers,name,dest) url_param_getbyname(url_headers,name,dest)

/**
 * Structure for referencing SIP urls.
 * @defvar url_t
 */
  typedef struct url_t url_t;

  struct url_t
  {
    char *scheme;
    char *username;
    char *password;
    char *host;
    char *port;
    list_t *url_params;
    list_t *url_headers;

    char *string;
		/** other url schemes are strings. (http, mailto...) */
  };

/**
 * Allocate a url element.
 * @param url The element to work on.
 */
  int url_init (url_t ** url);
/**
 * Free a url element.
 * @param url The element to work on.
 */
  void url_free (url_t * url);
/**
 * Parse a url.
 * @param url The element to work on.
 * @param buf The buffer to parse.
 */
  int url_parse (url_t * url, char *buf);
#ifndef DOXYGEN
/**
 * Parse the header part of a url.
 * @param url The element to work on.
 * @param buf The buffer to parse.
 */
  int url_parse_headers (url_t * url, char *buf);
/**
 * Parse the parameter part of a url.
 * @param url The element to work on.
 * @param buf The buffer to parse.
 */
  int url_parse_params (url_t * url, char *buf);
#endif
/**
 * Get a string representation of a url element.
 * @param url The element to work on.
 * @param dest The resulting new allocated buffer.
 */
  int url_2char (url_t * url, char **dest);
/**
 * Clone a url element.
 * @param url The element to work on.
 * @param dest The resulting new allocated element.
 */
  int url_clone (url_t * url, url_t ** dest);
/**
* Get a canonical string representation of a url element.
* as defined in 10.3-5
* @param url The element to work on.
* @param dest The resulting new allocated buffer.
*/
  int url_2char_canonical (url_t * url, char **dest);

/**
 * Set the scheme of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_setscheme (url_t * url, char *value);
/**
 * Get the scheme of a url element.
 * @param url The element to work on.
 */
  char *url_getscheme (url_t * url);
/**
 * Set the host of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_sethost (url_t * url, char *value);
/**
 * Get the host of a url element.
 * @param url The element to work on.
 */
  char *url_gethost (url_t * url);
/**
 * Set the username of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_setusername (url_t * url, char *value);
/**
 * Get the username of a url element.
 * @param url The element to work on.
 */
  char *url_getusername (url_t * url);
/**
 * Set the password of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_setpassword (url_t * url, char *value);
/**
 * Get the password of a url element.
 * @param url The element to work on.
 */
  char *url_getpassword (url_t * url);
/**
 * Set the host of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_sethost (url_t * url, char *value);
/**
 * Get the host of a url element.
 * @param url The element to work on.
 */
  char *url_gethost (url_t * url);
/**
 * Set the port of a url element.
 * @param url The element to work on.
 * @param value The token value.
 */
  void url_setport (url_t * url, char *value);
/**
 * Get the port of a url element.
 * @param url The element to work on.
 */
  char *url_getport (url_t * url);



/**
 * Set the transport parameter to UDP in a url element.
 * @param url The element to work on.
 */
#define url_set_transport_udp(url)   url_param_add((url)->url_params, sgetcopy("transport"), sgetcopy("udp"))
/**
 * Set the transport parameter to TCP in a url element.
 * @param url The element to work on.
 */
#define url_set_transport_tcp(url)   url_param_add((url)->url_params, sgetcopy("transport"), sgetcopy("tcp"))
/**
 * Set the transport parameter to SCTP in a url element.
 * @param url The element to work on.
 */
#define url_set_transport_sctp(url)  url_param_add((url)->url_params, sgetcopy("transport"), sgetcopy("sctp"))
/**
 * Set the transport parameter to TLS in a url element.
 * @param url The element to work on.
 */
#define url_set_transport_tls(url)   url_param_add((url)->url_params, sgetcopy("transport"), sgetcopy("tls"))
/**
 * Set the transport parameter to TLS in a url element.
 * @param url The element to work on.
 * @param value The value describing the transport protocol.
 */
#define url_set_transport(url,value) url_param_add((url)->url_params, sgetcopy("transport"), value)

/**
 * Set the user parameter to PHONE in a url element.
 * @param url The element to work on.
 */
#define url_set_user_phone(url)   url_param_add((url)->url_params, sgetcopy("user"), sgetcopy("phone"))
/**
 * Set the user parameter to IP in a url element.
 * @param url The element to work on.
 */
#define url_set_user_ip(url)      url_param_add((url)->url_params, sgetcopy("user"), sgetcopy("ip"))
/**
 * Set the user parameter in a url element.
 * @param url The element to work on.
 * @param value The value describing the user url.
 */
#define url_set_user(url, value)  url_param_add((url)->url_params, sgetcopy("user"), value)

/**
 * Set a method parameter to INVITE in a url element.
 * @param url The element to work on.
 */
#define url_set_method_invite(url)  url_param_add((url)->url_params, sgetcopy("method"), sgetcopy("INVITE"))
/**
 * Set a method parameter to ACK in a url element.
 * @param url The element to work on.
 */
#define url_set_method_ack(url)     url_param_add((url)->url_params, sgetcopy("method"), sgetcopy("ACK"))
/**
 * Set a method parameter to OPTIONS in a url element.
 * @param url The element to work on.
 */
#define url_set_method_options(url) url_param_add((url)->url_params, sgetcopy("method"), sgetcopy("OPTIONS"))
/**
 * Set a method parameter to BYE in a url element.
 * @param url The element to work on.
 */
#define url_set_method_bye(url)     url_param_add((url)->url_params, sgetcopy("method"), sgetcopy("BYE"))
/**
 * Set a method parameter to CANCEL in a url element.
 * @param url The element to work on.
 */
#define url_set_method_cancel(url)  url_param_add((url)->url_params, sgetcopy("method"), sgetcopy("CANCEL"))
/**
 * Set a method parameter to REGISTER in a url element.
 * @param url The element to work on.
 */
#define url_set_method_register(url) url_param_add((url)->url_params,sgetcopy("method"), sgetcopy("REGISTER"))
/**
 * Set a method parameter in a url element.
 * @param url The element to work on.
 * @param value The value for the method parameter.
 */
#define url_set_method(url, value) url_param_add((url)->url_params, sgetcopy("method"), value)
/**
 * Set a ttl parameter in a url element.
 * @param url The element to work on.
 * @param value The value for the ttl parameter.
 */
#define url_set_ttl(url, value)    url_param_add((url)->url_params, sgetcopy("ttl"), value)
/**
 * Set a maddr parameter in a url element.
 * @param url The element to work on.
 * @param value The value for the maddr parameter.
 */
#define url_set_maddr(url, value)  url_param_add((url)->url_params, sgetcopy("maddr"), value)

/**
 * Allocate and add a url parameter element in a url element.
 * @param url The element to work on.
 * @param name The token name.
 * @param value The token value.
 */
#define url_uparam_add(url,name,value) url_param_add((url)->url_params,name,value)
/**
 * Find in a url parameter element in a url element.
 * @param url The element to work on.
 * @param name The name of the url parameter element to find.
 * @param dest A pointer on the element found.
 */
#define url_uparam_getbyname(url,name,dest)  url_param_getbyname((url)->url_params,name,dest)

/**
 * Allocate and add a url header element in a url element.
 * @param url The element to work on.
 * @param name The token name.
 * @param value The token value.
 */
#define url_uheader_add(url,name,value)    url_header_add(url->url_headers,name,value)
/**
 * Find in a url header element in a url element.
 * @param url The element to work on.
 * @param name The name of the url header element to find.
 * @param dest A pointer on the element found.
 */
#define url_uheader_getbyname(url,name,dest) url_header_getbyname(url->url_headers,name,dest)

#ifndef DOXYGEN
/* internal method */
  char *next_separator (char *ch, int separator_to_find,
			int before_separator);

  char *url_escape_nonascii_and_nondef (const char *string, const char *def);
  char *url_escape_userinfo (const char *string);
  char *url_escape_password (const char *string);
  char *url_escape_uri_param (char *string);
  char *url_escape_header_param (char *string);
  void url_unescape (char *string);

#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif				/*  _URLS_H_ */
