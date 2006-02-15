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
#include <ortp/rtp.h>
#include <ortp/str_utils.h>

#include <stdio.h>

void qinit(queue_t *q){
	mblk_init(&q->_q_first);
	mblk_init(&q->_q_last);
	q->_q_first.b_next=&q->_q_last;
	q->_q_last.b_prev=&q->_q_first;
	q->q_mcount=0;
}

void mblk_init(mblk_t *mp)
{
	mp->b_cont=mp->b_prev=mp->b_next=NULL;
	mp->b_rptr=mp->b_wptr=NULL;
}

mblk_t *allocb(int size, int pri)
{
	mblk_t *mp;
	dblk_t *datab;
	gchar *buf;
	
	mp=g_malloc(sizeof(mblk_t));
	mblk_init(mp);
	datab=g_malloc(sizeof(dblk_t));
	
	buf=g_malloc(size);

	datab->db_base=buf;
	datab->db_lim=buf+size;
	datab->ref_count=1;
	datab->db_freefn=g_free;
	
	mp->b_datap=datab;
	mp->b_rptr=mp->b_wptr=buf;
	mp->b_next=mp->b_prev=mp->b_cont=NULL;
	return mp;
}

mblk_t *allocb_with_buf(char *buf, int size, int pri, void (*freefn)(void*) )
{
	mblk_t *mp;
	dblk_t *datab;
	
	mp=g_malloc(sizeof(mblk_t));
	mblk_init(mp);
	datab=g_malloc(sizeof(dblk_t));
	

	datab->db_base=buf;
	datab->db_lim=buf+size;
	datab->ref_count=1;
	datab->db_freefn=freefn;
	
	mp->b_datap=datab;
	mp->b_rptr=mp->b_wptr=buf;
	mp->b_next=mp->b_prev=mp->b_cont=NULL;
	return mp;
}

	
void freeb(mblk_t *mp)
{
	g_return_if_fail(mp->b_datap!=NULL);
	g_return_if_fail(mp->b_datap->db_base!=NULL);
	
	mp->b_datap->ref_count--;
	if (mp->b_datap->ref_count==0)
	{
		if (mp->b_datap->db_freefn!=NULL)
			mp->b_datap->db_freefn(mp->b_datap->db_base);
		
		g_free(mp->b_datap);
	}
	g_free(mp);
}	

void freemsg(mblk_t *mp)
{
	mblk_t *tmp1,*tmp2;
	tmp1=mp;
	while(tmp1!=NULL)
	{
		tmp2=tmp1->b_cont;
		freeb(tmp1);
		tmp1=tmp2;
	}
}

mblk_t *dupb(mblk_t *mp)
{
	mblk_t *newm;
	g_return_val_if_fail(mp->b_datap!=NULL,NULL);
	g_return_val_if_fail(mp->b_datap->db_base!=NULL,NULL);
	
	mp->b_datap->ref_count++;
	newm=g_malloc(sizeof(mblk_t));
	mblk_init(newm);
	newm->b_datap=mp->b_datap;
	newm->b_rptr=mp->b_rptr;
	newm->b_wptr=mp->b_wptr;
	return newm;
}

/* duplicates a complex mblk_t */
mblk_t	*dupmsg(mblk_t* m)
{
	mblk_t *newm=NULL,*mp,*prev;
	prev=newm=dupb(m);
	m=m->b_cont;
	while (m!=NULL){
		mp=dupb(m);
		prev->b_cont=mp;
		prev=mp;
		m=m->b_cont;
	}
	return newm;
}

void putq(queue_t *q,mblk_t *mp)
{
	q->_q_last.b_prev->b_next=mp;
	mp->b_prev=q->_q_last.b_prev;
	mp->b_next=&q->_q_last;
	q->_q_last.b_prev=mp;
	q->q_mcount++;
}

mblk_t *getq(queue_t *q)
{
	mblk_t *tmp;
	tmp=q->_q_first.b_next;
	if (tmp==&q->_q_last) return NULL;
	q->_q_first.b_next=tmp->b_next;
	tmp->b_next->b_prev=&q->_q_first;
	tmp->b_prev=NULL;
	tmp->b_next=NULL;
	q->q_mcount--;
	return tmp;
}

