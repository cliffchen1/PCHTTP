
// FTNNHTTPLogHelperDlg.h : ͷ�ļ�
//

#pragma once


// CFTNNHTTPLogHelperDlg �Ի���
class CFTNNHTTPLogHelperDlg : public CDialogEx
{
// ����
public:
	CFTNNHTTPLogHelperDlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL flag_UnCompress;
	static CString localFilePath;
	static BOOL CreatedMultipleDirectory(wchar_t* direct);
	static BOOL FolderExist(CString& strPath);
	CString GetLocalFilePath();
	static DWORD WINAPI HTTPGetFile(LPVOID lpParameter);
	BOOL unCompressFile(CString *mZipFileFullPath);
	BOOL downFlag;
	
	HANDLE m_ThreadDownload;
// �Ի�������
	enum { IDD = IDD_FTNNHTTPLOGHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedDownload();
	afx_msg LRESULT OnUserLogin(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeUrledit();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaitc();
};
