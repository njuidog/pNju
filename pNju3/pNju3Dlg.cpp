
// pNju3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pNju3.h"
#include "pNju3Dlg.h"
#include "afxdialogex.h"

#include <afxinet.h>
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpNju3Dlg 对话框




CpNju3Dlg::CpNju3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpNju3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpNju3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERID, m_UserID);
	DDX_Control(pDX, IDC_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_VERIFYCODE, m_VerifyCode);
}

BEGIN_MESSAGE_MAP(CpNju3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CpNju3Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CpNju3Dlg 消息处理程序

BOOL CpNju3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	/*GetVerifyPng(".\\VerifyCode.png");
	CImage img;
	img.Load(".\\VerifyCode.png");
	
	int Code=Verify(".\\VerifyCode.png");
	char VerifyCode[2];
	itoa(Code,VerifyCode,10);
	m_VerifyCode.SetWindowTextA(VerifyCode);
	
	//DeleteFile(".\\VerifyCode.png");*/




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpNju3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpNju3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	//显示验证码
	GetVerifyPng(".\\VerifyCode.png");
	CImage img;
	img.Load(".\\VerifyCode.png");
	HDC hdc=::GetDC(m_hWnd);
	img.Draw(hdc,135,85,80,25);

	CString VerifyCode=Verify(".\\VerifyCode.png");  //     识别验证码主程序
	m_VerifyCode.SetWindowTextA(VerifyCode);

	CString UserID,Password;
	ReadUserIDPassword(UserID,Password);
	m_UserID.SetWindowTextA(UserID);
	m_Password.SetWindowTextA(Password);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpNju3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CpNju3Dlg::GetVerifyPng(char* filepath)  //获取验证码图片
{
	CInternetSession Session;
	CHttpConnection* pServer;
	FILE* file;
	file=fopen(filepath,"wb");
	pServer = Session.GetHttpConnection("p.nju.edu.cn");
	CHttpFile *pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,"/portal/img.html?id=123");
	pFile->AddRequestHeaders("Content-Type: application/x-www-form-urlencoded");
	pFile->AddRequestHeaders("Cache-Control: no-cache");
	pFile->SendRequest();
	DWORD dwStatus = NULL;
	pFile->QueryInfoStatusCode(dwStatus);
	if (dwStatus == HTTP_STATUS_OK)
	{
		char *RecvBuf=new char[8001];
		memset(RecvBuf,0,sizeof(RecvBuf));
		int DataSize=0;
		while((DataSize=pFile->Read(RecvBuf,8000))>0)
		{
			fwrite(RecvBuf,sizeof(char),RecvBuf+DataSize-&RecvBuf[0],file);
			memset(RecvBuf,0,sizeof(RecvBuf));
		}
		delete[] RecvBuf;
	}
	pFile->Close();
	delete pFile;
	fclose(file);
	return 0;
}



CString CpNju3Dlg::Verify(char* VerifyPath) // 识别验证码 
{
	int VerifyData[4][25*17]={};

	CImage img;
	img.Load(VerifyPath);

	// cut png to four numbers
	for(int w=9;w<26;++w)
	{
		for(int h=0;h<25;++h)
		{
			VerifyData[0][(w-9)*25+h]=GetRValue(img.GetPixel(w,h))
				+GetGValue(img.GetPixel(w,h))+GetBValue(img.GetPixel(w,h));
		}
	}

	for(int w=26;w<43;++w)
	{
			for(int h=0;h<25;++h)
			{
				VerifyData[1][(w-26)*25+h]=GetRValue(img.GetPixel(w,h))
				+GetGValue(img.GetPixel(w,h))+GetBValue(img.GetPixel(w,h));
			}
	}

	for(int w=43;w<60;++w)
	{
		for(int h=0;h<25;++h)
		{
			VerifyData[2][(w-43)*25+h]=GetRValue(img.GetPixel(w,h))
				+GetGValue(img.GetPixel(w,h))+GetBValue(img.GetPixel(w,h));
		}
	}

	for(int w=60;w<77;++w)
	{
		for(int h=0;h<25;++h)
		{
			VerifyData[3][(w-60)*25+h]=GetRValue(img.GetPixel(w,h))
				+GetGValue(img.GetPixel(w,h))+GetBValue(img.GetPixel(w,h));
		}
	}

	// import standard data
	int StandardData[400][25*17]={};
	FILE *file;
	file=fopen("StandardData.dat","r"); 
	fread(StandardData,sizeof(int),400*25*17,file);
	fclose(file);

	// distance
	int Distance[400]={};

	for(int i=0;i<400;++i)
	{
		for(int j=0;j<25*17;++j)
		{
			int temp=StandardData[i][j]-VerifyData[i/100][j];		
			Distance[i]+=temp*temp;
		}
	}

	
	//nearst point 
	CString result;
	char ResultTemp[2];

	int ResultIndex=0;// first number
	for(int i=0;i<100;++i)  
	{
		if(Distance[i]<Distance[ResultIndex])
			ResultIndex=i;
	}
	itoa(ResultIndex/10,ResultTemp,10);
	result=ResultTemp;

	ResultIndex=100;// second number
	for(int i=100;i<200;++i)  
	{
		if(Distance[i]<Distance[ResultIndex])
			ResultIndex=i;
	}
	itoa((ResultIndex-100)/10,ResultTemp,10);
	result+=ResultTemp;

	ResultIndex=200;// third number
	for(int i=200;i<300;++i)  
	{
		if(Distance[i]<Distance[ResultIndex])
			ResultIndex=i;
	}
	itoa((ResultIndex-200)/10,ResultTemp,10);
	result+=ResultTemp;

	ResultIndex=300;// fourth number
	for(int i=300;i<400;++i)  
	{
		if(Distance[i]<Distance[ResultIndex])
			ResultIndex=i;
	}
	itoa((ResultIndex-300)/10,ResultTemp,10);
	result+=ResultTemp;

	
	return result;
}