/* insert mp in q just before emp */
void insq(queue_t *q,mblk_t *emp, mblk_t *mp)
{
	if (emp==NULL){
		putq(q,mp);
		return;
	}
	q->q_mcount++;
	emp->b_prev->b_next=mp;
	mp->b_prev=emp->b_prev;
	emp->b_prev=mp;
	mp->b_next=emp;	
}

void remq(queue_t *q, mblk_t *mp){
	q->q_mcount--;
	mp->b_prev->b_next=mp->b_next;
	mp->b_next->b_prev=mp->b_prev;
	mp->b_next=NULL;
	mp->b_prev=NULL;
}

/* remove and free all messages in the q */
void flushq(queue_t *q, int how)
{
	mblk_t *mp;
	
	while ((mp=getq(q))!=NULL)
	{
		freemsg(mp);
	}
}

gint msgdsize(mblk_t *mp)
{
	gint msgsize=0;
	while(mp!=NULL){
		msgsize+=mp->b_wptr-mp->b_rptr;
		mp=mp->b_cont;
	}
	return msgsize;
}

mblk_t * msgpullup(mblk_t *mp,int len)
{
	mblk_t *newm;
	gint msgsize=msgdsize(mp);
	gint rlen;
	gint mlen;
	
	
	if ((len==-1) || (len>msgsize)) len=msgsize;
	rlen=len;
	newm=allocb(len,BPRI_MED);

	while(mp!=NULL){
		mlen=mp->b_wptr-mp->b_rptr;
		if (rlen>=mlen)
		{
			memcpy(newm->b_wptr,mp->b_rptr,mlen);
			rlen-=mlen;
			newm->b_wptr+=mlen;
		}
		else /* rlen < mlen */
		{
			memcpy(newm->b_wptr,mp->b_rptr,rlen);
			newm->b_wptr+=rlen;
			
			/* put the end of the original message at the end of the new */
			newm->b_cont=dupmsg(mp);
			newm->b_cont->b_rptr+=rlen;
			return newm;
		}
		mp=mp->b_cont;
	}
	return newm;
}


mblk_t *copyb(mblk_t *mp)
{
	mblk_t *newm;
	gint len=mp->b_wptr-mp->b_rptr;
	newm=allocb(len,BPRI_MED);
	memcpy(newm->b_wptr,mp->b_rptr,len);
	newm->b_wptr+=len;
	return newm;
}

mblk_t *copymsg(mblk_t *mp)
{
	mblk_t *newm=0,*m;
	m=newm=copyb(mp);
	mp=mp->b_cont;
	while(mp!=NULL){
		m->b_cont=copyb(mp);
		m=m->b_cont;
		mp=mp->b_cont;
	}
	return newm;
}

mblk_t * appendb(mblk_t *mp, const char *data, int size, gboolean pad){
	gint padcnt=0;
	int i;
	if (pad){
		padcnt= (gint)(4L-( (long)(mp->b_wptr+size) % 4L)) % 4L;
	}
	if ((mp->b_wptr + size +padcnt) > (char*)mp->b_datap->db_lim){
		/* buffer is not large enough: append a new block (with the same size ?)*/
		int plen=(char*)mp->b_datap->db_lim - (char*) mp->b_datap->db_base;
		mp->b_cont=allocb(MAX(plen,size),0);
		mp=mp->b_cont;
	}
	if (size) memcpy(mp->b_wptr,data,size);
	mp->b_wptr+=size;
	for (i=0;i<padcnt;i++){
		mp->b_wptr[0]=0;
		mp->b_wptr++;
	}
	return mp;
}

void msgappend(mblk_t *mp, const char *data, int size, gboolean pad){
	while(mp->b_cont!=NULL) mp=mp->b_cont;
	appendb(mp,data,size,pad);
}

mblk_t *concatb(mblk_t *mp, mblk_t *newm){
	while (mp->b_cont!=NULL) mp=mp->b_cont;
	mp->b_cont=newm;
	while(newm->b_cont!=NULL) newm=newm->b_cont;
	return newm;
}
