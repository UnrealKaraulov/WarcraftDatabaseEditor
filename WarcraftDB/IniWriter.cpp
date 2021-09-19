#include <iostream>
#include <Windows.h> 

#include "IniWriter.h"

CIniWriter::CIniWriter(char* szFileName)
{
 memset(m_szFileName, 0x00, 255);
 memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteInteger(const char* szSection, const char* szKey, int iValue)
{
	if ( szSection != 0 && *( BYTE* ) szSection && ( ( int ) ( void* ) szSection < 0x7FFFFFFF ) )
	{

	}
	else
	{
		return;
	}


	if ( szKey != 0 && *( BYTE* ) szKey && ( ( int ) ( void* ) szKey < 0x7FFFFFFF ) )
	{

	}
	else
	{
		return;
	}

	if ( _stricmp( szKey , "BuildsCount" ) != 0 &&
		 _stricmp( szKey , "ResearchesCount" ) != 0 &&
		 _stricmp( szKey , "TrainsCount" ) != 0 &&
		 _stricmp( szKey , "MakeitemsCount" ) != 0 &&
		 _stricmp( szKey , "SellunitsCount" ) != 0 &&
		 _stricmp( szKey , "SellitemsCount" ) != 0 &&
		 _stricmp( szKey , "UpgradesCount" ) != 0 &&
		 _stricmp( szKey , "Revive" ) != 0 &&
		 _stricmp( szKey , "Reviveatcount" ) != 0 &&
		 _stricmp( szKey , "LoopingSoundFadeIn" ) != 0 &&
		 _stricmp( szKey , "LoopingSoundFadeOut" ) != 0 &&
		 _stricmp( szKey , "Buttonpos" ) != 0 &&
		 _stricmp( szKey , "RequiresCount" ) != 0 &&
		 _stricmp( szKey , "Requireshadcount" ) != 0 &&
		 _stricmp( szKey , "Missilespeed" ) != 0 &&
		 _stricmp( szKey , "Missilearc" ) != 0 &&
		 _stricmp( szKey , "Missilehoming" ) != 0 &&
		 _stricmp( szKey , "Spelldetail" ) != 0 &&
		 _stricmp( szKey , "Unbuttonpos" ) != 0 &&
		 _stricmp( szKey , "Researchbuttonpos" ) != 0 &&
		 _stricmp( szKey , "AnimnamesCount" ) != 0 &&
		 _stricmp( szKey , "Casterattachcount" ) != 0 &&
		 _stricmp( szKey , "Effectattachcount" ) != 0 &&
		 _stricmp( szKey , "Targetattachcount" ) != 0 &&
		 _stricmp( szKey , "Specialattachcount" ) != 0 &&
		 _stricmp( szKey , "Requiresamount" ) != 0 )
	{
		char szValue[ 255 ];
		sprintf_s( szValue , 255 , "%d" , iValue );
		WritePrivateProfileString( szSection , szKey , szValue , m_szFileName );
	}
}
void CIniWriter::WriteFloat(const char* szSection, const char* szKey, float fltValue)
{
 char szValue[255];
 sprintf_s(szValue,255, "%f", fltValue);
 WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}
void CIniWriter::WriteBOOLean(const char* szSection, const char* szKey, BOOL bolValue)
{
 char szValue[255];
 sprintf_s(szValue,255, "%s", bolValue ? "TRUE" : "FALSE");
 WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}
void CIniWriter::WriteString(const char* szSection, const char* szKey, const char* szValue)
{
 WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}