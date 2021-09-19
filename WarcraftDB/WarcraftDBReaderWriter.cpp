#include "Includes.h"










typedef void *( __fastcall * sub_6F7B2BE0 )( const char * valuename , int arguments , int a3 , int a4 , void * idifnotnull , void *a6 , int a7 , int *DefaultValue , const char * category );
sub_6F7B2BE0 ReadGameDataBase_org;
sub_6F7B2BE0 ReadGameDataBase_ptr;

typedef signed int( __stdcall * Storm_423 )( const char * category , char * name , int defaultvalue , int addr );
Storm_423 Storm_423_org;
Storm_423 Storm_423_ptr;
//02FA80
signed int __stdcall Storm_423_my( const char * category , char * name , int defaultvalue , int addr )
{
	char FullName[ 512 ];
	sprintf_s( FullName , "%s%s" , "HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\" , category );
	signed int returnvalue = Storm_423_ptr( category , name , defaultvalue , addr );
	CIniWriter writer = CIniWriter( ".\\WarcraftDB_reg.ini" );
	writer.WriteInteger( FullName , name , *( int* ) addr );
	return returnvalue;
}

void * __fastcall  ReadGameDataBase_my( const char * valuename , int arguments , int a3 , int a4 , void * idifnotnull , void *a6 , int a7 , int *DefaultValue , const char * category )
{
	if ( valuename )
	{

		char FullName[ 512 ];
		const char * categoryname = "NULL";
		if ( !category || !*( BYTE* ) category )
		{
			categoryname = "GENERAL";
		}
		else
		{
			categoryname = category;
		}

		sprintf_s( FullName , "%s[args:%i,id:%i]" , valuename , arguments , idifnotnull ? *( int* ) idifnotnull : 0 );

		/*	CIniReader reader = CIniReader( ".\\WarcraftDB.ini" );
			if ( reader.ReadInteger( categoryname , FullName , -500 ) == -500 )
			{*/
		CIniWriter writer = CIniWriter( ".\\WarcraftDB.ini" );
		writer.WriteInteger( categoryname , FullName , DefaultValue ? *( int* ) DefaultValue : 0 );
		/*}
		else
		{
		if ( DefaultValue )
		*( int* ) DefaultValue = reader.ReadInteger( categoryname , FullName , 0 );
		}
		*/
		void *  retaddr = ReadGameDataBase_ptr( valuename , arguments , a3 , a4 , idifnotnull , a6 , a7 , DefaultValue , category );
		/*	sprintf_s( FullName , "RET:%X. \nName:%S.\n%X,%X,%X,%X,%X,%X,%X,%X\0" , retaddr, valuename , arguments , a3 , a4 , idifnotnull , a6 , a7 , DefaultValue , category );

			MessageBox( 0 , FullName , FullName , 0 );*/
		return retaddr;

	}
	return ReadGameDataBase_ptr( valuename , arguments , a3 , a4 , idifnotnull , a6 , a7 , DefaultValue , category );
}


int StormDll = ( int ) LoadLibrary( "Storm.dll" );

int GameDll = ( int ) LoadLibrary( "Game.dll" );

void SetTlsForMe( )
{
#ifdef BOTDEBUG
	PrintDebugInfo( "Set thread access" );
#endif
	UINT32 Data = *( UINT32 * ) ( GameDll + 0xACEB4C );
	UINT32 TlsIndex = *( UINT32 * ) ( GameDll + 0xAB7BF4 );
	if ( TlsIndex )
	{
		UINT32 v5 = **( UINT32 ** ) ( *( UINT32 * ) ( *( UINT32 * ) ( GameDll + 0xACEB5C ) + 4 * Data ) + 44 );
		if ( !v5 || !( *( LPVOID * ) ( v5 + 520 ) ) )
		{
			Sleep( 1000 );
			SetTlsForMe( );
			return;
		}
		TlsSetValue( TlsIndex , *( LPVOID * ) ( v5 + 520 ) );
	}
	else
	{
		Sleep( 1000 );
		SetTlsForMe( );
		return;
	}
}

CIniWriter logfile = CIniWriter( ".\\xout.ini" );
typedef signed int( __thiscall *sub_6F7B0DA0 )( const char * addr );

void WriteLaststring( LPCTSTR data,int xxx )
{

	char valnam[ 256 ];
	sprintf_s( valnam , 256 , "%s%i" , "valnam" , xxx );
	HKEY key;
	
	if ( RegOpenKey( HKEY_LOCAL_MACHINE , TEXT( "Software\\MyKey\\" ) , &key ) != ERROR_SUCCESS )
		
	{
		

		
	}
	if ( RegSetValueEx( key , valnam , 0 , REG_SZ , ( LPBYTE ) data , strlen( data )*sizeof( char ) ) != ERROR_SUCCESS )
	{
		RegCloseKey( key );
		
	}
	else
	{
		
	}
}

int int10 = 10;

void TestBrute( const char *stringsting,const char * substring )
{
	if ( !stringsting || !*( BYTE* ) stringsting )
		return;

	if ( strlen( stringsting ) < 2 || strlen( stringsting ) > 50 )
		return;

	char buffer[ 256 ];
	memset( buffer , 0 , 256 );
	if ( substring )
	sprintf_s( buffer , "%s%s" , stringsting , substring );
	else
		sprintf_s( buffer , "%s" , stringsting  );
	int10--;
	if ( int10 == -1 )
		int10 = 10;
//	WriteLaststring( buffer , int10 );



	if ( ( ( sub_6F7B0DA0 ) ( GameDll + 0x7B0DA0 ) )( buffer ) != 0 )
	{
		logfile.WriteInteger( "GENERAL" , buffer , 1 );
		printf_s( "\nString: %s found" , stringsting );
	}

}



/*
void brute_sequential( )
{
	char alphabet[ ] = "abcdefghijklmnopqrstuvwxyz_";
	int alphabet_size = sizeof( alphabet ) -1;

	char * brutechar = new char[ 16 ];
	memset( brutechar , 0 , 16 );

	bool lvl5 = false;
	bool lvl6 = false;
	bool lvl7 = false;
	bool lvl8 = false;
	bool lvl9 = false;
	bool lvl10 = false;


	for ( int q = 0; q < alphabet_size; q++ )
	{
		for ( int w = 0; w < alphabet_size; w++ )
		{
			for ( int e = 0; e < alphabet_size; e++ )
			{
				for ( int r = 0; r < alphabet_size; r++ )
				{
					for ( int t = 0; t < alphabet_size; t++ )
					{
						for ( int y = 0; y < alphabet_size; y++ )
						{
							for ( int u = 0; u < alphabet_size; u++ )
							{
								for ( int i = 0; i < alphabet_size; i++ )
								{
									for ( int o = 0; o < alphabet_size; o++ )
									{
										for ( int p = 0; p < alphabet_size; p++ )
										{
											for ( int a = 0; a < alphabet_size; a++ )
											{
												brutechar[ 0 ] = alphabet[ a ];
												TestBrute( brutechar );
											}
											brutechar[ 1 ] = alphabet[ p ];
											TestBrute( brutechar );
										}
										brutechar[ 2 ] = alphabet[ o ];
										TestBrute( brutechar );
									}
									brutechar[ 3 ] = alphabet[ i ];
									TestBrute( brutechar );
								}
								brutechar[ 4 ] = alphabet[ u ];
								TestBrute( brutechar );
							}
							brutechar[ 5 ] = alphabet[ y ];
							TestBrute( brutechar );
							if ( !lvl5 )
							{
								lvl5 = true;
								printf_s( "\r[0][1][2][3][4][5]                    " );
							}
							Sleep( 300 );
						}
						brutechar[ 6 ] = alphabet[ t ];
						TestBrute( brutechar );
						if ( !lvl6 )
						{
							lvl6 = true;
							printf_s( "\r[0][1][2][3][4][5][6]                 " );
						}
					}
					brutechar[ 7 ] = alphabet[ r ];
					TestBrute( brutechar );
					if ( !lvl7 )
					{
						lvl7 = true;
						printf_s( "\r[0][1][2][3][4][5][6][7]          " );
					}

				}
				brutechar[ 8 ] = alphabet[ e ];
				TestBrute( brutechar );
				if ( !lvl8 )
				{
					lvl8 = true;
					printf_s( "\r[0][1][2][3][4][5][6][7][8]       " );
				}
			}
			brutechar[ 9 ] = alphabet[ w ];
			TestBrute( brutechar );
			if ( !lvl9 )
			{
				lvl9 = true;
				printf_s( "\r[0][1][2][3][4][5][6][7][8][9]    " );
			}
		}
		brutechar[ 10 ] = alphabet[ q ];
		TestBrute( brutechar );
		if ( !lvl10 )
		{
			lvl10 = true;
			printf_s( "\r[0][1][2][3][4][5][6][7][8][9][10]" );
		}
	}

}
*/


void Brute1( )
{

	ifstream file( "outstrings.txt" );
	string content;

	while ( file >> content )
	{
		if ( content.c_str( )[ 0 ] != '=' )
		{
			TestBrute( content.c_str( ) , 0 );
		}
	}
	MessageBox( 0 , "1OK" , "1OK" , 0 );
}

void Brute2( )
{

	ifstream file( "outstrings.txt" );
	string content;

	while ( file >> content )
	{
		if ( content.c_str( )[ 0 ] != '=' )
		{
			TestBrute( content.c_str( ) , " \"XXXX\"" );
		}
	}
	MessageBox( 0 , "2OK" , "2OK" , 0 );
}

void Brute3( )
{
	ifstream file( "outstrings.txt" );
	string content;

	while ( file >> content )
	{
		if ( content.c_str( )[ 0 ] != '=' )
		{
			TestBrute( content.c_str( ) , " 1" );
		}
	}
	MessageBox( 0 , "3OK" , "3OK" , 0 );
}

DWORD WINAPI BRUTETHREAD( LPVOID )
{
	Sleep( 3000 );
	SetTlsForMe( );

	Brute1( );
	Brute2( );
	Brute3( );



	//brute_sequential( );
	return 0;
}

typedef int( __cdecl * Storm_578 )( int a1 , int a2 , const char *a3 , ... );
Storm_578 Storm_578_ptr;
Storm_578 Storm_578_org;

int __cdecl Storm_578_my( int a1 , int a2 , const char *a3 , ... )
{
	va_list varlist;
	va_start( varlist , a3 );
	int retvalue = Storm_578_ptr( a1 , a2 , a3 , varlist );
	va_end( varlist );

	return retvalue;
}
static BOOL WINAPI MyConsoleCtrlHandler( DWORD dwCtrlEvent ) { return dwCtrlEvent == CTRL_C_EVENT; }


typedef int( __stdcall * Storm_580 )( const char*a1 , char a2 , __int64 a3 );
Storm_580 Storm_580_org;
Storm_580 Storm_580_ptr;

int tes1t = 0;
int __stdcall  Storm_580_my( const char *a1 , char a2 , __int64 a3 )
{
	char xvalue[ 256 ];
	sprintf_s( xvalue , 256 , "%s" , a1 );
	char xvalue2[ 256 ];

	int retvalue = Storm_580_ptr( a1 , a2 , a3 );
	int retvaluex2 = 0;
	__asm
	{
		mov retvaluex2 , EDX;
	}
	sprintf_s( xvalue2 , 256 , "0x%X,0x%X" , retvalue , retvaluex2 );

	CIniWriter writer( ".\\AllCheatCodes.ini" );
	writer.WriteString( "COMMANDS" , a1 , xvalue2 );

	if ( tes1t == 0 )
	{
		tes1t++;
		Storm_580_org( "WARPTEN" , 0 , 0 );
	}

	return retvalue;
}

DWORD WINAPI ConfigThread( LPVOID )
{
	/*ReadGameDataBase_org = ( sub_6F7B2BE0 ) ( GameDll + 0x7B2BE0 );
	MH_CreateHook( ReadGameDataBase_org , &ReadGameDataBase_my , reinterpret_cast< void** >( &ReadGameDataBase_ptr ) );
	MH_EnableHook( ReadGameDataBase_org );*/
	Storm_580_org = ( Storm_580 ) ( 0x34520 + StormDll );
	MH_CreateHook( Storm_580_org , &Storm_580_my , reinterpret_cast< void** >( &Storm_580_ptr ) );
	MH_EnableHook( Storm_580_org );

	return 0;
}


typedef int( __fastcall * sub_6F4D20E0 )( int addr , const char * sectionname , const char * keyname );
sub_6F4D20E0 sub_6F4D20E0org;
sub_6F4D20E0 sub_6F4D20E0ptr;




int __fastcall sub_6F4D20E0my( int addr , const char * sectionname , const char * keyname )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration1.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D20E0ptr( addr , sectionname , keyname );
}

