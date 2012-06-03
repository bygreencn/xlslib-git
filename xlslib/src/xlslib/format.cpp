/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * This file is part of xlslib -- A multiplatform, C/C++ library
 * for dynamic generation of Excel(TM) files.
 *
 * xlslib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xlslib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with xlslib.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Copyright 2004 Yeico S. A. de C. V.
 * Copyright 2008 David Hoerl
 *  
 * $Source: /cvsroot/xlslib/xlslib/src/xlslib/format.cpp,v $
 * $Revision: 1.5 $
 * $Author: dhoerl $
 * $Date: 2009/03/02 04:08:43 $
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * File description:
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <format.h>
#include <globalrec.h>

using namespace std;
using namespace xlslib_core;


static const unsigned16_t format2index_arr[] =
{
   FMTCODE_GENERAL,
   FMTCODE_NUMBER1,
   FMTCODE_NUMBER2,
   FMTCODE_NUMBER3,
   FMTCODE_NUMBER4,
   FMTCODE_CURRENCY1,
   FMTCODE_CURRENCY2,
   FMTCODE_CURRENCY3,
   FMTCODE_CURRENCY4,
   FMTCODE_PERCENT1,
   FMTCODE_PERCENT2,
   FMTCODE_SCIENTIFIC1,
   FMTCODE_FRACTION1,
   FMTCODE_FRACTION2,
   FMTCODE_DATE1,
   FMTCODE_DATE2,
   FMTCODE_DATE3,
   FMTCODE_DATE4,
   FMTCODE_HOUR1,
   FMTCODE_HOUR2,
   FMTCODE_HOUR3,
   FMTCODE_HOUR4,
   FMTCODE_HOURDATE,
   FMTCODE_ACCOUNTING1,
   FMTCODE_ACCOUNTING2,
   FMTCODE_ACCOUNTING3,
   FMTCODE_ACCOUNTING4,
   FMTCODE_CURRENCY5,
   FMTCODE_CURRENCY6,
   FMTCODE_CURRENCY7,
   FMTCODE_CURRENCY8,
   FMTCODE_HOUR5,
   FMTCODE_HOUR6,
   FMTCODE_HOUR7,
   FMTCODE_SCIENTIFIC2,
   FMTCODE_TEXT
};

unsigned16_t format_t::format2index(format_number_t idx)
{
	if ((unsigned16_t)idx > FMT_TEXT)
		idx = FMT_GENERAL;

	return format2index_arr[idx];
}



/* 
**********************************
**********************************
*/

format_t::format_t(const format_t& orig) :
		formatstr(orig.formatstr),
		index(0),
		m_usage_counter(0),
		m_GlobalRecords(orig.m_GlobalRecords)
{
	m_GlobalRecords.AddFormat(this);
}


format_t::format_t(CGlobalRecords& gRecords, const std::string& fmtstr) :
		formatstr(),
		index(0),
		m_usage_counter(0),
		m_GlobalRecords(gRecords)
{
	gRecords.char2str16(fmtstr, formatstr);
}

format_t::format_t(CGlobalRecords& gRecords, const std::ustring& fmtstr) :
		formatstr(),
		index(0),
		m_usage_counter(0),
		m_GlobalRecords(gRecords)
{
	gRecords.wide2str16(fmtstr, formatstr);
}

format_t::format_t(CGlobalRecords& gRecords, const u16string& fmtstr) :
		formatstr(fmtstr),
		index(0),
		m_usage_counter(0),
		m_GlobalRecords(gRecords)
{
}


format_t &format_t::operator =(const format_t &src)
{
	throw std::string("Should never have invoked the format_t copy operator!");
}



void format_t::MarkUsed(void) 
{
	m_usage_counter++;
}
void format_t::UnMarkUsed(void) 
{
	if(m_usage_counter)
		m_usage_counter--;
}
unsigned32_t format_t::Usage(void) const
{
	return m_usage_counter;
}



/* 
**********************************
CFormat class implementation
**********************************
*/
CFormat::CFormat(CDataStorage &datastore, const format_t* formatdef):
		CRecord(datastore)
{
	SetRecordType(RECTYPE_FORMAT);

	AddValue16(formatdef->GetIndex());
	//cerr << "Format: index=" << formatdef->GetIndex() << endl << flush;

	AddUnicodeString(formatdef->GetGlobalRecords(), formatdef->GetFormatStr(), LEN2_FLAGS_UNICODE);

	SetRecordLength(GetDataSize()-4);
}

CFormat::~CFormat()
{
}





/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * $Log: format.cpp,v $
 * Revision 1.5  2009/03/02 04:08:43  dhoerl
 * Code is now compliant to gcc  -Weffc++
 *
 * Revision 1.4  2009/01/23 16:09:55  dhoerl
 * General cleanup: headers and includes. Fixed issues building mainC and mainCPP
 *
 * Revision 1.3  2009/01/08 02:53:15  dhoerl
 * December Rework
 *
 * Revision 1.2  2008/10/25 18:39:54  dhoerl
 * 2008
 *
 * Revision 1.1.1.1  2004/08/27 16:31:48  darioglz
 * Initial Import.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
