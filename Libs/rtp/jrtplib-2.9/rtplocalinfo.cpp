/*

  This file is a part of JRTPLIB
  Copyright (c) 1999-2004 Jori Liesenborgs

  Contact: jori@lumumba.luc.ac.be

  This library (JRTPLIB) was partially developed for my thesis at the
  School for Knowledge Technology (Belgium/The Netherlands)

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

#include "rtplocalinfo.h"

RTPLocalInfo::RTPLocalInfo()
{
	Clear();
}

RTPLocalInfo::~RTPLocalInfo()
{
}

void RTPLocalInfo::Clear()
{
	portbase = 0;
	maxpacksize = RTP_DEFAULT_MAXPACKSIZE;
	seqnum = 0;
	timestamp = 0;
	timestampoffset = 0;
	packetcount = 0;
	octetcount = 0;
	tsoffsettime.tv_sec = 0;
	tsoffsettime.tv_usec = 0;
	defptset = false;
	defmarkset = false;
	deftsincset = false;
	defvaluesset = false;
	defmark = false;
	defpayloadtype = 0;
	deftsinc = 0;
	tsunit = RTP_DEFAULT_TIMESTAMPUNIT;
}