typedef int( __fastcall * sub_6F4D20C0 )( int addr , const char * sectionname , const char * keyname , unsigned int value );
sub_6F4D20C0 sub_6F4D20C0org;
sub_6F4D20C0 sub_6F4D20C0ptr;

int __fastcall sub_6F4D20C0my( int addr , const char * sectionname , const char * keyname , unsigned int value )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration2.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , value );
	return sub_6F4D20C0ptr( addr , sectionname , keyname , value );
}

typedef int( __thiscall * sub_6F002170 )( int a1 , const char * sectionname , const char * keyname );
sub_6F002170 sub_6F002170org;
sub_6F002170 sub_6F002170ptr;
int __fastcall  sub_6F002170my( int a1 , int a0 , const char * sectionname , const char * keyname )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration3.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F002170ptr( a1 , sectionname , keyname );
}























typedef int( __fastcall * sub_6F009F90 )( const char * sectionname , const char * keyname , unsigned int a3 );
sub_6F009F90 sub_6F009F90org;
sub_6F009F90 sub_6F009F90ptr;

int __fastcall sub_6F009F90my( const char * sectionname , const char * keyname , unsigned int a3 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F009F90ptr( sectionname , keyname , a3 );
}

typedef int( __fastcall * sub_6F009EE0 )( int a1 , const char * sectionname , const char * keyname , unsigned int a4 );
sub_6F009EE0 sub_6F009EE0org;
sub_6F009EE0 sub_6F009EE0ptr;

