/***************************************************************************
 *            utils.c
 *
 *  Wed Feb 23 14:15:36 2005
 *  Copyright  2005  Simon Morlat
 *  Email simon.morlat@linphone.org
 ****************************************************************************/
/*
  The oRTP library is an RTP (Realtime Transport Protocol - rfc1889) stack.
  Copyright (C) 2001  Simon MORLAT simon.morlat@linphone.org

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

#include <ortp/rtpport.h>
#include "utils.h"

OList *o_list_new(void *data){
	OList *new_elem=g_new0(OList,1);
	new_elem->data=data;
	return new_elem;
}

OList * o_list_append(OList *elem, void * data){
	OList *new_elem=o_list_new(data);
	OList *it=elem;
	if (elem==NULL) return new_elem;
	while (it->next!=NULL) it=o_list_next(it);
	it->next=new_elem;
	new_elem->prev=it;
	return elem;
}
