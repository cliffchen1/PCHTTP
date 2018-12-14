
// FTNNHTTPLogHelperDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CFTNNHTTPLogHelperDlg �Ի���

void CFTNNHTTPLogHelperDlg::OnOK()
{
	//����OnOK��ȡEnter
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


// CFTNNHTTPLogHelperDlg ��Ϣ�������

BOOL CFTNNHTTPLogHelperDlg::OnInitDialog()
{



	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// ID_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFTNNHTTPLogHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	unsigned short nPort;//�������˿�
	CString strServer, strObject;//�����������Լ��ļ�����
	DWORD dwServiceType, dwRet;
	if (!AfxParseURL(strURL, dwServiceType, strServer, strObject, nPort))//����URL
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
		CString str = _T("��������");
		int flag = 0;
		localPath.Format(_T("%s%s%s%s"), strSavePath, _T("\\"), pFile->GetFileName().Right(8),_T(".zip"));
		CFile localFile(localPath, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);

		while (dwRead)
		{

			memset(szBuffer, 0, (size_t)(fileLen + 1));
			//��ȡ��������
			dwRead = pFile->Read(szBuffer, fileLen);
			//д�뵽�ļ�
			localFile.Write(szBuffer, dwRead);
		}
		localFilePath = localPath;
		GetDlgItem(IDC_DOWNTEXT)->SetWindowTextW(_T("������ɣ�׼����ѹ..."));
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

	bi.lpszTitle = _T("��ѡ��Ҫ���ļ������Ŀ¼��");
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	AfxMessageBox(_T("���ؽ�ѹ���"));
}


void CFTNNHTTPLogHelperDlg::OnEnChangeUrledit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
BOOL CFTNNHTTPLogHelperDlg::unCompressFile(CString *mZipFileFullPath)
{

	ZRESULT zr;
	ZIPENTRY ze;

	CString mUnpackPath = mZipFileFullPath->Left(mZipFileFullPath->GetLength() - 4);
	if (mZipFileFullPath->IsEmpty() || mUnpackPath.IsEmpty())
		return FALSE;
	CFileFind unFile;
	if (!unFile.FindFile(*mZipFileFullPath))//��ȡѹ�����ļ�
	{
		return FALSE;
	}
	CString tZipFilePath = mUnpackPath;
	if (!CFTNNHTTPLogHelperDlg::FolderExist(tZipFilePath))//�����ѹ����·�������ھʹ�����
	{
		CStringW strWZipFilePath(tZipFilePath);
		if (CreatedMultipleDirectory((LPWSTR)(LPCWSTR)strWZipFilePath) == FALSE)
		{
			return FALSE;
		}
	}


	HZIP hz = OpenZip(*mZipFileFullPath, 0);//��ZIP�ļ�
	int nReadFileSize = 0;

	if (hz == 0)
		return FALSE;
	zr = SetUnzipBaseDir(hz, mUnpackPath);
	if (zr != ZR_OK)
	{
		CloseZip(hz);
		return FALSE;
	}
	zr = GetZipItem(hz, -1, &ze);//��ȡzip�ļ�����

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
		//������ڲ��������ļ��� 
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFTNNHTTPLogHelperDlg::OnStnClickedDowntext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