int __fastcall  sub_6F009EE0my( int a1 , const char * sectionname , const char * keyname , unsigned int a4 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F009EE0ptr( a1 , sectionname , keyname , a4 );
}

typedef int( __fastcall * sub_6F009D80 )( const char * sectionname , const char * keyname , unsigned int a3 );
sub_6F009D80 sub_6F009D80org;
sub_6F009D80 sub_6F009D80ptr;

int __fastcall  sub_6F009D80my( const char * sectionname , const char * keyname , unsigned int a3 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F009D80ptr( sectionname , keyname , a3 );
}

typedef double( __fastcall * sub_6F009E30 )( const char * sectionname , const char * keyname , unsigned int a3 );
sub_6F009E30 sub_6F009E30org;
sub_6F009E30 sub_6F009E30ptr;

double __fastcall  sub_6F009E30my( const char * sectionname , const char * keyname , unsigned int a3 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F009E30ptr( sectionname , keyname , a3 );
}

typedef int( __fastcall * sub_6F00A040 )( const char * sectionname , const char * keyname , int a3 , int a4 , unsigned int a5 );
sub_6F00A040 sub_6F00A040org;
sub_6F00A040 sub_6F00A040ptr;

int __fastcall sub_6F00A040my( const char * sectionname , const char * keyname , int a3 , int a4 , unsigned int a5 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F00A040ptr( sectionname , keyname , a3 , a4 , a5 );
}













