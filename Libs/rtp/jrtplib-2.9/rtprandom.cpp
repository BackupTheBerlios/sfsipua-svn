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

#include "rtprandom.h"
#include <time.h>
#ifdef WIN32
	#include <process.h>
#else
	#include <sys/types.h>
	#include <unistd.h>
#endif // WIN32

bool RTPRandom::initseed = false;

RTPRandom::RTPRandom()
{
	if (!initseed)
	{
		unsigned long x;
		x = (unsigned long)getpid();
		x += (unsigned long)time(0);
		x -= (unsigned long)clock();
		x ^= (unsigned long)(this);
		srand((unsigned int)x);
		initseed = true;
	}
}

RTPRandom::~RTPRandom()
{
}

RTPuint32 RTPRandom::RandomUInt32()
{
	RTPuint32 x,y;

	x = (RTPuint32)(65536.0*(double)rand()/((double)RAND_MAX+1.0));
	y = x;
	x = (RTPuint32)(65536.0*(double)rand()/((double)RAND_MAX+1.0));
	y ^= (x<<8);
	x = (RTPuint32)(65536.0*(double)rand()/((double)RAND_MAX+1.0));
	y ^= (x<<16);
	return y;
}

RTPuint16 RTPRandom::RandomUInt16()
{
	return (RTPuint16)(RandomUInt32()&0xFFFF);
}

