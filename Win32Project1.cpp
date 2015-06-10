// Win32Project1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100
#define MAX_IN_STR 20000

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
bool ViewFlag=FALSE,LoadFlag=FALSE;

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Load(HWND, UINT, WPARAM, LPARAM);
INT_PTR openf(HWND hDlg,int Id);
INT_PTR savef(HWND hDlg);
INT_PTR Loadf(HWND hDlg);
INT_PTR BuildHtm(LPSTR outStr,LPSTR titleStr,LPSTR imagePath,LPSTR mainStr);
BOOL FileExist(LPSTR strPath)  ;
int GBKToUTF8(char * lpGBKStr,char * lpUTF8Str,int nUTF8StrLen);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_LOAD:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LOAD), hWnd, Load);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//"��ȡ"�����Ϣ�������
INT_PTR CALLBACK Load(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_CLOSE: 
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
	case WM_COMMAND:{
		if (LOWORD(wParam)==IDC_L_Cancel)//��֪Ϊ��ʹ��switchǶ�׻ᵼ�³���
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			
		}
		else if (LOWORD(wParam)==IDC_View)
			openf(hDlg,IDC_Paths);
		else if (LOWORD(wParam)==IDC_L_OK){
			savef(hDlg);}
		else if (LOWORD(wParam)==IDC_L_Load){
			Loadf( hDlg);
		}
		break;
					}
	}
	return (INT_PTR)FALSE;
}
	INT_PTR openf(HWND hDlg,int Id) //��ȡ�ļ�λ��ģ��
{
OPENFILENAME opfn;  
WCHAR strFilename[MAX_PATH];//����ļ���  
//��ʼ��  
ZeroMemory(&opfn, sizeof(OPENFILENAME));  
opfn.lStructSize = sizeof(OPENFILENAME);//�ṹ���С  
//���ù���  
opfn.lpstrFilter = L"�����ļ�\0*.*\0ͼƬ�ļ�(*.jpg)\0*.jpg\0ͼƬ�ļ�(*.png)\0*.png\0";  
//Ĭ�Ϲ�����������Ϊ1  
opfn.nFilterIndex = 1;  
//�ļ������ֶα����Ȱѵ�һ���ַ���Ϊ \0  
opfn.lpstrFile = strFilename;  
opfn.lpstrFile[0] = '\0';  
opfn.nMaxFile = sizeof(strFilename);  
//���ñ�־λ�����Ŀ¼���ļ��Ƿ����  
opfn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;  
//opfn.lpstrInitialDir = NULL;  
// ��ʾ�Ի������û�ѡ���ļ�  
if(GetOpenFileName(&opfn))  
	{  
    //���ı�������ʾ�ļ�·��  
    HWND hEdt = GetDlgItem(hDlg, Id);  
    SendMessage(hEdt, WM_SETTEXT, NULL, (LPARAM)strFilename);  
	ViewFlag=TRUE;
	}  
return 0;
}
INT_PTR savef(HWND hDlg)//�ļ�����ģ��
{
	if(ViewFlag)
	{
		LPSTR Num,Inum,FileName,MainStrGB,MainStrUTF,TitleStrGB,TitleStrUTF,InStr;
		Num=(LPSTR)malloc(20*sizeof(CHAR));
		Inum=(LPSTR)malloc(20*sizeof(CHAR));
		if (GetDlgItemTextA(hDlg,IDC_Num,Num,4))//��ȡ�ļ����,�����ж��Ƿ�Ϊ��
			{	
				FileName=(LPSTR)malloc(MAX_PATH*sizeof(CHAR));
				MainStrGB=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));
				MainStrUTF=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));
				TitleStrGB=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));
				TitleStrUTF=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));//��ʼ��,��һ��ʵ�����������ȡģ������á��������ڴ���������͸�����ȥ����
				InStr=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));
				GetDlgItemTextA(hDlg,IDC_Paths,FileName,MAX_PATH);
				GetDlgItemTextA(hDlg,IDC_Main,MainStrGB,MAX_IN_STR);
				GetDlgItemTextA(hDlg,IDC_TITLE,TitleStrGB,MAX_IN_STR);
				strcpy_s(Inum,20,Num);
				strcat_s(Inum,20,PathFindExtensionA(FileName)); 
				strcat_s(Num,20,".htm");
				CopyFileA(FileName,Inum, FALSE);
				GBKToUTF8(MainStrGB,MainStrUTF,MAX_IN_STR);
				GBKToUTF8(TitleStrGB,TitleStrUTF,MAX_IN_STR);
				BuildHtm(InStr,TitleStrUTF,Inum,MainStrUTF);
				HANDLE FileHandle;
				FileHandle=CreateFileA(Num,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
				DWORD dwWrites;
				WriteFile(FileHandle,InStr,strlen(InStr),&dwWrites,NULL);
				CloseHandle(FileHandle);
				return 0;
			}else 
		{
			MessageBox(hDlg,TEXT("�ĵ���Ų���Ϊ��"),NULL,MB_OK|MB_ICONWARNING);
			return 0;
		}
	}else{
			MessageBox(hDlg,TEXT("����ѡ����ͼ"),NULL,MB_OK|MB_ICONWARNING);
			return 0;
		}
}
INT_PTR Loadf(HWND hDlg)
{
	WCHAR *OutStr,*MainStr,*TitleStr;
	LPSTR Num;
	int Count=0,C2=0;
	DWORD ERR;
	Num=(LPSTR)malloc(20*sizeof(CHAR));
	HANDLE hFile=(HANDLE)malloc(sizeof(HANDLE));
	if (GetDlgItemTextA(hDlg,IDC_Num,Num,4))
	{
		strcat_s(Num,20,".htm");
		if(!FileExist(Num))
		{
			if((MessageBox(hDlg,TEXT("�ļ������ڣ��Ƿ񴴽�?"),TEXT("ȷ��"),MB_YESNO|MB_ICONQUESTION))==IDYES)
			{
				LoadFlag=TRUE;
				PostMessage(hDlg,EM_SETREADONLY,1,0);
				
				return 0;
			}else
			{
				return 0;
			}
		}else
		{
			LPDWORD NumBuff=(LPDWORD)malloc(sizeof(DWORD));
			OutStr=(WCHAR*)malloc(MAX_IN_STR*sizeof(WCHAR));
			MainStr=(WCHAR*)malloc(MAX_IN_STR*sizeof(WCHAR));
			//=(LPSTR)malloc(MAX_IN_STR*sizeof(CHAR));
			LPSTR Start;
			WCHAR* TitleStr=(WCHAR*)malloc(MAX_IN_STR*sizeof(WCHAR));
			hFile=CreateFileA(Num,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			ReadFile(hFile,OutStr,MAX_IN_STR,NumBuff,NULL);
			ERR=GetLastError();
			Start=strstr(OutStr,"<TITLE>");
			Count=7,C2=0;
			while(Start[Count]!='<'){
				TitleStr[C2]=Start[Count];
				Count++,C2++;
			}
			TitleStr[C2]='\0';
			TitleStr[C2+1]='\0';
			HWND hElg;
			hElg=GetDlgItem(hDlg,IDC_TITLE);
			SendMessage(hElg, WM_SETTEXT, NULL, (LPARAM)TitleStr);
			return 0;
		}



	}else 
	{
		MessageBox(hDlg,TEXT("�ĵ���Ų���Ϊ��"),NULL,MB_OK|MB_ICONWARNING);
			return 0;
	}
}

int GBKToUTF8(char * lpGBKStr,char * lpUTF8Str,int nUTF8StrLen)
{
 wchar_t * lpUnicodeStr = NULL;
 int nRetLen = 0;

 if(!lpGBKStr)  //���GBK�ַ���ΪNULL������˳�
  return 0;

 nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,NULL,NULL);  //��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
 lpUnicodeStr = new WCHAR[nRetLen + 1];  //ΪUnicode�ַ����ռ�
 nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,lpUnicodeStr,nRetLen);  //ת����Unicode����
 if(!nRetLen)  //ת��ʧ��������˳�
  return 0;

 nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,NULL,0,NULL,NULL);  //��ȡת����UTF8���������Ҫ���ַ��ռ䳤��

 if(!lpUTF8Str)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
 {
  if(lpUnicodeStr)
   delete []lpUnicodeStr;
  return nRetLen;
 }

 if(nUTF8StrLen < nRetLen)  //���������������Ȳ������˳�
 {
  if(lpUnicodeStr)
   delete []lpUnicodeStr;
  return 0;
 }

 nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,(char *)lpUTF8Str,nUTF8StrLen,NULL,NULL);  //ת����UTF8����

 if(lpUnicodeStr)
  delete []lpUnicodeStr;

 return nRetLen;
}
INT_PTR BuildHtm(LPSTR outStr,LPSTR titleStr,LPSTR imageNum,LPSTR mainStr)//��д��ҳģ�飬��Ҫ�޸���ʽ�޸����Ｔ��
{
	*outStr=0;
	strcat_s(outStr,MAX_IN_STR,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"><HTML><HEAD><TITLE>");
	strcat_s(outStr,MAX_IN_STR,titleStr);
	strcat_s(outStr,MAX_IN_STR,"</TITLE><META content=\"text/html; charset=unicode\" http-equiv=Content-Type><META name=GENERATOR content=\"MSHTML 11.00.9600.16384\"></HEAD><BODY><P align=center><SPAN id=wiz_font_size_span_47009778 style=\"FONT-SIZE: 20pt\">&nbsp; ");
	strcat_s(outStr,MAX_IN_STR,titleStr);
	strcat_s(outStr,MAX_IN_STR,"</SPAN></P><P align=center><SPAN style=\"FONT-SIZE: 20pt\"><IMG border=0 hspace=0 alt=\"\" src=\"192.168.1.1\\");
	strcat_s(outStr,MAX_IN_STR,imageNum);
	strcat_s(outStr,MAX_IN_STR,"\" align=baseline></SPAN></P><P align=left><SPAN style=\"FONT-SIZE: 20pt\"><FONT size=3>");
	strcat_s(outStr,MAX_IN_STR,mainStr);
	strcat_s(outStr,MAX_IN_STR,"</FONT></SPAN></P></BODY></HTML>");
	return 0;
}
BOOL FileExist(LPSTR strPath)  
{  
    WIN32_FIND_DATAA wfd;  
    BOOL rValue = FALSE;  
    HANDLE hFind = FindFirstFileA(strPath, &wfd);  
    if ( hFind!=INVALID_HANDLE_VALUE )  
    {  
        rValue = TRUE;  
    }  
    FindClose(hFind);  
    return rValue;  
}  