typedef int (__fastcall * sub_6F4D1F80)( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 );
sub_6F4D1F80 sub_6F4D1F80org;
sub_6F4D1F80 sub_6F4D1F80ptr;
int __fastcall  sub_6F4D1F80my( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D1F80ptr( a1 , sectionname , keyname , a4 , a5 );
}

typedef int( __fastcall *  sub_6F4D1FC0 )( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 );
sub_6F4D1FC0 sub_6F4D1FC0org;
sub_6F4D1FC0 sub_6F4D1FC0ptr;

int __fastcall   sub_6F4D1FC0my( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D1FC0ptr( a1 , sectionname , keyname , a4 , a5 );
}
typedef int( __fastcall *  sub_6F4D2000 )( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 );
sub_6F4D2000 sub_6F4D2000org;
sub_6F4D2000 sub_6F4D2000ptr;

int __fastcall   sub_6F4D2000my( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D2000ptr( a1 , sectionname , keyname , a4 , a5 );
}

typedef signed int( __fastcall *  sub_6F4D2040 )( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 );
sub_6F4D2040 sub_6F4D2040org;
sub_6F4D2040 sub_6F4D2040ptr;

signed int __fastcall   sub_6F4D2040my( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 )
{ 

	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D2040ptr( a1 , sectionname , keyname , a4 , a5 );
}