int CpNju3Dlg::FillEdit(void)
{
	CString UserID,Password,VerifyCode;
	int Code;

	

	m_UserID.GetWindowTextA(UserID);
	if(UserID=="")
	{
		MessageBox("请输入用户名");
		return 1;
	}
	m_Password.GetWindowTextA(Password);
	if(Password=="")
	{
		MessageBox("请输入密码");
		return 1;
	}
	m_VerifyCode.GetWindowTextA(VerifyCode);
	if(VerifyCode=="")
	{
		MessageBox("请输入验证码");
		return 1;
	}
	Code=atoi(VerifyCode);

	Connect(UserID,Password,VerifyCode);  //连接
	SaveUserIDPassword(UserID,Password);

	

	return 0;

}




void CpNju3Dlg::Connect(CString UserID, CString Password, CString VerifyCode)
{
		CInternetSession Session;
	CHttpConnection* pServer;
	pServer = Session.GetHttpConnection("p.nju.edu.cn");
	CHttpFile *pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST,"/portal.do");

	CString strHeaders="Content-Type: application/x-www-form-urlencoded\r\nCache-Control: no-cache\r\n\
		Origin: http://p.nju.edu.cn\r\n";
	CString strPost="action=login&url=http%3A%2F%2Fp.nju.edu.cn&p_login=p_login&username="
		+UserID+"&password="+Password+"&code="+VerifyCode+"&x=29&y=23";
	pFile->SendRequest(strHeaders,strHeaders.GetLength(),(LPVOID)(LPCTSTR)strPost, strPost.GetLength());

	pFile->Close();
}


void CpNju3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(0==FillEdit())
	{
		CDialogEx::OnOK();
	}
}


void CpNju3Dlg::SaveUserIDPassword(CString UserID, CString Password)
{
	HKEY hKey;
	RegCreateKey(HKEY_LOCAL_MACHINE,"Software\\pNju\\admin",&hKey);

	RegSetValueEx(hKey,"UserID",0,REG_SZ,(CONST BYTE*)(LPCTSTR)UserID,UserID.GetLength());
	RegSetValueEx(hKey,"Password",0,REG_SZ,(CONST BYTE*)(LPCTSTR)Password,Password.GetLength());
	RegCloseKey(hKey);
}


void CpNju3Dlg::ReadUserIDPassword(CString& UserID, CString& Password)
{
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\pNju\\admin",&hKey);
	
	LPBYTE GetUserID=new BYTE[30];
	LPBYTE GetPassword=new BYTE[200];
	DWORD WordType=REG_SZ; 
	DWORD WordData=30;
	DWORD WordData2=200;
	if(ERROR_SUCCESS!=RegQueryValueEx(hKey,"UserID",NULL,&WordType,GetUserID,&WordData))
		return;
	RegQueryValueEx(hKey,"Password",NULL,&WordType,GetPassword,&WordData2);

	UserID=(LPTSTR)GetUserID;
	Password=(LPTSTR)GetPassword;

}
