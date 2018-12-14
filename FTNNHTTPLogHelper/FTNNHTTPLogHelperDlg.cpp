
// FTNNHTTPLogHelperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FTNNHTTPLogHelper.h"
#include "FTNNHTTPLogHelperDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include <afxmsg_.h>
#include <afxwin.h>
#include <string>
#include <vector>
#include "zip.h"
#include "Resource.h"
#include "zlib.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_UPDATE 1001
#define ZR_ENTITY 83886080
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


// CFTNNHTTPLogHelperDlg 对话框

void CFTNNHTTPLogHelperDlg::OnOK()
{
	//重载OnOK截取Enter
}

CFTNNHTTPLogHelperDlg::CFTNNHTTPLogHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTNNHTTPLogHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_FTNN);
}

void CFTNNHTTPLogHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTNNHTTPLogHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_DOWNLOAD, &CFTNNHTTPLogHelperDlg::OnBnClickedDownload)
	ON_EN_CHANGE(IDC_URLEDIT, &CFTNNHTTPLogHelperDlg::OnEnChangeUrledit)
	ON_STN_CLICKED(IDC_STATIC, &CFTNNHTTPLogHelperDlg::OnStnClickedStaitc)
	ON_STN_CLICKED(IDC_DOWNTEXT, &CFTNNHTTPLogHelperDlg::OnStnClickedDowntext)
END_MESSAGE_MAP()


// CFTNNHTTPLogHelperDlg 消息处理程序

BOOL CFTNNHTTPLogHelperDlg::OnInitDialog()
{



	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// ID_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFTNNHTTPLogHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFTNNHTTPLogHelperDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFTNNHTTPLogHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CFTNNHTTPLogHelperDlg::HTTPGetFile(CString URLStr, CString strLocalSavePath)
{

	
	CString strURL = URLStr;
	CString strSavePath = strLocalSavePath;
	CString localPath;

	if (strURL.IsEmpty())
		return FALSE;
	if (strSavePath.IsEmpty())
		return FALSE;
	unsigned short nPort;//服务器端口
	CString strServer, strObject;//服务器名称以及文件名称
	DWORD dwServiceType, dwRet;
	if (!AfxParseURL(strURL, dwServiceType, strServer, strObject, nPort))//解析URL
	{
		return FALSE;
	}
	CInternetSession pSession;
	CHttpConnection *pConnect = pSession.GetHttpConnection(strServer, nPort);

	if (pConnect == NULL)
	{
		pSession.Close();
		return FALSE;
	}

	CHttpFile *pFile = pConnect->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
	if (pFile == NULL)
	{
		pSession.Close();
		delete pConnect;
		pConnect = NULL;
		return FALSE;
	}
	pFile->SendRequest();
	pFile->QueryInfoStatusCode(dwRet);
	if (dwRet != HTTP_STATUS_OK)
	{
		pSession.Close();
		delete pConnect;
		pConnect = NULL;
		return FALSE;
	}
	UINT fileLen = (UINT)pFile->GetLength();
	DWORD dwRead = 1;
	CHAR *szBuffer = new CHAR[fileLen + 1];
	try{
		CString str = _T("正在下载");
		int flag = 0;
		localPath.Format(_T("%s%s%s%s"), strSavePath, _T("\\"), pFile->GetFileName().Right(8),_T(".zip"));
		CFile localFile(localPath, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);

		while (dwRead)
		{

			memset(szBuffer, 0, (size_t)(fileLen + 1));
			//读取到缓冲区
			dwRead = pFile->Read(szBuffer, fileLen);
			//写入到文件
			localFile.Write(szBuffer, dwRead);
		}
		localFilePath = localPath;
		GetDlgItem(IDC_DOWNTEXT)->SetWindowTextW(_T("下载完成，准备解压..."));
		//http://172.18.10.120:8080/HttpServer/Tencent.zip

		localFile.Close();
		delete[]szBuffer;
		delete pFile;
		delete pConnect;
		pSession.Close();

	}
	catch (CFileException e)
	{
		delete[]szBuffer;
		delete pFile;
		delete pConnect;
		pSession.Close();
		return FALSE;
	}
	return TRUE;
}

CString CFTNNHTTPLogHelperDlg::GetLocalFilePath()
{
	//
	char szPath[10000];
	CString strLocalDir = CString(szPath);
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	strLocalDir.Format(_T("%s"), strLocalDir);
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = T2W((LPTSTR)strLocalDir.GetBuffer(NULL));

	bi.lpszTitle = _T("请选择要将文件保存的目录：");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, bi.pszDisplayName))
		return strLocalDir;
	else return NULL;

}

void CFTNNHTTPLogHelperDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CFTNNHTTPLogHelperDlg::OnBnClickedDownload()
{
	flag = 0;
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_URLEDIT);
	flag_UnCompress = TRUE;
	CString URLStr;//http://172.18.10.120:8080/HttpServer/VS2010SP1.iso
	pEdit->GetWindowTextW(URLStr);

	CString strServer;
	CString strFileName;
	CString strLocalFile = GetLocalFilePath();

	//m_ThreadDownload = CreateThread(NULL, 0,HTTPGetFile, (LPVOID)&strURLAndFile, 0, NULL);
	BOOL IsSuccess = HTTPGetFile(URLStr, strLocalFile);

	if(unCompressFile(&localFilePath))
		DeleteFile(localFilePath);
	AfxMessageBox(_T("下载解压完成"));
}


void CFTNNHTTPLogHelperDlg::OnEnChangeUrledit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
BOOL CFTNNHTTPLogHelperDlg::unCompressFile(CString *mZipFileFullPath)
{

	ZRESULT zr;
	ZIPENTRY ze;

	CString mUnpackPath = mZipFileFullPath->Left(mZipFileFullPath->GetLength() - 4);
	if (mZipFileFullPath->IsEmpty() || mUnpackPath.IsEmpty())
		return FALSE;
	CFileFind unFile;
	if (!unFile.FindFile(*mZipFileFullPath))//获取压缩的文件
	{
		return FALSE;
	}
	CString tZipFilePath = mUnpackPath;
	if (!CFTNNHTTPLogHelperDlg::FolderExist(tZipFilePath))//如果解压缩的路径不存在就创建它
	{
		CStringW strWZipFilePath(tZipFilePath);
		if (CreatedMultipleDirectory((LPWSTR)(LPCWSTR)strWZipFilePath) == FALSE)
		{
			return FALSE;
		}
	}


	HZIP hz = OpenZip(*mZipFileFullPath, 0);//打开ZIP文件
	int nReadFileSize = 0;

	if (hz == 0)
		return FALSE;
	zr = SetUnzipBaseDir(hz, mUnpackPath);
	if (zr != ZR_OK)
	{
		CloseZip(hz);
		return FALSE;
	}
	zr = GetZipItem(hz, -1, &ze);//获取zip文件内容

	if (zr != ZR_OK)
	{
		CloseZip(hz);
		return FALSE;
	}
	int numItem = ze.index;
	for (int i = 0; i < numItem; i++)//http://172.28.249.58:8081/log/download?date=20181213
	{
		zr = GetZipItem(hz, i, &ze);
		zr = UnzipItem(hz, i, ze.name);
		if (zr != ZR_OK&&zr != ZR_ENTITY)//83886080
		{
			CloseZip(hz);
			DeleteFile(*mZipFileFullPath);
			return FALSE;
		}
	}
	
	CloseZip(hz);
	return TRUE;
}
BOOL CFTNNHTTPLogHelperDlg::FolderExist(CString& strPath)
{
	CString sCheckPath = strPath;

	if (sCheckPath.Right(1) != L"\\")
		sCheckPath += L"\\";

	sCheckPath += L"*.*";

	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;

	HANDLE hFind = FindFirstFile(sCheckPath, &wfd);

	if ((hFind != INVALID_HANDLE_VALUE) &&
		(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) || (wfd.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE))
	{
		//如果存在并类型是文件夹 
		rValue = TRUE;
	}

	FindClose(hFind);
	return rValue;
}


BOOL CFTNNHTTPLogHelperDlg::CreatedMultipleDirectory(wchar_t* direct)
{
	wstring Directoryname = direct;

	if (Directoryname[Directoryname.length() - 1] != '\\')
	{
		Directoryname.append(1, '\\');
	}
	vector< wstring> vpath;
	wstring strtemp;
	BOOL  bSuccess = FALSE;
	for (int i = 0; i < Directoryname.length(); i++)
	{
		if (Directoryname[i] != '\\')
		{
			strtemp.append(1, Directoryname[i]);
		}
		else
		{
			vpath.push_back(strtemp);
			strtemp.append(1, '\\');
		}
	}
	std::vector<wstring>::const_iterator vIter;
	for (vIter = vpath.begin(); vIter != vpath.end(); vIter++)
	{
		USES_CONVERSION;
		bSuccess = CreateDirectoryA(W2A(vIter->c_str()), NULL) ? true : false;

	}
	return bSuccess;

}

void CFTNNHTTPLogHelperDlg::OnStnClickedStaitc()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CFTNNHTTPLogHelperDlg::OnStnClickedDowntext()
{
	// TODO:  在此添加控件通知处理程序代码
}