typedef int( __fastcall *  sub_6F4D2080 )( int a1 , const char * sectionname , const char * keyname , int a4 , int a5 , unsigned int a6 );
sub_6F4D2080 sub_6F4D2080org;
sub_6F4D2080 sub_6F4D2080ptr;

int __fastcall  sub_6F4D2080my ( int a1 , const char * sectionname , const char * keyname , int a4 , int a5 , unsigned int a6 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D2080ptr( a1 , sectionname , keyname , a4 , a5 , a6 );

}

typedef int( __fastcall *  sub_6F4D1F30 )( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 );
sub_6F4D1F30 sub_6F4D1F30org;
sub_6F4D1F30 sub_6F4D1F30ptr;

int __fastcall sub_6F4D1F30my ( int a1 , const char * sectionname , const char * keyname , int a4 , unsigned int a5 )
{
	CIniWriter GlobalWriter( ".\\WarcraftConfiguration.ini" );

	GlobalWriter.WriteInteger( sectionname , keyname , 0 );
	return sub_6F4D1F30ptr( a1 , sectionname , keyname , a4 , a5 );
}


DWORD WINAPI ReadWarcraftConfiguration( LPVOID )
{
	/*ReadGameDataBase_org = ( sub_6F7B2BE0 ) ( GameDll + 0x7B2BE0 );
	MH_CreateHook( ReadGameDataBase_org , &ReadGameDataBase_my , reinterpret_cast< void** >( &ReadGameDataBase_ptr ) );
	MH_EnableHook( ReadGameDataBase_org );*/
	/*sub_6F4D20E0org = ( sub_6F4D20E0 ) ( 0x4D20E0 + GameDll );
	MH_CreateHook( sub_6F4D20E0org , &sub_6F4D20E0my , reinterpret_cast< void** >( &sub_6F4D20E0ptr ) );
	MH_EnableHook( sub_6F4D20E0org );

	sub_6F4D20C0org = ( sub_6F4D20C0 ) ( 0x4D20C0 + GameDll );
	MH_CreateHook( sub_6F4D20C0org , &sub_6F4D20C0my , reinterpret_cast< void** >( &sub_6F4D20C0ptr ) );
	MH_EnableHook( sub_6F4D20C0org );

	sub_6F002170org = ( sub_6F002170 ) ( 0x2170 + GameDll );
	MH_CreateHook( sub_6F002170org , &sub_6F002170my , reinterpret_cast< void** >( &sub_6F002170ptr ) );
	MH_EnableHook( sub_6F002170org );*/


	sub_6F009F90org = ( sub_6F009F90 ) ( 0x9F90 + GameDll );
	MH_CreateHook( sub_6F009F90org , &sub_6F009F90my , reinterpret_cast< void** >( &sub_6F009F90ptr ) );
	MH_EnableHook( sub_6F009F90org );
	sub_6F009EE0org = ( sub_6F009EE0 ) ( 0x9EE0 + GameDll );
	MH_CreateHook( sub_6F009EE0org , &sub_6F009EE0my , reinterpret_cast< void** >( &sub_6F009EE0ptr ) );
	MH_EnableHook( sub_6F009EE0org );
	sub_6F009D80org = ( sub_6F009D80 ) ( 0x9D80 + GameDll );
	MH_CreateHook( sub_6F009D80org , &sub_6F009D80my , reinterpret_cast< void** >( &sub_6F009D80ptr ) );
	MH_EnableHook( sub_6F009D80org );
	sub_6F009E30org = ( sub_6F009E30 ) ( 0x09E30 + GameDll );
	MH_CreateHook( sub_6F009E30org , &sub_6F009E30my , reinterpret_cast< void** >( &sub_6F009E30ptr ) );
	MH_EnableHook( sub_6F009E30org );
	sub_6F00A040org = ( sub_6F00A040 ) ( 0xA040 + GameDll );
	MH_CreateHook( sub_6F00A040org , &sub_6F00A040my , reinterpret_cast< void** >( &sub_6F00A040ptr ) );
	MH_EnableHook( sub_6F00A040org );



	sub_6F4D1F80org = ( sub_6F4D1F80 ) ( 0x4D1F80 + GameDll );
	MH_CreateHook( sub_6F4D1F80org , &sub_6F4D1F80my , reinterpret_cast< void** >( &sub_6F4D1F80ptr ) );
	MH_EnableHook( sub_6F4D1F80org );

	sub_6F4D1FC0org = ( sub_6F4D1FC0 ) ( 0x4D1FC0 + GameDll );
	MH_CreateHook( sub_6F4D1FC0org , &sub_6F4D1FC0my , reinterpret_cast< void** >( &sub_6F4D1FC0ptr ) );
	MH_EnableHook( sub_6F4D1FC0org );

	sub_6F4D2000org = ( sub_6F4D2000 ) ( 0x4D2000 + GameDll );
	MH_CreateHook( sub_6F4D2000org , &sub_6F4D2000my , reinterpret_cast< void** >( &sub_6F4D2000ptr ) );
	MH_EnableHook( sub_6F4D2000org );

	sub_6F4D2040org = ( sub_6F4D2040 ) ( 0x4D2040 + GameDll );
	MH_CreateHook( sub_6F4D2040org , &sub_6F4D2040my , reinterpret_cast< void** >( &sub_6F4D2040ptr ) );
	MH_EnableHook( sub_6F4D2040org );

	sub_6F4D2080org = ( sub_6F4D2080 ) ( 0x4D2080 + GameDll );
	MH_CreateHook( sub_6F4D2080org , &sub_6F4D2080my , reinterpret_cast< void** >( &sub_6F4D2080ptr ) );
	MH_EnableHook( sub_6F4D2080org );

	sub_6F4D1F30org = ( sub_6F4D1F30 ) ( 0x4D1F30 + GameDll );
	MH_CreateHook( sub_6F4D1F30org , &sub_6F4D1F30my , reinterpret_cast< void** >( &sub_6F4D1F30ptr ) );
	MH_EnableHook( sub_6F4D1F30org );

	return 0;
}




BOOL DetourJMP( DWORD offset , DWORD to , int nopcount )
{
	char* buff = new char[ 5 + nopcount ];
	buff[ 0 ] = 0xE9U;
	*( DWORD* ) &buff[ 1 ] = to - ( offset + 5 );
	for ( int i = 0; i < nopcount; i++ )
		buff[ 5 + i ] = 0x90U;
	delete[ ]buff;
	return TRUE;
}

BOOL WINAPI DllMain( HINSTANCE hDLL , UINT reason , LPVOID reserved )
{
	if ( reason == DLL_PROCESS_ATTACH )
	{
		/*if ( !AllocConsole( ) ) return 1;

		SetConsoleCtrlHandler( MyConsoleCtrlHandler , TRUE );
		RemoveMenu( GetSystemMenu( GetConsoleWindow( ) , FALSE ) , SC_CLOSE , MF_BYCOMMAND );
		const int in = _open_osfhandle( INT_PTR( GetStdHandle( STD_INPUT_HANDLE ) ) , _O_TEXT );
		const int out = _open_osfhandle( INT_PTR( GetStdHandle( STD_OUTPUT_HANDLE ) ) , _O_TEXT );

		*stdin = *_fdopen( in , "r" );
		*stdout = *_fdopen( out , "w" );
		*/

	

		DisableThreadLibraryCalls( hDLL );
		MH_Initialize( );
		//ConfigThread( 0 );
		CreateThread( 0 , 0 , ReadWarcraftConfiguration , 0 , 0 , 0 );
	}
	else if ( reason == DLL_PROCESS_DETACH )
	{
		MH_Uninitialize( );
	}
	return TRUE;
}